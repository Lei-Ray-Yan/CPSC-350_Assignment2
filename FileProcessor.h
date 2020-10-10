/*
- Raymond Raymond
- 2297956
- lyan@chapman.edu
- CPSC-350-01
- Assignment 2

- this is the header file for the FileProcessor object.
- FileProcessor objects handles everything about inputing and outputing into or from a txt file, etc. 

*/


#ifndef FILEPROCESSOR_H
#define FILEPROCESSOR_H

#include <iostream>
#include <fstream>
#include "Cell.h"

using namespace std;


class FileProcessor{
public:
  char** rawMap;
  int rawX;
  int rawY;

  FileProcessor();
  ~FileProcessor();

  bool readMap(string fileName);
  void outputMap(Cell** gridMap, int sizeX, int sizeY, int currentGeneration);
  bool getFileContent(ifstream& inputFile, string fileName);
  string extractNextString(ifstream& inputFile);
  bool fileEndReached(ifstream& inputFile);

};


#endif










