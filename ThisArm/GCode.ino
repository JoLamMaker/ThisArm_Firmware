//------------------------------------------------------------------------------
// ThisArm  - OpenSource Firmware for MeArm (or robot arm with similar Kinematic)
// Created by lamjonah@yahoo.com 2016-07-18


//------------------------------------------------------------------------------
// Copyright at end of file.
// please see https://github.com/lamjonah/ThisArm_Firmware for more information.


int debugMode=0;

void GcodeDebug (char input[]){
  if (debugMode==1){
    Serial.print(input);
  }
}
void GcodeDebugln (char input[]){
  if (debugMode==1){
    Serial.println(input);
  }
}

void GcodeDebugln (double input){
  if (debugMode==1){
    Serial.println(input);
  }
}

void GcodeDebug (double input){
  if (debugMode==1){
    Serial.print(input);
  }
}

/**
 * write a string followed by a float to the serial line.  Convenient for debugging.
 * @input code the string.
 * @input val the float.
 */
void output(char *code,float val) {
  Serial.print(code);
  Serial.print(val);
  Serial.print(" ");
}


/**
 * print the current position, feedrate, and absolute mode.
 */
void where() {
  output("X",X);
  output("Y",Y);
  output("Z",Z);
  output("C",AngularServos[ServoClaw].Angle);
  output("F",FeedRate);
  Serial.println(mode_abs?"ABS":"REL");
} 

/**
 * Look for character /code/ in the buffer and read the float that immediately follows it.
 * @return the value found.  If nothing is found, /val/ is returned.
 * @input code the character to look for.
 * @input val the return value if /code/ is not found.
 **/
float parsenumber(char code,float val) {
  char *ptr=buffer;
  while(ptr && *ptr && ptr<buffer+sofar) {
    if(*ptr==code) {
      return atof(ptr+1);
    }
    ptr=strchr(ptr,' ')+1;
  }
  return val;
} 

void pause(long ms) {
  Serial.println(ms);
  delay(ms);
  
}

/**
 * display helpful information
 */
void help() {
  Serial.print(F("GcodeServoRobotArm "));
  Serial.println(F("Commands:"));
  Serial.println(F("G00 [X/Y/Z/E(mm)] ; - Instance move"));
  Serial.println(F("G01 [X/Y/Z/E(mm)] [F(mm/s)]; - linear move"));
  Serial.println(F("G04 P[seconds]; - delay"));
  Serial.println(F("G90; - absolute mode"));
  Serial.println(F("G91; - relative mode"));
  
  
  Serial.println(F("M100; - this help message"));
  Serial.println(F("M106 [S(Claw angle)]; - set angle of Claw"));
  Serial.println(F("M114; - report position and feedrate"));
  Serial.println(F("All commands must end with a newline."));
}

int setpoint (double NewX, double NewY, double NewZ){
    double NewR, NewH, NewA;
    double NewShoulder, NewElbow;
    double NewLeft, NewRight;
    int rc=0;
    
    rc=C2P (NewX, NewY, NewZ, NewR, NewH, NewA);
//    GcodeDebug("NewX: ");
//    GcodeDebugln (NewX);
//    
//    GcodeDebug("NewY: ");
//    GcodeDebugln (NewY);
//
//    GcodeDebug("NewZ: ");
//    GcodeDebugln (NewZ);
//    GcodeDebugln("");
//    GcodeDebug("NerR: ");
//    GcodeDebugln (NewR);
//    GcodeDebug("NewH: ");
//    GcodeDebugln (NewH);
//    GcodeDebug("NewA: ");
//    GcodeDebugln (NewA);
//    GcodeDebug ("FirstRC: ");
//    GcodeDebugln (rc);
    
    if (rc!=0)  return rc;
    
    rc=InverseKinematicsTransform (NewR,NewH,NewShoulder,NewElbow);
//    GcodeDebug ("SecondRC: ");
//    GcodeDebugln (rc);
    if (rc!=0)  return rc;

//     GcodeDebug("NewShoulder: ");
//    GcodeDebugln (NewShoulder);
//     GcodeDebug("NewElbow: ");
//    GcodeDebugln (NewElbow);
//        
    ASet(AngularServos[ServoBase] , NewA);
    ASet(AngularServos[ServoRight], NewShoulder);
    ASet(AngularServos[ServoLeft], NewElbow+NewShoulder);
    
    X=NewX;
    Y=NewY;
    Z=NewZ;
    return 0;
}

