#include <iostream>
#include <fstream>
#include "block.h"

using namespace std;

BlockBuffer::BlockBuffer() {
	type = 'X';
	for (int i = 0; i < 6; i++ ) {
		c[i].setCell(0,0);
	}
	blockSize = 0;
}

BlockBuffer::~BlockBuffer() {}

void BlockBuffer::init(const char &x ) {
	switch (x) {
		case 'I':
			c[0].setCell(3,0);
			c[1].setCell(3,1); 
			c[2].setCell(3,2); 
			c[3].setCell(3,3);
			type = 'I';
			break;
		case 'J':
			c[0].setCell(3,0); 
			c[1].setCell(4,0); 
			c[2].setCell(4,1); 
			c[3].setCell(4,2);
			c[4].setCell(3,1);
			c[5].setCell(3,2);
			type = 'J';
			break; 
		case 'L':
			c[0].setCell(3,2); 
			c[1].setCell(4,0); 
			c[2].setCell(4,1); 
			c[3].setCell(4,2);
			c[4].setCell(3,0);
			c[5].setCell(3,1);
			type = 'L'; 
			break;
		case 'O':
			c[0].setCell(3,0); 
			c[1].setCell(3,1); 
			c[2].setCell(4,1); 
			c[3].setCell(4,0);
			type = 'O';
			break; 
		case 'S':
			c[0].setCell(3,1); 
			c[1].setCell(3,2); 
			c[2].setCell(4,0); 
			c[3].setCell(4,1);
			c[4].setCell(4,2);
			c[5].setCell(3,0);
			type = 'S';
			break; 
		case 'Z':
			c[0].setCell(3,0); 
			c[1].setCell(3,1); 
			c[2].setCell(4,1); 
			c[3].setCell(4,2);
			c[4].setCell(4,0);
			c[5].setCell(3,2);
			type = 'Z';
			break; 
		case 'T':
			c[0].setCell(3,0); 
			c[1].setCell(3,1); 
			c[2].setCell(3,2); 
			c[3].setCell(4,1);
			c[4].setCell(4,0);
			c[5].setCell(4,2);
			type = 'T';
			break;
	} // switch
	blockSize = 4;
}

void BlockBuffer::moveLeft( int n ) {
	for ( int i = 0; i < 4; i++ ) {
		if ( c[i].getY() - n < 0 ) return;  // check if the block can be moved to left
	} // for
	for ( int i = 0; i < 6; i++ ) {
		c[i].setCell(c[i].getX(), c[i].getY() - n ); // move the block
	} // for
}

void BlockBuffer::moveRight( int n ) {
        for ( int i = 0; i < 4; i++ ) {
                if ( c[i].getY()+ n >= 10 ) return;  // check if the block can be moved to right
        } // for
        for ( int i = 0; i < 6; i++ ) {
                c[i].setCell(c[i].getX(), c[i].getY()+ n ); // move the block
        } // for
}

void BlockBuffer::clock() {
	
	int base,baseX,baseY,baseNum = 0;
	if ( type == 'O' ) return;
	else if ( type == 'I' ) {
		if ( c[0].getX() == c[1].getX() ) {
			base = c[0].getX();
			c[0].setCell(base-3,c[0].getY());
			c[1].setCell(base-2,c[0].getY());
			c[2].setCell(base-1,c[0].getY());
			c[3].setCell(base,c[0].getY());
		} else {
			base = c[3].getX();
			c[0].setCell(base,c[0].getY());
			c[1].setCell(base,c[0].getY()+1);
			c[2].setCell(base,c[0].getY()+2);
			c[3].setCell(base,c[0].getY()+3);
		} // if
	} else {
		baseX = c[0].getX();
		baseY = c[0].getY();
		for ( int i = 1; i < 6; i++ ) {
			if ( c[i].getX() > baseX ) baseX = c[i].getX();
			if ( c[i].getY() < baseY ) baseY = c[i].getY();
		} // for
		for ( int i = 0; i < 6; i++ ) {
			if ( c[i].getX() == baseX ) baseNum++;
		} // for
		if (baseNum == 3) {
			for ( int i = 0; i < 6; i++ ) {
				if ( baseX - c[i].getX() == 1) {
					switch (c[i].getY() - baseY) {
						case 0:c[i].setCell(baseX-2,baseY+1);
							break;
						case 2:c[i].setCell(baseX,baseY+1);
							break;
					} //switch
				} else {
					switch (c[i].getY() - baseY) {
                                                case 0:c[i].setCell(baseX-2,baseY);
                                                        break;
						case 1:c[i].setCell(baseX-1,baseY);
                                                        break;
                                                case 2:c[i].setCell(baseX,baseY);
                                                        break;
                                        } //switch
				} // if
			} // for
		} else {
			for ( int i = 0; i < 6; i++ ) {
                                if ( c[i].getY() - baseY == 1) {
                                        switch (baseX - c[i].getX()) {
                                                case 0:c[i].setCell(baseX,baseY);
                                                        break;
						case 1:c[i].setCell(baseX,baseY+1);
                                                        break;
                                                case 2:c[i].setCell(baseX,baseY+2);
                                                        break;
                                        } //switch
                                } else {
                                        switch (baseX - c[i].getX()) {
                                                case 0:c[i].setCell(baseX-1,baseY);
                                                        break;
                                                case 1:c[i].setCell(baseX-1,baseY+1);
                                                        break;
                                                case 2:c[i].setCell(baseX-1,baseY+2);
                                                        break;
                                        } //switch
                                } // if
                        } // for
		}// if
	} // if
}

