#include <DFRobot_URM09.h>
#include <DFRobot_DF1201S.h>
#include <SoftwareSerial.h>

/* Create a URM09 object to communicate with IIC. */
DFRobot_URM09 URM09_01;
DFRobot_URM09 URM09_02;
DFRobot_URM09 URM09_03;
DFRobot_URM09 URM09_04;

SoftwareSerial DF1201SSerial(D2, D3);

DFRobot_DF1201S DF1201S;

int offset = 0;

void setup() {
  Serial.begin(115200);
  DF1201SSerial.begin(115200);
  while(!DF1201S.begin(DF1201SSerial)){
    Serial.println("Init failed, please check the wire connection!");
    delay(1000);
  }

  DF1201S.setVol(/*VOL = */20);
  DF1201S.switchFunction(DF1201S.MUSIC);
  /*Wait for the end of the prompt tone */
  delay(2000);
  /*Set playback mode to "single"*/
  DF1201S.setPlayMode(DF1201S.SINGLE);

  /**
   * I2c device number 1-127
   * When the i2c device number is not passed, the default parameter is 0x11
   */
  while(!URM09_01.begin(0x11)){
    Serial.println("I2c device 11 number error");
    delay(1000);
  }
  while(!URM09_02.begin(0x12)){
    Serial.println("I2c device 12 number error");
    delay(1000);
  }
  while(!URM09_03.begin(0x13)){
    Serial.println("I2c device 13 number error");
    delay(1000);
  }
  while(!URM09_04.begin(0x14)){
    Serial.println("I2c device 14 number error");
    delay(1000);
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
  URM09_01.setModeRange(MEASURE_MODE_AUTOMATIC ,MEASURE_RANG_500);
  delay(100);
  URM09_02.setModeRange(MEASURE_MODE_AUTOMATIC ,MEASURE_RANG_500);
  delay(100);
  URM09_03.setModeRange(MEASURE_MODE_AUTOMATIC ,MEASURE_RANG_500);
  delay(100);
  URM09_04.setModeRange(MEASURE_MODE_AUTOMATIC ,MEASURE_RANG_500);
  delay(100);
}

void loop() {

  offset = 0;
  if(digitalRead(D4) == LOW) {
    offset = 4;
  }

  int should_play = -1;
  int16_t dist = URM09_01.getDistance();                // Read distance
  float temp = URM09_01.getTemperature();               // Read temperature
  Serial.print("01: ");
  Serial.print(dist, DEC); Serial.print(" cm------");
  Serial.print(temp, 1); Serial.println(" C");
  if(dist < 10) {
    should_play = offset + 1;
  }
  //delay(100);
  dist = URM09_02.getDistance();                // Read distance
  temp = URM09_02.getTemperature();               // Read temperature
  Serial.print("02: ");
  Serial.print(dist, DEC); Serial.print(" cm------");
  Serial.print(temp, 1); Serial.println(" C");
  if(dist < 10) {
    should_play = offset + 2;
  }
  //delay(100);
  dist = URM09_03.getDistance();                // Read distance
  temp = URM09_03.getTemperature();               // Read temperature
  Serial.print("03: ");
  Serial.print(dist, DEC); Serial.print(" cm------");
  Serial.print(temp, 1); Serial.println(" C");
  if(dist < 10) {
    should_play = offset + 3;
  }
  //delay(100);
  dist = URM09_04.getDistance();                // Read distance
  temp = URM09_04.getTemperature();               // Read temperature
  Serial.print("04: ");
  Serial.print(dist, DEC); Serial.print(" cm------");
  Serial.print(temp, 1); Serial.println(" C");
  if(dist < 10) {
    should_play = offset + 4;
  }

  if(should_play > 0) {
    DF1201S.pause();
    DF1201S.playFileNum(should_play);
    delay(500);
  }

  delay(10);
}