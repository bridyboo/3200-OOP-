/*
* Matthew Brian Darmadi
* 5/7/2020
* p3
*/

/*
    * Class Invariants:
    * file is a constructor dependency injection
    * carries dependency from Robot parent
    * is-a Robot
    *
    * constructor resizes sensorArray based on new private data, all sensors are replaced
    * destructor is inheritted from base no new handle in heap
    */

#include "rotRobot.h"

using namespace std;

//pre: file needs to exist
//post: adds 15 new sensors
RotatingRobot::RotatingRobot(string file) :Robot(file)
{
    Resize(additionalSensors);
}

//pre: initialized properly
//post: change direction clockwise
void RotatingRobot::rotate()
{
    if (direction == "up")
        direction = "right";

    else if (direction == "right")
        direction = "up";

    else if (direction == "down")
        direction = "left";

    else
        direction = "up";
}

//pre: actuator and direction for sensor must exist battery is enough
//post : robot will move until wall
bool RotatingRobot::Move()
{
    if (direction == "left")
    {
        while (isValid(grid[row][col-1]))
        {
            col = actuatorArr[2]->moveForward(row, col);
            moves++;
        }
        return true;
    }
    else if (direction == "right")
    {
        while (isValid(grid[row][col + 1]))
        {
            col = actuatorArr[3]->moveForward(row, col);
            moves++;
        }
        return true;
    }

    return Robot::Move();
}

//pre: actuator and direction must exist battery enough
//post : robot will move
bool RotatingRobot::MoveOne()
{
    if (isValid(grid[row][col]))
    {
        if (direction == "down")
        {
            row = actuatorArr[1]->moveForward(row, col);
            return true;
        }
        else if (direction == "left")
        {
            col = actuatorArr[2]->moveForward(row, col);
            return true;
        }
        else if (direction == "right")
        {
            col = actuatorArr[3]->moveForward(row, col);
            return true;
        }
    }

    return Robot::MoveOne();
}

//pre : path should only be 0 or 1 and appropriate sensor must exist
//post : isValid could deplete sensor battery and change its state
bool RotatingRobot::isValid(int path)
{
    if (direction == "up")
        return sensorCalculate("up", path);

    else if (direction == "down")
        return sensorCalculate("down", path);

    else if (direction == "left")
        return sensorCalculate("left", path);

    else
        return sensorCalculate("right", path);
}

//pre : none
//post : battery depletes, battery might die
bool RotatingRobot::sensorCalculate(std::string direction, int path) {
    int count = 0;

    if (direction == "up")
    {
        for (int i = 0; i < 5; i++) {
            if (sensorArr[i]->getBattery_level() > 80 && sensorArr[i]->isValid(path))
                count++;
        }
    }
    else if (direction == "down") {
        for (int i = 5; i < 10; i++) {
            if (sensorArr[i]->getBattery_level() > 80 && sensorArr[i]->isValid(path))
                count++;
        }
    }
    else if (direction == "left") {
        for (int i = 10; i < 15; i++) {
            if (sensorArr[i]->getBattery_level() > 80 && sensorArr[i]->isValid(path))
                count++;
        }
    }
    else // for the "right" direction
    {
        for (int i = 15; i < 20; i++) {
            if (sensorArr[i]->getBattery_level() > 80 && sensorArr[i]->isValid(path))
                count++;
        }
    }

    return count >= 2;
}

RotatingRobot::~RotatingRobot()
{
    //automagically calls base destructor
}

/*
 * Implemnentation Invariants:
 * Direction only rotates clockswise.
 * this object is a descendant of Robot
 * shares all overhead and dependencies
 * has 4 sensors but doesn't have the functionality to go down as per requirement
 */