void BlockBuffer::counterClock() {
	int base,baseX,baseY,baseNum = 0;
	if ( type == 'O' ) return;
	else if ( type == 'I' ) {
		if ( c[0].getX() == c[1].getX() ) {
			base = c[0].getX();
			c[0].setCell(base-3,c[0].getY());
			c[1].setCell(base-2,c[0].getY());
			c[2].setCell(base-1,c[0].getY());
			c[3].setCell(base,c[0].getY());
		} else {
			base = c[3].getX();
			c[0].setCell(base,c[0].getY());
			c[1].setCell(base,c[0].getY()+1);
			c[2].setCell(base,c[0].getY()+2);
			c[3].setCell(base,c[0].getY()+3);
		} // if
	} else {
		baseX = c[0].getX();
		baseY = c[0].getY();
		for ( int i = 1; i < 6; i++ ) {
			if ( c[i].getX() < baseX ) baseX = c[i].getX();
			if ( c[i].getY() < baseY ) baseY = c[i].getY();
		} // for
		for ( int i = 0; i < 6; i++ ) {
			if ( c[i].getX() == baseX) baseNum ++;
		} // for
		if ( baseNum == 3) {
			for ( int i = 0; i < 6; i++ ) {
				if ( c[i].getX() - baseX == 1) {
					switch (c[i].getY() - baseY) {
						case 0: c[i].setCell(baseX+2,baseY+1);
							break;
						case 2: c[i].setCell(baseX,baseY+1);
                                                        break;
					} // switch
				} else {
					switch (c[i].getY() - baseY) {
                                                case 0: c[i].setCell(baseX+2,baseY);
                                                        break;
                                                case 1: c[i].setCell(baseX+1,baseY);
                                                        break;
                                                case 2: c[i].setCell(baseX,baseY);
                                                        break;
                                        } // switch
				} // if
			} // for
		} else {
			for ( int i = 0; i < 6; i++ ) {
                                if ( c[i].getY() - baseY == 1) {
                                        switch ( c[i].getX() - baseX) {
                                                case 0: c[i].setCell(baseX,baseY);
                                                        break;
						case 1: c[i].setCell(baseX,baseY+1);
                                                        break;
                                                case 2: c[i].setCell(baseX,baseY+2);
                                                        break;
                                        } // switch
                                } else {
                                        switch ( c[i].getX() - baseX) {
                                                case 0: c[i].setCell(baseX+1,baseY);
                                                        break;
                                                case 1: c[i].setCell(baseX+1,baseY+1);
                                                        break;
                                                case 2: c[i].setCell(baseX+1,baseY+2);
                                                        break;
                                        } // switch
                                } // if
                        } // for
		} // if
	} // if
}

void BlockBuffer::moveDown() {
	for ( int i = 0; i < 6; i++ ) {
		c[i].setCell(c[i].getX() + 1, c[i].getY());
	} // for
}

Block::Block(){
	level = 1;
	type = 'X';
	for ( int i = 0; i < 4; i++ ) {
		c[i].setCell(0,0);
	} // for
	blockSize = 4;
}

Block::~Block() {}

void Block::recalculate() {
	int j = 0;
	for ( int i = 0; i < 4; i++ ){
		if ( c[i].getExist() ) {
			j++;
		} // if
	} //for
	blockSize = j;
}

Block& Block::operator = (BlockBuffer &bb) {
	type = bb.type;
	for ( int i = 0; i < 4; i++ ) {
		c[i].setCell( bb.c[i].getX(), bb.c[i].getY());
	}
	blockSize = bb.blockSize;
}

	
NextBlock::NextBlock() {
	type = 'X';
	level = 1 ;
	sequence.open("sequence.txt");
}

NextBlock::~NextBlock() {}

void NextBlock::setSeed(uint32_t n) {
	prng.seed(n);
}
void NextBlock::blockSelector() {
	switch (level) {
		case 0:sequence >> type;
			break;
		case 1:switch(prng(11)) {
				case 0: type = 'Z';
					break;
				case 1: type = 'S';
					break;
				case 2:case 3: type ='I';
					break;
				case 4:case 5: type ='J';
					break;
				case 6:case 7: type ='L';
                                        break;
				case 8:case 9: type ='O';
                                        break;
				case 10:case 11: type ='T';
                                        break;
			} break;
		case 2:switch (prng(6)) {
				case 0: type = 'Z';
                                        break;
                                case 1: type = 'S';
                                        break;
				case 2: type = 'I';
                                        break;
                                case 3: type = 'J';
                                        break;
				case 4: type = 'L';
                                        break;
                                case 5: type = 'T';
                                        break;
				case 6: type = 'O';
                                        break;
			} break;
		case 3:switch ( prng(8)) {
				case 6:case 7: type ='S';
                                        break;
                                case 8:case 5: type ='Z';
					break;
				case 0: type = 'T';
                                        break;
                                case 1: type = 'O';
                                        break;
                                case 2: type = 'I';
                                        break;
                                case 3: type = 'J';
                                        break;
                                case 4: type = 'L';
			} break;
	} // switch	
}

char NextBlock::getType() {
	return type;
}

int NextBlock::getLevel(){
	return level;
}
	
