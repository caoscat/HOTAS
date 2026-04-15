# HOTAS Project

A PlatformIO project for HOTAS (Hands On Throttle And Stick) hardware control and configuration.

## Description

This project implements firmware for HOTAS control systems, providing interface and communication protocols for flight simulation and gaming applications. Currently only the Throttle is avaliable.

## Features

- HOTAS device management
- Input handling and calibration
- Communication protocol support

## Hardware 
- [ESP32](https://www.adafruit.com/product/5400)
- 10KOhm slide potentiometer
- Buttons or switches 

## Getting Started

1. Install [PlatformIO](https://platformio.org/)
2. Clone or open this project in PlatformIO
3. Build the project: `pio run`
4. Upload to device: `pio run -t upload`

## Project Structure

```
HOTAS/
├── src/          # Source code
├── include/      # Header files
├── lib/          # Libraries
└── platformio.ini # Project configuration
```
## Dependency 

- [ESP32-BLE-Gamepad](https://github.com/lemmingDev/ESP32-BLE-Gamepad)

## License

Use my code in this however you want i don't realy care