#include <stdlib.h>
#include <time.h>
//#include <unistd.h>

/*
 * Matthew Brian Darmadi
 * 4/23/2020
 * p2
 */


/*
* Class Overview :
* Sensor is a class that senses. Initially it starts with a full battery, and
* reduces by flat linear percent down. When the battery is below or equal to 0% it will automatically turn off and you won't be
* able to query it untill it's charged. It also won't be query-able when it's low on battery (10%).
*
* recharge will always charge to 100% because we're in the future and it will automatically set state
* true
*/

/*
* Interface Invariants:
* is in a "Robot HAS-A Sensor" relationship
* isValid will involutarily switch state to false, when battery is <= 0
* recharge() is the only way to turn a false state to true
* recharge() will always charge battery to 100% and automatically switch state to true
*/

#ifndef SENSOR_H
#define SENSOR_H

#pragma once
class Sensor
{
public:
	Sensor(bool state, int rate);
	bool isValid(int path);
	bool recharge();
	int getBattery_level();
	~Sensor();

private:
	int battery_level;
	bool state;
	int rate;
	const int DEFAULT_BATTERY_LEVEL = 100;

};
#endif // !SENSOR_H

