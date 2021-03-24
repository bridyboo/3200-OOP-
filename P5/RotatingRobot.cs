using System;

/*
* Matthew Brian Darmadi
* 5/7/2020
* p3
*/

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

/*
    * Class Invariants:
    * file is a constructor dependency injection 
    * carries dependency from Robot parent 
    * is-a Robot 
    */


public class RotatingRobot : Robot, IRotRobot
{
    private int additionalSensors = 3;

    //pre: file needs to exist 
    //post: adds 3 new sensors
    public RotatingRobot(string file) : base(file)
    {
        for (int i = 1; i <= additionalSensors; i++)
            sensorArr[i] = new Sensor(true);
    }

    //pre: initialized properly
    //post: change direction clockwise
    public override void rotate()
    {
        if (direction == "up")
            direction = "right";

        else if (direction == "right")
            direction = "up";

        else if (direction == "down")
            direction = "left";
        else
            direction = "up";
    }

    //pre: actuator and direction for sensor must exist battery is enough
    //post : robot will move until wall
    public override bool move()
    {
        if (direction == "left")
        {
            while (isValid(grid[row, col - 1]))
                col = actuatorArr[2].moveForward(row, col);

            return true;
        }
        else if (direction == "right")
        {
            while (isValid(grid[row, col + 1]))
                col = actuatorArr[3].moveForward(row, col);

            return true;
        }

        return base.move();
    }

    //pre: actuator and direction must exist battery enooughg
    //post : robot will move 
    public override bool moveOne()
    {
        if (isValid(grid[row, col]))
        {
            if (direction == "down")
            {
                row = actuatorArr[1].moveForward(row, col);
                return true;
            }
            else if (direction == "left")
            {
                col = actuatorArr[2].moveForward(row, col);
                return true;
            }
            else if (direction == "right")
            {
                col = actuatorArr[3].moveForward(row, col);
                return true;
            }
        }

        return base.moveOne();
    }
}

/*
 * Impelemnentation Invariants:
 * Direction only rotates clockswise. 
 * this object is a descendant of Robot
 * shares all overhead and dependencies
 * has 4 sensors but doesn't have the functionality to go down as per requirement
 */
