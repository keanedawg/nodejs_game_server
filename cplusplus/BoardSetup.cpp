#include "board.h"

/*Initializes the board setting up all of the special letters.
All letters are assumed to be empty char and no type by default,
so we only handle special cases. */
Board::Board() {
	tiles[0][0] = Tile('$');
	tiles[0][3] = Tile('!');
	tiles[0][7] = Tile('$');
	tiles[0][11] = Tile('!');
	tiles[0][14] = Tile('$');

	tiles[1][1] = Tile('#');
	tiles[1][5] = Tile('@');
	tiles[1][9] = Tile('@');
	tiles[1][13] = Tile('#');

	tiles[2][2] = Tile('#');
	tiles[2][6] = Tile('!');
	tiles[2][8] = Tile('!');
	tiles[2][12] = Tile('#');

	tiles[3][0] = Tile('!');
	tiles[3][3] = Tile('#');
	tiles[3][7] = Tile('!');
	tiles[3][11] = Tile('#');
	tiles[3][14] = Tile('!');

	tiles[4][4] = Tile('#');
	tiles[4][10] = Tile('#');

	tiles[5][1] = Tile('@');
	tiles[5][5] = Tile('@');
	tiles[5][9] = Tile('@');
	tiles[5][13] = Tile('@');

	tiles[6][2] = Tile('!');
	tiles[6][6] = Tile('!');
	tiles[6][8] = Tile('!');
	tiles[6][12] = Tile('!');

	tiles[7][0] = Tile('$');
	tiles[7][3] = Tile('!');
	tiles[7][7] = Tile('+');
	tiles[7][11] = Tile('!');
	tiles[7][14] = Tile('$');

	tiles[8][2] = Tile('!');
	tiles[8][6] = Tile('!');
	tiles[8][8] = Tile('!');
	tiles[8][12] = Tile('!');

	tiles[9][1] = Tile('@');
	tiles[9][5] = Tile('@');
	tiles[9][9] = Tile('@');
	tiles[9][13] = Tile('@');

	tiles[10][4] = Tile('#');
	tiles[10][10] = Tile('#');

	tiles[11][0] = Tile('!');
	tiles[11][3] = Tile('#');
	tiles[11][7] = Tile('!');
	tiles[11][11] = Tile('#');
	tiles[11][14] = Tile('!');

	tiles[12][2] = Tile('#');
	tiles[12][6] = Tile('!');
	tiles[12][8] = Tile('!');
	tiles[12][12] = Tile('#');

	tiles[13][1] = Tile('#');
	tiles[13][5] = Tile('@');
	tiles[13][9] = Tile('@');
	tiles[13][13] = Tile('#');

	tiles[14][0] = Tile('$');
	tiles[14][3] = Tile('!');
	tiles[14][7] = Tile('$');
	tiles[14][11] = Tile('!');
	tiles[14][14] = Tile('$');
}
