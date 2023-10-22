#include "PPMEncoder.h"

#define OUTPUT_PIN 9 //10

uint32_t sim_counter = 0;


void setup() {

  ppmEncoder.begin(OUTPUT_PIN, 6, false);
  ppmEncoder.setChannel(0, 1100);
  ppmEncoder.setChannel(1, 1500);
  ppmEncoder.setChannel(2, 1800);
//  ppmEncoder.setChannel(3, 1100);
//  ppmEncoder.setChannel(4, 1500);
//  ppmEncoder.setChannel(5, 1800);
//  ppmEncoder.setChannel(6, 1500);
//  ppmEncoder.setChannel(7, 1500);
}

void loop() {
  
  ppmEncoder.setChannel(0, 1000 + sim_counter);
  ppmEncoder.setChannel(2, 2000 - sim_counter);
  if (sim_counter <= 500){
    sim_counter++;
  }
  else sim_counter = 0;
  
  // // Min value
  // ppmEncoder.setChannel(0, 500);
  // ppmEncoder.setChannel(0, PPMEncoder::MIN);
  // ppmEncoder.setChannelPercent(0, 0);

  // // Max value
  // ppmEncoder.setChannel(0, 2500);
  // ppmEncoder.setChannel(0, PPMEncoder::MAX);
  // ppmEncoder.setChannelPercent(0, 100);
  delay(20);
}
