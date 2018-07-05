#DISCLAIMER:   THIS CODE WAS ORIGINALLY AUTHORED BY ANDREW PARKHURST
#              AS PART OF A HOMEWORK ASSIGNMENT FOR ENSC 251 AT SFU IN FALL 2017.
#              PLEASE DO NOT MODIFY OR COPY THIS CODE            
#
#NOTE:         SOME CHANGES HAVE SINCE THE ASSIGNMENT TO MAKE THE CODE CLEANER AND EASIER TO READ OVERALL
#              INCLUDING REMOVING SOME COMMENTS PRESENT FOR THE MARKERS AND SEPERATING THE CODE INTO MULTIPLE FILES
#              AND MAKING CHANGES TO THE MAKEFILE
#              THE OVERALL FUNCTIONALITY OF THE CODE HAS NOT BEEN CHANGED IN ANY WAY

all: 2DLifeSim

2DLifeSim: Critters.o 2DLifeSim.o 
	g++ -o 2DLifeSim 2DLifeSim.o Critters.o 

2DLifeSim.exe: Critters.o 2DLifeSim.o 
	g++ -o 2DLifeSim.exe 2DLifeSim.o Critters.o 

2DLifeSim.o: 2DLifeSim.cpp Critters.o Critters.h
	g++ -c -std=c++11 2DLifeSim.cpp

Critters.o: Critters.cpp Critters.h
	g++ -c -std=c++11 Critters.cpp

clean:
	rm -f 2DLifeSim *.o
	rm -f 2DLifeSim.exe *.o