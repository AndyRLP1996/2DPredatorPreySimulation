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
#include "Critters.h"

using namespace std;

//Organism Functions
    Organism::Organism()
    {
        turnTaken=0;
        death=0;
        life=0;
    }

    int Organism::getTurn()
    {
        return turnTaken;
    }
    int Organism::changeTurn(int temp)
    {
        turnTaken=temp;
    }
    int Organism::getLife()
    {
    }
    int Organism::getDeath()
    {
    }
    int Organism::moveOrganism(int up1, int down1, int left1, int right1)//check for other Organism present handled externally
    {
    }
    void Organism::feed()
    {
    }

//DoodleBug Functions
    int DoodleBug::getDeath()//removal of Organism handled externally
    {
        death++;
        return death;
    }
    void DoodleBug::feed()//called if Doodle gets a meal
    {
        death=0;
    }
    int DoodleBug::getLife()//spawning done outside of class
    {
        int temp;
        life++;
        temp=life;
        if(life>=8)
        {
            life=0;
        }
        return temp;
    }
    int DoodleBug::moveOrganism(int up1, int down1, int left1, int right1)//checks for Ants, Resets death timer if fed and returns a number between 0 and 4
    {
        int temp;
        if(up1==65)
        {
            temp=1;
            feed();
        }
        else if(right1==65)
        {
            temp=4;
            feed();
        }
        else if(down1==65)
        {
            temp=2;
            feed();
        }
        else if(left1==65)
        {
            temp=3;
            feed();
        }
        else
        {
            temp=rand()%4;
            temp=temp+1;
            if(temp==1&&up1!=46)
            {
                temp=0;
            }
            if(temp==2&&down1!=46)
            {
                temp=0;
            }
            if(temp==3&&left1!=46)
            {
                temp=0;
            }
            if(temp==4&&right1!=46)
            {
                temp=0;
            }
        }
        return temp;
    }


//Ant Functions
    int Ant::getLife()//spawning done outside of class
    {
        int temp;
        life++;
        temp=life;
        if(life>=3)
        {
            life=0;
        }
        return temp;
    }
    int Ant::moveOrganism(int up1, int down1, int left1, int right1)//returns 0 if unable to move in chosen direction, otherwise returns a number between 1 and 4
    {
        int temp;
        temp=rand()%4;
        temp++;
        if(temp==1&&up1!=46)
        {
            temp=0;
        }
        if(temp==2&&down1!=46)
        {
            temp=0;
        }
        if(temp==3&&left1!=46)
        {
            temp=0;
        }
        if(temp==4&&right1!=46)
        {
            temp=0;
        }
        return temp;
    }