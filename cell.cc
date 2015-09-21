#include <iostream>
#include "cell.h"
using namespace std;

Cell::Cell(): x(0), y(0), exist(true){}

void Cell::setCell(int x, int y) {
	this->x = x;
	this->y = y;  // change cell
} 

void Cell::setLive(bool n) {
	exist = n;
}
int Cell::getX() {
	return x;
}

int Cell::getY() {
	return y;
}

bool Cell::getExist() {
	return exist;
}


