#include <Wire.h>
#include "MS5837.h"

// Check out the documentation here: https://github.com/bluerobotics/BlueRobotics_MS5837_Library
// The white wire, SDA, is plugged into pin 20 (Arduino Mega)
// The green wire, SCL, is plugged into pin 21
MS5837 depth_sensor;

/* Time Constants */
// Since reading from the sensor takes up to 40ms,
// make sure this is at least 40.
constexpr unsigned long MEASUREMENT_DELAY_MS = 50;

/* Fluid Density */
// Units are in kg/m^3
const int BAUD_RATE = 9600;
const int DENSITY_FRESHWATER  = 997;

/* Hall Effect Digital Pins */
const int HALL_EFFECT_CHARM   = 2;
const int HALL_EFFECT_STRANGE = 3;

void setup() {
  Serial.begin(BAUD_RATE);
  pinMode(HALL_EFFECT_CHARM,   INPUT_PULLUP);
  pinMode(HALL_EFFECT_STRANGE, INPUT_PULLUP);

  //Wait for Depth Sensor to initialize
  Wire.begin();
  while (!depth_sensor.init()) {
    Serial.println("Are SDA/SCL connected correctly?");
    Serial.println("Blue Robotics Bar30: White=SDA, Green=SCL");
    Serial.println("\n\n\n");
    delay(5000);
  }

  depth_sensor.setModel(MS5837::MS5837_30BA);
  depth_sensor.setFluidDensity(DENSITY_FRESHWATER);
}

void loop() {
  //Read sensor inputs
  int charm_reading   = digitalRead(HALL_EFFECT_CHARM);
  int strange_reading = digitalRead(HALL_EFFECT_STRANGE);
  depth_sensor.read();
  float depth = depth_sensor.depth();

  //Recasting depth data to a long because floats can't be bit shifted
  float *f_ptr = &depth;
  long *l_ptr = reinterpret_cast<long*>(f_ptr);
  long depthLong = *l_ptr;

  //Write to serial a message header that the Jetson uses to confirm the start of a message
  Serial.write(0xFF);
  Serial.write(0xFF);
  Serial.write(0xFF);
  Serial.write(0xFF);

  //Begin writing data to serial one byte at a time
  Serial.write(strange_reading); // Charm and Strange are at beginning and end to prevent header check on Jetson from looking at depth
  Serial.write(depthLong & 0xFF);
  Serial.write((depthLong >>  8) & 0xFF);
  Serial.write((depthLong >>  16) & 0xFF);
  Serial.write((depthLong >>  24) & 0xFF);
  Serial.write(charm_reading);

  delay(MEASUREMENT_DELAY_MS);
}