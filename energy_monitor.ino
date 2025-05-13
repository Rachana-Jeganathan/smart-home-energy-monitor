<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Smart Home Energy Monitor</title>
  <style>
    /* Dashboard container */
    .dashboard {
      display: flex;
      flex-wrap: wrap;
      gap: 1rem;
      padding: 1rem;
      max-width: 1200px;
      margin: 0 auto;
    }

    /* Widget card */
    .energy-card {
      background: #ffffff;
      border-radius: 8px;
      box-shadow: 0 4px 6px rgba(0, 0, 0, 0.1);
      padding: 1.5rem;
      flex: 1 1 300px;
      transition: transform 0.2s;
    }
    .energy-card:hover {
      transform: translateY(-5px);
    }

    /* Chart styling */
    .chart {
      width: 100%;
      height: 200px;
      background: #f0f4f8;
      border-radius: 4px;
    }

    /* Responsive design */
    @media (max-width: 768px) {
      .energy-card {
        flex: 1 1 100%;
        padding: 1rem;
      }
      h2 {
        font-size: 1.25rem;
      }
    }

    /* Button styling */
    .btn {
      background: #2563eb;
      color: white;
      padding: 0.5rem 1rem;
      border-radius: 4px;
      text-decoration: none;
      transition: background 0.3s;
    }
    .btn:hover {
      background: #1e40af;
    }

    /* Accessibility */
    :focus {
      outline: 2px solid #2563eb;
      outline-offset: 2px;
    }
  </style>
</head>
<body>
  <div class="dashboard">
    <div class="energy-card">
      <h2>Current</h2>
      <p id="current">0.00 A</p>
    </div>
    <div class="energy-card">
      <h2>Power</h2>
      <p id="power">0.00 W</p>
    </div>
    <div class="energy-card">
      <h2>Status</h2>
      <p id="alert">Normal</p>
    </div>
    <div class="energy-card">
      <h2>Power Trend</h2>
      <div class="chart" id="chart"></div>
    </div>
  </div>

  <script>
    // Mock Blynk data fetch (replace with actual Blynk API call)
    async function fetchEnergyData() {
      // Simulate data from Blynk (V0: current, V1: power)
      const mockData = {
        current: (Math.random() * 5).toFixed(2), // Random current (0-5A)
        power: (Math.random() * 1000).toFixed(2), // Random power (0-1000W)
        threshold: 100 // From Arduino code
      };
      return mockData;
    }

    // Update dashboard
    async function updateDashboard() {
      const data = await fetchEnergyData();
      document.getElementById('current').textContent = `${data.current} A`;
      document.getElementById('power').textContent = `${data.power} W`;
      document.getElementById('alert').textContent = data.power > data.threshold ? 'High Consumption!' : 'Normal';
      // Placeholder for chart update (e.g., using Chart.js)
      console.log('Chart update with power:', data.power);
    }

    // Update every second
    setInterval(updateDashboard, 1000);

    // Initial update
    updateDashboard();
  </script>

  <!-- Arduino Code Reference (runs on ESP8266, not executed in browser) -->
  <!--
    #include <Wire.h>
    #include <Adafruit_GFX.h>
    #include <Adafruit_SSD1306.h>
    #include <BlynkSimpleEsp8266.h>

    #define SCREEN_WIDTH 128
    #define SCREEN_HEIGHT 64
    Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

    #define BLYNK_AUTH_TOKEN "YOUR_BLYNK_AUTH_TOKEN"
    char ssid[] = "YOUR_WIFI_SSID";
    char pass[] = "YOUR_WIFI_PASSWORD";

    const int currentPin = A0;
    const float voltage = 220.0;
    const float sensitivity = 0.185;
    const float threshold = 100.0;

    void setup() {
      Serial.begin(9600);
      if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println(F("OLED init failed"));
        for(;;);
      }
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(SSD1306_WHITE);
      Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
    }

    void loop() {
      Blynk.run();
      int rawValue = analogRead(currentPin);
      float voltageADC = (rawValue / 1023.0) * 5.0;
      float current = (voltageADC - 2.5) / sensitivity;
      float power = current * voltage;
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
      Blynk.virtualWrite(V0, current);
      Blynk.virtualWrite(V1, power);
      if (power > threshold) {
        Blynk.notify("Warning: High power consumption!");
      }
      delay(1000);
    }
  -->
</body>
</html>
