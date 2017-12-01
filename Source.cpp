#include <iostream>
 
  #include <fstream> 
#include <iostream> 
#include <string> 
#include <cstdlib> // for exit() 
using namespace std;
int main(){
  /*
  cout << "Welcome to my Soduko Game" << endl;
  cout << "Very Easy (1)" << endl;
  cout << "Easy (2)" << endl;
  cout << "Medium (3)" << endl;
  cout << "Hard (4)" << endl;
  cout << "Enter difficulty (1-4): ";
  int difficulty = 1;
  //cin >> difficulty;
  cout << endl;
  //cout << difficulty << endl;
  
 //*/
  

  ifstream infile("2/games/1.txt"); 
  // If we couldn't open/findthe input file stream for reading 
  if (!infile){// Print an error and exit 
    cerr << "Uh oh, file could not be opened for reading!" << endl; 
    exit(1); 
  }// While there's still stuff left to read, eof means end of file. 
  char tmpChar = '\0';
  infile.get(tmpChar);
  int count = 1;
  cout << count << "- ||";
  while (!infile.eof()){// read stuff from the file into a string and print  
    if(tmpChar == '\n'){
      
      cout << endl;
      count++;
      cout << count << "- ||";
    }else if(tmpChar == '0'){
      cout << " |";

      
    }else{
      cout << tmpChar << "|";
    }
    infile.get(tmpChar);

  } 
  cout << endl;
  return 0;
}