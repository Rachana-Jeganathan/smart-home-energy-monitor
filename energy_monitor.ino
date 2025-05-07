#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <BlynkSimpleEsp8266.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define BLYNK_AUTH_TOKEN "YOUR_BLYNK_AUTH_TOKEN" // Replace with your Blynk token
char ssid[] = "YOUR_WIFI_SSID"; // Replace with Wi-Fi SSID
char pass[] = "YOUR_WIFI_PASSWORD"; // Replace with Wi-Fi password

const int currentPin = A0;
const float voltage = 220.0; // Adjust for your region (e.g., 110V for US)
const float sensitivity = 0.185; // ACS712 5A sensitivity (V/A)
const float threshold = 100.0; // Power threshold in watts

void setup() {
  Serial.begin(9600);
  
  // Initialize OLED
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("OLED init failed"));
    for(;;);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  
  // Initialize Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {
  Blynk.run();
  
  // Read current
  int rawValue = analogRead(currentPin);
  float voltageADC = (rawValue / 1023.0) * 5.0;
  float current = (voltageADC - 2.5) / sensitivity; // ACS712 zero point is 2.5V
  float power = current * voltage;
  
  // Display on OLED
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Current: ");
  display.print(current, 2);
  display.println(" A");
  display.print("Power: ");
  display.print(power, 2);
  display.println(" W");
  if (power > threshold) {
    display.println("High Consumption!");
  }
  display.display();
  
  // Send to Blynk
  Blynk.virtualWrite(V0, current);
  Blynk.virtualWrite(V1, power);
  if (power > threshold) {
    Blynk.notify("Warning: High power consumption!");
  }
  
  delay(1000); // Update every second
}