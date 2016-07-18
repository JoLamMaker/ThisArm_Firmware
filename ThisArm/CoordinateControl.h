//------------------------------------------------------------------------------
// ThisArm  - OpenSource Firmware for MeArm (or robot arm with similar Kinematic)
// Created by lamjonah@yahoo.com 2016-07-18


//------------------------------------------------------------------------------
// Copyright at end of file.
// please see https://github.com/lamjonah/ThisArm_Firmware for more information.

int InverseKinematicsTransform (double R, double H, double &Shoulder, double &Elbow);

// by the length of arm, Transform r and h to angle input of Shoulder and Elbow joint
double BackArm_mm=80;
double ForeArm_mm=80;
double d_Min=15;
double d_Max=155;

//offset for physical structure
double R_offset_mm=7.5; // length in MM, that the Left and Right servo place outward than rotation centre

//a function to transform R-H to Shoulder-Elbow, in terms of rotation centre
int InverseKinematicsTransform (double R, double H, double &Shoulder, double &Elbow){
  double sqr_d;
  double d;
  double Shoulder_Rad_1;
  double Shoulder_Rad_2;

  sqr_d=R*R+H*H;
  d=sqrt(sqr_d);
  //Serial.println (sqr_d);
  if (d>BackArm_mm+ForeArm_mm||d>d_Max) // trivially out of range
    return 1;
  if (d<=0 || d<d_Min) // not possible for structure of arm
    return 2;
  
  R=R-R_offset_mm;
  Elbow=acos((BackArm_mm*BackArm_mm+ForeArm_mm*ForeArm_mm-sqr_d)/(2*BackArm_mm*ForeArm_mm));

  Shoulder_Rad_1= asin((ForeArm_mm*sin(Elbow))/d);
  Shoulder_Rad_2=atan (H/R);
  
  //Serial.println (Shoulder_Rad_1);
  //Serial.println (Shoulder_Rad_2);
    
  Shoulder=(Shoulder_Rad_1+Shoulder_Rad_2)*180/M_PI;
  Elbow=Elbow*180/M_PI;
 
  return 0;
}


//a function to transform Shoulder-Elbow to R-H
int ForwardKinematicsTransform (double Shoulder, double Elbow, double &R, double &H){
  
}

//Function to transform XYZ(Cartesian ) to RHA (Polar)
int C2P (double x, double y, double z, double &R, double &H, double &A){
  H=z;
  if (y<0) {
    return 1;
  }
  R=sqrt(x*x+y*y);
  if (x==0) {
    A=90;
  }else if (x>0){
    A=atan(y/x)*180/M_PI;
  }else {
    // the case of x<0
    A=180+atan(y/x)*180/M_PI;
  }
  return 0;
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

