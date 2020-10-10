/*
- Raymond Raymond
- 2297956
- lyan@chapman.edu
- CPSC-350-01
- Assignment 2

- this is the header file for the Map object.
- Map object defines the map which all the activities of cells take place on, and is in charge of updating generation, storing information, etc.

*/


#ifndef MAP_H
#define MAP_H

#include <stdlib.h>
#include <cmath>
#include <time.h>
#include <unistd.h>
#include "Cell.h"
#include "FileProcessor.h"

using namespace std;


class Cell;

class Map{
public:
  /*
    the size of the map.
  */
  int sizeX;
  int sizeY;

  /*
    these information are about the simulation. The current generation of the simulation cycle, the mode of the simulation.
  */
  int currentGeneration;
  int mapMode;  //0 for Classic mode, 1 for Doughnut mode, 2 for Mirror mode;

  /*
    these stores information regarding the output method.
  */
  int outputMode; //0 for pause, 1 for enter, 2 for file.
  string filePath;

  /*
    a pointer to this object itself, and a 2-d array holding all the cells.
  */
  Map* currentMap;
  Cell** gridMap;

  /*
    default constructor, destructor.
  */
  Map();
  ~Map();

  /*
    these functions are in charge of generating a new "grid map", "map ground" for the simulation to happen. The generateMap takes in parameters, and calls one of the 2 others based on user inputs.
  */
  void generateMap(int mapCreation, int m, int o, int x, int y, float density, string inputFilePath);
  void generateMapByDensity(float d, int x, int y);
  void generateMapByFile(string fileName);

  /*
    these functions generate and initialize cells into the map.
  */
  void initializeMap(int x, int y);
  void initializeMapCells();

  /*
    these functions handles everything about the simulation itself, as well as generating new generation, etc.
  */
  void generateSimulations(int outputType, string outputFilePath);
  void updateNextGeneration();
  void refreshMapCells();
  bool checkSimulationEndCondition();

  /*
    these are the utility functions that helps the previous "core functions".
  */
  int getMapSize();
  bool checkSizeBoundary(int x, int y);
  void updateBoundary();
  bool weightedRandomBool(float p);
  int getRandomX();
  int getRandomY();

  /*
    these functions handles how the results will be output. 
  */
  void outputMap(int type, string outputFilePath);
  void outputMapToFile(string outputFilePath);
  void outputMapToTerminal(int type);



};

#endif