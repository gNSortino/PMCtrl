PMCtrl 
==============================
*(aka. Pololu Maestro Control for Arduino)*

###Description:
This is a library I wrote that is used to control a Pololu Maestro via an Arduino using the Software Serial (Arduino) Library.

###Currently the following methods are supported:
* **setTarget:** sets the position of the servo
* **setServoSpeed**: sets the speed the servo moves at
* **goHome:** moves all servos connected to a device to their home position
* **getPosition:** returns the current position of a servo
* **getErrors:** returns information regarding the error state of servos (I have not tested this one yet).

The implemented methods are based off the Pololu protocol (see: http://www.pololu.com/docs/0J40/all#5.e).

For more information on Software Serial see: http://arduino.cc/en/Reference/SoftwareSerial 

I wrote this library specifically to use with my Arduino Uno and Pololu Micro Maestro and all testing was done with this combination in mind but it 
\*should\* work with other combinations as well.

I did not include all of the methods (I only needed a few), however, if people would like others added or would like to add to this code themselves I’m happy to support this.

###Getting Started:
There is a sample piece of code (PMCtrl.ino) that demonstrates how this library is intended to be used. Full documentation of the methods can be found in the PMCtrl.cpp file.

###Bugs/Issues:
I have not yet tested the getErrors method. 
