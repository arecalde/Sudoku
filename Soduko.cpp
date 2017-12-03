#include <iostream>
#include <fstream> 
#include <sstream> 
#include <string> 
#include <cstdlib>
#include "Soduko.h"
using namespace std;
//const int GRIDSIZE = 9;

void Sudoku::beginNewGame() {
	loadStats(); //get the stats from the file
	getUserDifficulty(); //get the user's difficulty
	//level
	startGame(); //start the game
}

void Sudoku::loadStats() {
	ifstream fin("stats.txt"); //open
	//the stats file
	int count = 0; //start at 0
	while (count < 4) //keep going until the end of the array
	{
		fin >> gameAverages[count]; //put the
		//info from the file into the array to store the averages
		count++; //onto the next
	}
	count = 0; //start at 0
	while (count < 4) //keep going until the end of the array
	{
		fin >> numofGames[count]; //put the info
		//from the file into the array
		//to store the averages
		count++; //onto the next
	}
	fin.close(); //close the connection
}

void Sudoku::unloadStats() {
	ofstream fout("stats.txt"); //open
	//the stats file
	int count = 0; //start at 0
	while (count < 4) //keep going until the end of the array
	{
		fout << gameAverages[count] << endl; //put the info
		//from the array into the file
		count++; //onto the next
	}
	count = 0;
	while (count < 4) {
		fout << numofGames[count] << endl;
		count++;
	} //does the same thing as above
	fout.close(); //close the connection
}

void Sudoku::startGame() {
	score = 100;
	int gameNumber = rand() % 10 + 1; //get the game number 1-10

	//start getting file names
	stringstream ss1, ss2;
	ss1 << difficulty << "/games/" << gameNumber << ".txt";
	ss2 << difficulty << "/answer/" << gameNumber << ".txt";
	gameFileStr = ss1.str();
	answerFileStr = ss2.str();
	//end getting file names

	initializeArrays(); //fill the game array
	//and the answer array with appropriate values
	//from the game file and answer file, respectively

	int playerResponse = 0;
	displayGrid(); //show the game board
	bool gameInProgress = !isComplete(); //while there are
	//empty squares left, the game is in progress
	while (gameInProgress) //keep going until the game is finished
	{
		cout << "Enter a line number to edit (-1 to quit)(0 for new game): ";
		//prompt the user for either a line number or
		//new game/quit game
		cin >> playerResponse; //store response
		if (playerResponse == -1) { //if the user wants to quit
			break;
		}
		else if (playerResponse == 0) { //if the user wants a new game
			break;
		}
		play(playerResponse); //call the play soduko function
		gameInProgress = !isComplete(); //check if the game is finished
		//yet
	}
	if (gameInProgress) //if the game had squares left
	{
		cout << "Game not completed" << endl;
		cout << "Final Score: " << score << endl;
	}
	else { //if the game was finished
		
		//start doing stats stuff
		int tmpDifficulty = difficulty-1;
		gameAverages[tmpDifficulty] = gameAverages[tmpDifficulty] + score;
		gameAverages[tmpDifficulty] = gameAverages[tmpDifficulty] / 2;
		numofGames[tmpDifficulty]++;
		//end doing stats stuff

		cout << "Game finished" << endl;
		cout << "Final Score: " << score << endl;
		//start displaying different closing messages
		if (score == 100) {
			cout << "Excellent Player, should try next level" << endl;
		}
		else if (score >= 80) {
			cout << "Good player, keep practicing on this level" << endl;
		}
		else if (score >= 60) {
			cout << "OK player... keep practicing on this level if you dare" << endl;
		}
		else if (score >= 40) {
			cout << "‘Well.. suggest trying a easier level" << endl;
		}
		else {
			cout << "Watch videos to learn how to play" << endl;
		}
		//end displaying different closing messages
	}
	

	if (playerResponse == 0) //if the user wanted a new game
	{
		cout << "Starting new game" << endl;
		startGame(); //start a new game
	}
	else {
		unloadStats();
		mainMenu(); //otherwise show the main menu
		
	}
}

void Sudoku::getUserDifficulty(){
	cout << "Welcome to my Soduko Game" << endl;
	cout << "Very Easy (1)" << endl;
	cout << "Easy (2)" << endl;
	cout << "Medium (3)" << endl;
	cout << "Hard (4)" << endl; //explain to the user
	//the different options
	cout << "Enter difficulty (1-4): "; //prompt for the difficulty
	cin >> difficulty; //store that difficult in the member
	
}

void Sudoku::mainMenu() {
	char optionChar; //store user response
	cout << "P - Play" << endl;
	cout << "S - Stats" << endl;
	cout << "Q - Quit" << endl; //explain user options
	cout << "Please enter an option: "; //prompt for option
	cin >> optionChar; //store entered option
	optionChar = toupper(optionChar); //make the option char caps
	//to reduce errors
	if (optionChar == 'P') //if the player wants a new game
	{
		beginNewGame(); //start a new game
	}
	else if (optionChar == 'S') //if the player wants to see games played 
	{
		cout << "Statistics" << endl; 
		int count = 0;
		double total = 0;
		int numOfTotalGames = 0;
		while (count < 4) {
			cout << "Level " << (count + 1) << " - Average: " << gameAverages[count];
			total = total + gameAverages[count];
			cout << " | Number of Games: " << numofGames[count] << endl;
			numOfTotalGames = numOfTotalGames + numofGames[count];
			count++;
		}
		cout << "Overall - Average: " << (total / 4);
		cout << " | Number of Games: " << numOfTotalGames << endl;
		mainMenu();

	}
}



