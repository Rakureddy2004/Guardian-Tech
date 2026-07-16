🔧 1. Library and Pin Setup

#include <FastLED.h>
Loads the FastLED library for controlling the RGB LED strip.


#define ULTRASONIC_TRIGGER_PIN 15  
#define ULTRASONIC_ECHO_PIN 13  
#define STRIP_LEDS_PIN 22  
#define BUZZER_PIN 26  
These define which ESP32 pins are connected to the ultrasonic sensor, LED strip, and buzzer.


#define NUM_LEDS 7  
#define SOUND_SPEED 0.034  // cm/µs
Defines how many LEDs are in the strip.

Speed of sound used to calculate distance from time.

🌈 2. LED Strip Initialization

CRGB leds[NUM_LEDS];
Creates an array of 7 CRGB objects to control each LED.


#define SAFE_DISTANCE 50
If something is closer than 50 cm, the system considers it a threat.

🚀 3. Setup Function

void setup() {
    Serial.begin(115200);
Starts Serial Monitor for debugging output.


    pinMode(ULTRASONIC_TRIGGER_PIN, OUTPUT);
    pinMode(ULTRASONIC_ECHO_PIN, INPUT);
Set up the ultrasonic sensor pins.


    FastLED.addLeds<WS2812, STRIP_LEDS_PIN, GRB>(leds, NUM_LEDS);
    setLEDColor(CRGB::Green);
Initializes the LED strip and sets the color to green (safe).


    pinMode(BUZZER_PIN, OUTPUT);
    digitalWrite(BUZZER_PIN, LOW);
Prepares the buzzer pin and turns it off initially.


    ledcSetup(0, 2000, 8);
For ESP32, we use ledc PWM channel 0 for the buzzer (2 kHz, 8-bit resolution).

🔁 4. Loop Function
void loop() {
    float distance = getDistance();
Continuously measures the distance from the ultrasonic sensor.


    if (distance == -1) {
        Serial.println("⚠️ No echo received. Skipping...");
        return;
    }
If there's no echo, the sensor didn’t detect anything. We skip further processing.


    if (distance < SAFE_DISTANCE) {
        triggerAlert();  // 🚨 Stranger Too Close
    } else {
        resetAlert();  // ✅ All Clear
    }

    delay(500);  // Prevent flickering or constant triggering
Calls either triggerAlert() or resetAlert() based on how close the object is.

📏 5. getDistance() Function

float getDistance() {
    // Send 10µs pulse to trigger
}
Triggers the ultrasonic sensor to send a sound wave.


    long duration = pulseIn(ULTRASONIC_ECHO_PIN, HIGH, 30000);
Waits for echo. If no echo in 30 ms, return -1 (i.e., no detection).


    float distance = (duration * SOUND_SPEED) / 2.0;
Converts echo time into distance (in cm).

🚨 6. triggerAlert() Function

void triggerAlert() {
    for (int i = 0; i < 3; i++) {
        setLEDColor(CRGB::Red);
        ledcAttachPin(BUZZER_PIN, 0);
        ledcWriteTone(0, 1000);
        delay(300);

        setLEDColor(CRGB::Black);
        ledcWriteTone(0, 0);
        delay(300);
    }
}
Blinks red LEDs 3 times and beeps buzzer at 1000 Hz, turning off in between.

✅ 7. resetAlert() Function

void resetAlert() {
    setLEDColor(CRGB::Green);
    ledcDetachPin(BUZZER_PIN);
}
Sets LEDs back to green and makes sure buzzer is off.

🎨 8. setLEDColor() Function

void setLEDColor(CRGB color) {
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = color;
    }
    FastLED.show();
}
Updates the color of all 7 LEDs in the strip and shows them.

💡 Summary Flow
Step	Action
🟢 No Obstacle	LED is Green, Buzzer off
🔴 Obstacle Close (<50 cm)	LED Blinks Red, Buzzer beeps
⚠️ Sensor Error	Skips measurement to avoid false alert