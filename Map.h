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
  int sizeX;
  int sizeY;

  int currentGeneration;
  int mapMode;  //0 for Classic mode, 1 for Doughnut mode, 2 for Mirror mode;
  int outputMode; //0 for pause, 1 for enter, 2 for file.
  string filePath;

  Map* currentMap;
  Cell** gridMap;

  Map();
  ~Map();

  void generateMap(int mapCreation, int m, int o, int x, int y, float density, string inputFilePath);
  void initializeMap(int x, int y);
  void initializeMapCells();
  void generateMapByDensity(float d, int x, int y);
  void generateMapByFile(string fileName);
  void generateSimulations(int outputType, string outputFilePath);
  void updateNextGeneration();
  void refreshMapCells();
  bool checkSimulationEndCondition();


  int getMapSize();
  bool checkSizeBoundary(int x, int y);
  void updateBoundary();
  bool weightedRandomBool(float p);
  int getRandomX();
  int getRandomY();

  void outputMap(int type, string outputFilePath);
  void outputMapToFile(string outputFilePath);
  void outputMapToTerminal(int type);



};

#endif