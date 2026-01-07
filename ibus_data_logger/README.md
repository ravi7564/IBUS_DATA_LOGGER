# ESP32 RC iBUS Live Monitor 🛰️

A real-time, low-latency web dashboard to monitor RC Receiver channels (iBUS protocol) using ESP32 WebSockets.

## ✨ Features
- **Zero-Lag Monitoring:** Uses WebSockets for real-time data streaming.
- **Wireless Access:** No USB needed, monitor directly on your mobile/PC browser.
- **Auto-Scale UI:** Responsive dashboard with dynamic progress bars.
- **Protocol:** High-speed iBUS (FlySky/Turnigy compatible).

## 🛠️ Hardware Requirements
- ESP32 (32S or similar)
- iBUS compatible RC Receiver (e.g., FlySky iA6B)
- RC Transmitter

## 🔌 Wiring Diagram
| Component | ESP32 Pin |
|-----------|-----------|
| iBUS Signal| GPIO 16 (RX2) |
| VCC       | 5V / VIN  |
| GND       | GND       |

## 🚀 Installation (PlatformIO)
1. Install [PlatformIO](https://platformio.org/).
2. Clone this repo: `git clone https://github.com/yourusername/project-name.git`
3. Connect ESP32 and click **Upload**.
4. Connect to WiFi: `ESP32-RC-Live` and open `192.168.4.1` in your browser.

## 📱 Dashboard Preview

![RC Dashboard Screenshot](assets/dashboard.png)
