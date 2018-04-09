#pragma once

#include "tile.h"
#include <iostream>
#include <string>
#include "player.h"

using namespace std;

class Board {
private:
	const int size = 15; 
	Tile tiles[15][15]; // Rows, followed by Cols?

public:
	Board();
	void printBoard();
	int addWord(Player &p, int x, int y, string word, bool isDown);
};