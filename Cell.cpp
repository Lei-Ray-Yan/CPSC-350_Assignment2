/*
- Raymond Raymond
- 2297956
- lyan@chapman.edu
- CPSC-350-01
- Assignment 2

- this is the .cpp file for the Cell objects, which all the functions are defined.

*/


#include "Cell.h"

using namespace std;


int x;
int y;
int status;   //0 for empty, 1 for occupied
int futureStatus; //status for next generation

Map* parentMap;
int gameMode;   //0 for Classic mode, 1 for Doughnut mode, 2 for Mirror mode;



Cell :: Cell(){
  x = 0;
  y = 0;
  status = 0;
  futureStatus = 0;
  parentMap = NULL;
  gameMode = 0;
}

Cell :: Cell(int posX, int posY, Map* map, int mode){
  x = posX;
  y = posY;
  status = 0;
  futureStatus = 0;
  parentMap = map;
  gameMode = mode;
}

Cell :: ~Cell(){
  //do nothing
}

void Cell :: refresh(){
  status = futureStatus;
  futureStatus = 0;
}

void Cell :: updateNextGeneration(Cell** grids, int sx, int sy){
  Cell** gridMap = grids;
  int boundX = sx - 1;
  int boundY = sy - 1;

  Cell tempCell;
  int neighbor = 0;
  int neighborGrids[8][2];
  findAllNeighborGrids(neighborGrids, sx, sy);

  int gridLines = sizeof neighborGrids/ sizeof neighborGrids[0];
  int values = sizeof neighborGrids[0]/ sizeof(int);
  for (int i=0; i<gridLines; ++i){
    int cx = neighborGrids[i][0];
    int cy = neighborGrids[i][1];
    if(cx<0 || cy<0){
      if((cx<0 && cx!=-5) || (cy<0 && cy!=-5)){
        cout << "Error: error in processing cell neighbor" << endl;
      }
      continue;
    }

    tempCell = gridMap[cx][cy];
    if (checkCellOccupied(tempCell)){neighbor += 1;}
  }

  //cout << "neighbor: " << neighbor << endl;
  if(neighbor <= 1){
    this->changeFutureStatus(0);
  }else if(neighbor <= 2){
    this->changeFutureStatus(getStatus());
  }else if(neighbor <= 3){
    this->changeFutureStatus(1);
  }else{
    this->changeFutureStatus(0);
  }

}




void Cell :: findAllNeighborGrids(int neighborGrids[8][2], int sx, int sy){
  int gridLines = 8;
  int values = 2;
  for (int i=0; i<gridLines; ++i){
    for (int j=0; j<values; ++j){
      neighborGrids[i][j] = 0;
    }
  }

  //upper-left
  neighborGrids[0][0] = x-1;
  neighborGrids[0][1] = y-1;
  //upper
  neighborGrids[1][0] = x;
  neighborGrids[1][1] = y-1;
  //upper-right
  neighborGrids[2][0] = x+1;
  neighborGrids[2][1] = y-1;
  //mid-left
  neighborGrids[3][0] = x-1;
  neighborGrids[3][1] = y;
  //mid-right
  neighborGrids[4][0] = x+1;
  neighborGrids[4][1] = y;
  //lower-left
  neighborGrids[5][0] = x-1;
  neighborGrids[5][1] = y+1;
  //lower
  neighborGrids[6][0] = x;
  neighborGrids[6][1] = y+1;
  //lower-right
  neighborGrids[7][0] = x+1;
  neighborGrids[7][1] = y+1;


  for (int i=0; i<8; ++i){
    for (int j=0; j<2; ++j){
      int tempInt = neighborGrids[i][j];
      int condition = checkSpecialCellPosition(j, tempInt, sx, sy);
      if (condition > 0){
        switch (gameMode){
          case 0: //classic mode
            {
            neighborGrids[i][j] = -5; //-5 is the designated value for "null" in this case.
            break;
            }
          case 1: //doughnut mode
            {
            switch (condition){
              case 1:
              {
                j == 0? neighborGrids[i][j] = tempInt + sx : neighborGrids[i][j] = tempInt + sy;
                break;
              }
              case 2:
              {
                j == 0? neighborGrids[i][j] = tempInt - sx : neighborGrids[i][j] = tempInt - sy;
                break;
              }
            }
            break;
            }
          case 2: //mirror mode
            {
            switch (condition){
              case 1:
              {
                j == 0? neighborGrids[i][j] = tempInt + 1 : neighborGrids[i][j] = tempInt + 1;
                break;
              }
              case 2:
              {
                j == 0? neighborGrids[i][j] = tempInt - 1 : neighborGrids[i][j] = tempInt - 1;
                break;
              }
            }
            break;
          }
        }
      }
    }
  }
}

int Cell :: checkSpecialCellPosition(int valueCategory, int value, int sx, int sy){
  if (value < 0){
    return 1;
  }
  if (valueCategory == 0 && value >= sx){
    return 2;
  }
  if (valueCategory == 1 && value >= sy){
    return 2;
  }
  return 0;
}








bool Cell :: checkCellOccupied(Cell cell){
  int status = cell.getStatus();
  if(status == 1){
    return true;
  }
  return false;
}



int Cell :: getStatus(){
  return status;
}

void Cell :: changeStatus(int newStatus){
  this->status = newStatus;
}

int Cell :: getFutureStatus(){
  return futureStatus;
}

void Cell :: changeFutureStatus(int newStatus){
  this->futureStatus = newStatus;
}

int Cell :: getX(){
  return x;
}

int Cell :: getY(){
  return y;
}