int LinearSetpoint (double NewX, double NewY, double NewZ, double MMpM){ // feed rate in MM per Minute
  int num_of_Loop;
  int msPerLoop=10;// around 100 Hz
  int i=0;
  double deltaX, deltaY, deltaZ;
  double Distance;
  int Startmillis;
  deltaX=NewX-X;
  deltaY=NewY-Y;
  deltaZ=NewZ-Z;

  Distance=sqrt(deltaX*deltaX+deltaY*deltaY+deltaZ*deltaZ);
  num_of_Loop=Distance/MMpM*60*1000/msPerLoop;
  
  //Serial.print ("num_of_Loop:");
  //Serial.println (num_of_Loop);
  
  for (i=1; i<=num_of_Loop;i++){
    Startmillis=millis();
    setpoint(X+deltaX/num_of_Loop, Y+deltaY/num_of_Loop, Z+deltaZ/num_of_Loop);
    while (millis()-Startmillis<msPerLoop){ };
  }
  setpoint(NewX, NewY, NewZ);
}

/**
 * Read the input buffer and find any recognized commands.  One G or M command per line.
 */
 /**
  * This function is a modified version of GcodeCNCDemo
  * http://www.github.com/MarginallyClever/GcodeCNCDemo
  * 
  */
void processCommand() {
  double NewX, NewY, NewZ;
  
  int rc=0;
  int cmd = parsenumber('G',-1);
  switch(cmd) {
  case  0:{
    if (mode_abs==1){
      NewX=parsenumber('X',X);
      NewY=parsenumber('Y',Y);
      NewZ=parsenumber('Z',Z);
    }else {
      NewX=X+parsenumber('X',0);
      NewY=Y+parsenumber('Y',0);
      NewZ=Z+parsenumber('Z',0);
    }
    
    rc=setpoint(NewX, NewY, NewZ);
    where();
    break;
  }
  case  1: { // line
    if (mode_abs==1){
      NewX=parsenumber('X',X);
      NewY=parsenumber('Y',Y);
      NewZ=parsenumber('Z',Z);
    }else {
      NewX=X+parsenumber('X',0);
      NewY=Y+parsenumber('Y',0);
      NewZ=Z+parsenumber('Z',0);
    }
    FeedRate=parsenumber('F',FeedRate);
    
    rc=LinearSetpoint(NewX, NewY, NewZ,FeedRate);
    where();
    break;
  }
  
  case  4:  pause(parsenumber('P',0)*1000);  break;  // dwell
  case 90:  mode_abs=1;  break;  // absolute mode
  case 91:  mode_abs=0;  break;  // relative mode
  
  default:  break;
  }

  cmd = parsenumber('M',-1);
  switch(cmd) {
  case 100:  help();  break;
  case 106: {
    //Serial.print(parsenumber('S',90)); 
    ASet(AngularServos[ServoClaw], parsenumber('S',AngularServos[ServoClaw].Angle));
    break; // set Claw 
  }
  case 114:  where();  break;
  default:  break;
  }
}


/**
 * prepares the input buffer to receive a new message and tells the serial connected device it is ready for more.
 */
void ready() {
  sofar=0;  // clear input buffer
  Serial.println(F("ok"));  // signal ready to receive input
  Serial.print(F(">"));  // signal ready to receive input
  
}


//Function to integrate into the Stage framework
void Gcodeinit(){
  Serial.println("Gcode Control initializated");
  
  setpoint(00,20,00);
  LinearSetpoint(00,20,00,1000);
  where();
  ready();
}

void GCodeControl(){
  // listen for serial commands
  while(Serial.available() > 0) {  // if something is available
    char c=Serial.read();  // get it
    Serial.print(c);  // repeat it back so I know you got the message
    if(sofar<MAX_BUF-1) buffer[sofar++]=c;  // store it
    if(c=='\n') {
      // entire message received
      buffer[sofar]=0;  // end the buffer so string functions work right
      
      //Serial.print ("sofar Size: ");
      //Serial.println (sofar);
      
      Serial.print(F("\r\n"));  // echo a return character for humans
      processCommand();  // do something with the command
      ready();
    }
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

