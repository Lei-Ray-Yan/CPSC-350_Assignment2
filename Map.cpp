/*
- Raymond Raymond
- 2297956
- lyan@chapman.edu
- CPSC-350-01
- Assignment 2

- this is the .cpp file for the Map objects, which all the functions are defined.

*/


#include "Map.h"

using namespace std;


int sizeX;
int sizeY;

int currentGeneration;
int mapMode;  //0 for Classic mode, 1 for Doughnut mode, 2 for Mirror mode;
int outputMode; //0 for pause, 1 for enter, 2 for file.
string filePath;

Map* currentMap;
Cell** gridMap;


Map :: Map(){
  //do nothing
}


Map :: ~Map(){
  //do nothing
}

void Map :: generateMap(int mapCreation, int m, int o, int x, int y, float density, string inputFilePath){
  int theMapMode = m-1;
  int outputMode = o-1;

  mapMode = theMapMode;

  switch (mapCreation){
    case 1:
      generateMapByDensity(density, x, y);
      break;
    case 2:
      generateMapByFile(inputFilePath);
      break;
  }
}


void Map :: initializeMap(int x, int y){
  sizeX = x;
  sizeY = y;

  currentGeneration = 0;

  gridMap = new Cell*[sizeX];
  for(int i=0; i<sizeX; ++i){
    gridMap[i] = new Cell[sizeY];

  }
  cout << "Map initialized. " << endl;
  initializeMapCells();
  cout << "Map cells initialized. " << endl;
}

void Map :: initializeMapCells(){
  for (int i=0; i<sizeX; ++i){
    for (int j=0; j<sizeY; ++j){
      Cell tempCell(i, j, currentMap, mapMode);
      gridMap[i][j] = tempCell;
    }
  }
}

void Map :: generateMapByDensity(float d, int x, int y){
  int mapSize;
  int occupiedGridNum;
  int occupyCount = 0;
  float density = d;

  initializeMap(x, y);

  mapSize = getMapSize();
  occupiedGridNum = int(round(mapSize * density));

  cout << "Occupied grid starting quantity is going to be: " << occupiedGridNum << endl;

  int loopCount = 0;
  int loopLimit = 100000;
  srand(time(0));
  while(occupyCount < occupiedGridNum){
    loopCount++; if(loopCount >= loopLimit){cout << "Warning: Loop count exceeds max allowance, SafeExit triggerred. "<<endl; break; }
    int rx = getRandomX();
    int ry = getRandomY();
    Cell& tempCell = gridMap[rx][ry];
    int tempCellStatus = tempCell.getStatus();

    if(tempCellStatus == 0){
      tempCell.changeStatus(1);
      occupyCount += 1;
      //cout << "generated 1 cell"<<endl;
    }
  }
  cout << "Finished generating map by given density. " << endl;
  return;
}

void Map :: generateMapByFile(string fileName){
  FileProcessor fp;

  fp.readMap(fileName);
  int rawX = fp.rawX;
  int rawY = fp.rawY;
  char** rawMap = fp.rawMap;

  initializeMap(rawX, rawY);

  for (int i=0; i<sizeY; ++i){
    for (int j=0; j<sizeX; ++j){
      Cell& tempCell = gridMap[j][i];
      char& currChar = rawMap[j][i];
      if (currChar == 'X'){
        tempCell.changeStatus(1);
      }
    }
  }
  cout << "Finished generating map by given file. " << endl;
}






void Map :: generateSimulations(int outputType, string outputFilePath){
  bool end = false;
  int loopLimit = 10000;
  int safeExit = 0;

  outputMap(outputType, outputFilePath);
  while(end == false){
    safeExit+=1; if(safeExit>=loopLimit){cout << "Safe exit triggered while updating generations, too many loops. " << endl; break; }

    cout << "Updating for a new generation. " << endl;
    updateNextGeneration();
    currentGeneration += 1;

    if (checkSimulationEndCondition()){
      cout << "End condition reached. Map is stablized or emptied. " << endl;
      end = true;
    }else{
      cout << "Generation updated. Refreshing map. " << endl;
      refreshMapCells();
      cout << "Outputing Map. " << endl;
      outputMap(outputType, outputFilePath);
    }
  }
  cout << "Simulation generation completion. " << endl;
}

void Map :: updateNextGeneration(){
    for (int i=0; i<sizeX; ++i){
      for (int j=0; j<sizeY; ++j){
        Cell& tempCell = gridMap[i][j];
        tempCell.updateNextGeneration(gridMap, sizeX, sizeY);
      }
    }
}

bool Map :: checkSimulationEndCondition(){
  cout << "Checking simulation ending condition" << endl;
  bool reached = true;

  for (int i=0; i<sizeX; ++i){
    for (int j=0; j<sizeY; ++j){
      Cell& tempCell = gridMap[i][j];
      if (tempCell.getStatus() != tempCell.getFutureStatus()){
        reached = false;
        return reached;
      }
    }
  }

  return reached;
}

void Map :: refreshMapCells(){
  for (int i=0; i<sizeY; ++i){
    for (int j=0; j<sizeX; ++j){
      Cell& tempCell = gridMap[j][i];
      tempCell.refresh();
    }
  }
}




int Map :: getMapSize(){
  int size = sizeX * sizeY;

  return size;
}

bool Map :: checkSizeBoundary(int x, int y){
  bool outcome;

  if ((x == 1) || (x == sizeX) || (y == 1) || (y == sizeY)){
    outcome = true;
  }else{
    outcome = false;
  }

  return outcome;
}

bool Map :: weightedRandomBool(float p){
  float boundary;
  float randPoint;
  bool outcome;

  boundary = p * 100;
  randPoint = float(rand() % 101);
  if (randPoint <= boundary){
    outcome = true;
  }else{
    outcome = false;
  }

  return outcome;
}

int Map :: getRandomX(){
  int rx;

  rx = rand() % (sizeX);

  return rx;
}

int Map :: getRandomY(){
  int ry;

  ry = rand() % (sizeY);

  return ry;
}


void Map :: outputMap(int type, string outputFilePath){
  switch (type){
    case 1: //pause
      outputMapToTerminal(type);
      break;
    case 2: //enter
      outputMapToTerminal(type);
      break;
    case 3: //file
      outputMapToFile(outputFilePath);
      break;
  }
}

void Map :: outputMapToFile(string outputFilePath){
  FileProcessor mapOutPut;
  mapOutPut.outputMap(gridMap, sizeX, sizeY, currentGeneration);
}

void Map :: outputMapToTerminal(int type){
  switch (type){
    case 1: //pause
      //system("pause");
      sleep(1);
      break;
    case 2: //enter
      while(true){
        if (cin.get() == '\n'){
          break;
        }
      }
      break;
  }
  cout << currentGeneration << endl;
  for (int i=0; i<sizeY; ++i){
    for (int j=0; j<sizeX; ++j){
      Cell tempCell = gridMap[j][i];
      int status = tempCell.getStatus();
      switch (status){
        case 0:
          cout << "-";
          break;
        case 1:
          cout << "X";
          break;
        default:
          cout << "ERROR";
      }
    }
    cout << endl;
  }
}
















