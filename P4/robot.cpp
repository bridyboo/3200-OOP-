#include "robot.h"

/*
* Class Invariants:
* The number of initialized actuators determine its movement ability.
* 1 actuator -> up
* 2 actuators -> up, down
* 3 actuators -> up, down, left
* 4 actuators -> up,down, left,right
*
* move semantics and copying supported
*
* echoes functionality for sensor->isValid() and sensor->Recharge()
* Resize() is mostly used for derived classes
 *
 * overloaded operator only implemented relational and comparison operators
 * why? because The specification explicitly wanted a new function (countMove())
 * just to compare move distances.
*/

using namespace std;

//pre: file should contain a grid the same dimension as
//     defaultGrid.
//post: object initialized and robot has data of the grid. Movement limits are determined
//		depending on number of actuators
Robot::Robot(string file)
{
    if (file.empty()) throw std::invalid_argument("invalid file");

    actuatorRange = defaultActuatorCount;
    sensorRange = defaultSensorCount;

    row = 5;
    col = 5; //starting location is 5,5
    moves = 0;

    ifstream myfile;
    myfile.open(file);

    while (!myfile.eof())
    {
        for (int i = 0; i < defaultGrid; i++)
        {
            for (int j = 0; j < defaultGrid; j++)
            {
                myfile >> grid[i][j]; //saving grid into Robot
            }
        }
    }
    myfile.close();

    sensorArr = new Sensor*[sensorRange];

    actuatorArr = new Actuator*[actuatorRange];
    string directions[defaultSensorCount] = { "up", "down", "left", "right" };

    for (int i = 0; i < actuatorRange; i++)
    {
        actuatorArr[i] = new Actuator(directions[i]);
    }

    for (int i = 0 ; i < sensorRange; i ++)
        sensorArr[i] = new Sensor(true); //initial forward sensor

    direction = "up";

}

//pre : none
//post : none
int Robot::countMoves()
{
    return moves;
}

//pre : path should only be 0 or 1 and appropriate sensor must exist
//post : isValid could deplete sensor battery and change its state
bool Robot::isValid(int path)
{
    if (direction == "up")
        return sensorArr[0]->isValid(path);

    else if (direction == "down")
        return sensorArr[1]->isValid(path);

    else if (direction == "left")
        return sensorArr[2]->isValid(path);

    else
        return sensorArr[3]->isValid(path);}


//pre: actuator and corresponding direction must exist
//post : robot will move until it hits a wall
bool Robot::Move()
{
    if(!actuatorPower())
        return false;

    if (direction == "up") {
        while (isValid(grid[row - 1][col]))
        {
            row = actuatorArr[0]->moveForward(row, col);
            moves++;
        }
    }

    return true;
}

//pre: actuator and corresponding direction must exit
//post : robot will move once
bool Robot::MoveOne()
{
    if(!actuatorPower())
        return false;

    if(isValid(grid[row][col]))
    {
        if (direction == "up")
            row = actuatorArr[0]->moveForward(row, col);
    }

    moves++;
    return true;
}

bool Robot::sensorCalculate(std::string direction, int path)
{
    return true;
}

//pre = object initialized and only resized going up
//post : size will change and array will be repopulated
void Robot::Resize(int newSize)
{
    delete[] sensorArr;

    sensorArr = new Sensor*[newSize];

    for (int i = 0 ; i < newSize; i ++)
    {
        sensorArr[i] = new Sensor(true);
    }
}

//pre: initialized correctly
//post: battery will be 100% and state true
void Robot::hasPower()
{
    for (int i = 0 ; i < sensorRange; i++)
        sensorArr[i]->recharge();

}

//pre: none
//post none
int Robot::getCol()
{
    return col;
}

//pre : none
//post : none
int Robot::getRow()
{
    return row;
}

bool Robot::actuatorPower()
{
    for(int i = 0 ; i < actuatorRange; i++)
    {
        if (actuatorArr[i]->isPoweredup())
            return true;
    }
    return false;
}

/**
 * Overloaded assignments
 */

