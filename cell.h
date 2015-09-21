#ifndef __CELL_H__
#define __CELL_H__
#include <iostream>

class Cell {
	int x,y;
	bool exist;
   public:
	Cell(); // Cell default constructor
	void setCell(int x, int y); // change cell
	void setLive(bool n); //set it's living condition
	int getX();
	int getY();
	bool getExist();
};
#endif
