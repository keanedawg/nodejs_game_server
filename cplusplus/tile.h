#pragma once

class Tile {
public:
	Tile() : type(' '), letter(' ') {}
	Tile(char type) : type(type), letter(' ') {}
	Tile(char type, char letter) : type(type), letter(letter) {}

	inline bool isEmpty() { return letter == ' '; }  // does it have a letter on it?
	inline void addLetter(char letter) { this->letter = letter; };
	inline char getLetter() { return letter; }
	inline char getType() { return type; }
	char print();

private:
	char type; // Is it a normal tile, 4x word, 3x letter?
	char letter;   // The letter on it, set to ' ' by default.
};