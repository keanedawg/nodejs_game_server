#include "board.h"

void Board::printBoard() {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			cout << tiles[i][j].print() << " ";
		}
		cout << "\n";
	}
}

/*adds a word to the board. Returns the score back to the user. Returns -1 if word cannot be added.*/
int Board::addWord(Player &p, int x, int y, string word, bool isDown) {
	if ((isDown && y + word.length() > 15) || (!isDown && x + word.length() > 15)) {
		throw "Word goes outside of the bounds of the board.";
	}
	
	for (int i = 0; i < word.length(); i++) {
		
		// set t at the beginning so I don't have to keep checking if isDown
		Tile* t;
		if (isDown) {
			t = &tiles[y + i][x];
		}
		else {
			t = &tiles[y][x + i];
		}
		// Check that user has letter or it's already on the board
		if (!p.hasLetter(word[i]) && t->getLetter() != word[i]) {
			throw "Word cannot be created from available letters.";
		}
		t->addLetter(word[i]);
	}
	return 0; // Remove later
}
