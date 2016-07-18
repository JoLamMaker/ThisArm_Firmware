//------------------------------------------------------------------------------
// ThisArm  - OpenSource Firmware for MeArm (or robot arm with similar Kinematic)
// Created by lamjonah@yahoo.com 2016-07-18


//------------------------------------------------------------------------------
// Copyright at end of file.
// please see https://github.com/lamjonah/ThisArm_Firmware for more information.


//Function for Display
void EncoderDisplay() {
  Serial.print (digitalRead(Encoder1_Click));
  Serial.print (" ReleaseCount: ");
  Serial.print (ReleaseTurnCount);
  Serial.print (" PressedCount: ");
  Serial.print (PressTurnCount );
  Serial.print(" Click Count: ");
  Serial.print(ClickCount);
  Serial.print(" DoubleClickCount: ");
  Serial.print(DubleClickCount);
  Serial.println();
}

void DisplayRaw(){
  Serial.print ("Servo: ");
  Serial.print (servoSelected);
  Serial.print ("  RawValue: ");
  Serial.print (AngularServos[servoSelected].value);
  Serial.print (" MappedAngle: ");
  Serial.print (LinearMap_float(AngularServos[servoSelected].raw_1, AngularServos[servoSelected].ang_1,AngularServos[servoSelected].raw_2, AngularServos[servoSelected].ang_2,AngularServos[servoSelected].value));
  Serial.println();
}

void DisplayAngle(){
  Serial.print ("Servo: ");
  Serial.print (servoSelected);
  Serial.print ("  Angle: ");
  Serial.print (AngularServos[servoSelected].Angle);
  Serial.print (" RawValue: ");
  Serial.print (LinearMap_float(AngularServos[servoSelected].ang_1,AngularServos[servoSelected].raw_1,AngularServos[servoSelected].ang_2,AngularServos[servoSelected].raw_2, AngularServos[servoSelected].Angle));
  Serial.println();  
}

void DisplayLogicAngle(){
  Serial.print ("Part: ");
  switch (servoSelected){
    case 0:
      Serial.print(" Base: ");
      Serial.print(BaseAngle);
      break;
    case 1:
      Serial.print(" Shoulder: ");
      Serial.print(Shoulder);
      break;
    case 2:
      Serial.print(" Elbow: ");
      Serial.print(Elbow);
      break;
    case 3:
      Serial.print(" Claw: ");
      Serial.print(Claw);
      break;
  }
  Serial.println();
}


void DisplayJointRaw () {
  Serial.print ( Joints[0].value);
  Serial.print (" ");
  Serial.print ( Joints[1].value);
  Serial.print (" ");
  Serial.print ( Joints[2].value);
  Serial.print (" ");
  Serial.print ( Joints[3].value);
  
  Serial.println ();
}

void DisplayJointAngle () {
  Serial.print ("Base: ");
  Serial.print ( Joints[0].value);
  Serial.print (" ");
  Serial.print ( LinearMap_float(Joints[JointBase].raw_1, Joints[JointBase].ang_1,Joints[JointBase].raw_2, Joints[JointBase].ang_2, Joints[JointBase].value));
  Serial.print (" Shoulder: ");
  Serial.print ( Joints[1].value);
  Serial.print (" ");
  Serial.print ( LinearMap_float(Joints[JointShoulder].raw_1, Joints[JointShoulder].ang_1,Joints[JointShoulder].raw_2, Joints[JointShoulder].ang_2, Joints[JointShoulder].value));
  Serial.print (" Elbow: ");
  Serial.print ( Joints[2].value);
  Serial.print (" ");
  Serial.print ( LinearMap_float(Joints[JointElbow].raw_1, Joints[JointElbow].ang_1,Joints[JointElbow].raw_2, Joints[JointElbow].ang_2, Joints[JointElbow].value));
  Serial.print (" Claw: ");
  Serial.print ( Joints[3].value);
  Serial.print (" ");
  Serial.print ( LinearMap_float(Joints[JointClaw].raw_1, Joints[JointClaw].ang_1,Joints[JointClaw].raw_2, Joints[JointClaw].ang_2, Joints[JointClaw].value));
  Serial.println ();
}

void DisplayARH (){
  double tmp_s;
  double tmp_e;
  int rc;
  rc=InverseKinematicsTransform(R,H,tmp_s,tmp_e);
  Serial.print ("[Selected:");
  switch (servoSelected){
    case 0:
      Serial.print(" A] ");
      break;
    case 1:
      Serial.print(" R] ");
      break;
    case 2:
      Serial.print(" H] ");
      break;
    case 3:
      Serial.print(" Claw] ");
      break;
  }
  Serial.print("Values A: ");
  Serial.print(BaseAngle);
  Serial.print(" Values R: ");
  Serial.print(R);
  Serial.print(" Values H: ");
  Serial.print(H);
  Serial.print (" Shoulder: ");
  Serial.print (Shoulder);
  Serial.print (" Elbow: ");
  Serial.print (Elbow);
  Serial.print(" Values Claw: ");
  Serial.print(Claw);
  Serial.print(" RC: ");
  Serial.print(rc);
  Serial.println();
  
}

void DisplayXYZ (){
  double tmp_R;
  double tmp_H;
  double tmp_A;
  int rc;
  C2P (X,Y,Z, tmp_R,tmp_H,tmp_A);
  
  Serial.print ("[Selected:");
  switch (servoSelected){
    case 0:
      Serial.print(" X] ");
      break;
    case 1:
      Serial.print(" Y] ");
      break;
    case 2:
      Serial.print(" Z] ");
      break;
    case 3:
      Serial.print(" Claw] ");
      break;
  }
  Serial.print("Values X: ");
  Serial.print(X);
  Serial.print(" Values Y: ");
  Serial.print(Y);
  Serial.print(" Values Z: ");
  Serial.print(Z);
  Serial.print(" Values R: ");
  Serial.print(tmp_R);
  Serial.print(" Values H: ");
  Serial.print(tmp_H);
  Serial.print(" Values A: ");
  Serial.print(tmp_A);
  
  Serial.println();
  
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

