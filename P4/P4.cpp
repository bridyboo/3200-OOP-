//
// Created by Matthew Darmadi on 5/28/2020.
//

/*
 * Assumption:
 * grid is a 11 x 11 matrix
 * robot starts from row 5 column 5
 * objects initialized properly
 * file grid.txt exists and path is set correctly (location of 0 1 doesn't matter)
 * make_unique doesn't exist in c++11 i used a function template from
 * "https://stackoverflow.com/questions/7038357/make-unique-and-perfect-forwarding"
 *
 * battery will never die in this driver because I've explicitly recharged the robot
 * after every Move() function. battery percent and state is client's responsibility
 * per- the contract.
 *
 * everything from p3 c# ported properly to p4 C++
 *
 * overloaded operator only implemented relational and comparison operators
 * why? because The specification explicitly wanted a new function (countMove())
 * just to compare move distances.
 *
 * reason for not implementing arithmetic operator: redundant feature for Robot class
 * moveOne() would serve the same function. And a combination of 2 Robots doesn't really
 * make sense.
 * 
 */

#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <vector>
#include <memory>
#include "robot.h"
#include "rotRobot.h"
#include "tranRobot.h"
#include "actuator.h"
#include "sensor.h"
#include "actuator.h"

using namespace std;

const int arrSize = 4;
const int lowest = 1;
const int highest = 5;
const int pinglim = (highest + lowest) +1;
const int def_direction = 4;
const int types = 3;
const std::string FILENAME = "grid.txt";

template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args)
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

void testRobot(shared_ptr<Robot>& robot);
void initRobot(vector<shared_ptr<Robot>>& arr);
void testUnique(vector<unique_ptr<TranRobot>>& arr);
void testOperation();

int main()
{
    vector<shared_ptr<Robot>> arr;
    vector<unique_ptr<TranRobot>> uniqueArr;
    initRobot(arr);
    testUnique(uniqueArr);
    testOperation();
}

void testOperation() {
    cout << endl << "-----testing overloaded operators -----" << endl;
    shared_ptr<Robot> rob = make_shared<Robot>(FILENAME);
    cout << "we'll move object1 by one and pass by value, theoretically they should be the same" << endl;
    rob->MoveOne();
    cout << "object 1 | row : " << rob->getRow() << " col : " << rob->getCol() << endl;
    cout << "now lets pass by value . .  . " << endl;
    shared_ptr<Robot> rob2 = make_shared<Robot>(FILENAME);
    cout << "object 2 | row : " << rob2->getRow() << " col : " << rob2->getCol() << endl;

    bool ans = rob2 == rob;
    cout << " testing rob2 == rob results -> " << ans << "(true(1) / false(0))" << endl;
    ans = rob2 > rob;
    cout << " testing rob2 > rob results -> " << ans << "(true(1) / false(0))" << endl;
    ans = rob2 < rob;
    cout << " testing rob2 < rob results -> " << ans << "(true(1) / false(0))" << endl;
    ans = rob2 <= rob;
    cout << " testing rob2 <= rob results -> " << ans << "(true(1) / false(0))" << endl;
    ans = rob2 >= rob;
    cout << " testing rob2 >= rob results -> " << ans << "(true(1) / false(0))" << endl;
    ans = rob2 != rob;
    cout << " testing rob2 != rob results -> " << ans << "(true(1) / false(0))" << endl;

}

void initRobot(vector<shared_ptr<Robot>>& arr)
{
    cout << "Initialize Robot" << endl;

    srand((unsigned int)time(NULL));
    shared_ptr<Robot> robot;
    for (int i = 0; i < arrSize; i++)
    {
        unsigned int num = rand() % types + 1;
        switch (num)
        {
            case 1:
                robot = make_shared<Robot>(FILENAME);
                arr.push_back(move(robot));
                break;
            case 2:
                robot = make_shared<TranRobot>(FILENAME);
                arr.push_back(move(robot));
                break;
            case 3 :
                robot = make_shared<RotatingRobot>(FILENAME);
                arr.push_back(move(robot));
                break;
        }
    }
    cout << "initialize Complete" << endl;

    for (int i = 0; i < arrSize; i++)
    {
        cout << endl << "[][][] testing " << typeid(*arr[i]).name() << " [][][]" << endl;
        testRobot(arr[i]);
    }
}

void testRobot(shared_ptr<Robot>& robot)
{
    cout << "--- testing moveOne ---" << endl;
    cout << "initial Row" << robot->getRow() << " | Initial Col " << robot->getCol() << endl;

    robot->MoveOne();
    cout << "new Row : " <<  robot->getRow() << "   | new col: " << robot->getCol() << endl;
    robot->hasPower();
    cout << " --- testing move ---" <<  endl;
    cout << "initial Row " << robot->getRow() << " | Initial Col " << robot->getCol() << endl;

    robot->Move();
    cout << "total moves " <<  robot->countMoves()<< endl;
    cout << "new Row : " << robot->getRow() << "   | new col: " << robot->getCol() << endl;
}

void testUnique(vector<unique_ptr<TranRobot>>& arr)
{
    cout << "---Initialize unique_ptr Robot---" << endl;

    srand((unsigned int)time(NULL));

    for (int i = 0; i < arrSize; i++)
    {
        //unsigned int num = lowest + (rand() % pinglim);
        unique_ptr<TranRobot> robot = make_unique<TranRobot>(FILENAME);
        arr.push_back(move(robot));
    }

    cout << "initialized " << arrSize << " unique_ptr Complete" << endl;


    cout << endl << "[][]][] testing UNIQUE robot number [][][]" << endl;
    arr[0]->Left();
    arr[0]->hasPower();
    cout << endl << "--- testing move(left) ---" << endl << endl;
    cout << "new row " << arr[0]->getRow() << " new col " << arr[0]->getCol() << endl;
    arr[1]->Down();
    arr[1]->hasPower();
    cout << endl << "--- testing move(down) ---" << endl << endl;
    cout << "new row " << arr[0]->getRow() << " new col " << arr[0]->getCol() << endl;
    arr[2]->Right();
    cout << endl << "--- testing move(right) ---" << endl << endl;
    cout << "new row " << arr[0]->getRow() << " new col " << arr[0]->getCol() << endl;

}
