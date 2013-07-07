/*
 Title: PMCtrl (Demo)
  Author/Date: gNSortino@yahoo.com / 2013-07-06
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
*/

#include <SoftwareSerial.h>
#include <PMCtrl.h>


PMCtrl servoCtrl (11, 10, 9600); //RX, TX, Baud

void setup ()
{
  
}

void loop ()
{
  Serial.print ("Begining. Position is: "); Serial.println (getPositions(0,12));
  setTarget (650, 0, 12);
  delay (1000);
  setServoSpeed (15, 0, 12);
  Serial.print ("Position is: "); Serial.println (getPositions(0,12));
  setTarget (1650, 0, 12);
  delay (5000);
  setServoSpeed (0, 0, 12);
  
  goHome(12);
  
  delay (4000);
  Serial.println ("Done";
}
