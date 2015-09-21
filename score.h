#ifndef __SCORE_H__
#define __SCORE_H__
#include <iostream>

class Board;
class Score { 
	int cScore, hScore, level;
   public:
	
	Score(); // default constructor
	~Score(); // destructor
	
	void cleanLineAddScore(int lines); // add score based on the level
	void cleanBlockAddScore(int l);// add score if a block clean
	void clean(); // clean the score
	void levelUp();
	void levelDown();
	
	friend std::ostream& ::operator << (std::ostream& out, Board &board); 
};

#endif
