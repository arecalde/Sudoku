#include <iostream>

#include <fstream> 
#include <iostream> 
#include <string> 
#include <cstdlib> // for exit() 
using namespace std;
void printLine(char arg[], int length) {
	int count = 0;
	while (count < length) {
		if (arg[count] == '0') {
			cout << " |";
		}
		else {
			cout << arg[count] << "|";
		}
		count++;
	}
}
int main() {
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
	if (!infile) {// Print an error and exit 
		cerr << "Uh oh, file could not be opened for reading!" << endl;
		exit(1);
	}// While there's still stuff left to read, eof means end of file. 
	char tmpChar = '\0';
	infile.get(tmpChar);
	int count = 1;
	//cout << count << "- ||";
	char gameGrid[9][9];
	char playerGrid[9][9];
	int row, column;
	row = 0;
	column = 0;
	while (!infile.eof()) {// read stuff from the file into a string and print  
		if (tmpChar == '\n') {
			row++;
			column = -1;
		}
		else {
			gameGrid[row][column] = tmpChar;
			playerGrid[row][column] = tmpChar;
		}
		infile.get(tmpChar);
		column++;
	}

	row = 0;
	column = 0;
	while (row < 9) {// read stuff from the file into a string and print 
		cout << (row + 1) << "- ||";
		printLine(gameGrid[row], 9);
		cout << endl;
		row++;
	}


	
	cout << endl;
	cout << "Enter a line number to edit: ";
	int lineNumber;
	char placeInLineChar;
	int placeInLine;
	cin >> lineNumber;
	lineNumber--;
	cout << "A|B|C|D|E|F|G|H|I|" << endl;
	printLine(gameGrid[lineNumber], 9);
	cout << endl;
	cout << "Enter a position in line to edit: ";

	cin >> placeInLineChar;

	placeInLineChar = toupper(placeInLineChar);

	placeInLine = (int) placeInLineChar;
	placeInLine = placeInLine-65;
	if (gameGrid[lineNumber][placeInLine] == '0') {
		cout << "Not Filled" << endl;
	}
	else {
		cout << "Filled" << endl;
	}
	cout << gameGrid[lineNumber][placeInLine] << endl;
	//system("PAUSE");
	return 0;
}