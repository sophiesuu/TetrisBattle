#ifndef __BLOCK_H__
#define __BLOCK_H__

#include <iostream>
#include <fstream>
#include "PRNG.h"
#include "cell.h"

class Block;
class Board;

class BlockBuffer {
	char type; // the type of the block
	Cell c[6]; // there are 4 cells in each block
	int blockSize; // the block's size if changes
   public:
	BlockBuffer();  // default constructor
	~BlockBuffer(); // destructor
	
	void init(const char &c ); // initialize the block with the type, there are 7 types 
			     // I, J, L, O, S, Z, T
	void moveLeft(int n); // move the block to left with n step
	void moveRight( int n ); // move the block to right with n step
	void clock(); // rotate the block clockwise
	void counterClock(); // rotate the block counterclock wise
	void moveDown(); // move down the block from the top to the board
	friend class Block; // BlockBuffer is a friend of Block
	friend class Board;
};

class Block {
	int level;
	char type;
	Cell c[4]; // 4 cells in each block
	int blockSize; // the number of the cells in this block
   public:
	Block(); // default constructor
	~Block(); // destructor
			
	void recalculate(); // after an entire row has been filled, recalculate the cells and the
			    // size of the new block
	Block& operator= (BlockBuffer &bb); // equal operator overload
	friend class Board;
};

class NextBlock {
	char type; // the type of the block
	int level; // the level right now
	std::ifstream sequence;
	PRNG prng;	
   public:
	NextBlock(); // default constructor
	~NextBlock(); // destructor
	
	void blockSelector(); // generate new block based on the level
       	char getType(); // copy the block to BlockBuffer and then generate a new block.
	int getLevel();
	void setSeed(uint32_t n);
	void levelUp() { if ( level < 3 ) level++;};
	void levelDown() { if ( level > 0 ) level--;};
	friend class Board;
};

#endif
