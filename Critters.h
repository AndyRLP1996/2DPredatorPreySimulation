//DISCLAIMER:   THIS CODE WAS ORIGINALLY AUTHORED BY ANDREW PARKHURST
//              AS PART OF A HOMEWORK ASSIGNMENT FOR ENSC 251 AT SFU IN FALL 2017.
//              PLEASE DO NOT MODIFY OR COPY THIS CODE            
//
//NOTE:         SOME CHANGES HAVE SINCE THE ASSIGNMENT TO MAKE THE CODE CLEANER AND EASIER TO READ OVERALL
//              INCLUDING REMOVING SOME COMMENTS PRESENT FOR THE MARKERS AND SEPERATING THE CODE INTO MULTIPLE FILES
//              AND MAKING CHANGES TO THE MAKEFILE
//              THE OVERALL FUNCTIONALITY OF THE CODE HAS NOT BEEN CHANGED IN ANY WAY

#include <iostream>
#include <cstdlib>
#include <ctime>
#define CRITTERS_H

using namespace std;

class Organism //parent class for both ants and doodlebugs
{
    public:
    Organism();
    
    int getTurn();

    int changeTurn(int temp);

    virtual int getLife();

    virtual int getDeath();

    virtual int moveOrganism(int up1, int down1, int left1, int right1);//check for other Organism present handled externally

    virtual void feed();

    int death;//count for starving
    int life;//count for breeding
    private:
    int turnTaken;//set to 0 at the end of each cycle, becomes 1 if bug has taken its turn moving
};

class DoodleBug : public Organism //class for doodlebug
{
    public:
    int getDeath();//removal of Organism handled externally

    void feed();//called if Doodle gets a meal

    int getLife();//spawning done outside of class

    int moveOrganism(int up1, int down1, int left1, int right1);//checks for Ants, Resets death timer if fed and returns a number between 0 and 4
};

class Ant : public Organism //class for ant
{
    public:
    int getLife();//spawning done outside of class

    int moveOrganism(int up1, int down1, int left1, int right1);//returns 0 if unable to move in chosen direction, otherwise returns a number between 1 and 4
};