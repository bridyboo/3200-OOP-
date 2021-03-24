using System;

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

 /*
  * Class Invariants:
  * CONSTRUCTOR DEPENDENCY INJECTION for file
  * Move() isn't overriden no specific requirements 
  * carries dependency from Robot 
  */ 
public class TranRobot: Robot, ITranRobot
{
    private int additionalSensors = 3;
    //pre: file must exist
    //post : object initalized and with extra 3 sensors
    public TranRobot(string file) : base(file)
    {
        for (int i = 1; i <= additionalSensors; i++)
            sensorArr[i] = new Sensor(true);
    }

    //pre: actuator and direction must exist battery enooughg
    //post : robot will move 
    public void Down()
    {
        direction = "down";
        if (isValid(grid[row, col]))
            row = actuatorArr[1].moveForward(row, col);
    }
    //pre: actuator and direction must exist battery enooughg
    //post : robot will move 
    public void Left()
    {
        direction = "left";
        if (isValid(grid[row, col]))
            col = actuatorArr[2].moveForward(row, col);
    }
    //pre: actuator and direction must exist battery enooughg
    //post : robot will move 
    public void Right()
    {
        direction = "right";
        if (isValid(grid[row, col]))
            col = actuatorArr[3].moveForward(row, col);
    }
    //pre: actuator and direction must exist battery enooughg
    //post : robot will move 
    public override bool moveOne()
    {
        if (!actuatorPower())
            return false;

        direction = "up";
        if (isValid(grid[row, col]))
            row = actuatorArr[0].moveForward(row, col);
        return true;
    }

    //pre: actuator and direction must exist battery enooughg
    //post : robot will move till wall
    public override bool move()
    {
        return base.move();
    }
}

/**
 * Implementation Invariant:
 * Object is a descendant of robot
 * shares all overhead and dependencies
 * constructor uses dependency injection 
 * has 4 sensors and doesn't need to rotate to go to a specific location on grid therefore "direction" field
 *  never changes
 * Move() has no overidden function because no specification so it just deprecates from Robot() parent
 */ 