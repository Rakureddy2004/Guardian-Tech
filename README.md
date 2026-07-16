# GuardianTech – Smart Wearable Safety Solution

## Overview

GuardianTech is an ESP32-based wearable safety system designed to provide automatic obstacle and threat alerts.

It uses an ultrasonic sensor to detect nearby objects and alerts the user through:

- 🔴 WS2812 RGB LED Strip
- 🔊 Buzzer Alarm
- 💡 Silent wearable notification

No internet connection or mobile application is required.

---

## Features

- Automatic obstacle detection
- Real-time LED warning
- Buzzer alert
- Offline operation
- Low-cost hardware
- ESP32 based

---

## Hardware Used

- ESP32
- HC-SR04 Ultrasonic Sensor
- WS2812 LED Strip
- Buzzer
- Jumper Wires
- Power Supply

---

## Software

- Arduino IDE
- FastLED Library

---

## Pin Connections

| Component | GPIO |
|-----------|------|
| Trigger | GPIO 4 |
| Echo | GPIO 2 |
| LED Strip | GPIO 21 |
| Buzzer | GPIO 19 |

---

## Working

1. Sensor measures distance.
2. If an object is detected within 50 cm:
   - LED turns Red
   - Buzzer sounds
3. Otherwise:
   - LED remains Green
   - Buzzer stays OFF

---

## Future Improvements

- GPS Tracking
- GSM Emergency SMS
- AI Threat Detection
- Mobile Application
- Smart Bracelet Synchronization

---

## Author

Rakshitha Reddy
