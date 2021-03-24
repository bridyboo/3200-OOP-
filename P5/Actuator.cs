using System;


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

public class Actuator
{

    const int row = 11;
    const int column = 11;
    string orientation;
    bool state;

    //pre : direction only [up , down, left, right]
    //post : actuator is on
    public Actuator(string direction)
    {
        orientation = direction;
        state = true;
    }

    //pre: direction only accepts [up , down, left, right]
    //post: returns int of new row or collumn depending of the changed axis
    public int moveForward(int loc_row, int loc_col)
    {
        if (orientation == "up")
            return --loc_row;
        else if (orientation == "down")
            return ++loc_row;
        else if (orientation == "left")
            return --loc_col;

        return ++loc_col;
    }

    //pre: none
    //post: none
    public bool isPoweredup()
    {
        return state;
    }


}


/*
* Implementation Invariants:
* direction is set intially in the constructor
* state is always true and will stay true until further functionality in the future
* direction only accepts these strings [up , down, left, right]
*/
