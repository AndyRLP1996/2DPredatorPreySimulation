DISCLAIMER:   THIS CODE WAS ORIGINALLY AUTHORED BY ANDREW PARKHURST
              AS PART OF A HOMEWORK ASSIGNMENT FOR ENSC 251 AT SFU IN FALL 2017.
              PLEASE DO NOT MODIFY OR COPY THIS CODE            

NOTE:         SOME CHANGES HAVE SINCE THE ASSIGNMENT TO MAKE THE CODE CLEANER AND EASIER TO READ AND USE OVERALL
              INCLUDING REMOVING SOME COMMENTS PRESENT FOR THE MARKERS AND SEPERATING THE CODE INTO MULTIPLE FILES
              AND MAKING CHANGES TO THE MAKEFILE
              THE OVERALL FUNCTIONALITY OF THE CODE HAS NOT BEEN CHANGED IN ANY WAY
              THE PROGRAM WAS COMPILED USING GCC v5.4 AND REQUIRES THE C++11 STANDARD TO COMPILE

Use & Function:
    To use the program, run it from the terminal (or cmd), enter the desired number of cycles you would like to run,
    Then decide whether you would  like the program to wait for a key press between each cycle.
    To exit the program: Complete the number of cycles entered (10 by default) or close the cmd or terminal
    This program was written to simulate a "basic" predator prey scenario.
        The scenario runs on a basic 2D landscape divided into 20 "tiles"
        Only 1 creature can occupy a tile at a time
        The program starts with 5 predators (referred to in code as DoodleBugs),
        And 100 prey (referred to in the code as ants)
        The DoodleBugs are represented by D and the Ants by A
        The Ants will breed (on their own) if not eaten within a certain number of turns
        The DoodleBugs will breed (on their own) if they have not died of starvation within a certain number of turns
        The Doodlebugs must eat Ants in order to survive 
            (the number of turns to breed is greater than the amount they can go without food for)
        Each cycle, the doodlebugs will prioritize "eating"
            if an adjacent tile contains an ant, they will move to that one
            otherwise they will move to a random unoccupied tile
        The ants will only move to unoccupied tiles (chosen randomly)
