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

struct tile //structure for array used to simulate environment. 
//contains the type of bug in that tile and the pointer to that bug's object
{
    int Organismtype;
    Organism* link;
};

typedef Organism* OrganismPtr;

void printArray(tile enviro[20][20]); //prints the array that simulates the environment
int moveDoodleBugs(int dooCount,tile enviro[20][20]);//takes the current number of doodlebugs and the array
//of structures as input, returns the updated count of doodlebugs.
//moves each doodlebug to the location of an ant if possible,
//otherwise moves to a random spot. Checks if doodle has been alive for 8 cycles since last breeding and spawns new doodle if so. 
//Checks if doodle has gone 3 cycles without eating and deletes bugs that starve.
int moveAnts(int AntCount,tile enviro[20][20]);//moves ants to empty spaces if possible, 
//breeds ants that have survived 3 cycles
void turnReset(tile enviro[20][20]);//sets the turntaken variable for each doodle and ant in the array to 0

int main()
{
    tile enviro[20][20];//initialize environment
    int timeCount;
    int AntCount;
    int dooCount;
    srand(time(NULL));
    AntCount=0;
    dooCount=0;
    timeCount=0;
    OrganismPtr dooTemp, AntTemp, linker;
    for(int i=0;i<20;i++)
    {
        for(int j=0;j<20;j++)
        {
            enviro[i][j]={46,NULL};
        }
    }//populate environment with empty tiles
    for(int k=0;k<5;k++)//generate 5 doodles and add them to the array in random locations
    {
        dooTemp=new DoodleBug();
        int tempx;
        int tempy;
        tempx=rand()%20;
        tempy=rand()%20;
        while(enviro[tempx][tempy].Organismtype==68)
        {
            tempx=rand()%20;
            tempy=rand()%20;
        }
        enviro[tempx][tempy].link=dooTemp;
        enviro[tempx][tempy].Organismtype=68;
        dooCount=k+1;
    }
    for(int k=0;k<100;k++)//generate 100 ants and add them to the array in random unfilled locations
    {
        AntTemp=new Ant();
        int tempx, tempy;
        tempx=rand()%20;
        tempy=rand()%20;
        while(enviro[tempx][tempy].Organismtype==68||enviro[tempx][tempy].Organismtype==65)
        {
            tempx=rand()%20;
            tempy=rand()%20;
        }
        enviro[tempx][tempy].link=AntTemp;
        enviro[tempx][tempy].Organismtype=65;
        AntCount=k+1;
    }
    printArray(enviro);//prints the stored array
    cout<<"the number of cycles that has occured is: "<<timeCount<<endl;
    timeCount++;
    cout<<"the number of DoodleBugs is: "<<dooCount<<endl;
    cout<<"the number of Ants is: "<<AntCount<<endl<<endl;
    int z;
    z=0;
    while(z==0)
    {
        dooCount=moveDoodleBugs(dooCount,enviro);//doodles move first
        AntCount=moveAnts(AntCount,enviro);//ants move second
        turnReset(enviro);//each bug has turn taken reset
        printArray(enviro);
        cout<<"the number of cycles that has occured is: "<<timeCount<<endl;
        timeCount++;
        cout<<"the number of DoodleBugs is: "<<dooCount<<endl;
        cout<<"the number of Ants is: "<<AntCount<<endl<<endl;
        cin.ignore();
    }
}

void printArray(tile enviro[20][20])
{
    for(int j=0;j<20;j++)
    {
        for(int i=0;i<20;i++)
        {
            cout<<(char)enviro[i][j].Organismtype;
        }
        cout<<endl;
    }
}

