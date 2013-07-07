/*
 Title: PMCtrl.h
  Author/Date: gNSortino@yahoo.com / 2013-07-06
  Description: This library implements the main features
	of the Pololu Maestro. It was tested against the
	micro-maestro. Additional features will be added as
	needed/requested.
	
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
*/

#include "Arduino.h"
#include "SoftwareSerial.h"
#include "PMCtrl.h"

/*
	Sets the transit and receive pins on the 
	SoftwareSerial Interface.
*/
PMCtrl::PMCtrl (int rxPin, int txPin, long baudRate) : _serialCtrl (rxPin, txPin)	// RX, TX
{
	_serialCtrl.begin (baudRate);
}

/*
  sets the servo to the desired 'pos'ition in 
  microseconds.
*/
void PMCtrl::setTarget (unsigned int pos, unsigned char channel, int deviceID)
{
  //Maestro uses quarter microseconds so convert accordingly
  pos = pos * 4;
  
  _serialCtrl.write(0xAA);               // start byte
  _serialCtrl.write(deviceID);           // device id
  _serialCtrl.write(0x04);               // command number
  _serialCtrl.write(channel);            // servo number
  _serialCtrl.write(pos & 0x7F);         // target low bits
  _serialCtrl.write((pos >> 7) & 0x7F);  // target high bits

}


/* 
  Sets the speed that the servo moves at. Note that 
  this does not have to be set. If left alone it will
  take the default value, which should be instaneous. 
  Although this is of course limited by the physical speed 
  of the servo. Speed is set set in units of .25us/10ms. 
  For example, setting a value of 140 corresponds to a 
  speed of 3.5 us/ms eg. 
	3.5 = 140 * (.25 us / 10ms)
  In practical terms this means that the servo can move 
  3.5us in 1 ms. For example, moving from 1000us to 1350us
   would take 100ms 
*/
void PMCtrl::setServoSpeed (unsigned int servoSpeed, unsigned char channel, int deviceID)
{
  //Maestro uses quarter microseconds so convert accordingly
  //pos = pos * 4;
  
  _serialCtrl.write(0xAA);                      // start byte
  _serialCtrl.write(deviceID);                  // device id
  _serialCtrl.write(0x07);                      // command number
  _serialCtrl.write(channel);                   // servo number
  _serialCtrl.write(servoSpeed & 0x7F);         // target low bits
  _serialCtrl.write((servoSpeed >> 7) & 0x7F);  // target high bits
}

/*
  Sends all servos to their home positions
*/
void PMCtrl::goHome (int deviceID)
{
  _serialCtrl.write(0xAA);               // start byte
  _serialCtrl.write(deviceID);           // device id
  _serialCtrl.write(0x22);               // command number
}

/*
   Returns the position of the specified servo in microseconds
   Note that if the microcontroller is unable to read from the 
   servo for any reason than Null or some other obscure value
   could be returned.
*/
unsigned int PMCtrl::getPosition (unsigned char channel, int deviceID)
{
  unsigned int servoPosition;
  
  _serialCtrl.write(0xAA);                      // start byte
  _serialCtrl.write(deviceID);                  // device id
  _serialCtrl.write(0x10);                      // command number
  _serialCtrl.write(channel);                   // servo number
  
  if ( _serialCtrl.available() )
  {
    servoPosition = _serialCtrl.read();
    if ( _serialCtrl.available() )
    {
      servoPosition += ( _serialCtrl.read() * 256 );
      return servoPosition / 4;
    }
  }
  else
    return 0;  
}


/*
  Returns error codes from the maestro. 
  See: http://www.pololu.com/docs/0J40/all#4.b for a list of error
  codes.
*/
unsigned int PMCtrl::getErrors (unsigned char channel, int deviceID)
{
  unsigned int errors;
 
  _serialCtrl.write(0xAA);                      // start byte
  _serialCtrl.write(deviceID);                  // device id
  _serialCtrl.write(0x21);                      // command number
  
  if ( _serialCtrl.available() )
  {
    errors = _serialCtrl.read();
    if ( _serialCtrl.available() )
    {
      errors += _serialCtrl.read() * 256;
      return errors;
    }
  }
  else
    return 0;  
}

/*
	Destructor (cleanup)
*/
PMCtrl::~PMCtrl()
{

}