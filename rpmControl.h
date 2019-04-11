// rpmControl.h

#ifndef _rpmCONTROL_h
#define _rpmCONTROL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "CurieTimerOne.h"

class rpmControl {
public: 
	rpmControl();
	int setSpeedInt(int speedint);
	int updateSpeed();
	int getSpeedSignal1();
	int getSpeedSignal2();
	int getSpeed();
private:
	int _pinPotentiometer = A0;
	int _pinPWM = 6;//Analog output that the rpm is attached to. 5 and 6 are attached to timer0, 62500Hz, 9 and 10 time 1, 31250Hz
	int _pinLED = 7;
	int _pinSpeed1 = 5; 
	int _pinSpeed2 = 8; 
	int _currentSpeed = 0; //currentSpeed is in % not from 0 to 1023
  int _speedThreshold = 90; // Threshold Speed ON or OFF, compare speed in percent
	int CountPulse(int pinSpeed);
};

#endif

