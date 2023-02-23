#include <DFRobot_URM09.h>
#include <BLEMIDI_Transport.h>
#include <hardware/BLEMIDI_ESP32.h>

BLEMIDI_CREATE_INSTANCE("AWESOME_INSTRUMENT", MIDI)

int offset = 0;
int distance = 10;

DFRobot_URM09 sensor[4];
bool sensor_hit[4] = {false, false, false, false};
int8_t note[8] = {36, 38, 45, 55, 35, 40, 47, 37};

void setup() {
  Serial.begin(115200);
  MIDI.begin();
  /**
   * I2c device number 1-127
   * When the i2c device number is not passed, the default parameter is 0x11
   */
  for (int i = 0; i < 4; i++) {
    while (!sensor[i].begin(17 + i)) {
      Serial.println("I2c device 11 number error");
      delay(1000);
    }
  }
  /**
   * The module is configured in automatic mode or passive
   *  MEASURE_MODE_AUTOMATIC       automatic mode
   *  MEASURE_MODE_PASSIVE         passive mode
   * The measurement distance is set to 500,300,150 
   *  MEASURE_RANG_500             Ranging from 500 
   *  MEASURE_RANG_300             Ranging from 300 
   *  MEASURE_RANG_150             Ranging from 150 
  */
  for (int i = 0; i < 4; i++) {
    sensor[i].setModeRange(MEASURE_MODE_AUTOMATIC, MEASURE_RANG_500);
    delay(100);
  }
}

void loop() {

  offset = 0;
  if (digitalRead(D4) == LOW) {
    offset = 4;
  }

  for (int i = 0; i < 4; i++) {
    int16_t measurements[3];
    for (int j = 0; j < 3; j++) {
      measurements[j] = sensor[i].getDistance();
      delay(5);
    }
    float dist = (measurements[0] + measurements[1] + measurements[2]) / 3.0;
    if (dist < distance) {
      if(sensor_hit[i] == false) {
        sensor_hit[i] = true;
        MIDI.sendNoteOn(note[i + offset], 127, 4);
      }
    } else {
      sensor_hit[i] = false;
    }
  }
}