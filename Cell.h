/*
- Raymond Raymond
- 2297956
- lyan@chapman.edu
- CPSC-350-01
- Assignment 2

- this is the header file for the Cell object.
- Cell objects fills into the Map object, each of them take one grid on the map, they are simulating the "empty spot" or "alive cells" depending on the desinated
status. They are in charge of calculating their own destiny based on the map, and storing information, etc.
- Difference in game mode is handles by conditional branches in this object.

*/


#ifndef CELL_H
#define CELL_H

#include <iostream>

using namespace std;


class Map;

class Cell{
public:
  int x;
  int y;
  int status;   //0 for empty, 1 for occupied. 
  int futureStatus;

  Map* currentMap;
  int gameMode;

  Cell();
  ~Cell();

  Cell(int posX, int posY, Map* map, int mode);

  void refresh();
  void updateNextGeneration(Cell** grids, int sx, int sy);
  void findAllNeighborGrids(int emptyGrids[8][2], int sx, int sy);
  int checkSpecialCellPosition(int valueCategory, int value, int sx, int sy);

  bool checkCellOccupied(Cell cell);
  int getStatus();
  void changeStatus(int newStatus);
  int getFutureStatus();
  void changeFutureStatus(int newStatus);
  int getX();
  int getY();
};

#endif