//pre : none
//post : none
bool Robot::operator==(Robot &obj) {
    return moves == obj.moves;
}

//pre : none
//post : none
bool Robot::operator!=(Robot &obj) {
    return moves != obj.moves;
}

//pre : none
//post : none
bool Robot::operator>(Robot &obj) {
    return moves > obj.moves;
}

//pre : none
//post : none
bool Robot::operator<(Robot &obj) {
    return moves <obj.moves;
}

//pre : none
//post : none
bool Robot::operator>=(Robot &obj) {
    return moves >= obj.moves;
}

//pre : none
//post : none
bool Robot::operator<=(Robot &obj) {
    return moves <= obj.moves;
}

/**
 * Memory management stuff
 **/

//pre: initialized
//post: none
void Robot::Copy(const Robot& rbt)
{
    this->row = rbt.row;
    this->col = rbt.col;
    this->moves = rbt.moves;

    for (int i = 0; i < defaultGrid; i++)
    {
        for (int j = 0; j < defaultGrid; j++)
        {
            grid[i][j] = rbt.grid[i][j];
        }
    }

    actuatorRange = rbt.actuatorRange;

    for (int i = 0; i < actuatorRange; i++)
        actuatorArr[i] = rbt.actuatorArr[i];


    for (int i = 0 ; i < sensorRange; i++)
        sensorArr[i] = rbt.sensorArr[i];

}


//pre :none
//post : none
Robot::Robot(const Robot& rbt)
{
    Copy(rbt);
}

//pre: none
//post : none
Robot& Robot::operator= (const Robot& rbt)
{
    if (this != &rbt)
    {
        delete[]actuatorArr;
        delete[]sensorArr;
        Copy(rbt);
    }

    return *this;
}

//pre : none
//post : memory will be freed
Robot::~Robot()
{
    for (int i = 0; i < actuatorRange; i++)
        delete actuatorArr[i];

    for(int i = 0; i < sensorRange; i++)
        delete sensorArr[i];

    delete[]actuatorArr;
    delete[]sensorArr;
}


template <typename T>
void Robot::swap(T& lhs, T&rhs)
{
  T temp = lhs;
  lhs = rhs;
  rhs = temp;
}

//pre: none
//post : none
Robot::Robot(Robot &&obj) // can't get move semantic to work bug with swap can't figure out
{
  swap(row, obj.row);
  swap(col, obj.col);

  for (int i = 0; i < defaultGrid; i++)
    {
      for (int j = 0; j < defaultGrid; j++)
        {
          swap(grid[i][j], obj.grid[i][j]);
        }
    }

  swap(actuatorRange ,obj.actuatorRange);

  for (int i = 0; i < actuatorRange; i++)
    {
      swap(actuatorArr[i],obj.actuatorArr[i]);
    }

  for (int i = 0 ; i < sensorRange; i++)
    swap(sensorArr[i], obj.sensorArr[i]);
}

//pre: none
//post : none
Robot& Robot::operator= (Robot&& rbt)
{
  if (this != &rbt)
    {
      delete[]actuatorArr;
      delete[]sensorArr;

      swap(this->row, rbt.row);
      swap(this->col, rbt.col);

      for (int i = 0; i < defaultGrid; i++)
        {
          for (int j = 0; j < defaultGrid; j++)
            {
              swap(grid[i][j], rbt.grid[i][j]);
            }
        }

      swap(actuatorRange ,rbt.actuatorRange);

      for (int i = 0; i < actuatorRange; i++)
        {
          swap(actuatorArr[i],rbt.actuatorArr[i]);
        }

      for (int i = 0 ; i < sensorRange; i ++)
        swap(sensorArr[i], rbt.sensorArr[i]);
    }

  return *this;
}

/*
 * Implementation Invariants
 * direction only accepts strings could be changed to ints
 * actuator has no battery and state will always stay as true
 * sensor does have battery and will change to false if battery is 0% from move() and MoveOnce()
 * Has-a relationship with Sensor and HOlds-a relationship with Actuator
 * Parent of Rotatting robot and Tranrobot
 * Deep copying and move semantics is implemented
 */
