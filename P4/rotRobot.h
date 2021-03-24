//
// Created by Matthew Darmadi on 5/28/2020.
//

#include "robot.h"

#ifndef ROTATINGROBOT_H
#define ROTATINGROBOT_H

/*
* Class OVerview:
* Robot that adds more sensors on top of the orignial robot. Rotates its sensor around to
* change it's direction
*/

/*
    * Interface Invariants:
    * RotatingRobot is-a Robot
    * rotate() rotates clockwise through up->right ->  down -> left -> up this motion
    * shares all invariants and overhead as Robot parent
    */


class RotatingRobot: public Robot{

private:
    int additionalSensors = 15;

public:
    RotatingRobot(std::string file);
    ~RotatingRobot();

    void rotate();
    bool Move() override;
    bool MoveOne() override;
    bool isValid(int path) override ;
    bool sensorCalculate(std::string direction, int path) override ;
};


#endif //ROTATINGROBOT_H
