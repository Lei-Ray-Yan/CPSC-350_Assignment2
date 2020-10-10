/*
- Raymond Raymond
- 2297956
- lyan@chapman.edu
- CPSC-350-01
- Assignment 2

- this is the Main file of this assignment.
- In the Main file, the program prompt for all the required configuration from the user to deside the operating mode, outputing inputing mode, etc.

*/


#include <iostream>
#include "Map.h"
#include "FileProcessor.h"
#include "Cell.h"

using namespace std;


int main(int argc, char** argv){
  //defining variables for holding user inputs.
  int mapCreationType;
  int inputX;
  int inputY;
  float density;
  string inputFilePath;
  int mapBoundaryType;
  int resultsOutputType;
  string outputFilePath;
  //initializing the map.
  Map map;


  //constructions and taking user inputs.
  cout << "Game of Life: Simulation of Bacteria Lifecyles" << endl;

  cout << "Choose Map Creation (by typing in 1 or 2): " << endl;
  cout << "1: Random Map. "<< endl;
  cout << "2: Provide a map file. "<< endl;
  cin >> mapCreationType;
  if (mapCreationType == 1){
    cout << "Please provide the desired Map X size: " << endl;
    cout << "(aka how many colums. )" << endl;
    cin >> inputX;
    cout << "Please provide the desired Map Y size: " << endl;
    cout << "(aka how many rows. )" << endl;
    cin >> inputY;
    cout << "Please provide the desired population density,  " << endl;
    cout << "Enter a number between 0 and 1: " << endl;
    cin >> density;
  } else if (mapCreationType == 2){
    cout << "Please provide the input filepath: " << endl;
    cin >> inputFilePath;
  }

  cout << "Choose Map Boundary Type (by typing in 1, 2 or 3): " << endl;
  cout << "1. Classic Mode. " << endl;
  cout << "2. Doughnut Mode. " << endl;
  cout << "3. Mirror Mode. " << endl;
  cin >> mapBoundaryType;

  cout << "How do you want the generation to continue? " << endl;
  cout << "1. Output to terminal with a brief pause between each generation. " << endl;
  cout << "2. Output to terminal, wait for Enter key before each generation. " << endl;
  cout << "3. Output all results to a file, with a given file path. " << endl;
  cin >> resultsOutputType;
  if (resultsOutputType == 3){
    cout << "Enter desired filename: " << endl;
    cin >> outputFilePath;
  }


  //executing.
  map.generateMap(mapCreationType, mapBoundaryType, resultsOutputType, inputX, inputY, density, inputFilePath);
  map.generateSimulations(resultsOutputType, outputFilePath);


  //waiting for user input to end the program.
  cout << endl;
  cout << "Press Enter to exit the program. " << endl;
  if(resultsOutputType == 1){ //fix the bug that sleep() causes an auto '\n' input to deactivate the "wait for enter to exit" feature. 
    cin.ignore(1);
  }
  while(true){
    if (cin.get() == '\n'){
      break;
    }
  }

  return 0;
}

















