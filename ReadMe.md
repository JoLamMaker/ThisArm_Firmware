

# More documented in my BLOG: [http://lamjonah.no-ip.info/wp\_tech/?cat=20](http://lamjonah.no-ip.info/wp_tech/?cat=20)

## Introduction of &quot;ThisArm&quot; Firmware

I put this hobby project open-source with a view to change the close source nature of Robot Arm firmware. More detail on calibration steps was included in the document &quot;MainDocumentWithCalibrationSteps.docx&quot;

This Firmware aim to provide a higher level of automation and user interaction with hobby level robot arm. This firmware is compatible with Robot Arm that replicate kinematic of ABB IRB460.  Existing example in the market/open source world include:

- MeArm
- EEZYbotArm
- EEZYbotArm MK2
- And a lot more in E-bay, Taobao¡K¡K

Feature in this version include:

- Utilize the calibration data, convert human-understanding angle to RC-servo signal
- Invert kinematic to calculate desirable angle of Left, Right Servo from shoulder and elbow angle
- Interaction with robot arm with Mechanical Encoder with push button.
- Control of Robot arm by 4 potentialmeter
- G-code interpreter
  - Able to automate motion of arm by any G-code senders in the internet:
    - [https://chrome.google.com/webstore/detail/gcode-sender/ngncibnakmabjlfpadjagnbdjbhoelom](https://chrome.google.com/webstore/detail/gcode-sender/ngncibnakmabjlfpadjagnbdjbhoelom)
    - [https://github.com/MarginallyClever/GcodeSender](https://github.com/MarginallyClever/GcodeSender)

## Hardware Requirement of this Firmware

- Computer with Arduino IDE 1.6.9 (or higher version) set-up
- Arduino UNO (or any higher grade model like Arduino Mega Uno)
  - This is the brain
- Encoder with Push button
  - This is a great human computer interaction interface
  - This would make your life much more easier during calibration
- RC-servo based Robot arm share the same kinematic of ABB IRB460

## Optional Hardware

- Arduino Sensor shield V5 (save you a lot of time when wiring the servo motors and others)
- Female Dupont Cable (save you from soldering)
- Linear Potentialmeter (4 of them, each for one dimension)
  - Beware **do not** use logarithmic potentiometer

## Default pin assignment

You can change the pin assignment as you want after you understand the code. The following is the default pin assignment:

| Pin | Function of pin | Defined location |
| --- | --- | --- |
| 10 | Base servo (a.k.a. middle servo) | Procedure &quot;AngularServoInit()&quot; in &quot;AngularServo.h&quot; |
| 9 | Left servo   | Procedure &quot;AngularServoInit()&quot; in &quot;AngularServo.h&quot; |
| 6 | Right servo | Procedure &quot;AngularServoInit()&quot; in &quot;AngularServo.h&quot; |
| 5 | Claw servo | Procedure &quot;AngularServoInit()&quot; in &quot;AngularServo.h&quot; |
| 12 | Encoder Channel A (Encoder1\_A) | &quot;ThisArm.ino&quot; |
| 13 | Encoder Channel B (Encoder1\_B) | &quot;ThisArm.ino&quot; |
| 11 | Encoder Push button (Encoder1\_Click) | &quot;ThisArm.ino&quot; |
| A2 | Potentiometer for Base | Procedure &quot;initJointsControl()&quot; of &quot;AnalogControl.h&quot; |
| A1 | Potentiometer for Shoulder | Procedure &quot;initJointsControl()&quot; of &quot;AnalogControl.h&quot; |
| A0 | Potentiometer for Elbow | Procedure &quot;initJointsControl()&quot; of &quot;AnalogControl.h&quot; |
| A3 | Potentiometer for Claw | Procedure &quot;initJointsControl()&quot; of &quot;AnalogControl.h&quot; |

## Source Code Files Explained

This part aim to deliver a brief view on structure and usage of different files. Skip this part if you just want to set the arm up without more understanding.

| File Name | Function |
| --- | --- |
| AnalogControl.h | Contain Structure that convert  potential meter input to corresponding angle |
| AngularServo.h | Contain Logic that convert input angle to Servo signal |
| ControlFunctions.h | Header for ControlFunctions.ino |
| ControlFunctions.ino | Contains function for different system stage that supposed to put into LOOP() for getting user&#39;s input and deliver servo output |
| CoordinateControl.h | Contains coordinate management and invert kinematic logics. |
| DisplayFunctions.h | Header for DisplayFunctions.ino |
| DisplayFunctions.ino | Contains functions for different system stage that deliver debug/calibration assistance output via Serial interface |
| GCode.h | Header for GCode.ino |
| GCode.ino | Contains functions for taking G-code and convert it to arm output. |
| InitFunctions.h | Header for InitFunctions.ino |
| InitFunctions.ino | Contains Initialize functions for different machine stage |
| ThisArm.ino | The Main file of the This Arm software |
| StageContainer.h | Contains structures that help to manage different stages of the firmware. |
| Transformation.h | Contains functions for Linear linear interpolation |

## Explanation of Encoder control interface:

Available action:

- Turn
  - Increase/Decrease the parameter selected.
- Pushdown and Turn
  - Increase/Decrease the parameter selected in a larger step
- Click
  - Switch selected item (Except G-code and Analog Control Stage)
- Double Click
  - Button was clicked twice within &quot;DoubleClickInteral\_ms&quot; (10ms by default)
  - Execute DoubleClick Routine (For change of machine Stage)

## Reference:

- GCode CNC Demo by MarginallyClever
  - [https://github.com/MarginallyClever/GcodeCNCDemo](https://github.com/MarginallyClever/GcodeCNCDemo)

