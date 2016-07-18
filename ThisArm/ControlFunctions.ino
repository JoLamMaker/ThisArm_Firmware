//------------------------------------------------------------------------------
// ThisArm  - OpenSource Firmware for MeArm (or robot arm with similar Kinematic)
// Created by lamjonah@yahoo.com 2016-07-18


//------------------------------------------------------------------------------
// Copyright at end of file.
// please see https://github.com/lamjonah/ThisArm_Firmware for more information.



//Function for Control
void EncoderRawControl (){
  AngularServos[servoSelected].value=AngularServos[servoSelected].value+ReleaseTurnCount+PressTurnCount *4;
  PressTurnCount=0;
  ReleaseTurnCount =0;
  
  //Acturate servo output
  for (int i = 0; i < NumOfServo; i++){
    if (AngularServos[i].value<=AngularServos[i].MIN)
      AngularServos[i].value=AngularServos[i].MIN;
    if (AngularServos[i].value>=AngularServos[i].MAX)
      AngularServos[i].value=AngularServos[i].MAX;
    AngularServos[i].ServoObj.write(AngularServos[i].value);
  }
}

void EncoderAngleControl (){
  //Assign values to Angle from Encoder
  AngularServos[servoSelected].Angle=AngularServos[servoSelected].Angle+ReleaseTurnCount/2+PressTurnCount;
  PressTurnCount=0;
  ReleaseTurnCount =0;
  
  //Acturate servo output
  for (int i = 0; i < NumOfServo; i++){
    //Calculate the raw value by mapping function
    ASet(AngularServos[i], AngularServos[i].Angle);
  }
}

void EncoderLogicAngleControl(){
  //Acquire input from Encoder
  switch (servoSelected){
    case 0:
      BaseAngle=BaseAngle+ReleaseTurnCount/2+PressTurnCount;
      PressTurnCount=0;
      ReleaseTurnCount =0;
      break;
    case 1:
      Shoulder=Shoulder+ReleaseTurnCount/2+PressTurnCount;
      PressTurnCount=0;
      ReleaseTurnCount =0;
      break;
    case 2:
      Elbow=Elbow+ReleaseTurnCount/2+PressTurnCount;
      PressTurnCount=0;
      ReleaseTurnCount =0;
      break;
    case 3:
      Claw=Claw+ReleaseTurnCount/2+PressTurnCount;
      PressTurnCount=0;
      ReleaseTurnCount =0;
      break;
  }
  
  //Calculate angle for each servo
  AngularServos[ServoBase].Angle=BaseAngle;
  AngularServos[ServoRight].Angle=Shoulder;
  AngularServos[ServoLeft].Angle=Elbow+AngularServos[ServoRight].Angle;
  AngularServos[ServoClaw].Angle=Claw;
  
  //Acturate servo output
  for (int i = 0; i < NumOfServo; i++){
    //Calculate the raw value by mapping function
    ASet(AngularServos[i], AngularServos[i].Angle);
  }
}


void AnalogLogicAngleControl(){
//  //Acquire input from Encoder
// Claw=Claw+Encoder1.read()/2;
// Encoder1.write(0);

  //Acquire input from Analog 
  BaseAngle=Joints[JointBase].angle;
  Shoulder=Joints[JointShoulder].angle;
  Elbow=Joints[JointElbow].angle;
  Claw=Joints[JointClaw].angle;
  
  //Calculate angle for each servo
  AngularServos[ServoBase].Angle=BaseAngle;
  AngularServos[ServoRight].Angle=Shoulder;
  AngularServos[ServoLeft].Angle=Elbow+AngularServos[ServoRight].Angle;
  AngularServos[ServoClaw].Angle=Claw;
  
  
  //Acturate servo output
  for (int i = 0; i < NumOfServo; i++){
    //Calculate the raw value by mapping function
    ASet(AngularServos[i], AngularServos[i].Angle);
  }
}


void EncoderARHControl(){
  //Acquire input from Encoder
  switch (servoSelected){
    case 0:
      BaseAngle=BaseAngle+ReleaseTurnCount/2+PressTurnCount;
      PressTurnCount=0;
      ReleaseTurnCount =0;
      break;
    case 1:
      R=R+ReleaseTurnCount/2+PressTurnCount;
      PressTurnCount=0;
      ReleaseTurnCount =0;
      break;
    case 2:
      H=H+ReleaseTurnCount/2+PressTurnCount;
      PressTurnCount=0;
      ReleaseTurnCount =0;
      break;
    case 3:
      Claw=Claw+ReleaseTurnCount/2+PressTurnCount;
      PressTurnCount=0;
      ReleaseTurnCount =0;
      break;
  }

  InverseKinematicsTransform ( R, H, Shoulder, Elbow);

  //Calculate angle for each servo
  AngularServos[ServoBase].Angle=BaseAngle;
  AngularServos[ServoRight].Angle=Shoulder;
  AngularServos[ServoLeft].Angle=Elbow+AngularServos[ServoRight].Angle;
  AngularServos[ServoClaw].Angle=Claw;
  
  //Acturate servo output
  for (int i = 0; i < NumOfServo; i++){
    //Calculate the raw value by mapping function
    ASet(AngularServos[i], AngularServos[i].Angle);
  }
  
}



void EncoderXYZControl(){
  //Acquire input from Encoder
  switch (servoSelected){
    case 0:
      X=X+ReleaseTurnCount/2+PressTurnCount;
      PressTurnCount=0;
      ReleaseTurnCount =0;
      break;
    case 1:
      Y=Y+ReleaseTurnCount/2+PressTurnCount;
      PressTurnCount=0;
      ReleaseTurnCount =0;
      break;
    case 2:
      Z=Z+ReleaseTurnCount/2+PressTurnCount;
      PressTurnCount=0;
      ReleaseTurnCount =0;
      break;
    case 3:
      Claw=Claw+ReleaseTurnCount/2+PressTurnCount;
      PressTurnCount=0;
      ReleaseTurnCount =0;
      break;
  }

  C2P(X,Y,Z,R,H,A);
  
  InverseKinematicsTransform ( R, H, Shoulder, Elbow);
  BaseAngle=A;

  //Calculate angle for each servo
  AngularServos[ServoBase].Angle=BaseAngle;
  AngularServos[ServoRight].Angle=Shoulder;
  AngularServos[ServoLeft].Angle=Elbow+AngularServos[ServoRight].Angle;
  AngularServos[ServoClaw].Angle=Claw;
  
  //Acturate servo output
  for (int i = 0; i < NumOfServo; i++){
    //Calculate the raw value by mapping function
    ASet(AngularServos[i], AngularServos[i].Angle);
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

