# HOTAS Project

A PlatformIO project for HOTAS (Hands On Throttle And Stick) hardware control and configuration.

## Description

This project implements firmware for HOTAS control systems, providing interface and communication protocols for flight simulation and gaming applications. Currently only the Throttle is avaliable.

## Features

- HOTAS device management
- Input handling and calibration
- Communication protocol support

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

## License

See LICENSE file for details.
