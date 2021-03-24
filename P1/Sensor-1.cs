using System;
using System.Threading;

/*
 * Matthew Brian Darmadi
 * 4/13/2020
 * p1
 */

/*
 * Class Overview : 
 * Sensor is a class that senses whether or not you're going to have good luck or 
 * bad luck for the next 10 minutes. By passing in your name and age, it will be able to 
 * predict with an accurate rate how lucky you're going to be. 
 * 
 * When the battery is below or equal to 0% it will automatically turn off and you won't be 
 * able to query it untill it's charged. It also won't be query-able when it's low on battery (10%).
 * 
 * to turn on and off the Sensor just flip the switch
 * sensor state = false -> off | true -> on
 * 
 * recharge will always charge to 100% because we're in the future
 * 
 * /

 /*
  * Class Invariants:
  * when battery_level is < 10% you can't use isValid() until recharge()
  * when state is false you can't use isValid() until state is true
  * state and battery_level directly effects the ability to use isValid()
  * when battery is <=0% you can't flipSwitch() must recharge()
  */

/*
 * Interface Invariants:
 * isValid will involutarily switch state to false, when battery is <= 0
 * flipSwitch is the only way to turn a false state to true
 * flipSwitch() will not work if battery_level is <= 0
 */

public class Sensor
{

    private const int DEFAULT_BATTERY_LEVEL = 100;

    private bool state;
    private int battery_level;
    private int rate;

    //pre : none
    //post : sensor will be initialized and state will be set according to user input
    public Sensor(bool state)
    {
        Random rnd = new Random();
        rate = rnd.Next(1,100);
        this.state = state;
        battery_level = DEFAULT_BATTERY_LEVEL;
    }

    //pre : none
    //post : sensor will be initialized with state off.
    public Sensor()
    {
        state = false;
        battery_level = DEFAULT_BATTERY_LEVEL;
        Random rnd = new Random();
        rate = rnd.Next(1, 99);
    }

    //pre : age has to be larger than 0 
    //post : if battery_level is <= 0 it will turn state false
    // p.s. if developer check implementation Invariants for details
    public int isValid(string name, uint age)
    {
        battery_level -= rate;

        if (battery_level <= 0)
            state = false;

        if (state == false)
            return 0;

        else if (battery_level < 10)
            return 10;

        else if (state == true && battery_level < 10)
            return 10;


        Random rnd = new Random();

        int luckCoefficient = name.Length + (int)age + rnd.Next(1, 50);

        if (luckCoefficient % rnd.Next(1, 8) == 0)
            return 1;

        return -1;
    }

   //pre : none
   //post : battery will be at 100%
    public bool recharge()
    {
        battery_level = DEFAULT_BATTERY_LEVEL;
        return true;
    }

    //pre : none
    //post : state will always negate itself. from off to on and on to off
    //       - if battery is <= 0 no change in state should be false
    public bool flipSwitch()
    {
        if (battery_level <= 0)
            return false;
      
        state = !state;
        Thread.Sleep(2);
        return state;
    }
    
   
}

/*
 * Implementation Invariants
 * -isValid() returns an int. 
 * - 0 -> power off
 * - 1 -> good luck 
 * - '-1' -> bad luck
 * - 10 -> battery too low
 * 
 * isValid functionality is abitrary luck cannot be calculated.
 * isValid can change State if battery_level is <= 0.
 * battery_state linearly reduces by "rate" every time isValid() is called
 * recharge() always fills to 100% no matter previous percentage
 * flipSwitch() won't switch states when battery_level is <= 0
 * only reduce battery from isValid()
 */ 