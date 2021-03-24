#include "robot.h"

/*
* Class Invariants:
* The number of initialized actuators determine its movement ability. 
* 1 actuator -> up
* 2 actuators -> up, down
* 3 actuators -> up, down, left
* 4 actuators -> up,down, left,right
*
* echoes functionality for sensor->isValid() and sensor->Recharge()
*/

//pre: rate cannot be negative, file should contain a grid the same dimension as 
//     defaultGrid.
//post: object initialized and robot has data of the grid. Movement limits are determined
//		depending on number of actuators

using namespace std;

Robot::Robot(int rate, int actuatorNum, string file)
{
	if (actuatorNum > 4)
		actuatorNum = 4;

	row = 5;
	col = 5; //starting location is 5,5

	actuatorRange = actuatorNum;

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

	sensor = new Sensor(true, rate);

	actuatorArr = new Actuator*[actuatorRange];
	string directions[4] = { "up", "down", "left", "right" };

	for (int i = 0; i < actuatorNum; i++)
	{
		actuatorArr[i] = new Actuator(directions[i]);
	}
}

//pre : path should only be 0 or 1
//post : isValid could deplete sensor battery
bool Robot::isValid(int path)
{
	return sensor->isValid(path);
}

//pre: actuator and corresponding direction must exist 
//post : robot will move until it hits a wall
bool Robot::Move(string direction)
{
	
	if (direction == "up")
	{
		while (isValid(grid[row-1][col]))
			row = actuatorArr[0]->MoveForward(row, col, direction);
	}
	else if (direction == "down")
	{
		while (isValid(grid[row+1][col]))
			row = actuatorArr[1]->MoveForward(row, col, direction);
	}
	else if (direction == "left")
	{
		while (isValid(grid[row][col-1]))
			col = actuatorArr[2]->MoveForward(row, col, direction);
	}
	else if (direction == "right")
	{
		while (isValid(grid[row][col+1]))
			col = actuatorArr[3]->MoveForward(row, col, direction);
	}

	return true;
}

//pre: actuator and corresponding direction must exit
//post : robot will move once
bool Robot::MoveOne(string direction)
{
	if(isValid(grid[row][col]))
	{
		if (direction == "up")
			row = actuatorArr[0]->MoveForward(row, col, direction);
		else if (direction == "down")
			row = actuatorArr[1]->MoveForward(row, col, direction);
		else if (direction == "left")
			col = actuatorArr[2]->MoveForward(row, col, direction);
		else if (direction == "right")
			col = actuatorArr[3]->MoveForward(row, col, direction);

	}

	return true;
}

//pre: initialized correctly
//post: battery will be 100% and state true 
bool Robot::hasPower()
{
	sensor->recharge();
	return true;
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

//pre: initialized
//post: none
void Robot::Copy(const Robot& rbt)
{
	this->row = rbt.row;
	this->col = rbt.col;

	for (int i = 0; i < defaultGrid; i++)
	{
		for (int j = 0; j < defaultGrid; j++)
		{
			grid[i][j] = rbt.grid[i][j];
		}
	}

	actuatorRange = rbt.actuatorRange;

	for (int i = 0; i < actuatorRange; i++)
	{
		actuatorArr[i] = rbt.actuatorArr[i];
	}

	sensor = rbt.sensor;
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
		delete (sensor);
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

	delete[]actuatorArr;
    delete (sensor);
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
Robot::Robot(const Robot &&obj) // can't get move semantic to work bug with swap can't figure out
{
	//swap(this->row, obj.row);
	//swap(this->col, rbt.col);

	for (int i = 0; i < defaultGrid; i++)
	{
		for (int j = 0; j < defaultGrid; j++)
		{
			//swap(grid[i][j], obj.grid[i][j]);
		}
	}

	//swap(actuatorRange ,obj.actuatorRange);

	for (int i = 0; i < defaultGrid; i++)
	{
		//swap(actuatorArr[i],obj.actuatorArr[i]);
	}

	//swap(sensor ,obj.sensor);
}

//pre: none
//post : none
Robot& Robot::operator= (const Robot&& rbt)
{
	if (this != &rbt)
	{
		delete[]actuatorArr;
		delete (sensor);
		
		//swap(this->row, obj.row);
	//swap(this->col, rbt.col);

		for (int i = 0; i < defaultGrid; i++)
		{
			for (int j = 0; j < defaultGrid; j++)
			{
				//swap(grid[i][j], obj.grid[i][j]);
			}
		}

		//swap(actuatorRange ,obj.actuatorRange);

		for (int i = 0; i < actuatorRange; i++)
		{
			//swap(actuatorArr[i],obj.actuatorArr[i]);
		}

		//swap(sensor ,obj.sensor);
	}

	return *this;
}

/*
 * Implementation Invariants
 * direction only accepts strings could be changed to ints
 * actuator has no battery and state will always stay as true
 * sensor does have battery and will change to false if battery is 0% from move() and MoveOnce()
 * Has-a relationship with Sensor and HOlds-a relationship with Actuator
 */