int moveDoodleBugs(int dooCount,tile enviro[20][20])
{
    OrganismPtr dooTemp, discard, baby;
    int x;//x coordinate in array
    int y;//y coordinate in array
    int up1;//bug type for tile above
    int down1;//bug type for tile below
    int left1;//bug type for tile to the left
    int right1;//bug type for tile to the right
    int temp;//stores choice of direction bug moves in. 0 if no move, 1 if up, 2 if down, 3 if left, 4 if right
    int death;//counts number of turns since bug last ate
    int life;//counts number of turns since bug last bred
    int fed;//temporarily stores if an ant was eaten
    x=0;
    y=0;
    for(int i=0;i<dooCount;i++)
    {
        x=0;
        y=0;
        for(y=0;y<20;y++)
        {
            for(x=0;x<20;x++)
            {
                dooTemp=enviro[x][y].link;
                if(enviro[x][y].Organismtype==68&&dooTemp->getTurn()==0)
                {
                    dooTemp->changeTurn(1);
                    up1=enviro[x][y-1].Organismtype;
                    down1=enviro[x][y+1].Organismtype;
                    left1=enviro[x-1][y].Organismtype;
                    right1=enviro[x+1][y].Organismtype;
                    if(y==0)
                    {
                        up1=0;
                    }
                    if(y==19)
                    {
                        down1=0;
                    }
                    if(x==0)
                    {
                        left1=0;
                    }
                    if(x==19)
                    {
                        right1=0;
                    }
                    temp=dooTemp->moveOrganism(up1, down1, left1, right1);
                    if(temp==1)
                    {
                        discard=enviro[x][y-1].link;
                        enviro[x][y-1].link=dooTemp;
                        enviro[x][y].link=NULL;
                        fed=enviro[x][y-1].Organismtype;
                        if(discard!=NULL)
                        {
                            delete discard;
                        }
                        enviro[x][y-1].Organismtype=68;
                        enviro[x][y].Organismtype=46;
                        if(fed==65)
                        {
                            dooTemp->feed();
                        }
                        life=dooTemp->getLife();
                        if(life>=8)
                        {
                            baby=new DoodleBug;
                            int tempx;
                            int tempy;
                            tempx=rand()%20;
                            tempy=rand()%20;
                            while(enviro[tempx][tempy].Organismtype==68||enviro[tempx][tempy].Organismtype==65)
                            {
                                tempx=rand()%20;
                                tempy=rand()%20;
                            }
                            enviro[tempx][tempy].link=baby;
                            enviro[tempx][tempy].Organismtype=68;
                            dooCount++;
                        }
                        death=dooTemp->getDeath();
                        if(death>3)
                        {
                            enviro[x][y-1].link=NULL;
                            delete dooTemp;
                            enviro[x][y-1].Organismtype=46;
                            dooCount=dooCount-1;
                        }
                    }
                    if(temp==2)
                    {
                        discard=enviro[x][y+1].link;
                        enviro[x][y+1].link=dooTemp;
                        enviro[x][y].link=NULL;
                        fed=enviro[x][y+1].Organismtype;
                        if(discard!=NULL)
                        {
                            delete discard;
                        }
                        enviro[x][y+1].Organismtype=68;
                        enviro[x][y].Organismtype=46;
                        if(fed==65)
                        {
                            dooTemp->feed();
                        }
                        life=dooTemp->getLife();
                        if(life>=8)
                        {
                            baby=new DoodleBug;
                            int tempx;
                            int tempy;
                            tempx=rand()%20;
                            tempy=rand()%20;
                            while(enviro[tempx][tempy].Organismtype==68||enviro[tempx][tempy].Organismtype==65)
                            {
                                tempx=rand()%20;
                                tempy=rand()%20;
                            }
                            enviro[tempx][tempy].link=baby;
                            enviro[tempx][tempy].Organismtype=68;
                            dooCount++;
                        }
                        death=dooTemp->getDeath();
                        if(death>3)
                        {
                            enviro[x][y+1].link=NULL;
                            delete dooTemp;
                            enviro[x][y+1].Organismtype=46;
                            dooCount=dooCount-1;
                        }
                    }
                    if(temp==3)
                    {
                        discard=enviro[x-1][y].link;
                        enviro[x-1][y].link=dooTemp;
                        enviro[x][y].link=NULL;
                        fed=enviro[x-1][y].Organismtype;
                        if(discard!=NULL)
                        {
                            delete discard;
                        }
                        enviro[x-1][y].Organismtype=68;
                        enviro[x][y].Organismtype=46;
                        if(fed==65)
                        {
                            dooTemp->feed();
                        }
                        life=dooTemp->getLife();
                        if(life>=8)
                        {
                            baby=new DoodleBug;
                            int tempx;
                            int tempy;
                            tempx=rand()%20;
                            tempy=rand()%20;
                            while(enviro[tempx][tempy].Organismtype==68||enviro[tempx][tempy].Organismtype==65)
                            {
                                tempx=rand()%20;
                                tempy=rand()%20;
                            }
                            enviro[tempx][tempy].link=baby;
                            enviro[tempx][tempy].Organismtype=68;
                            dooCount++;
                        }
                        death=dooTemp->getDeath();
                        if(death>3)
                        {
                            enviro[x-1][y].link=NULL;
                            delete dooTemp;
                            enviro[x-1][y].Organismtype=46;
                            dooCount=dooCount-1;
                        }
                    }
                    if(temp==4)
                    {
                        discard=enviro[x+1][y].link;
                        enviro[x+1][y].link=dooTemp;
                        enviro[x][y].link=NULL;
                        fed=enviro[x+1][y].Organismtype;
                        if(discard!=NULL)
                        {
                            delete discard;
                        }
                        enviro[x+1][y].Organismtype=68;
                        enviro[x][y].Organismtype=46;
                        if(fed==65)
                        {
                            dooTemp->feed();
                        }
                        life=dooTemp->getLife();
                        if(life>=8)
                        {
                            baby=new DoodleBug;
                            int tempx;
                            int tempy;
                            tempx=rand()%20;
                            tempy=rand()%20;
                            while(enviro[tempx][tempy].Organismtype==68||enviro[tempx][tempy].Organismtype==65)
                            {
                                tempx=rand()%20;
                                tempy=rand()%20;
                            }
                            enviro[tempx][tempy].link=baby;
                            enviro[tempx][tempy].Organismtype=68;
                            dooCount++;
                        }
                        death=dooTemp->getDeath();
                        if(death>3)
                        {
                            enviro[x+1][y].link=NULL;
                            delete dooTemp;
                            enviro[x+1][y].Organismtype=46;
                            dooCount=dooCount-1;
                        }
                    }
                }
            }
        }
    }
    return dooCount;
}

