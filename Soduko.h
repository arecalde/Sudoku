/*
This header file only works if the game and answer files have numbers
seperated by either 0s or spaces
void beginGame();
Pre Condition: none
Post Condition: startGame has been called

void initializeArrays();
Pre Condition: the file strings have values that match a file location
Post Condition: the answer and game arrays now have the appropriate values
from the files

void printLine(char arg[], int length);
Pre Condition: none
Post condition: numerical values are printed while 0s are replaced with
a space, all seperated by vertical bars

void displayGrid();
Pre condition: initialize arrays has been called
Post condition: displays the game array and the current score

bool isComplete();
Pre condition: initialize arrays has been called
Post condition: if all values in the game array match the answer array
then the game is complete

void play(int& playerResponse);
pre condition: initailize arrays has been called, and player response
is between 1-9
post condition: there is either a new value in the grid, 
or the user has a lower score

void getUserDifficulty();
pre condition: none
post condition: difficulty is a number between 1-4

void startGame();
pre condition: difficulty is a number between 1-4
post condition: The game has been played, the stats have been
put in a file and the menu is now
waiting for the user response

void mainMenu();
pre condition: stats have been loaded
post condition: The user is done, and the program exits

void unloadStats();
pre condition: stats arrays have been
loaded and changed appropriately
post condition: data from stats arrays has been put into the stats file

void loadStats();
pre condition: none
post condition: data from the stats file has been loaded into the appropriate array
*/

#include <string>
const int GRIDSIZE = 9;
class Sudoku {
public:
	void beginNewGame();
	void initializeArrays();
	void printLine(char arg[], int length);
	void displayGrid();
	bool isComplete();
	void play(int& playerResponse);
	void getUserDifficulty();
	void startGame();
	void mainMenu();
	void unloadStats();
	void loadStats();
private:
	char gameGrid[GRIDSIZE][GRIDSIZE];
	char answerGrid[GRIDSIZE][GRIDSIZE];
	double gameAverages[4];
	int numofGames[4];
	int score;
	int difficulty; 
	std::string answerFileStr;
	std::string gameFileStr;
};
