#include <Wire.h>
#include "config.h"
#include "variables.h"

//Macros
#define LEFTDISTANCE getDistance(LEFT)
#define FRONTDISTANCE getDistance(MIDDLE)
#define RIGHTDISTANCE getDistance(RIGHT)



//Overclock digital and analog I/O
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

int buzzPin           = 13;

int COUNT = 0;

void setup() {
  pinMode(LMF, OUTPUT);
  pinMode(LMR, OUTPUT);
  pinMode(RMF, OUTPUT);
  pinMode(RMR, OUTPUT);

  pinMode(buzzPin, OUTPUT);

  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  pinMode(LCLICK, INPUT_PULLUP);
  pinMode(RCLICK, INPUT_PULLUP);


  // Setting frequency-scaling to 100%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, HIGH);


  Serial.begin(115200);

#ifdef DEBUG
  while (1) {
    IMUloop();
    String msg = "";
    msg += LEFTDISTANCE;
    msg += ",";
    msg += FRONTDISTANCE;
    msg += ",";
    msg += RIGHTDISTANCE;
    msg += ",";
    msg += digitalRead(LCLICK);
    msg += ",";
    msg += digitalRead(RCLICK);
    msg += ",";
    msg += accY;
    msg += ",";
    msg += detectAngle();
    Serial.println(msg);
    delay(50);
  }
#endif

  //wait for front ultrasonic to stabilize.
  for (int i = 0; i < 5; i++) {
    int x = FRONTDISTANCE;
    delay(50);
  }

  //Wait for starting signal
  while (1) {
    digitalWrite(buzzPin, HIGH);
    delay(50);
    digitalWrite(buzzPin, LOW);
    delay(10);
    Serial.println("waiting.....");
    if (FRONTDISTANCE < 10)
      break;
  }

  delay(200);
  beginMotion(); //Initialize IMU MPU-6050 module
  delay(200);
  CalibrateMPU6050_gryo(50); //Calibrate Gyroscope
  delay(200);
  CalibrateMPU6050_Acc(50); //Calibrate accelerometer
  delay(200);

  curDistance = FRONTDISTANCE;
  previousMillis = millis();
}

void loop() {
  //for delay based TILERUN only
  unsigned long currentMillis = millis();

  moveStraightAligned();

  bumpAlign();

  //sense colour during normal run ( only for detecting hazard area )
  senseColour(true);

  //condition to complete a single TILERUN
  //for delay based TILERUN only
  if ((currentMillis - previousMillis >= TILERUN)) {

    if (detectAngle()) {
      moveMotor(0, 0);
      delay(100);
      while (1) {
        moveStraightAligned();
        IMUloop();
        if (abs(accY) < RAMPAMGLE) {
          break;
        }
      }
      delay(200);
      moveMotor(-80, -80);
      delay(10);
      moveMotor(0, 0);
    } else {
      moveMotor(-80, -80);
      delay(10);
      moveMotor(0, 0);
      if (FRONTDISTANCE < 100 and FRONTDISTANCE > 5) {
        //correction algorithm
        correctTilePlacement();
      }
    }


    //Stop the motors before checking the cases
    moveMotor(0, 0);
    delay(500);


    //algorithm to be used (set in config.h)
    SOLVE();

    //blink an LED at the end of every tilerun.
    indicateEndOfTileRun();

    //sense colours except black/hazard
    senseColour(false);

    //for delay based TILERUN only
    previousMillis = millis();

  } //end of tile
} //end of main loop
