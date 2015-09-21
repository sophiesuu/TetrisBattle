#include <iostream>
#include "board.h"
#include <sstream>

using namespace std;

Board::Board () {
	newboard = new char*[15];
	for ( int i = 0; i < 15 ; i++ ) {
		newboard[i] = new char[10];
	} // for
	buffer = new BlockBuffer;
	nblock = new NextBlock;
	s = new Score;
	blockNum = 0;
	level = 1;
	window = new Xwindow;
	textonly = false;
}

Board::~Board() {
	for( int i = 0; i < 15; i++ ) {
		delete[] newboard[i];
	} // for
	delete[] newboard;
	delete buffer;
	delete nblock;
	delete s;
	delete window;
	// delete s;
}

void Board::newGame() {
	blockNum = 0;
	level = 1;
	nblock->level = 1;
	s->clean();
	b.clear();
	nblock->blockSelector();
	buffer->init(nblock->getType());
	nblock->blockSelector();
}

void Board::init() {
	for ( int i = 0; i < 15; i++ ) {
		for ( int j = 0; j < 10; j++ ) {
			newboard[i][j] = 'X';
		} // for
	} // for
}

void Board::drawBuffer() {
	for ( int i = 0; i<4; i++ ) {
		newboard[buffer->c[i].getX()][buffer->c[i].getY()] = buffer->type;
	}// for
}

void Board::drawBoard() {
	for ( int i = 0; i < blockNum; i++ ) {
		for ( int j = 0; j < 4; j++ ) {
			if (b.at(i).c[j].getExist()) {
				newboard[b.at(i).c[j].getX()][b.at(i).c[j].getY()] = b.at(i).type;
			} // if
		} // for
	} // for
}

void Board::moveLeft(int n) {
	buffer->moveLeft( n );
}

void Board::moveRight(int n) {
	buffer->moveRight( n );
}

void Board::clock() {
	buffer->clock();
	for ( int i = 0; i < 4; i++ ) {
		if (newboard[buffer->c[i].getX()][buffer->c[i].getY()] != 'X' || buffer->c[i].getY() >= 10 ) {
			buffer->counterClock();
			buffer->counterClock();
			buffer->clock();
			break;
		} // if
	} // for
}

void Board::counterClock() {
	buffer->counterClock();
	for ( int i = 0; i < 4; i++ ) {
                if (newboard[buffer->c[i].getX()][buffer->c[i].getY()] != 'X' || buffer->c[i].getY() >= 10 ) {
                        buffer->clock();
                        buffer->clock();
			buffer->counterClock();
			break;
                } // if
        } // for
}

void Board::cleanBlock( int n ) {
	b.at(n).recalculate();
	if (b.at(n).blockSize == 0) {
		s->cleanBlockAddScore(b.at(n).level);	
		b.erase(b.begin() + n);
		blockNum--;
	}// if
}


bool Board::lineClean( int i ) {
	for ( int j = 0; j < 10; j++ ) {
		if ( newboard[i][j] == 'X') {
			return false;
		}// if
	} // for
	return true;
}

void Board::allMoveDown ( int i ) {
	for ( int j = 0; j < blockNum; j++ ) {
		for ( int x = 0; x < 4; x++ ) {
			if ( b.at(j).c[x].getX() == i ) {
				b.at(j).c[x].setLive(false);
			} else if ( b.at(j).c[x].getX() < i ) {
				b.at(j).c[x].setCell(b.at(j).c[x].getX()+1, b.at(j).c[x].getY());
			} // if
		} // for
	} // for
}

bool Board::checkDownPosition() {
	for ( int i = 0; i < 4; i++ ) {
		if (buffer->c[i].getX()>=14 || newboard[buffer->c[i].getX()+1][buffer->c[i].getY()] !='X' ) {
			return false;
		} // if
	} // for
	return true;
}

void Board::bufferDownOne() {
	if ( checkDownPosition() ) {
		buffer->moveDown();
	} // if
}

void Board::levelUp() {
	nblock->levelUp();
	s->levelUp();
	if ( level < 3) level ++;
}

void Board::levelDown() {
	nblock->levelDown();
	s->levelDown();
	if ( level > 0) level --;
}

void Board::downBuffer() {
	Block x;
	int cleanLines=0;
	while( checkDownPosition() ) {
		bufferDownOne();
	}
	x = *buffer;
	x.level = level;
	b.push_back( x );
	blockNum++;
	init();
	drawBoard();
	for ( int i = 0; i < 15; i++ ) {
		if ( lineClean(i) ) {
			allMoveDown(i);
			cleanLines++;
		}// if
	} // for
	s->cleanLineAddScore(cleanLines);
	
	for ( int i = 0; i < blockNum; i++ ) {
		cleanBlock(i);
	} // for
	buffer->init(nblock->getType());
	nblock->blockSelector();
}

