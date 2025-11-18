# Fog-Enabled Smart Security System

[![Platform](https://img.shields.io/badge/Platform-ESP32-brightgreen.svg)](https://www.espressif.com/en/products/socs/esp32)
[![Simulation](https://img.shields.io/badge/Simulation-Wokwi-blue.svg)](https://wokwi.com/)
[![Dashboard](https://img.shields.io/badge/Dashboard-Blynk-cyan.svg)](https://blynk.io/)

A real-time, low-latency intrusion detection system using Fog/Edge computing principles on an ESP32. This project avoids the latency and reliability issues of cloud-only systems by processing sensor data locally.

## The Problem with Cloud-Only IoT Security

Traditional smart security systems rely on sending all sensor data to the cloud for processing. This approach has critical flaws:

* **High Latency:** The round-trip (Sensor -> Cloud -> User Alert) can take several seconds, which is too long for a security event.
* **Poor Reliability:** If your internet connection fails, the entire security system is blind.
* **Bandwidth Waste:** Constantly streaming data 24/7 (even "no motion detected") wastes bandwidth and energy.

## Our Solution: Fog Computing at the Edge

This system moves the "intelligence" to the edge (the "Fog"), right where the sensors are.

1.  **The Fog Node (ESP32):** The ESP32 processes data from the PIR and LDR sensors *instantly*. It makes decisions locally, in milliseconds.
2.  **The Cloud (Blynk):** The cloud is only used for what it's best at: receiving *critical alerts* (e.g., "Intrusion Detected!") and displaying the system status on a global dashboard.

This hybrid model gives you the best of both worlds: the instant response of a local system and the global accessibility of a cloud app.

## Key Features

* **Low-Latency Alerts:** Local processing provides near-instantaneous alerts (~5-10ms) vs. seconds for cloud-only systems.
* **High Efficiency:** Reduces network traffic by over 99% by only sending critical alerts, not constant data streams.
* **Sensor Fusion:** Combines a PIR (motion) and LDR (light) sensor. An alert is only triggered if motion is detected *and* it's dark, reducing false positives.
* **Offline Functionality:** The core security logic works even if the internet is down.
* **Global Dashboard:** Uses the Blynk platform to send mobile notifications and display real-time sensor status from anywhere.

## Hardware & Software

### Hardware
* ESP32 Microcontroller
* HC-SR501 PIR Motion Sensor
* LDR (Light Dependent Resistor)
* 10kΩ Resistor
* Breadboard and Jumper Wires

### Software
* [Wokwi](https://wokwi.com/) (for simulation)
* [Blynk](https://blynk.io/) (for mobile dashboard and notifications)
* Arduino IDE or PlatformIO

## How to Use

1.  **Clone this Repository:**
    ```bash
    git clone [https://github.com/YOUR_USERNAME/YOUR_REPO_NAME.git](https://github.com/YOUR_USERNAME/YOUR_REPO_NAME.git)
    ```

2.  **Set up Hardware:**
    * Wire the components according to the circuit diagram (see `diagram.json` or the project report).
    * **PIR Sensor:** `VCC` -> `3V3`, `GND` -> `GND`, `OUT` -> `GPIO 27`
    * **LDR Sensor:** `VCC` -> `3V3`, `GND` -> `GND`, `AO` (with 10k pulldown) -> `GPIO 34`

3.  **Configure Software:**
    * Open `sketch.ino` in the Arduino IDE.
    * Install the ESP32 board definitions and the `BlynkSimpleEsp32` library.
    * Set up a new project in the Blynk app to get your **Auth Token**.
    * Update the `sketch.ino` file with your credentials:
        ```cpp
        #define BLYNK_AUTH_TOKEN "YOUR_BLYNK_TOKEN"
        char ssid[] = "YOUR_WIFI_SSID";
        char pass[] = "YOUR_WIFI_PASSWORD";
        ```

4.  **Deploy:**
    * Connect your ESP32 to your computer.
    * Select the correct board and port in the Arduino IDE.
    * Click **Upload**.
    * Open the Serial Monitor to watch it connect, and use the Blynk app to monitor the system.

## Project Files

* `/sketch.ino`: The main Arduino code for the ESP32.
* `/diagram.json`: The circuit diagram for the Wokwi simulator.
* `/project_report.pdf`: The full academic report for this project.
* `/README.md`: This file.

## Future Work

* Integrate a camera (like an ESP32-CAM) for local image verification.
* Implement a TinyML model to distinguish between a person and a pet.
* Add a deep-sleep mode to optimize for battery power.
