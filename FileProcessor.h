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
  /*
    these information are used for reading a map from .txt file.
  */
  char** rawMap;
  int rawX;
  int rawY;

  /*
    default constructor, destructor.
  */
  FileProcessor();
  ~FileProcessor();

  /*
    this function reads the map from a given file path.
  */
  bool readMap(string fileName);
  /*
    this function output the gridMap of a map objects to a txt file.
  */
  void outputMap(Cell** gridMap, int sizeX, int sizeY, int currentGeneration);
  /*
    this function attracts the string content from a txt file.
  */
  bool getFileContent(ifstream& inputFile, string fileName);
  /*
    this function extract the next line of string.
  */
  string extractNextString(ifstream& inputFile);
  /*
    check if the end of a file has been reached. 
  */
  bool fileEndReached(ifstream& inputFile);

};


#endif










