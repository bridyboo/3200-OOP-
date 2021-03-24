//
// Created by Matthew Darmadi on 5/28/2020.
//

/*
 * Class Invariants:
 * CONSTRUCTOR DEPENDENCY INJECTION for file
 * Move() isn't overriden no specific requirements
 * carries dependency from Robot
 *
 * constructor resizes sensorArray and fills in new array
 * destructor is inheritted from parent and move semantics
 *
 * Resize() is a special array resize for the Robot class
 */

#include "tranRobot.h"

using namespace std;

//pre : file must exist
//post : object initialized and with extra 20 sensors
TranRobot::TranRobot(std::string file) : Robot(file)
{
    Resize(additionalSensors);
}

//pre: none
//post : robot tries to move + battery depletes and might die
void TranRobot::Down()
{
    direction = "down";
    if (isValid(grid[row][col]))
        row = actuatorArr[1]->moveForward(row, col);
    moves++;
}

//pre: none
//post : robot tries to move + battery depletes and might die
void TranRobot::Left()
{
    direction = "left";
    if (isValid(grid[row][col]))
        row = actuatorArr[2]->moveForward(row, col);
    moves++;

}

//pre: none
//post : robot tries to move + battery depletes and might die
void TranRobot::Right()
{
    direction = "right";
    if (isValid(grid[row][col]))
        row = actuatorArr[3]->moveForward(row, col);
    moves++;
}

//pre: none
//post : robot tries to move + battery depletes and might die
bool TranRobot::MoveOne()
{
    if(!actuatorPower())
        return false;

    direction = "up";

    if (isValid(grid[row][col]))
        row = actuatorArr[0]->moveForward(row, col);
    return true;
    moves++;
}

//pre: none
//post : robot tries to move + battery depletes and might die
bool TranRobot::Move()
{
    return Robot::Move();
}

//pre : path should only be 0 or 1 and appropriate sensor must exist
//post : isValid could deplete sensor battery and change its state
bool TranRobot::isValid(int path)
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
bool TranRobot::sensorCalculate(std::string direction, int path) {
    int count = 0;

    if (direction == "up")
    {
        for (int i = 0; i < 5; i++)
        {
            if (sensorArr[i]->getBattery_level() > 80 &&sensorArr[i]->isValid(path))
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

TranRobot::~TranRobot()
{
    //automagically calls parent destructor
}
