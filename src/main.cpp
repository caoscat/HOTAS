#include <Arduino.h>
#include <BleGamepad.h>

// BLE Gamepad
BleGamepad bleGamepad("ESP32 HOTAS", "MoWa", 100);
void schiebhebel();

// Potentiometer für Gashebel
const int throttlePin = 26; // Mittelpin Schieberegler
int throttleValue = 0;

const int ButtonArray[9] = {12,25,34,39,36,4,5,19,21}; 
// Joystick Pins (falls analog benötigt, sonst nur virtuell)
//const int joy1X = A0; // optional
//const int joy1Y = A1;
//const int joy2X = A2;
//const int joy2Y = A3;

void setup() {
  Serial.begin(9600);
  Serial.println("Starting BLE HOTAS...");

  analogReadResolution(12); 

  pinMode(throttlePin, INPUT);
  pinMode(ButtonArray[0], INPUT_PULLDOWN); 

  for (int i = 1; i < 9; i++) {
    pinMode(ButtonArray[i], INPUT); 
  }
  bleGamepad.begin();

  while (!bleGamepad.isConnected()) {
    Serial.println("Waiting for Bluetooth connection...");
    delay(1000);
  }

  Serial.println("BLE HOTAS connected!");
}

void loop() {
  if (!bleGamepad.isConnected()) {
    delay(1000);
    return;
  }
  for (int i = 0; i < 4; i++) {
    schiebhebel(); // Throttle aktualisieren
    delay(50);
  }
  
  // --- Buttons ---
  if (digitalRead(ButtonArray[0]) == HIGH) { // Button gedrückt (aktiver LOW)
    bleGamepad.press(1); // Button 1 drücken
  } else {
    bleGamepad.release(1); // Button 1 loslassen
  }
  // --- Optional: Joystick 1 X/Y Steuerung ---
  // int16_t joy1_x = map(analogRead(joy1X), 0, 4095, -32767, 32767);
  // int16_t joy1_y = map(analogRead(joy1Y), 0, 4095, -32767, 32767);
  // bleGamepad.setLeftThumb(joy1_x, joy1_y);

  // --- Optional: Joystick 2 X/Y Steuerung ---
  // int16_t joy2_x = map(analogRead(joy2X), 0, 4095, -32767, 32767);
  // int16_t joy2_y = map(analogRead(joy2Y), 0, 4095, -32767, 32767);
  // bleGamepad.setRightThumb(joy2_x, joy2_y);

  // --- Beispiel Button (Taste 1) ---
  // bleGamepad.press(1); 
  // delay(50);
  // bleGamepad.release(1);

  // Ausgabe für Debugging
 
  
}


void schiebhebel() {
  throttleValue = analogRead(throttlePin);          // 0–4095
  throttleValue = constrain(throttleValue, 1930, 4095); // Sicherstellen, dass der Wert im erwarteten Bereich liegt
  int16_t mappedThrottle = map(throttleValue, 0, 4095, -32767, 32767); // Throttle Achse 
  bleGamepad.setSlider1(mappedThrottle);      // Linker Trigger = Gashebel 
  Serial.print("Throttle ADC: "); Serial.print(throttleValue);
  Serial.print(" → Mapped: "); Serial.println(mappedThrottle);
}