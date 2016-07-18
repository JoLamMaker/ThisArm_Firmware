//------------------------------------------------------------------------------
// ThisArm  - OpenSource Firmware for MeArm (or robot arm with similar Kinematic)
// Created by lamjonah@yahoo.com 2016-07-18


//------------------------------------------------------------------------------
// Copyright at end of file.
// please see https://github.com/lamjonah/ThisArm_Firmware for more information.



//Function for initializate stages
void DefaultInit(){
  servoSelected=0;
  
}

void EncoderRawControl_Init(){
  DefaultInit();
  for (int i = 0; i < NumOfServo; i++){
    AngularServos[i].value = 1500;
    AngularServos[i].idle = 0;
    
  }
}

void EncoderAngleControl_Init(){
  DefaultInit();
  for (int i = 0; i < NumOfServo; i++){
    AngularServos[i].Angle = AngularServos[i].INITANGLE;
    AngularServos[i].idle = 0;
    
  }
}

void EncoderLogicAngleControl_Init(){
  DefaultInit();
  //JointControl
  BaseAngle =90;
  Shoulder=90;
  Elbow=90;
  Claw=45;
}

void EncoderARHControl_Init (){
  DefaultInit();
  A=90;
  R=80;
  H=0;
  Claw=45; 
}


void EncoderXYZControl_Init (){
  DefaultInit();
  Claw=45; 
  X=00;
  Y=80;
  Z=0;
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

