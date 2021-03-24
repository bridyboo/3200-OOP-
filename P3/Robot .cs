using System;

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
* Parent of Rotating robot and transRobot
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

/*
* Class Invariants:
* The number of initialized actuators determine its movement ability. 
* echoes functionality for sensor->isValid() and sensor->Recharge()
* Dependency injection on constructor for Grid.txt path
* Is parent of RotatingRobot and TranRobot
*/


public class Robot
{
    private const int defaultGrid = 11;
    private const int defaultActuatorCount = 4; 


    private int actuatorRange;
    private string path = @"C:\Users\Matthew Darmadi\source\repos\p3(3200rr)\p3(3200rr)\grid.txt";

    protected int[,] grid = new int[defaultGrid, defaultGrid];
    protected Actuator[] actuatorArr;
    protected Sensor[] sensorArr;
    protected string direction;
    protected int row;
    protected int col;

    //pre: file should contain a grid the same dimension as 
    //     defaultGrid.
    //post: object initialized and robot has data of the grid. Movement limits are determined
    //		depending on number of actuators
    public Robot(string file)
    {
        if (file == null) throw new ArgumentNullException("invalid file");

        actuatorRange = defaultActuatorCount;

        string text = System.IO.File.ReadAllText(path);
        
        string ss = text.Replace("\r", " ");
        ss = string.Join(" ", ss.Split(new char[] { ' ' }, StringSplitOptions.RemoveEmptyEntries));
        string[] arr = ss.Split(' ');

        int count = 0;
        for (int r = 0; r <= 10; r++)
        {
            for (int c = 0; c <= 10; c++)
            {
                grid[r, c] = Convert.ToInt32(arr[count]); ;
                count++;
            }
        }


        sensorArr = new Sensor[actuatorRange];
        actuatorArr = new Actuator[actuatorRange];
        string[] directions = new string[] {"up", "down", "left", "right"};

        for (int i = 0; i < actuatorRange; i++)
        {
            actuatorArr[i] = new Actuator(directions[i]);
        }

        sensorArr[0] = new Sensor(true); // initial forward sensor
        direction = "up";

        row = 5;
        col = 5;
    }

    //pre : path should only be 0 or 1 and appropriate sensor must exist
    //post : isValid could deplete sensor battery and change its state
    public bool isValid(int path)
    {
        if (direction == "up")
            return sensorArr[0].isValid(path);

        else if (direction == "down")
            return sensorArr[1].isValid(path);

        else if (direction == "left")
            return sensorArr[2].isValid(path);

        else
            return sensorArr[3].isValid(path);
    }

    //pre: actuator and corresponding direction must exist 
    //post : robot will move until it hits a wall
    public virtual bool move()
    {
        if (!actuatorPower())
            return false;

        if (direction == "up")
        {
            if (row == 0)
                return true;
            while (isValid(grid[row - 1, col]))
                row = actuatorArr[0].moveForward(row, col);
        }

        return true;
    }

    //pre: actuator and corresponding direction must exit
    //post : robot will move once
    public virtual bool moveOne()
    {
        if (!actuatorPower())
            return false;

        if (isValid(grid[row, col]))
        {
            if (direction == "up")
                row = actuatorArr[0].moveForward(row, col);
        }

        return true;
    }

    //pre: initialized correctly
    //post: battery will be 100% and state true
    public void hasPower()
    {
        for (int i = 0; i < sensorArr.Length; i++)
            sensorArr[i].recharge();
    }

    //pre: none
    //post :none
    public int getCol()
    {
        return col;
    }

    //pre: none
    //post : none
    public int getRow()
    {
        return row;
    }

    //pre : none
    //post : none
    protected bool actuatorPower()
    {
        for (int i = 0; i < actuatorRange; i++)
        {
            if (actuatorArr[i].isPoweredup())
                return true;
        }
        return false;
    }
}

/*
 * Implementation Invariants
 * direction only accepts strings could be changed to ints
 * actuator has no battery and state will always stay as true
 * sensor does have battery and will change to false if battery is 0% from move() and MoveOnce()
 * Has-a relationship with Sensor and HOlds-a relationship with Actuator
 * Parent of Rotatting robot and Tranrobot
 * 
 */
