#pragma once

#include <iostream>
#include <string>
using namespace std;

class Player {
public:
	//void playTurn();
	void printLetters();
	void addLetters(char letters[], int size);
	bool hasLetter(char letter);

private:
	int letterCount = 7;
	int myLetters[27] = {0};
	int score = 0;
	string name;
};