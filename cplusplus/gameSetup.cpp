#include "game.h"

void Game::setup() {
	setPlayers();
	setupDictionary();
	setupScoreMap();
}

// Reads the Dictionary Text File and enters values to the hashmap
void Game::setupDictionary() {
	// Use dictionary.txt for real game, tinydict for quick debugging.
	//	ifstream fin("dictionary.txt");  
	ifstream fin("tinydict.txt");
	std::string word;

	while (fin >> word) {
		dictionary[word] = true;
		cout << word << "\n";
	}

	fin.close();
}

void Game::setPlayers() {
	int players = 0;
	cout << "Please enter the number of people playing: ";
	while (players < 2 || players > 4) {
		cin >> players;
		if (players < 2 || players > 4) {
			cout << "Scrabble rules require there to be 2-4 players\n";
			cout << "Please enter the number of people playing: ";
		}
	}
	this->players = players;

	char lettersToAdd[7] = { 'A', 'S', 'T', 'U', 'D', 'Y', 'C' };

	for (int i = 0; i < players; i++) {
		myPlayers[i].addLetters(lettersToAdd, 7);
	}
}

// The bag is going to be just a counter full of frequencies of different letters	
void Game::setupBag() {
//	letterBag.push_back();
	// bag
}

// The bag is going to be just a counter full of frequencies of different letters	
void Game::setupScoreMap() {
	scoreMap['A'] = 1;
	scoreMap['B'] = 3;
	scoreMap['C'] = 3;
	scoreMap['D'] = 2;
	scoreMap['E'] = 1;
	scoreMap['F'] = 4;
	scoreMap['G'] = 2;
	scoreMap['H'] = 4;
	scoreMap['I'] = 1;
	scoreMap['J'] = 8;
	scoreMap['K'] = 5;
	scoreMap['L'] = 1;
	scoreMap['M'] = 3;
	scoreMap['N'] = 1;
	scoreMap['O'] = 1;
	scoreMap['P'] = 3;
	scoreMap['Q'] = 10;
	scoreMap['R'] = 1;
	scoreMap['S'] = 1;
	scoreMap['T'] = 1;
	scoreMap['U'] = 1;
	scoreMap['V'] = 4;
	scoreMap['W'] = 4;
	scoreMap['X'] = 8;
	scoreMap['Z'] = 10;
}
