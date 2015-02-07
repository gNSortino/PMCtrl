/*
 Title: PMCtrl (Demo)
  Author: gNSortino
  Description: This is a demo library that shows how to
        test the main features of the Pololu Maestro library (PMCtrl)
        written for the arduino development environment.
        	
	The code is based off the Pololu user guide as
	well as the software serial** arduino library see
	the relevant links below:
		# Sofware Serial Library
			http://arduino.cc/en/Reference/SoftwareSerial
		# Pololu Arduino Tutorial
			http://forum.pololu.com/viewtopic.php?f=16&t=5696
		# Pololu User Guide
			http://www.pololu.com/docs/0J40/all#7.c   	
	
	**This code relies on the SoftwareSerial Arduino
	library. It is recomended that this library also be 
	#included in the calling code as the Arduino can
	sometimes have problems if this isn't done.
	
	Function descriptions can be found in the .cpp file
	of the same name. I am happy to add additional functions 
        as requested or have others add them as well.
  Revision History:
    2013-07-06/gNSortino : inital release
    2014-11-02/gNSortino : changed structure of sample program to reflect 
      arduino standards. Code suggestions were kindly made by Adriano @ Adrirobot 
      http://it.emcelettronica.com/author/adrirobot/
	2015-02-07/gNSortino : added set setAcceleration call to demo program
*/

#include <SoftwareSerial.h>
#include <PMCtrl.h>


PMCtrl servoCtrl (11, 3, 9600); //RX, TX, Baud

void setup ()
{
  Serial.begin(9600);  // needed for console output
}

void loop ()
{
  Serial.println ("Beginning"); 

  Serial.println ("Now I rotate the servo - Speed 50"); 
  servoCtrl.setServoSpeed (50, 0, 12);
  servoCtrl.setTarget (900, 0, 12);
  delay (5000);
  servoCtrl.getPosition(0,12);
  Serial.print ("Position is: "); Serial.println (servoCtrl.getPosition(0,12));


  Serial.println ("Now I rotate the servo - Speed 15");
  servoCtrl.setServoSpeed (15, 0, 12);
  servoCtrl.setTarget (1680, 0, 12);
  delay (5000);
  servoCtrl.getPosition(0,12); Serial.print ("Position is: "); Serial.println (servoCtrl.getPosition(0,12));


  servoCtrl.setAcceleration(2,0,12);
  servoCtrl.goHome(12);
  delay (5000);

  Serial.println ("Done");
  servoCtrl.setAcceleration(0,0,12);
  delay (2000);
}