void Sudoku::initializeArrays() {
	ifstream infile; //get the game file
	infile.open(gameFileStr.c_str());
  
  ifstream answerFile; //get the answer file
  answerFile.open(answerFileStr.c_str());
	char tmpChar = '\0'; //will store the character from the game file
	char answerChar = '\0'; //will store the character from the answer file

	int row, column;
	row = 0;
	column = 0; //both start at 0
	infile.get(tmpChar); //get the 1st char
	while (!infile.eof()) //keep going until the end of the file.
	{
		if (tmpChar == '\n') //if there is a new line
		{
			row++; //new row
			column = 0; //start at the first column
		}
		else if (tmpChar != ' ') //if the character is not a space
			//it is a number
		{
			gameGrid[row][column] = tmpChar; //put that number
			//into the game grid
			column++; //go to the next column
		}

		infile.get(tmpChar); //get the next char
	}
	infile.close(); //stop reading from that file
	row = 0; 
	column = 0; //start over for the answer file
	answerFile.get(answerChar); //get the 1st char in file
	while (!answerFile.eof()) //keep going until the end of the file
	{
		if (answerChar == '\n') //if there is a new line
		{
			row++; //new row
			column = 0; //start at the first column
		}
		else if (answerChar != ' ')  //if the character
			//is not a space, it is a number
		{
			answerGrid[row][column] = answerChar; //store the current
			//character in the answer grid
			column++; //go to the next column
		}
		answerFile.get(answerChar); //move to next char
	}
	
	answerFile.close(); //close file
}




void Sudoku::printLine(char arg[], int length) {
	int count = 0;
	while (count < length) //keep going until end of the array
	{
		if (arg[count] == '0') //if its a 0, show an empty space
		{
			cout << " |";
		}
		else 
		{
			cout << arg[count] << "|"; //otherwise show that character
			//use vertical lines to seperate characters
		}
		count++; //move onto next character in the array
	}
}




void Sudoku::displayGrid() {
	int row = 0;
	while (row < GRIDSIZE) 
	{ 
		cout << (row + 1) << "- ||"; //indicate to user
		//the number of the grid
		printLine(gameGrid[row], GRIDSIZE); //print the particular row
		cout << endl; //formatting
		row++; //next row
	}
	cout << "Current Score: " << score << endl; //show current score

}





bool Sudoku::isComplete() {
	int row = 0;
	int column = 0; //start at 0
	bool areEqual = true;
	while (row < GRIDSIZE && areEqual) //keep going until end
									   //of array or they aren't equal
	{
		while (column < GRIDSIZE && areEqual) //keep going until end
			//of array or they aren't equal
		{
			if (gameGrid[row][column] != answerGrid[row][column]) {
				areEqual = false; //if at any point
				//the position in the game grid does not equal the position
				//in the answer grid, they are not equal
				//and both loops will exit
			}
			column++; //onto next column
		}
		column = 0; //column is 0
		row++; //onto next row
	}
	return areEqual; //return whether or not they are equal
}



void Sudoku::play(int& playerResponse) 
{
	int lineNumber = playerResponse; //the line number
	//is the number the user wants to edit
	char placeInLineChar; //store the place in line as a char
	int placeInLine; //store the position in array
	lineNumber--; //move line down 1 to match the array
	cout << "A|B|C|D|E|F|G|H|I|" << endl; //show the characters that the user can choose
	printLine(gameGrid[lineNumber], GRIDSIZE); //print
	//the line the user chose
	cout << endl; //formatting
	cout << "Enter a position in line to edit: ";
	//prompt the user for the alphabetical position

	cin >> placeInLineChar; //get that

	placeInLineChar = toupper(placeInLineChar);
	//put it in upper for uniformity
	placeInLine = (int)placeInLineChar; //get the
	//int value of char
	placeInLine = placeInLine - 65; 
	//subtract 65 so A is 0, B is 1
	//so on and so forth
	if (gameGrid[lineNumber][placeInLine] == '0') //if
		//the cell is empty
	{
		cout << "Enter the number you would like here: ";
		//Prompt the user for the number
		char newCharacter = '\0'; //character to store that
		cin >> newCharacter; //get that character
		int tmpCharValue = (int)newCharacter; //translate character
		//to int
		if (tmpCharValue >= 49 && tmpCharValue <= 57) //use int values to make sure that 
			//the char is valid
		{ //if it is valid
			if (newCharacter == answerGrid[lineNumber][placeInLine]) 
				//check if it is correct
			{
				gameGrid[lineNumber][placeInLine] = newCharacter;
				//change the gameGrid value to that new character
				cout << "Correct" << endl; //indicate to the user that their
				//answer was correct
				displayGrid(); //show the now changed game board
			}
			else {
				score = score - 5; //if its wrong subtract 5
				cout << "-5 Points, Incorrect. Current Score: " << score << endl;
				//tell the user it was wrong and show new score
				//board is unchanged, no need to display it
			}
		}
		else //if it isn't 1-9, then the character is not valid
		{
			cout << "Invalid Character" << endl;
		}
	}
	else //if it isn't 0, then that means it is already filled
	{
		cout << "Filled, please select a different location" << endl;
		//indicate that to user
	}
}