#include "rpmControl.h"


rpmControl::rpmControl() {
	pinMode(_pinLED, OUTPUT);
	pinMode(_pinPWM, OUTPUT);
	pinMode(_pinPotentiometer, INPUT);
	pinMode(_pinSpeed1, INPUT);
  pinMode(_pinSpeed2, INPUT);
}

int rpmControl::updateSpeed() {
	// Read the current voltage level on the A4 analog input pin.
    Serial.print("rpm: AnalogRead from potentiometer/pin A0 : ");
	int wantedSpeed = analogRead(_pinPotentiometer);
	Serial.println(wantedSpeed);
	//Speed Percentage to be displayed
	int speedPercent = map(wantedSpeed, 0, 1023, 0, 100);
	//DutyCyle for the PWM : from 0 to 255 (full speed)

	if (speedPercent != _currentSpeed) {      // if the speed has changed
		Serial.print("Wanted Fan Speed % is now: "); // print it
		Serial.println(speedPercent);
		if (speedPercent <= _speedThreshold) {
			digitalWrite(_pinLED, LOW);
		}
		else {
			digitalWrite(_pinLED, HIGH);
		}
		int timerus = 1; //1MHz => 10^-6s = 1us
		CurieTimerOne.pwmStart(_pinPWM, wantedSpeed, timerus);//CurieTimerOne.pwmStart(_pinPWM, dutyCycle, timerus);
		_currentSpeed = speedPercent;           // save the level for next comparison
	}
	getSpeedSignal1();
	getSpeedSignal2();
	return 0;
}

int rpmControl::setSpeedInt(int speedint) {

	if (speedint != _currentSpeed) {      // if the speed has changed
		Serial.print("Wanted Fan Speed % is now: "); // print it
		Serial.println(speedint);
		if (speedint <= _speedThreshold) {
			digitalWrite(_pinLED, LOW);
		}
		else {
			digitalWrite(_pinLED, HIGH);
		}
		//DutyCyle for the PWM : from 0 to 255 (full speed)
		int dutyCycle = map(speedint, 0, 100, 0, 255); // map to the range of the analog output
		int timerus = 1; //1MHz => 10^-6s = 1us
		CurieTimerOne.pwmStart(_pinPWM, dutyCycle, timerus);
		_currentSpeed = speedint;           // save the level for next comparison
	}
	return 0;
}

int rpmControl::getSpeed() {
	return _currentSpeed;
}

int rpmControl::getSpeedSignal1() {
  int rpm = CountPulse(_pinSpeed1);
  Serial.print("Speed 1 in RPM: ");  Serial.println(rpm);
  return rpm;
}

int rpmControl::getSpeedSignal2() {
  int rpm = CountPulse(_pinSpeed2);
  Serial.print("Speed 2 in RPM: ");  Serial.println(rpm);
  return rpm;
}

int rpmControl::CountPulse(int pinSpeed) {
	int T1, T2, T3, T4, T5, T6;
	float speed;
	T1 = pulseIn(pinSpeed, HIGH, 2000);// timeout (optional): the number of microseconds to wait for the pulse to be completed: the function returns 0 if no complete pulse was received within the timeout. Default is one second
	T2 = pulseIn(pinSpeed, LOW);
	T3 = pulseIn(pinSpeed, HIGH);
	T4 = pulseIn(pinSpeed, LOW);
	T5 = pulseIn(pinSpeed, HIGH);
	T6 = pulseIn(pinSpeed, LOW);
	speed = 60 * 1000000 / (T1 + T2 + T3 + T4 + T5 + T6); // 60/ par minute *1000000/ pulsIn returns microseconds
	return speed;
}


