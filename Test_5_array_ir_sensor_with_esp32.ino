#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// -------- WiFi Hotspot Credentials --------
const char* ssid = "ESP8266-LineSensor";
const char* password = "12345678";

// -------- IR Sensor Pins --------
#define IR1 D1
#define IR2 D2
#define IR3 D5
#define IR4 D6
#define IR5 D7

ESP8266WebServer server(80);

// HTML & CSS stored in Program Memory
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>Line Sensor Monitor</title>
  <style>
    /* Background matches the app feel */
    body { font-family: sans-serif; background-color: #808080; text-align: center; margin: 0; padding: 20px; }
    h1 { color: white; text-shadow: 1px 1px 2px black; }
    
    .sensor-container {
      display: flex;
      justify-content: center;
      gap: 10px;
      margin-top: 50px;
      padding: 20px;
      background: #555;
      border-radius: 10px;
      box-shadow: inset 0 0 10px #000;
    }

    .sensor-box {
      width: 50px;
      height: 80px;
      border-radius: 5px;
      display: flex;
      align-items: center;
      justify-content: center;
      font-weight: bold;
      font-size: 20px;
      border: 3px solid #333;
      transition: background-color 0.1s;
    }

    /* --- THE LOGIC STYLES --- */
    
    .is-white {
      background-color: #ffffff;
      color: #000;
      box-shadow: 0 0 15px rgba(255, 255, 255, 1); /* Glowing White */
    }

    .is-black {
      background-color: #000000;
      color: #fff;
      border-color: #fff;
    }

  </style>
</head>
<body>

  <h1>IR Sensor View</h1>

  <div class="sensor-container">
    <div id="s1" class="sensor-box is-black">1</div>
    <div id="s2" class="sensor-box is-black">2</div>
    <div id="s3" class="sensor-box is-black">3</div>
    <div id="s4" class="sensor-box is-black">4</div>
    <div id="s5" class="sensor-box is-black">5</div>
  </div>

  <p style="color:white; margin-top:20px;">
    Reading from: 192.168.4.1
  </p>

  <script>
    function updateSensors() {
      fetch('/read')
        .then(response => response.json())
        .then(data => {
          for (let i = 1; i <= 5; i++) {
            let el = document.getElementById('s' + i);
            let val = data['s' + i];

            // ----------------------------------------------------
            // LOGIC FLIPPED HERE
            // ----------------------------------------------------
            // Previous code: 1 = Black, 0 = White
            // NEW Code:      0 = Black, 1 = White
            // ----------------------------------------------------
            
            if (val === 0) {
              el.className = "sensor-box is-black"; // Show Black
            } else {
              el.className = "sensor-box is-white"; // Show White
            }
          }
        });
    }

    // Refresh every 100ms
    setInterval(updateSensors, 100);
  </script>
</body>
</html>
)rawliteral";

void handleRoot() {
  server.send(200, "text/html", index_html);
}

void handleRead() {
  // Read digital values from sensors
  int s1 = digitalRead(IR1);
  int s2 = digitalRead(IR2);
  int s3 = digitalRead(IR3);
  int s4 = digitalRead(IR4);
  int s5 = digitalRead(IR5);

  String json = "{";
  json += "\"s1\":" + String(s1) + ",";
  json += "\"s2\":" + String(s2) + ",";
  json += "\"s3\":" + String(s3) + ",";
  json += "\"s4\":" + String(s4) + ",";
  json += "\"s5\":" + String(s5);
  json += "}";

  server.send(200, "application/json", json);
}

void setup() {
  Serial.begin(115200);

  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  pinMode(IR3, INPUT);
  pinMode(IR4, INPUT);
  pinMode(IR5, INPUT);

  WiFi.softAP(ssid, password);
  server.on("/", handleRoot);
  server.on("/read", handleRead);
  server.begin();
}

void loop() {
  server.handleClient();
}
