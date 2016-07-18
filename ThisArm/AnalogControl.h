//------------------------------------------------------------------------------
// ThisArm  - OpenSource Firmware for MeArm (or robot arm with similar Kinematic)
// Created by lamjonah@yahoo.com 2016-07-18


//------------------------------------------------------------------------------
// Copyright at end of file.
// please see https://github.com/lamjonah/ThisArm_Firmware for more information.



#define NumOfJoint 4
#define JointBase 0
#define JointShoulder 1
#define JointElbow  2
#define JointClaw 3

struct AnalogJoint {
  byte pin;
  int raw_1;
  float ang_1;
  int raw_2;
  float ang_2;
  int value;
  float angle;
};

struct AnalogJoint Joints[NumOfJoint];

void initJointsControl (){
  
  //init of base
  Joints[JointBase].pin=A2;
  Joints[JointBase].raw_1=468;
  Joints[JointBase].ang_1=90;
  Joints[JointBase].raw_2=727;
  Joints[JointBase].ang_2=180;
  
  //init of Shoulder
  Joints[JointShoulder].pin=A1;
  Joints[JointShoulder].raw_1=797;
  Joints[JointShoulder].ang_1=0;
  Joints[JointShoulder].raw_2=532;
  Joints[JointShoulder].ang_2=90;
  
  //init of Elbow
  Joints[JointElbow].pin=A0;
  Joints[JointElbow].raw_1=461;
  Joints[JointElbow].ang_1=90;
  Joints[JointElbow].raw_2=744;
  Joints[JointElbow].ang_2=180;

  //init of Claw
  Joints[JointClaw].pin=A3;
  Joints[JointClaw].raw_1=726;
  Joints[JointClaw].ang_1=90;
  Joints[JointClaw].raw_2=560;
  Joints[JointClaw].ang_2=0;

  for (int i=0;i<NumOfJoint;i++){
    pinMode (Joints[i].pin,INPUT_PULLUP);
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

