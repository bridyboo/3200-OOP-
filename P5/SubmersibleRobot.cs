using System;

/*
 * Class OVerview: 
 * Submersible robot is a  result of pseudo multiple inheritance with composition 
 * between 2 interfaces Isubmersible and IRobot. It is able to do anything a robot can 
 * do and also go into depths(different files) 
 */

 /*
  * Interface Invariants: 
  * is-a IRobot is-a ISubmersible. 
  * forces implementation of Interface methods and must take ownership 
  * and keep track  of each object's status. 
  * Source class (Robot) has been made more complex because of MI 
  * for robotType: 
  * 0 -> Robot
  * 1 -> RotatingRobot
  * 2 -> TranRobot
  */ 

/*
 * Class Invariants:
 * string[] of  file names is a constructor dependency injection 
 * int robotType relies on client fulfilling contract 
 * subObject specific functions will only work properly if initially initialized properly
 * 
 * Move() is unique for submersibleRobot when hit a wall on one depth will go to another
 * to depth to find a new path. It will always call Move() twice at most unless if 
 * reach edge of depth.
 * 
 * MoveDown() changes the depth to go one level of text file down also changes the Robot's 
 * position etc. 
 * 
 * MoveUp() changes the depth to go one level of text file up also changes the Robot 
 * position
 */ 

class SubmersibleRobot : IRobot,ISubmersible,ITranRobot,IRotRobot
{
    protected Robot robot;
    protected readonly Submersible submersible;

    protected const int defaultDepth = 0;

    protected string[] files;
    protected string direction;

    //pre: files all exist and are all 11X11 in size. there are only 3 robot types
    //post : object initialized successfully 
    public SubmersibleRobot(string[] files, int robotType)
    {
        this.files = files;
        submersible = new Submersible(files);

        switch (robotType)
        {
            case 0:
                robot = new Robot(files[defaultDepth]);
                break;
            case 1:
                robot = new RotatingRobot(files[defaultDepth]);
                break;
            case 2:
                robot = new TranRobot(files[defaultDepth]);
                break;
        }

        direction = "up";
    }

    //ppre : none
    //post : none
    public bool isValid(int path)
    {
        return robot.isValid(path);
    }

    //pre: initialized to specific subObjects for proper functionality
    //post: direction will change (only for RotateRobot)
    public void rotate()
    {
        robot.rotate();
    }

    //pre: initialized to specific subObjects for proper functionality
    //post : robot will move "left" direction (only for TranRobot)
    public void Left()
    {
        robot.Left();
    }

    //pre: initialized to specific subObjects for proper functionality
    //post: robot will move "right" direction  (only for TranRobot)
    public void Right()
    {
        robot.Right();
    }

    //pre: initialized to specific subObjects for proper functionality
    //post: robot will move "down" direction (only for TranRobot)
    public void Down()
    {
        robot.Down();
    }

    //pre: none
    //post: robot and depth will move battery will stay on because charged every depth
    public virtual bool move()
    {
        robot.move();

        if (isEdge())
            return false;

        if (getDepth() < files.Length / 2) //if current depth is less than half go up
        {
            while (!robot.isValid(robot.checkGrid(robot.getRow(), robot.getCol())))
            {
                robot.hasPower();
                moveUp(); //moves the depth and grid of robot

                if (isEdge()) //leave depth traversal if edge of depth
                    return false;
            }
        }

        else
        {
            while (!robot.isValid(robot.checkGrid(robot.getRow(), robot.getCol())))
            {
                robot.hasPower();
                moveDown(); //moves depth and robo grid

                if (isEdge()) //leave depth traversal if edge of depth
                    return false;
            }
        }

        robot.move();
        return true;
    }

    //pre: none
    //post: none
    private bool isEdge()
    {
        if(getDepth() == files.Length || getDepth() == 0)
            return true;

        return false;
    }
    //pre: none
    //post : robot will move
    public bool moveOne()
    {
        return robot.moveOne();
    }

    //pre : none
    //post: depth is changed grid of robot is also changed
    public string moveUp()
    {
        string ans = submersible.moveUp();
        robot.changeGrid(files[getDepth()]);
        return ans;
    }

    //pre : none
    //post: depth is changed grid of robot changed
    public string moveDown()
    {
        string ans = submersible.moveDown();
        robot.changeGrid(files[getDepth()]);
        return ans;
    }

    //pre: none
    //post : none
    public int getDepth()
    {
        return submersible.getDepth();
    }
}

/*
 * MI is not supported for c# so we rely on composition with multiple interfaces
 * MI is normally not a good idea since abstraction for source (base class) is sacrificed
 * MI also makes the base class super complex 
 * 
 * for Move() maybe recursion is a better implementation than what I have right now
 * MoveUp() changes depth and file and grid of robot. 
 * so does MoveDown()s
 */ 