#include <Wire.h>
#include "MS5837.h"
#include <Servo.h>
// Check out the documentation here: https://github.com/bluerobotics/BlueRobotics_MS5837_Library
//MS5837 sensor;
// The white wire, SDA, is plugged into pin 20 (Arduino Mega)
// The green wire, SCL, is plugged into pin 21
const int BAUD_RATE = 9600;
const int DENSITY_FRESHWATER  = 997;
const int DENSITY_SALTWATER   = 1029;
const int HALL_EFFECT_CHARM   = 2;
const int HALL_EFFECT_STRANGE = 3;
const byte TERMINATOR[] = {0xFF, 0xFF, 0xFF, 0xFF};
const int TERMINATOR_LENGTH = sizeof(TERMINATOR);
byte message_buffer[8];
int bufferIndex = 0;
unsigned int sp1_0 = 0;
unsigned int sp1_1 = 0;
unsigned int sp2_0 = 0;
unsigned int sp2_1 = 0;
int dropper1Pos = 0;
int dropper2Pos = 0;
Servo dropper1;
Servo dropper2;
bool process = true;
void setup() {
  Serial.begin(BAUD_RATE);
  pinMode(HALL_EFFECT_CHARM,   INPUT_PULLUP);
  pinMode(HALL_EFFECT_STRANGE, INPUT_PULLUP);
  Wire.begin();
  /*while (!sensor.init()) {
    Serial.println("Are SDA/SCL connected correctly?");
    Serial.println("Blue Robotics Bar30: White=SDA, Green=SCL");
    Serial.println("\n\n\n");
    delay(5000);
  }
  sensor.setModel(MS5837::MS5837_30BA);
  sensor.setFluidDensity(DENSITY_FRESHWATER);*/
}
void loop() {
  // put your main code here, to run repeatedly:
  int charm_reading   = 1;//digitalRead(HALL_EFFECT_CHARM);
  int strange_reading = 0;//digitalRead(HALL_EFFECT_STRANGE);
  //sensor.read();
  float depth = 1.3;//sensor.depth();
  float *f_ptr = &depth;
  long *l_ptr = reinterpret_cast<long*>(f_ptr);
  long depthLong = *l_ptr;
  Serial.write(0xFF);
  Serial.write(0xFF);
  Serial.write(0xFF);
  Serial.write(0xFF);
  Serial.write(strange_reading); // Charm and Strange are at beginning and end to prevent header check from looking at depth
  Serial.write(depthLong & 0xFF);
  Serial.write((depthLong >>  8) & 0xFF);
  Serial.write((depthLong >>  16) & 0xFF);
  Serial.write((depthLong >>  24) & 0xFF);
  Serial.write(charm_reading);
  //BEGIN READING CODE FOR SERVOS
  /*if(Serial.available(8)) {
    Serial.readBytes(message_buffer, 8);
    bool TerminatorFound = true;
    for (int i = 0; i < TERMINATOR_LENGTH; i++) { //Checking for alignment
      if (message_buffer[i] != TERMINATOR[i]) {
        TerminatorFound = false;
      }
    }
    if (TerminatorFound == false) { //Shift Serial if not aligned
      Serial.read();
      bool process = false;
    }
    if (process) {
      unsigned int sp1_0 = message_buffer[4];
      unsigned int sp1_1 = message_buffer[5];
      unsigned int sp2_0 = message_buffer[6];
      unsigned int sp2_1 = message_buffer[7];
      dropper1Pos = sp1_0 + (sp1_1 << 8) & 0xFF00;
      dropper2Pos = sp2_0 + (sp2_1 << 8) & 0xFF00;
      dropper1.write(dropper1Pos);
      dropper2.write(dropper2Pos);
    }
    process = true;
  }*/
  delay(1000);
}