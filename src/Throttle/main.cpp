#include <Arduino.h>
#include <BleGamepad.h>

// BLE Gamepad konfigurieren: Name, Hersteller,
BleGamepad bleGamepad("ESP32 HOTAS", "MoWa", 100);
void schiebhebel();

// Potentiometer für Gashebel
const int throttlePin = 26; // Mittelpin Schieberegler 
const int NonePulldownPin = 12;
int throttleValue = 0;

// Button Pins
const int ButtonArray[8] = {25, 34, 39, 36, 4, 5, 19, 21};

void setup()
{
  // Serielle Ausgabe für Debugging
  Serial.begin(9600);
  Serial.println("Starting BLE HOTAS...");

  // ADC Auflösung auf 12 Bit setzen (0–4095)
  analogReadResolution(12);

  // Pins konfigurieren
  pinMode(NonePulldownPin, INPUT_PULLDOWN); 
  pinMode(throttlePin, INPUT);
  for (int i = 0; i < 8; i++)
  {
    pinMode(ButtonArray[i], INPUT);
  }
  // BLE Gamepad starten
  bleGamepad.begin();

  // Warten auf Bluetooth-Verbindung
  while (!bleGamepad.isConnected())
  {
    Serial.println("Waiting for Bluetooth connection...");
    delay(1000);
  }
  // Serielle Ausgabe für Debugging
  Serial.println("BLE HOTAS connected!");
}

void loop()
{
  // Nur weiter machen, wenn eine Bluetooth-Verbindung besteht
  if (!bleGamepad.isConnected())
  {
    delay(1000);
    return;
  }
  // Throttle schneller als die Buttons aktualisieren, um eine flüssige Steuerung zu gewährleisten
  for (int i = 0; i < 4; i++)
  {
    schiebhebel(); // Throttle aktualisieren
    delay(50);
  }

  // --- Buttons ---
  for (int i = 0; i < 8; i++)
  { // Buttons 2–9
    if (digitalRead(ButtonArray[i]) == HIGH)
    {                          
      bleGamepad.press(i + 1); // Button i+1 drücken
    }
    else
    {
      bleGamepad.release(i + 1); // Button i+1 loslassen
    }
  }
}

void schiebhebel()
{
  throttleValue = analogRead(throttlePin);                             // 0–4095
  throttleValue = constrain(throttleValue, 1930, 4095);                // Sicherstellen, dass der Wert im erwarteten Bereich liegt
  int16_t mappedThrottle = map(throttleValue, 0, 4095, -32767, 32767); // Throttle Achse
  bleGamepad.setSlider1(mappedThrottle);                               // Linker Trigger = Gashebel
  Serial.print("Throttle ADC: ");
  Serial.print(throttleValue);                                         // Serielle Ausgabe für Debugging
  Serial.print(" → Mapped: ");
  Serial.println(mappedThrottle);                                      // Serielle Ausgabe für Debugging
}