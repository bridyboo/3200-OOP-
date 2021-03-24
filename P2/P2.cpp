/*
 * Matthew Brian Darmadi
 * 4/26/2020
 * p2
 */

/*
 * Class Overview:
*  driver class for Robot
 */

/*
 * Assumption: 
 * grid is a 11 x 11 matrix
 * robot starts from row 5 column 5
 * objects initialized properly
 * file exists in the same directoory and is a grid.txt (location of 0 1 doesn't matter)
 * make_unique doesn't exist in c++11 i used a function template from
 * "https://stackoverflow.com/questions/7038357/make-unique-and-perfect-forwarding"
 */

#include "actuator.h"
#include "robot.h"
#include "sensor.h"
#include "actuator.h"
#include "sensor.h"
#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include <memory>

using namespace std;

const int arrSize = 3;
const int lowest = 1;
const int highest = 5;
const int pinglim = (highest + lowest) +1;
const int def_direction = 4;
const string FILENAME = "grid.txt";

void testRobot(shared_ptr<Robot>& robot);
void initRobot(vector<shared_ptr<Robot>>& arr);
void testPassBy();
void testUnique(vector<unique_ptr<Robot>>& arr);

template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args)
{
  return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

int main()
{
  vector<shared_ptr<Robot>> arr;
  vector<unique_ptr<Robot>> uniqueArr;
  initRobot(arr);
  testPassBy();
  testUnique(uniqueArr);

  cin.get();
  return 0;
}

void testPassBy()
{
	cout << endl << "-----testing pass by value-----" << endl;
	shared_ptr<Robot> rob = make_shared<Robot>();
	cout << "we'll move object1 by one and pass by value, theoretically they should be the same" << endl;
	rob->MoveOne("up");
	cout << "object 1 | row : " << rob->getRow() << " col : " << rob->getCol() << endl;
	cout << "now lets pass by value . .  . " << endl;
	shared_ptr<Robot> rob2 = rob;
	cout << "object 2 | row : " << rob2->getRow() << " col : " << rob2->getCol() << endl;

}

void testUnique(vector<unique_ptr<Robot>>& arr)
{
	cout << "---Initialize unique_ptr Robot---" << endl;

	srand((unsigned int)time(NULL));

	for (int i = 0; i < arrSize; i++)
	{
		unsigned int num = lowest + (rand() % pinglim);
		unique_ptr<Robot> robot = make_unique<Robot>(num, def_direction, FILENAME);
		arr.push_back(move(robot));
	}

	cout << "initialized " << arrSize << " unique_ptr Complete" << endl;

	
	cout << endl << "[][]][] testing UNIQUE robot number [][][]" << endl;
	arr[0]->MoveOne("up");

	cout << endl << "--- testing move(up) ---" << endl << endl;
	cout << "new row " << arr[0]->getRow() << " new col " << arr[0]->getCol() << endl;
}

void initRobot(vector<shared_ptr<Robot>>& arr)
{
	cout << "Initialize Robot" << endl;

	srand((unsigned int)time(NULL));

	for (int i = 0; i < arrSize; i++)
	{
		unsigned int num = lowest + (rand() % pinglim);
		shared_ptr<Robot> robot = make_shared<Robot>(num, def_direction, FILENAME);
		arr.push_back(move(robot));
	}
	cout << "initialize Complete" << endl;

	for (int i = 0; i < arrSize; i++)
	{
		cout << endl << "[][]][] testing robot number " << i << " [][][]" << endl;
		testRobot(arr[i]);
	}
}


void testRobot(shared_ptr<Robot>& robot)
{
	srand((unsigned int)time(NULL));
	int num = rand() % 3;

	cout <<endl <<  "--- testing move one ---" << endl;
	cout << "initial row " << robot->getRow() << " initial col " << robot->getCol() << endl;

	switch (num)
	{
	case 0:
		robot->MoveOne("up");
		cout << "moving up" << endl;
		break;
	case 1:
		robot->MoveOne("down");
		cout << "moving down" << endl;
		break;
	case 2:
		robot->MoveOne("left");
		cout << "moving left" << endl;
		break;
	case 3:
		robot->MoveOne("right");
		cout << "moving right" << endl;
		break;
	}

	cout << "new row : " << robot->getRow() << " new Col : " << robot->getCol() << endl;
	
	cout << endl<< "--- testing move() ---" << endl << endl;
	cout << "initial row " << robot->getRow() << " initial col " << robot->getCol() << endl;

	num = rand() % 3;
	switch (num)
	{
	case 0:
		robot->Move("up");
		cout << "moving up" << endl;
		break;
	case 1:
		robot->Move("down");
		cout << "moving down" << endl;
		break;
	case 2:
		robot->Move("left");
		cout << "moving left" << endl;
		break;
	case 3:
		robot->Move("right");
		cout << "moving right" << endl;
		break;
	}

	cout << "new row : " << robot->getRow() << " new Col : " << robot->getCol() << endl;

}