int moveAnts(int AntCount,tile enviro[20][20])
{
    OrganismPtr AntTemp, baby;
   int x;//x coordinate in array
    int y;//y coordinate in array
    int up1;//bug type for tile above
    int down1;//bug type for tile below
    int left1;//bug type for tile to the left
    int right1;//bug type for tile to the right
    int temp;//stores choice of direction bug moves in. 0 if no move, 1 if up, 2 if down, 3 if left, 4 if right
    int life;//counts number of turns since bug last bred
    x=0;
    y=0;
    AntCount=0;
    for(x=0;x<20;x++)//recounts ants in array since some may have been eaten by doodles
    {
        for(y=0;y<20;y++)
        {
            if(enviro[x][y].Organismtype==65)
            {
                AntCount++;
            }
        }
    }
    for(int i=0;i<AntCount;i++)
    {
        x=0;
        y=0;
        for(y=0;y<20;y++)
        {
            for(x=0;x<20;x++)
            {
                AntTemp=enviro[x][y].link;
                if(enviro[x][y].Organismtype==65&&AntTemp->getTurn()==0)
                {
                    AntTemp->changeTurn(1);
                    up1=enviro[x][y-1].Organismtype;
                    down1=enviro[x][y+1].Organismtype;
                    left1=enviro[x-1][y].Organismtype;
                    right1=enviro[x+1][y].Organismtype;
                    if(y==0)
                    {
                        up1=0;
                    }
                    if(y==19)
                    {
                        down1=0;
                    }
                    if(x==0)
                    {
                        left1=0;
                    }
                    if(x==19)
                    {
                        right1=0;
                    }
                    temp=AntTemp->moveOrganism(up1, down1, left1, right1);
                    if(temp==1)
                    {
                        enviro[x][y-1].link=AntTemp;
                        enviro[x][y].link=NULL;
                        enviro[x][y-1].Organismtype=65;
                        enviro[x][y].Organismtype=46;
                        life=AntTemp->getLife();
                        if(life>=3)
                        {
                            baby=new Ant;
                            int tempx;
                            int tempy;
                            tempx=rand()%20;
                            tempy=rand()%20;
                            while(enviro[tempx][tempy].Organismtype==68||enviro[tempx][tempy].Organismtype==65)
                            {
                                tempx=rand()%20;
                                tempy=rand()%20;
                            }
                            enviro[tempx][tempy].link=baby;
                            enviro[tempx][tempy].Organismtype=65;
                            AntCount++;
                        }
                    }
                    if(temp==2)
                    {
                        enviro[x][y+1].link=AntTemp;
                        enviro[x][y].link=NULL;
                        enviro[x][y+1].Organismtype=65;
                        enviro[x][y].Organismtype=46;
                        life=AntTemp->getLife();
                        if(life>=3)
                        {
                            baby=new Ant;
                            int tempx;
                            int tempy;
                            tempx=rand()%20;
                            tempy=rand()%20;
                            while(enviro[tempx][tempy].Organismtype==68||enviro[tempx][tempy].Organismtype==65)
                            {
                                tempx=rand()%20;
                                tempy=rand()%20;
                            }
                            enviro[tempx][tempy].link=baby;
                            enviro[tempx][tempy].Organismtype=65;
                            AntCount++;
                        }
                    }
                    if(temp==3)
                    {
                        enviro[x-1][y].link=AntTemp;
                        enviro[x][y].link=NULL;
                        enviro[x-1][y].Organismtype=65;
                        enviro[x][y].Organismtype=46;
                        life=AntTemp->getLife();
                        if(life>=3)
                        {
                            baby=new Ant;
                            int tempx;
                            int tempy;
                            tempx=rand()%20;
                            tempy=rand()%20;
                            while(enviro[tempx][tempy].Organismtype==68||enviro[tempx][tempy].Organismtype==65)
                            {
                                tempx=rand()%20;
                                tempy=rand()%20;
                            }
                            enviro[tempx][tempy].link=baby;
                            enviro[tempx][tempy].Organismtype=65;
                            AntCount++;
                        }
                    }
                    if(temp==4)
                    {
                        enviro[x+1][y].link=AntTemp;
                        enviro[x][y].link=NULL;
                        enviro[x+1][y].Organismtype=65;
                        enviro[x][y].Organismtype=46;
                        life=AntTemp->getLife();
                        if(life>=3)
                        {
                            baby=new Ant;
                            int tempx;
                            int tempy;
                            tempx=rand()%20;
                            tempy=rand()%20;
                            while(enviro[tempx][tempy].Organismtype==68||enviro[tempx][tempy].Organismtype==65)
                            {
                                tempx=rand()%20;
                                tempy=rand()%20;
                            }
                            enviro[tempx][tempy].link=baby;
                            enviro[tempx][tempy].Organismtype=65;
                            AntCount++;
                        }
                    }
                }
            }
        }
    }
    return AntCount;
}

void turnReset(tile enviro[20][20])
{
    int x;
    int y;
    OrganismPtr temp;
    for(y=0;y<20;y++)
    {
        for(x=0;x<20;x++)
        {
            if(enviro[x][y].link!=NULL)
            {
                temp=enviro[x][y].link;
                temp->changeTurn(0);
            }
        }
    }
}
