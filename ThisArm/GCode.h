//------------------------------------------------------------------------------
// ThisArm  - OpenSource Firmware for MeArm (or robot arm with similar Kinematic)
// Created by lamjonah@yahoo.com 2016-07-18


//------------------------------------------------------------------------------
// Copyright at end of file.
// please see https://github.com/lamjonah/ThisArm_Firmware for more information.


#define MAX_BUF              (32)  // What is the longest message Arduino can store?
#define MAX_FEEDRATE         (1000000) //millimeters per minute
#define MIN_FEEDRATE         (1)      //millimeters per minute
#define NUM_AXIES            (4)

//------------------------------------------------------------------------------
// STRUCTS
//------------------------------------------------------------------------------
typedef struct {
  long delta;  // number of steps to move
  long absdelta;
  long over;  // for dx/dy bresenham calculations
} Axis;

//------------------------------------------------------------------------------
// GLOBALS
//------------------------------------------------------------------------------
Axis atemp;  // for line()

char buffer[MAX_BUF];  // where we store the message until we get a ';'
int sofar;  // how much is in the buffer

// settings
char mode_abs=1;  // absolute mode, default yes
double FeedRate=1000;

long line_number=0;

void GCodeControl ();
void Gcodeinit ();

void where();

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

