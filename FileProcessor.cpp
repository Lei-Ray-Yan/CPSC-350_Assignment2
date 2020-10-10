/*
- Raymond Raymond
- 2297956
- lyan@chapman.edu
- CPSC-350-01
- Assignment 2

- this is the .cpp file for the FileProcessor objects, which all the functions are defined.

*/


#include "FileProcessor.h"

using namespace std;


char ** rawMap;
int rawX;
int rawY;



FileProcessor :: FileProcessor(){

}

FileProcessor :: ~FileProcessor(){

}


bool FileProcessor :: readMap(string fileName){
  ifstream inputFile;
  FileProcessor fp;

  string currString;

  if(!fp.getFileContent(inputFile, fileName)){
    cout << "Error: Cannot find the file given. " << endl;
    return false;
  }

  currString = fp.extractNextString(inputFile);
  rawY = stoi(currString);
  currString = fp.extractNextString(inputFile);
  rawX = stoi(currString);

  rawMap = new char*[rawX];
  for (int i=0; i<rawX; ++i){
    rawMap[i] = new char [rawY];
  }

  for (int i=0; i<rawY; ++i){
    currString = fp.extractNextString(inputFile);
    if (currString.length() != rawX){
      cout << "Warning: given file's given size not matching actual content" << endl;
    }
    for (int j=0; j<rawX; ++j){
      rawMap[j][i] = currString[j];
    }
  }

  inputFile.close();

  return true;
}

void FileProcessor :: outputMap(Cell** gridMap, int sizeX, int sizeY, int currentGeneration){
  cout << "writing a new generation to file. " << endl;

  fstream newFile;
  newFile.open("RaymondYan.txt", ios :: app);

  if(!newFile.is_open()){
    cout << "cannot write to a new file for unknown reason. " << endl;
  }

  newFile << currentGeneration << endl;
  for (int i=0; i<sizeY; ++i){
    for (int j=0; j<sizeX; ++j){
      Cell tempCell = gridMap[j][i];
      int status = tempCell.getStatus();
      string newString;
      switch (status){
        case 0:
          newString = "-";
          break;
        case 1:
          newString = "X";
          break;
      }
      //cout << newString;
      newFile << newString;
    }
    //cout << endl;
    newFile.flush();
    newFile << endl;
  }

  cout << "Writing completed. Going to close the file. " << endl;
  newFile.close();
}




bool FileProcessor :: getFileContent(ifstream& inputFile, string fileName){
  inputFile.open(fileName);
  if(!inputFile.is_open()){
    return false;
  }
  return true;
}

string FileProcessor :: extractNextString(ifstream& inputFile){
  string currString;
  inputFile >> currString;
  return currString;
}

bool FileProcessor :: fileEndReached(ifstream& inputFile){
  if (inputFile.eof()){
    return true;
  }
  return false;
}































