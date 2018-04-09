#include "tile.h"


char Tile::print() {
	if (this->letter == ' ') {
		if (this->type == ' ') {
			return '_';
		}
		return this->type;
	}
	return this->letter;
}