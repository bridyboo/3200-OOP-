#include "actuator.h"

/*
* matthew Brian Darmadi
* 4/26/2020
* p2
*/


/*
* Class Invariants:
* in a HOLDS-A RELATIONSHIP with robot
* state will stay true
* direction only accepts these strings [up , down, left, right]
*/

using namespace std;

//pre : direction only [up , down, left, right]
//post : actuator is on
Actuator::Actuator(string direction)
{
    orientation = direction;
    state = true;
}

//pre: direction only accepts [up , down, left, right]
//post: returns int of new row or collumn depending of the changed axis
int Actuator::moveForward(int loc_row, int loc_col)
{
    if (orientation == "up")
        return --loc_row;
    else if (orientation == "down")
        return ++loc_row;
    else if (orientation == "left")
        return --loc_col;

    return ++loc_col; // for direction "right"
}

//pre: none
//post: none
bool Actuator::isPoweredup()
{
    return state;
}

Actuator::~Actuator()
{
}


/*
* Implementation Invariants:
* direction is set intially in the constructor
* state is always true and will stay true until further functionality in the future
* direction only accepts these strings [up , down, left, right]
*/
