#include "actuator.h"
#include "sensor.h"
#include <string>
#include <iostream>
#include <fstream>
#include <utility>
#include <exception>

/*
 * Matthew Brian Darmadi
 * 4/26/2020
 * p2
 */

/*
* Class Overview:
* Robot has a sensor with its own battery, and a number of actuators depending on how many
* is initialized in the constructor. The robot also requires a grid for it to work.
* for this specific robot it requires a 11 x 11 grid. It can be altered but you must attach
* an actuator that also reads from an 11x11 grid.
*
* The number of initialized actuators determine its movement ability.
* 1 actuator -> up
* 2 actuators -> up, down
* 3 actuators -> up, down, left
* 4 actuators -> up,down, left,right
*/

/*
* Interface Invariants:
* HAS-A sensor
* HOLDS-A  Actuator
* to function properly actuator and robot must have the same row collumn size
*
* The number of initialized actuators determine its movement ability.
* 1 actuator -> up
* 2 actuators -> up, down
* 3 actuators -> up, down, left
* 4 actuators -> up,down, left,right
*
* Move() and MoveOnce() may change state of sensor() because of the battery drain on isValid()
* hasPower() will change battery state to true and battery level
*/
#ifndef ROBOT_H
#define ROBOT_H

class Robot
{

public:
    Robot(std::string file);
    virtual ~Robot();
    Robot& operator= (const Robot& rbt);
    Robot& operator= (Robot&& rbt);
    Robot(const Robot& rbt);
    Robot(Robot&& rbt);

    Robot();
    int countMoves();
    virtual bool isValid(int path);
    virtual bool Move();
    virtual bool MoveOne();
    void hasPower();
    int getRow();
    int getCol();

    bool operator==(Robot &rbt);
    bool operator!=(Robot &rbt);
    bool operator>(Robot &rbt);
    bool operator<(Robot &rbt);
    void operator++();
    bool operator>=(Robot &rbt);
    bool operator<=(Robot &rbt);

    template <typename T>
    void swap(T& lhs, T& rhs);

private:
    static const int defaultGrid = 11;
    static const int defaultActuatorCount = 4;
    static const int defaultSensorCount = 4;

    int actuatorRange;

    void Copy(const Robot& rbt);

protected:


    int grid[defaultGrid][defaultGrid];

    int row;
    int col;
    int moves;
    std::string direction;

    int sensorRange;
    Sensor** sensorArr;
    Actuator** actuatorArr;

    bool actuatorPower();
    virtual bool sensorCalculate(std::string direction, int path);
    void Resize(int newSize);

};

#endif // !ROBOT_H
