# mrobosub_arduino
An Arduino sketch project for Michigan Robotic Submarine. 

## Current Modules
- [Arduino.ino](main/Arduino.ino) - For sending hall effect and depth data to Jetson

## Pins Used
- Depth Sensor - [Arduino.ino](main/Arduino.ino) - SDA, SCL
- Hall Effect Sensors Charm and Strange - [Arduino.ino](main/Arduino.ino) - Digital 2 (Charm), Digital 3 (Strange)

## Tools Used
- arduino-ide, for general libraries and IDE - https://www.arduino.cc/en/software/
- BlueRobotics MS5837 Library, for getting readings from the Bar30 Depth Sensor - https://github.com/bluerobotics/BlueRobotics_MS5837_Library

## Authors
- Colten Germundson (colteng@umich.edu)