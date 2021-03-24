//
// Created by Matthew Darmadi on 5/28/2020.
//

/*
 * Class Overview:
 * TranRobot is a descendant of Robot. TranRobot is a robot with individual sensors for each
 * direction. It is able to go to a specific direction without needing to rotate its head.
 *
 */

/*
 * Interface Invariatns:
 * is-a Robot relationship.
 * shares all dependencies and invariants as Robot
 * Move() isn't overidden since it's  not specified in requirement therefore only forward capability
 **/

#include "robot.h"

#ifndef TRANROBOT_H
#define TRANROBOT_H

class TranRobot : public Robot{

private:
    int additionalSensors = 20;

public:
    TranRobot(std::string file);
    ~TranRobot();

    void Down();
    void Left();
    void Right();
    bool MoveOne() override;
    bool Move() override;
    bool isValid(int path) override;
    bool sensorCalculate(std::string direction, int path) override ;
};


#endif //TRANROBOT_H
