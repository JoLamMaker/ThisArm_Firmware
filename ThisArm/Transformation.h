//------------------------------------------------------------------------------
// ThisArm  - OpenSource Firmware for MeArm (or robot arm with similar Kinematic)
// Created by lamjonah@yahoo.com 2016-07-18


//------------------------------------------------------------------------------
// Copyright at end of file.
// please see https://github.com/lamjonah/ThisArm_Firmware for more information.



long int LinearMap_int (long int Input_1,long int Output_1,long int Input_2,long int Output_2,long int Input){
  int output;
  output=(Input-Input_1)*(Output_2-Output_1)/(Input_2-Input_1)+Output_1;
  
  return output;
}

float LinearMap_float (float Input_1,float Output_1,float Input_2,float Output_2,float Input){
  float output;
  output=(Input-Input_1)*(Output_2-Output_1)/(Input_2-Input_1)+Output_1;
  
  return output;
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

