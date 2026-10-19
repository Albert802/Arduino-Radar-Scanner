# Arduino-Radar-Scanner
Arduino radar scanner: sweeps an HC-SR04 ultrasonic sensor 180° with a servo and streams angle/distance/status over serial for real-time visualization.
# Arduino Radar Scanner

A 180° radar sweep built with an Arduino, an HC-SR04 ultrasonic sensor, and a 
servo motor. The sensor sweeps back and forth, measuring distance at every 
degree and streaming `angle,distance,status` over serial for real-time 
visualization (e.g., in Processing or Python).

## Features
- 180° servo sweep with configurable start/end and step delay
- Distance measurement with 30ms `pulseIn` timeout (no loop freezing)
- Distance clamped to 400 cm; `999` returned when no echo
- Status classification per reading: `CRITICAL`, `WARNING`, `SAFE`, `CLEAR`
- Compact CSV-style serial output: `angle,distance,status`

## Hardware

| Component | Arduino Pin |
|---|---|
| HC-SR04 TRIG | 9 |
| HC-SR04 ECHO | 10 |
| Servo signal | 11 |
| VCC (sensor + servo) | 5V |
| GND | GND |

> **Note:** Power the servo from an external 5V supply if you see jitter or 
> Arduino resets — servos can draw more current than the board can provide.

## Serial Output Format

Each line is:
