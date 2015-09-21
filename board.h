#ifndef __BOARD_H__
#define __BOARD_H__

#include <iostream>
#include <vector>
#include "block.h"
#include "score.h"
#include "window.h"

class Board {
	char **newboard;   //  a two-dimensional array of chars
	BlockBuffer *buffer;  // the block contained on the top left of the board
	NextBlock *nblock;   // the next block that contains the block that is next
	std::vector<Block> b; // so far all Blocks in the board
	Score *s; // current score
	int blockNum;
	int level;
	Xwindow *window;
   public:
	Board(); // default constructor
	~Board(); // destructor
	bool textonly;

	void newGame();
	void init(); // initialize the board and ready to take the first block
	void drawBuffer(); // put the Buffer on the board
	void drawBoard(); // put the other blocks on the board
	void moveLeft (int n); // Buffer move left
	void moveRight (int n); // Buffer move right
	void clock(); // Buffer clockwise
	void counterClock(); // Buffer counter clockwise
	void cleanBlock(int n); // if b[n] has been cleaned, delete it and move every other block to the front by one
	bool lineClean(int i); //check if line i in the board filled, true if yes, false otherwise 
	void allMoveDown(int i); // if line i is removed, move down all the cells above
	bool checkDownPosition(); // check where the block is gonna sit, return the height	
	void bufferDownOne(); // the buffer go down one step
        void levelUp();
	void levelDown();
	void downBuffer(); // the block in the blockbuffer go down to the board,
			   // the next block goes into blockbuffer,
	   		   // nextblock generate a new block, also,
			   // check if there is any lineclean, if so, move down
			   // recalculate each block
	bool gameOver(); // check if game is over, true if so
	void setSeed( uint32_t n);
	NextBlock* getNblock(){return nblock;};
	friend std::ostream& ::operator << (std:: ostream& out,Board &board ); // overload << operator
											// print out the board
};

#endif
