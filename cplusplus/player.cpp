#include "player.h"

void Player::addLetters(char letters[], int size) {
	for (int i = 0; i < size; i++) {
		if ('*' == letters[i]) {
			this->myLetters[26]++;
		}
		else {
			this->myLetters[letters[i] - 'A']++;
		}
	}
}

void Player::printLetters() {
	cout << "Your letters are: ";
	for (int i = 0; i < 26; i++) {
		for (int hits = 0; hits < this->myLetters[i]; hits++) {
			cout << (char)('A' + i) << ' ';
		}
	}
	for (int hits = 0; hits < myLetters[26]; hits++) {
		cout << '*' << ' ';
	}
	cout << '\n';
}

bool Player::hasLetter(char letter) {
	if ('*' == letter) {
		// transform '*' into the proper letter it needs to be
		return this->myLetters[26] > 0;
	}
	return this->myLetters[letter - 'A'] > 0;
}