bool Board::gameOver() {
	for ( int i = 0; i< 4; i++ ) {
		if ( newboard[buffer->c[i].getX()][buffer->c[i].getY()] !='X' ) {
			return true;
		} // if
	} // for
	return false;
}

void Board::setSeed(uint32_t n) {
	nblock->setSeed( n );
}

ostream& operator <<(ostream& out,Board &board) {
	out << "Level:      " <<board.level << endl;
	out << "Score:      " <<board.s->cScore <<endl;
	out << "Hi Score:   " <<board.s->hScore <<endl;
	out << "----------" << endl;
	for ( int i = 0; i < 15; i++ ) {
		for ( int j = 0; j < 10; j++ ) {
			if ( board.newboard[i][j] == 'X') {
				out << " ";
			} else {
				out << board.newboard[i][j];
			} // if
		} // for
		out << endl;
	}// for
	out << "----------" << endl;
	out << "Next:" << endl;
	switch (board.getNblock()->getType() ) {
		case 'I': out <<"IIII" << endl;
			break;
		case 'L': out <<"  L" <<endl<<"LLL"<<endl;
			break;
		case 'J': out <<"J" <<endl<<"JJJ"<<endl;
			break;
		case 'O': out <<"OO"<<endl<<"OO" <<endl;
			break;
		case 'T': out <<"TTT"<<endl<<" T"<<endl;
			break;
		case 'S': out <<" SS"<<endl<<"SS"<<endl;
			break;
		case 'Z': out <<"ZZ" <<endl<<" ZZ"<<endl;
			break;
	} // switch
	
	// Xwindow part
	if(board.textonly == false)
	{
	stringstream s1,s2,s3;
	s1<< board.level;
	s2<< board.s->cScore;
	s3<< board.s->hScore;
	board.window->fillRectangle(0,0,235,500,0);
	board.window->fillRectangle(1,63,233,342,1);
	board.window->fillRectangle(6,68,223,332,0);
	board.window->drawString(10,10,"Level:");
	board.window->drawString(100,10,s1.str());
	board.window->drawString(10,30,"Score:");
	board.window->drawString(100,30,s2.str());
	board.window->drawString(10,50,"Hi Score:");
	board.window->drawString(100,50,s3.str());
	int color = 0;
	for ( int i = 0; i < 15; i++ ) {
		for ( int j = 0; j < 10; j++ ) {
			switch ( board.newboard[i][j] ) {
				case 'X': color = 0; break;
				case 'I': color = 2; break;
				case 'J': color = 3; break;
				case 'T': color = 4; break;
				case 'O': color = 5; break;
				case 'S': color = 6; break;
				case 'Z': color = 7; break;
				case 'L': color = 8; break;
			} // switch
			if ( color != 0) {
				board.window->fillRectangle(10+22*j,70+22*i,20,20,color);
			}
		} // for
	} // for
	board.window->drawString(10,430,"Next: ");
	switch (board.getNblock()->getType()) {
		case 'I':
			board.window->fillRectangle(10,440,20,20,2);
			board.window->fillRectangle(32,440,20,20,2);
			board.window->fillRectangle(54,440,20,20,2);
			board.window->fillRectangle(76,440,20,20,2);
			break;
		case 'J':
                        board.window->fillRectangle(10,440,20,20,3);
                        board.window->fillRectangle(10,462,20,20,3);
                        board.window->fillRectangle(32,462,20,20,3);
                        board.window->fillRectangle(54,462,20,20,3);
                        break;
		case 'L':
                        board.window->fillRectangle(10,462,20,20,8);
                        board.window->fillRectangle(32,462,20,20,8);
                        board.window->fillRectangle(54,462,20,20,8);
                        board.window->fillRectangle(54,440,20,20,8);
                        break;
		case 'O':
                        board.window->fillRectangle(10,440,20,20,5);
                        board.window->fillRectangle(32,440,20,20,5);
                        board.window->fillRectangle(10,462,20,20,5);
                        board.window->fillRectangle(32,462,20,20,5);
                        break;
		case 'S':
                        board.window->fillRectangle(10,462,20,20,6);
                        board.window->fillRectangle(32,440,20,20,6);
                        board.window->fillRectangle(54,440,20,20,6);
                        board.window->fillRectangle(32,462,20,20,6);
                        break;
		case 'Z':
                        board.window->fillRectangle(10,440,20,20,7);
                        board.window->fillRectangle(32,440,20,20,7);
                        board.window->fillRectangle(32,462,20,20,7);
                        board.window->fillRectangle(54,462,20,20,7);
                        break;
		case 'T':
                        board.window->fillRectangle(10,440,20,20,4);
                        board.window->fillRectangle(32,440,20,20,4);
                        board.window->fillRectangle(54,440,20,20,4);
                        board.window->fillRectangle(32,462,20,20,4);
                        break;
	} // switch
	}
	return out;
}
