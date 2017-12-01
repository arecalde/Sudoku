#include <iostream>

#include <fstream> 
#include <iostream> 
#include <string> 
#include <cstdlib> // for exit() 
using namespace std;
const int GRIDSIZE = 9;

class Sudoku {
public:
	int num;
private:
	char gameGrid[GRIDSIZE][GRIDSIZE];
	char answerGrid[GRIDSIZE][GRIDSIZE];
};
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

void displayGrid(char gameGrid[][9]) {
	int row = 0;
	while (row < 9) {// read stuff from the file into a string and print 
		cout << (row + 1) << "- ||";
		printLine(gameGrid[row], 9);
		cout << endl;
		row++;
	}

}

void play(char grid[][9], char answer[][9], int playerResponse) {
	int lineNumber = playerResponse;
	char placeInLineChar;
	int placeInLine;
	lineNumber--;
	cout << "A|B|C|D|E|F|G|H|I|" << endl;
	printLine(grid[lineNumber], 9);
	cout << endl;
	cout << "Enter a position in line to edit: ";

	cin >> placeInLineChar;

	placeInLineChar = toupper(placeInLineChar);
	placeInLine = (int)placeInLineChar;
	placeInLine = placeInLine - 65;
	if (grid[lineNumber][placeInLine] == '0') {
		cout << "Not Filled" << endl;
		cout << "Enter the number you would like here: ";
		char newCharacter = '\0';
		//newCharacter = grid[lineNumber][placeInLine];
		cin >> newCharacter;
		if (newCharacter == answer[lineNumber][placeInLine]) {
			grid[lineNumber][placeInLine] = newCharacter;
			cout << "Correct" << endl;
		}
		else {
			cout << "Incorrect" << endl;
		}
		displayGrid(grid);
	}
	else {
		cout << "Filled, please select a different location" << endl;
	}
	//cout << grid[lineNumber][placeInLine] << endl;
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
	ifstream answerFile("2/answer/1.txt");

	// If we couldn't open/findthe input file stream for reading 
	if (!infile) {// Print an error and exit 
		cerr << "Uh oh, file could not be opened for reading!" << endl;
		exit(1);
	}
	if (!answerFile) {// Print an error and exit 
		cerr << "Uh oh, file could not be opened for reading!" << endl;
		exit(1);
	}
	char tmpChar = '\0';
	char answerChar = '\0';
	answerFile.get(answerChar);
	infile.get(tmpChar);
	int count = 1;
	//cout << count << "- ||";
	char gameGrid[9][9];
	char answerGrid[9][9];
	int row, column;
	row = 0;
	column = 0;
	while (!infile.eof() || !answerFile.eof()) {// read stuff from the file into a string and print  
		if (tmpChar == '\n') {
			row++;
			column = -1;
		}
		else {
			gameGrid[row][column] = tmpChar;
			answerGrid[row][column] = answerChar;
		}
		infile.get(tmpChar);
		answerFile.get(answerChar);
		column++;
	}



	int playerResponse = 0;
	displayGrid(gameGrid);
	cout << "Enter a line number to edit (-1 to quit): ";
	cin >> playerResponse;
	while (playerResponse != -1) {
		play(gameGrid, answerGrid, playerResponse);
		cout << "Enter a line number to edit (-1 to quit)(0 for new game): ";
		cin >> playerResponse;	
	}
	cout << endl;
	
	//system("PAUSE");
	return 0;
}