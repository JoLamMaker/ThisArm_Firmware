//------------------------------------------------------------------------------
// ThisArm  - OpenSource Firmware for MeArm (or robot arm with similar Kinematic)
// Created by lamjonah@yahoo.com 2016-07-18


//------------------------------------------------------------------------------
// Copyright at end of file.
// please see https://github.com/lamjonah/ThisArm_Firmware for more information.


typedef void (*VoidProcedure) ();


void EmptyProc (){
  
}
struct StageContainer {
  char *StageName;
  VoidProcedure InitProc;
  VoidProcedure ControlProc ;
  VoidProcedure DisplayProc;
  VoidProcedure CickProc ;
};

#define NumOfStage 8

StageContainer Stages [NumOfStage];
StageContainer TheOnlyStage;
int CurrentStage=0;

void initStages () {
  TheOnlyStage.StageName="AnalogLogicAngle: ";
  TheOnlyStage.ControlProc = AnalogLogicAngleControl;
  TheOnlyStage.DisplayProc = DisplayJointAngle;

}

void initStages_Multi(){
  CurrentStage=7;
  
  //Init the Stage 0, raw stage
  Stages[0].StageName="RawEncoderStage";
  Stages[0].InitProc= EncoderRawControl_Init;
  Stages[0].ControlProc=EncoderRawControl;
  Stages[0].DisplayProc=DisplayRaw;
  
  //init the Stage1, Encoder AngularControl
  Stages[1].StageName="AnguleEncoderStage";
  Stages[1].InitProc= EncoderAngleControl_Init;
  Stages[1].ControlProc=EncoderAngleControl;
  Stages[1].DisplayProc=DisplayAngle;

  //init the Stage 2, Encoder Logical Angle Control
  Stages[2].StageName="LogicalAnguleEncoderStage";
  Stages[2].InitProc= EncoderLogicAngleControl_Init;
  Stages[2].ControlProc=EncoderLogicAngleControl;
  Stages[2].DisplayProc=DisplayLogicAngle;

  //init the Stage3, Analog Angle Display Only
  Stages[3].StageName="AnalogAnguleDisplayStage";
  Stages[3].InitProc= EmptyProc;
  Stages[3].ControlProc=EmptyProc;
  Stages[3].DisplayProc=DisplayJointAngle;

  //init the Stage4, Analog Angle Control
  Stages[4].StageName="AnalogAnguleControlStage";
  Stages[4].InitProc= EmptyProc;
  Stages[4].ControlProc=AnalogLogicAngleControl;
  Stages[4].DisplayProc=DisplayJointAngle;

  //init the Stage 5, PolarCoordinate Encoder Control
  Stages[5].StageName="PolarEncoderControlStage";
  Stages[5].InitProc= EncoderARHControl_Init;
  Stages[5].ControlProc=EncoderARHControl;
  Stages[5].DisplayProc=DisplayARH;

  //init the Stage 6, PolarCoordinate Encoder Control
  Stages[6].StageName="XYZEncoderControlStage";
  Stages[6].InitProc= EncoderXYZControl_Init;
  Stages[6].ControlProc=EncoderXYZControl;
  Stages[6].DisplayProc=DisplayXYZ;

  //init the Stage 7, PolarCoordinate Encoder Control
  Stages[7].StageName="GCodeXYZControlStage";
  Stages[7].InitProc= Gcodeinit;
  Stages[7].ControlProc=GCodeControl;
  Stages[7].DisplayProc=EmptyProc;
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

