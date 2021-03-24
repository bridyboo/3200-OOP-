using System;

/*
 * Matthew Brian Darmadi
 * 4/13/2020
 * p1
 * 
 */

/*
 * Class Overview : 
 * a driver class that runs the Sensor class 
 */

/*
 * Assumptions: 
 * -clients follow all pre-conditions
 * -nameArr names are filled 
 */

public class p1
{

    private const int arrSize = 10;
    private readonly static string[] nameArr = new string[]{ "brian", "matthew", "darmadi", "rachel", "grace" };

    public static void Main()
    {
        Sensor[] sensorArr = new Sensor[arrSize];
        initializeSensor(sensorArr);
        testIsValid(sensorArr);
        testRechargeAndFlipSwitch(sensorArr);
        testIsValid(sensorArr);

        Console.ReadLine();
    }

    public static void initializeSensor(Sensor[] sensorArr)
    {
        Console.WriteLine("--- Intializing Object ---");
        Random rnd = new Random();
        for (int i = 0; i < arrSize; i++)
        {
            int num = rnd.Next(1, 10);

            if (num <= 4)
                sensorArr[i] = new Sensor(true);

            else if (num > 4 && num <= 7)
                sensorArr[i] = new Sensor(false);

            else
                sensorArr[i] = new Sensor();
        }
        Console.WriteLine("--- Intialize Complete ---");
    }

    public static void testIsValid(Sensor[] sensArr)
    {
        Random rnd = new Random();
        Console.WriteLine("\n--- testing isValid() ---");
        
        for (int i = 0; i < arrSize; i++)
        {
            uint age = (uint)rnd.Next(1,100);
            int index = (int)age % 5;
            int reply = sensArr[i].isValid(nameArr[index], age);

            Console.WriteLine(nameArr[index] + validResponse(reply)); 
        }
        
    }

    public static void testRechargeAndFlipSwitch(Sensor[] sensArr)
    {
        Random rnd = new Random();
        Console.WriteLine("\n--- testing Recharge() ---");

        for (int i = 0; i < arrSize; i++)
        {
            sensArr[i].recharge();
            sensArr[i].flipSwitch();
        }
        Console.WriteLine("--- all fully charged and switch flipped");
    }

    private static string validResponse(int num)
    {
        if (num == 0)
            return " -- SCREEN OFF -- ";

        if (num == 1)
            return " Good luck for the next 10 minutes!!";

        if (num == 10)
            return " battery too low to function... please charge...";

        return " Bad luck :( but only for 10 minutes!";
    }
}

