#include "game.h"

using namespace std;


// Sets up all initial objects then plays the game
void Game::startGame() {
	cout << "Scrable has started\n";
	setup();
	board.printBoard();
	play();
	return;
}

// Main Game Loop
void Game::play() {
	while (!this->gameFinished) {
		for (int i = 1; i <= players; i++) {
			system("cls");
			board.printBoard();
			cout << "TURN " << turns << ": Player " << i << ", it is your move\n";
			cout << playTurn(i) << '\n';
		}
		turns++;
	}
	cout << "Thank you for playing!\n";
}


int Game::playTurn(int player) {
	bool endturn = false;
	while (!endturn) {
		char move = promptMove();
		switch (move) {
		case 'h':
			printHelp();
			break;
		case 'c':
		{
			string word;
			cin >> word;
			transform(word.begin(), word.end(), word.begin(), toupper);
			if (isValidWord(word)) {
				cout << word << " is a valid Scrabble word.\n";
			}
			else {
				cout << word << " is NOT a valid Scrabble word.\n";
			}
		}
		break;
		case 'm':
		{
			// should add checker to ensure syntax is all good.
			try {
				int x, y;
				string word;
				bool isDown;
				char down;
				cin >> x >> y >> word >> down;
				down = tolower(down);
				transform(word.begin(), word.end(), word.begin(), toupper);
				// throws exception if any check fails.
				checkCoordinate(x);
				checkCoordinate(y);
				isDown = getAndCheckIsDown(down);
				checkWord(word);
				board.addWord(this->myPlayers[player], x-1, y-1, word, isDown);
				
				endturn = true; // player finishes his turn
			}
			catch (const char * err) {
				cout << "Input Error: " << err << "\n" << "Format is \"m <1-15> <1-15> <English Word> <'h' or 'v'>\"\n";
			}
			
		}
			break;
		case 'q':
			this->gameFinished = true;
			cout << "Quitting the game.\n";
			endturn = true;
			break;
		case 's':
			cout << "Skipping turn";
			endturn = true;
			break;
		case 'd':
			system("cls");
			board.printBoard();
			break;
		case 'p':
			myPlayers[player - 1].printLetters();
			break;
		default:
			cout << "Invalid Command Entered, please enter 'h' to get a list of available commands.\n";
			break;
		}
	}
	return 0;
}


bool Game::isValidWord(const string & word) {
	return dictionary.count(word) == 1;
}

// Main Game Loop
void Game::printHelp() {
	cout << "Here are all the possible commands:\n"
		 << "h - Help\n"
		 << "c - check if word is valid\n"
		 << "m - enter a move\n"
		 << "p - print your letters\n"
		 << "q - quit\n"
		 << "d - clear screen\n"
		 << "s - skip turn\n";
}


char Game::promptMove() {
	char move;
	cout << "What would you like to do: ";
	cin >> move;
	return tolower(move);
}

// Check Logic
void Game::checkWord(const string & word) {
	if (!isValidWord(word)) {
		throw "Word given was not found in the dictionary.";
	}
}


void Game::checkCoordinate(int x) {
	if (x > 15 || x < 1) {
		throw "X and/or Y coordinate are not valid. Must be between 1 to 15";
	}
}

// Checkdown returns a bool 
bool Game::getAndCheckIsDown(char down) {
	bool isDown;
	if (down == 'h') {
		isDown = false;
	}
	else if (down == 'v') {
		isDown = true;
	}
	else {
		throw "Failed to specify whether the word is horizontal or vertical.";
	}
	return isDown;
}