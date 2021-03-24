using System;

/*
 * Class OVerview:
 * Submersible is a class that handles moving depth (moving from file to file). 
 * The class can only go up and down the level of depth but cannot actually read it,
 * it functions as a container for files and also an interator. 
 */ 

/*
 * Interface Invariants:
 * must conform to ISumbersible
 * is made with MI in mind
 */ 

/*
 * Class Invariants:
 * Constructor dependency injection of correct array of file names. 
 * All files are  expected to have a 11x11 grid inside (refer to grid.txt for example)
 */ 

public class Submersible : ISubmersible
{
    protected Actuator subActuator;

    protected string[] files;
    protected int depth;

    //pre: files must all exist and containt a 11x11 grid
    //post : object initialized with actuator
    public Submersible(string[] files)
    {
        for (int i = 0; i < files.Length; i++)
            if (files[i] == null) throw new ArgumentNullException("invalid file");

        this.files = files;

        subActuator = new Actuator("up");
        depth = 0; 
    }

    //pre: none
    //post : none
    public int getDepth()
    {
        return depth;
    }

    //pre: none
    //post: depth changed
    public string moveUp()
    {
        depth++;
        return files[depth];
    }

    //pre: none
    //post: depth changed
    public string moveDown()
    {
        if (depth == 0)
            return files[0];

        depth--;
        return files[depth];
    }

}

/*
 * Actuator is initialized in constructor but not used in the class
 * This is to fulfill requirements for assignment but I don't think for my design
 * the function of actuator is necessary. 
 */ 