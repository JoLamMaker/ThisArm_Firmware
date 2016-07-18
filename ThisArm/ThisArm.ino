//------------------------------------------------------------------------------
// ThisArm  - OpenSource Firmware for MeArm (or robot arm with similar Kinematic)
// Created by lamjonah@yahoo.com 2016-07-18


//------------------------------------------------------------------------------
// Copyright at end of file.
// please see https://github.com/lamjonah/ThisArm_Firmware for more information.



#include <Encoder.h>
#include <Servo.h>
#include <math.h>
#include "Transformation.h"
#include "AngularServo.h"
#include "AnalogControl.h"
#include "ControlFunctions.h"
#include "DisplayFunctions.h"
#include "GCode.h"
#include "InitFunctions.h"
#include "StageContainer.h"
#include "CoordinateControl.h"


//For Debugging 
void DisplayRaw();
void EmptyProc();

//encoder definition
#define Encoder1_A 12
#define Encoder1_B 13
#define Encoder1_Click 11

byte Drag_Flag=0;//flag indicate whether a Drag action occured
long ReleaseTurnCount =0;
long PressTurnCount =0;
long ClickCount=0;
long DubleClickCount=0;
byte prevClick=0;
byte currClick=0;
unsigned long PrevClick_milliSec=0;
unsigned long ThisClick_milliSec=0;
unsigned int DoubleClick_Threshold_millisec=300; // detect as "Double Click " if two click within 300 ms

Encoder Encoder1 (Encoder1_A,Encoder1_B);

//Control Loop set-up
#define MainLoopPeriod_MicroSecond 2500 //2.5 milli second
#define Loop200Hz_overflowVal 5000/MainLoopPeriod_MicroSecond
#define Loop100Hz_overflowVal 10000/MainLoopPeriod_MicroSecond
#define Loop25Hz_overflowVal 40000/MainLoopPeriod_MicroSecond

unsigned int counter_25Hz=0;
unsigned int counter_100Hz=0;
unsigned int counter_200Hz=0;
unsigned long timer=0;   //general purpuse timer
unsigned long timer_old;
unsigned long executionTime = 8;
unsigned long executionTimeStart = 0;
unsigned long G_Dt=2500;    // Integration time (DCM algorithm)

//ControlCounter
unsigned int servoSelected=0;
unsigned int analogJointSelected=0;

//JointControl, angle in Degree
double BaseAngle =90;
double Shoulder=90;
double Elbow=90;
double Claw=45;

//Invert Kinetic control, in polar coordinate R, H and A
double R;
double H;
double A;

//Cartesian control, in XYZ coordinate
double X=00;
double Y=80;
double Z=0;

void setup() {
  // put your setup code here, to run once:
  //setting up encoder pins
  Serial.begin(115200);

  //Encoder Push Button
  pinMode(Encoder1_Click,INPUT_PULLUP) ;

  //Servo Init
  AngularServoInit();

  //Potentialmeter Joint init
  initJointsControl();  

  //Stage init
  initStages_Multi();
  Stages[CurrentStage].InitProc();
}

void loop() {
  // put your main code here, to run repeatedly:
  executionTimeStart = micros();
  if((micros()-timer)>=MainLoopPeriod_MicroSecond)  // Main loop runs at 400Hz
  {
    //looping Infrastructure
    counter_25Hz++;
    counter_100Hz++;
    counter_200Hz++;
    timer_old = timer;
    timer=micros();
    
    if (timer>timer_old)
      G_Dt = timer-timer_old;    // Real time of loop run. We use this on the DCM algorithm (gyro integration time)
    else
      G_Dt = 0; 
      
    //Main Control logic loop
    //auto control logic / G-code interpertater/ path planning should be here......

    prevClick=currClick;
    currClick=digitalRead(Encoder1_Click);
    
    if (currClick ==1){ //when released
      ReleaseTurnCount += Encoder1.read();
      Encoder1.write(0);
    } else { // when pressed down
      if (Encoder1.read() != 0){
        PressTurnCount  += Encoder1.read();
        Encoder1.write(0);
        Drag_Flag=1;
      }
    }
    
    if (currClick!=prevClick){
      if (prevClick==0 and currClick==1)// Do when the button was Released
      {
        PrevClick_milliSec=ThisClick_milliSec;
        ThisClick_milliSec=millis();
        if (ThisClick_milliSec-PrevClick_milliSec<DoubleClick_Threshold_millisec && ThisClick_milliSec >20){// detect double click situation
          DoubleClick_Routine();
        }

        //for single click situation
        if (Drag_Flag ==0){
          Click_Routine();
        } else {
          Drag_Flag=0;
        }
      }
    }


    //User Input Loop at 200 Hz (2 Loop runs)
    if (counter_200Hz > Loop200Hz_overflowVal){
      counter_200Hz=0;
      //do something here.....
      //Acquire Click parameter, released=1, pressed down=0

      //Acquire Potentialmeter reading
      Joints[analogJointSelected].value=analogRead(Joints[analogJointSelected].pin);
      Joints[analogJointSelected].angle=LinearMap_int(Joints[analogJointSelected].raw_1, Joints[analogJointSelected].ang_1,Joints[analogJointSelected].raw_2, Joints[analogJointSelected].ang_2, Joints[analogJointSelected].value);
      analogJointSelected++;
      if (analogJointSelected>=NumOfJoint)
        analogJointSelected=0;
    }
    
    //Output Loop at 100 Hz (4 loop runs)
    //update output to servo
    
    if (counter_100Hz > Loop100Hz_overflowVal)
    {
      counter_100Hz=0;
      //do something here.....

      ////RawControl (Encoder directly change the raw value)
      //EncoderRawControl ();
          
      ////Angle Control (Encoder control the Angular value of each servo)
      //EncoderAngleControl();

      //LogicalAngleControl (Encoder control the logical angle value rather than value of each servo)
      //EncoderLogicAngleControl();

      //AnalogLogicAngleControl();
      
      Stages[CurrentStage].ControlProc();
    }
    
    //Display Loop
    if (counter_25Hz > Loop25Hz_overflowVal)  // Print data at 25Hz... (16 loop runs)
    {
      counter_25Hz=0;
      //EncoderDisplay();
      //DisplayRaw();
      //DisplayAngle();
      //DisplayLogicAngle();
      //DisplayJointRaw();
      //DisplayJointAngle();
      if ( Stages[CurrentStage].DisplayProc!=EmptyProc){
        Serial.print (Stages[CurrentStage].StageName);
        Serial.print (": ");
      }
      Stages[CurrentStage].DisplayProc();
      
    }

    executionTime=micros() - executionTimeStart;
  }
  else {
    if (micros()-timer<=0){
      //Handle the case of marcos() function overflow
      timer=0;
    }
  }
  
  
  
}
//End of Loop Function

//Routine for click and double click
void Click_Routine(){
    ClickCount++;
    SwitchSelection();
    

}                                                                                                                                                                                                                                                                                                                                                                                                                    
void DoubleClick_Routine(){
  Serial.println ("Double Click detected");
  DubleClickCount++;
  CurrentStage++;
  CurrentStage%=NumOfStage;
  Stages[CurrentStage].InitProc();
  servoSelected=0;
}

//Function for ButtonClick
void SwitchSelection(){
  servoSelected++;     
  servoSelected=servoSelected%NumOfServo;  
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

