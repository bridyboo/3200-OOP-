#include "sensor.h"



/*
* Class Invariants:
* when battery_level is < 10% you can't use isValid() until recharge()
* when state is false you can't use isValid() until state is true
* state and battery_level directly effects the ability to use isValid()
* when you recharge state will automatically turn on
*/

   
using namespace std;

//pre : none
//post : sensor will be initialized and state will be set according to user input
Sensor::Sensor(bool state, int rate)
{
	this->rate = rate;
	this->state = state;
	battery_level = DEFAULT_BATTERY_LEVEL;
}

//pre : path only works properly when reading 0 and 1
//post : if battery_level is <=0 it will turn state false
bool Sensor::isValid(int path)
{
	battery_level -= rate;

	if (battery_level <= 0)
		state = false;

	if (state == false) return false;
	else if (battery_level < 10) return false;
	else if (state == true && battery_level < 10) return false;

	if (path == 0)
		return false;

	return true;
}

//pre: none
//post : none
int Sensor::getBattery_level()
{
	return battery_level;
}

//pre : none
//post : battery will be 100 and state is set to true
bool Sensor::recharge()
{
	battery_level = DEFAULT_BATTERY_LEVEL;
	//sleep(2);
	state = true;
	return true;
}

Sensor::~Sensor()
{
}

/*
 * Implementation Invariants
 * isValid can change State if battery_level is <= 0.
 * battery_state linearly reduces by "rate" every time isValid() is called
 * recharge() always fills to 100% no matter previous percentage
 * recharge() always flips the state to true
 * only reduce battery from isValid()
 */
