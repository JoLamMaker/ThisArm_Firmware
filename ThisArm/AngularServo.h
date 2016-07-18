//------------------------------------------------------------------------------
// ThisArm  - OpenSource Firmware for MeArm (or robot arm with similar Kinematic)
// Created by lamjonah@yahoo.com 2016-07-18


//------------------------------------------------------------------------------
// Copyright at end of file.
// please see https://github.com/lamjonah/ThisArm_Firmware for more information.



struct AngularServo {
  byte PIN;
  int value;
  int idle;
  int raw_1;
  int ang_1;
  int raw_2;
  int ang_2;
  float Angle;
  int MIN;
  int MAX;
  int INITANGLE;
  Servo ServoObj;  
};

//servo control setup
#define NumOfServo 4
#define ServoBase 0
#define ServoLeft 1
#define ServoRight 2
#define ServoClaw 3

AngularServo AngularServos [NumOfServo];
//Servo myservo[NumOfServo];

int ACheck(AngularServo AServo, float angle, int &rawVale){
  rawVale=LinearMap_float(AServo.ang_1,AServo.raw_1,AServo.ang_2,AServo.raw_2, angle);

  if (rawVale >= AServo.MAX) return 1;
  if (rawVale <= AServo.MIN) return -1;
  return 0;
}


int ASet(AngularServo AServo, float angle){
  int tempValue=0;
  int rc;
  rc=ACheck(AServo, angle,tempValue);
 
  switch (rc) {
    case 1:
      AServo.value=AServo.MAX;
      AServo.Angle=LinearMap_float(AServo.raw_1, AServo.ang_1,AServo.raw_2, AServo.ang_2,AServo.MAX);
      //Serial.print ("O");
      break;
    case -1:
      AServo.value=AServo.MIN;
      AServo.Angle=LinearMap_float(AServo.raw_1, AServo.ang_1,AServo.raw_2, AServo.ang_2,AServo.MIN);
      //Serial.print ("U");
      break;
    default:
      AServo.value=tempValue;
      AServo.Angle=angle;
  }
  AServo.ServoObj.write (AServo.value);
  return rc;
  
}

void AngularServoInit(){// extreme value: 654~2400
  //Base Servo
  AngularServos[ServoBase].PIN = 10;
  AngularServos[ServoBase].MIN = 654;
  AngularServos[ServoBase].MAX = 2400;
  AngularServos[ServoBase].raw_1=1499;
  AngularServos[ServoBase].ang_1=90; //This should bring the arm face forward
  AngularServos[ServoBase].raw_2=2382;
  AngularServos[ServoBase].ang_2=180; // This should bring the arm face the left hand side
  AngularServos[ServoBase].INITANGLE = 90;
  //Left Servo
  AngularServos[ServoLeft].PIN = 9;
  AngularServos[ServoLeft].MIN = 841; 
  AngularServos[ServoLeft].MAX = 2248;
  AngularServos[ServoLeft].raw_1=1887;
  AngularServos[ServoLeft].ang_1=180;// This should bring the lever parallel with the ground
  AngularServos[ServoLeft].raw_2=865;
  AngularServos[ServoLeft].ang_2=90; // This should bring the lever vertical to the ground
  AngularServos[ServoLeft].INITANGLE = 180; 
  //Right Servo
  AngularServos[ServoRight].PIN = 6;
  AngularServos[ServoRight].MIN = 600;
  AngularServos[ServoRight].MAX = 2412;
  AngularServos[ServoRight].raw_1=2319;
  AngularServos[ServoRight].ang_1=0; // This should bring the lever parallel with the ground
  AngularServos[ServoRight].raw_2=1292;
  AngularServos[ServoRight].ang_2=90; // This should bring the lever vertical to the ground
  AngularServos[ServoRight].INITANGLE = 90;
  //Claw Servo
  AngularServos[ServoClaw].PIN = 5;
  AngularServos[ServoClaw].MIN = 800;
  AngularServos[ServoClaw].MAX = 2400;
  AngularServos[ServoClaw].raw_1=2400;
  AngularServos[ServoClaw].ang_1=0; // This is the angle where the claw completely close
  AngularServos[ServoClaw].raw_2=1126;
  AngularServos[ServoClaw].ang_2=90; // This is the angle where the two claws are 90 degree with the centre line (180 degree with each other)
  AngularServos[ServoClaw].INITANGLE = 45;
  
  for (int i = 0; i < NumOfServo; i++){
    AngularServos[i].ServoObj.attach(AngularServos[i].PIN);
    AngularServos[i].ServoObj.write(AngularServos[i].INITANGLE);
    AngularServos[i].value=1500; // supposed to be middle
    AngularServos[i].Angle = AngularServos[i].INITANGLE;
    AngularServos[i].idle = 0;
    
  }
}
  


/**
* This file is part of ThisArm.
*
* ThisArm is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* ThisArm is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with Foobar. If not, see <http://www.gnu.org/licenses/>.
*/

