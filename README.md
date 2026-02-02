🚗📡 ESP8266 5-Channel IR Line Tracker Web Monitor

A real-time web dashboard for monitoring a 5-Channel Infrared Line Tracking Sensor using an ESP8266 (NodeMCU / Wemos).

This project transforms the ESP8266 into a standalone Wi-Fi hotspot and hosts a sleek dashboard that instantly shows each sensor’s state (White vs Black line).
Perfect for debugging and calibrating line-follower robots—no Serial Monitor required 😎⚡

📸 Screenshots
🤍 White Background Mode :
<p align="center">
  <img src="https://github.com/user-attachments/assets/aa8f57cb-bd63-46d7-9c74-0c31ced28864" width="45%">
  <img src="https://github.com/user-attachments/assets/2c64ed81-b24a-417e-bd57-b31976a7438e" width="45%">
</p>






🖤 Dark Background Mode


<p align="center">
  <img src="https://github.com/user-attachments/assets/033b44f9-9467-4290-81d1-f98c8d893d28" width="500">
  <img src="https://github.com/user-attachments/assets/35d8e3db-1a35-457c-a7c5-464bb982aebe" width="500">
</p>

⚡ Features

✨ Real-Time Visualization — Five live indicators update instantly
📡 Wi-Fi Hotspot Mode — No router needed
🔄 Auto-Updating Dashboard — AJAX / Fetch powered refresh
🌙 Modern Dark UI — Works beautifully on mobile & desktop
🧠 Inverted Logic Support — Adapt easily to different sensor outputs
🛠 Debug-Friendly — Ideal for calibration and testing

🧰 Hardware Required

📟 ESP8266 Board (NodeMCU, Wemos D1 Mini, etc.)
👀 5-Channel IR Tracker Module (TCRT5000-based or similar)
🔌 Jumper Wires
🔋 Power Source (USB or Battery Pack)

🔌 Pin Connections

Wire the IR module to the ESP8266 exactly as shown below 👇

Sensor Pin	ESP8266 Pin	Description
VCC	3.3V	Power ⚠️ (Do NOT use 5V / Vin)
GND	GND	Common Ground
IR1	D1 (GPIO 5)	Sensor 1
IR2	D2 (GPIO 4)	Sensor 2
IR3	D5 (GPIO 14)	Sensor 3 (Center)
IR4	D6 (GPIO 12)	Sensor 4
IR5	D7 (GPIO 13)	Sensor 5
photo of connections: <img width="732" height="458" alt="image" src="https://github.com/user-attachments/assets/42fc0cdb-2266-4666-9ec5-3811b89d6d06" />


⚠️ Important: Pins D3 and D4 are avoided because they affect boot mode on ESP8266 boards.

🚀 Installation & Usage
1️⃣ Clone the Repository
git clone https://github.com/YOUR_USERNAME/esp8266-ir-tracker-monitor.git

2️⃣ Open in Arduino IDE

Open the .ino file

Install ESP8266 Board Manager from Boards Manager

3️⃣ Upload the Code

Select your board (NodeMCU 1.0 / Wemos D1 Mini)

Choose the correct COM Port

Click Upload ⬆️

4️⃣ Connect to ESP Wi-Fi

📶 Network: ESP8266-LineSensor
🔐 Password: 12345678

5️⃣ Open the Dashboard

🌐 Open your browser and visit:

http://192.168.4.1


You’ll see live sensor values immediately ⚡👀

⚙️ Configuration (Logic Inversion)

If your sensors behave opposite (Black appears as White), modify this JavaScript logic:

// Change this logic if colors are reversed
if (val === 0) {
    el.className = "sensor-box is-black";
} else {
    el.className = "sensor-box is-white";
}
