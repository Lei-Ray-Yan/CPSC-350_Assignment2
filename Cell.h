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
  /*
    the basic informations about the cell, including the location (x, y) on the map, status (alive or empty), futureStatus (what it will become in the next generation)
  */
  int x;
  int y;
  int status;   //0 for empty, 1 for occupied.
  int futureStatus;

  /*
    the pointer to the map object it "placed on", and the game mode desinated to that map/ simulation.
  */
  Map* currentMap;
  int gameMode;

  /*
    default contructor, destructor.
  */
  Cell();
  ~Cell();

  /*
    overloaded contructor.
  */
  Cell(int posX, int posY, Map* map, int mode);

  /*
    change the future status to (current) status.
  */
  void refresh();
  /*
    this function calculates and decides the future status in the next generation of the cell.
  */
  void updateNextGeneration(Cell** grids, int sx, int sy);
  /*
    this function finds all the neighbors of the current cell.
    The difference in game mode is reflected and handled in this part, which for 3 game modes, it provides 3 different ways to handle the "out-of-bounds" neigbours.
  */
  void findAllNeighborGrids(int emptyGrids[8][2], int sx, int sy);
  /*
    check if a location is "out-of-bounds".
  */
  int checkSpecialCellPosition(int valueCategory, int value, int sx, int sy);
  /*
    check a given cell's status.
  */
  bool checkCellOccupied(Cell cell);
  /*
    get a cell's status.
  */
  int getStatus();
  /*
    change a cell's status.
  */
  void changeStatus(int newStatus);
  /*
    get a cell's future status.
  */
  int getFutureStatus();
  /*
    change a cell's future status.
  */
  void changeFutureStatus(int newStatus);
  /*
    get the x location of the cell.
  */
  int getX();
  /*
    get the y location of the cell.
  */
  int getY();
};

#endif
