using System;

/*
 * Matthew brian darmadi 
 * 5/8/2020
 * p3
 */ 

/*
 * Class overview:
 * Driver clas for Robot and descendants
 */    

/*
 * Assumption :
 * grid is a 11 x 11 matrix 
 * robot starts at 5 , 5 row column 
 * file exist in same directory or path is set correctly
 * client follows precondition 
 */ 

class P3
{
    const int arrSize = 5;
    const int lowest = 0;
    const int highest = 5;
    const int types = 3;
    const int pinglim = (highest + lowest) + 1;
    const int def_direction = 4;
    const string FILENAME = "grid.txt";


    public static void Main()
    {
        Robot[] robotArr = new Robot[arrSize];
        initRobot(robotArr, FILENAME);
        Console.ReadLine();
    }

    public static void initRobot(Robot[] robotArr, string FILENAME)
    {
        Random rnd = new Random();
        int num = rnd.Next(lowest, types);
        Console.WriteLine("--- Initialize Robots ---");
        for (int i = 0; i < robotArr.Length; i++)
        { 
            switch(num)
            {
                case 0:
                    robotArr[i] = new Robot(FILENAME);
                    break;

                case 1:
                    robotArr[i] = new RotatingRobot(FILENAME);
                    break;

                case 2:
                    robotArr[i] = new TranRobot(FILENAME);
                    break;
            }
            num = rnd.Next(lowest, types);
        }

        Console.WriteLine("--- Initialize Complete ---");

        for (int i = 0; i < robotArr.Length; i++)
        {
            Console.WriteLine("\n [][] testing " + robotArr[i].GetType() + " no. " + i +" [][]");

            Console.WriteLine("initial Row " + robotArr[i].getRow() + " | Initial Col " + robotArr[i].getCol());

            if (robotArr[i].GetType() == typeof(RotatingRobot))
                testRotateRobot((RotatingRobot)robotArr[i]);
            else if (robotArr[i].GetType() == typeof(TranRobot))
                testTranRobot((TranRobot)robotArr[i]);

            testRobotDefault(robotArr[i]);
        }
    }

    public static void testRobotDefault(Robot robot)
    { 

        Console.WriteLine(" --- testing moveOne ---");
        Console.WriteLine("initial Row " + robot.getRow() + " | Initial Col " + robot.getCol());

        robot.moveOne();
        Console.WriteLine("new Row : " + robot.getRow() + "   | new col: " + robot.getCol());

        Console.WriteLine(" --- testing move ---");
        Console.WriteLine("initial Row " + robot.getRow() + " | Initial Col " + robot.getCol());

        robot.move();
        Console.WriteLine("new Row : " + robot.getRow() + "   | new col: " + robot.getCol());

    }

    
    public static void testRotateRobot(RotatingRobot robot)
    {
        Random rnd = new Random();
        int num = rnd.Next(lowest, types);

        for (int i = 0; i < num; i++)
        {
            robot.rotate();
            Console.Write("rotating");
        }
        robot.move();
        Console.WriteLine("new Row : " + robot.getRow() + "   | new col: " + robot.getCol());

    }

    public static void testTranRobot(TranRobot robot)
    {
        Random rnd = new Random();
        int num = rnd.Next(lowest, types);

        switch (num)
        {
            case 0:
                robot.moveOne();
                Console.WriteLine("moving up");
                break;

            case 1:
                robot.Down();
                Console.WriteLine("moving down");
                break;

            case 2:
                robot.Left();
                Console.WriteLine("moving left");
                break;

            case 3:
                robot.Right();
                Console.WriteLine("moving right");
                break;
        }
        robot.move();
        Console.WriteLine("new Row : " + robot.getRow() + "   | new col: " + robot.getCol());
    }
}

