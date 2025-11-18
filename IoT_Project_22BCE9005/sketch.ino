/*
  Virtual Smart Plant Monitor (Wokwi Simulation)
  - Reads an LDR (light sensor)
  - Reads a PIR (motion sensor)
  - Sends data to Blynk and the Serial Monitor
*/

// --- 1. BLYNK DEFINITIONS ---
// These MUST come BEFORE you include the Blynk library
#define BLYNK_TEMPLATE_ID "TMPL3lZqChf8Q"
#define BLYNK_TEMPLATE_NAME "Motion Detector"
#define BLYNK_AUTH_TOKEN "2eJi4BnFii3yP5XfjIcBGnBWNEvX6VtA" //2eJi4BnFii3yP5XfjIcBGnBWNEvX6VtA Your real auth token
#define BLYNK_PRINT Serial // Enables Blynk debug prints

// --- 2. LIBRARIES ---
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h> // Now this will see the definitions above

// --- 3. WIFI SETTINGS ---
// Wokwi Simulator WiFi Settings
char ssid[] = "Wokwi-GUEST";
char pass[] = ""; // No password for Wokwi-GUEST

// --- 4. PIN DEFINITIONS ---
#define LDR_PIN 34   // LDR is on pin 34
#define PIR_PIN 27   // PIR is on pin 27

// --- 5. GLOBAL OBJECTS ---
SimpleTimer timer; // Create a timer object

// --- 6. FUNCTION TO SEND DATA ---
// --- 6. FUNCTION TO SEND DATA ---
void sendSensorData()
{
  int lightLevel = analogRead(LDR_PIN);
  int motionDetected = digitalRead(PIR_PIN);

  Serial.print("Light: ");
  Serial.print(lightLevel);
  Serial.print(" | Motion: ");
  Serial.println(motionDetected);

  // Send to your Virtual Pins
  Blynk.virtualWrite(V2, lightLevel);     // Light data to V2
  Blynk.virtualWrite(V3, motionDetected); // Motion data to V3

  // --- THIS IS THE UPDATED PART FOR YOUR LED ---
  if (motionDetected == 1) {
    // Send 255 (max brightness) to the LED widget on V1
    Blynk.virtualWrite(V1, 255); 
  } else {
    // Send 0 (OFF) to the LED widget on V1
    Blynk.virtualWrite(V1, 0);
  }
}

// --- 7. MAIN SETUP ---
void setup() {
  Serial.begin(115200);
  pinMode(PIR_PIN, INPUT);

  // Connect to Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  Serial.println("Connecting to Blynk...");
}

// --- 8. MAIN LOOP ---
void loop() {
  Blynk.run();
  timer.run();
}

// This function runs when Blynk connects
BLYNK_CONNECTED() {
  Serial.println("Blynk Connected!");
  // Set up the timer only AFTER connecting to Blynk
  timer.setInterval(1000L, sendSensorData);
}