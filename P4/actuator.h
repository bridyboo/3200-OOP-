#include <stdlib.h>
#include <time.h>
#include <string>

/*
 * Matthew Brian Darmadi
 * 4/23/2020
 * p2
 */

/*
* Class Overview:
* Actuator moves forward in one single axis depending on the initial direction of the actuator
* an actuator's direction is fixed and cannot be changed. State is always true and will not
* change in this current version
*/


/*
* Interface Invariants:
* is in a "Robot HOLDS-A Actuator" relationship
* to function properly row and collumn should be the same size as the robot it will be attached to
* state is always initialized as true
* state will stay true
*/

#ifndef  ACTUATOR_H
#define ACTUATOR_H

#pragma once
class Actuator
{
private:
    static const int row = 11;
    static const int column = 11;

    bool state;


public:

    Actuator(std::string direction);

    int moveForward(int loc_row, int loc_col);
    std::string orientation;
    bool isPoweredup();
    ~Actuator();

};

#endif // ! ACTUATOR_H