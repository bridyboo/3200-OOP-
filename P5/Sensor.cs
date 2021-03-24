using System;
using System.Threading;

/*
 * Matthew Brian Darmadi
 * 4/13/2020
 * p1
 */

/*
* Class Overview :
* Sensor is a class that senses. Initially it starts with a full battery, and
* reduces by flat linear percent down. When the battery is below or equal to 0% it will automatically turn off and you won't be
* able to query it untill it's charged. It also won't be query-able when it's low on battery (10%).
*
* recharge will always charge to 100% because we're in the future and it will automatically set state
* true
*/



 /*
  * Class Invariants:
  * when battery_level is < 10% you can't use isValid() until recharge()
  * when state is false you can't use isValid() until state is true
  * state and battery_level directly effects the ability to use isValid()
  * when battery is <=0% you can't flipSwitch() must recharge()
  */

/*
* Interface Invariants:
* is in a "Robot HAS-A Sensor" relationship
* isValid will involutarily switch state to false, when battery is <= 0
* recharge() is the only way to turn a false state to true
* recharge() will always charge battery to 100% and automatically switch state to true
*/

public class Sensor
{

    private const int DEFAULT_BATTERY_LEVEL = 100;
    private const int MAX_BATTERY_DRAIN = 40;
    private bool state;
    private int battery_level;
    private int rate;
    //pre : none
    //post : sensor will be initialized and state will be set according to user input
    public Sensor(bool state)
    {
        Random rnd = new Random();
        rate = rnd.Next(1, MAX_BATTERY_DRAIN);
        this.state = state;
        battery_level = DEFAULT_BATTERY_LEVEL;
    }

    //pre : age has to be larger than 0 
    //post : if battery_level is <= 0 it will turn state false
    // p.s. if developer check implementation Invariants for details
    public bool isValid(int path)
    {
        battery_level -= rate;

        if (battery_level <= 0)
            state = false;

        if (state == false) return false;
        else if (battery_level < 10) return false;
        else if (state == true && battery_level < 10) return false;

        if (path == 0)
            return false;

        return true;
    }
    
    //pre : none
    //post : none
    public int getBattery_level()
    {
        return battery_level;
    }

    //pre : none
    //post : battery will be at 100%
    public bool recharge()
    {
        battery_level = DEFAULT_BATTERY_LEVEL;
        Thread.Sleep(2);
        state = true;
        return true;
    }

  
}

/*
 * Implementation Invariants
 * isValid can change State if battery_level is <= 0.
 * battery_state linearly reduces by "rate" every time isValid() is called
 * recharge() always fills to 100% no matter previous percentage
 * recharge() always flips the state to true
 * only reduce battery from isValid()
 */
