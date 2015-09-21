#include <iostream>
#include "score.h"

using namespace std;

Score::Score() {
	cScore = 0;
	hScore = 0;
	level = 1;
}

Score::~Score() {}

void Score::cleanLineAddScore(int lines) {
	if ( lines == 0 ) return;
	cScore = cScore + (lines+level)*(lines+level);
	if ( hScore < cScore ) hScore = cScore;
}

void Score::cleanBlockAddScore(int l) {
	cScore += ( l*l) ;
	if ( hScore < cScore) hScore = cScore;
}

void Score::clean() {
	cScore = 0;
	level = 1;
}

void Score::levelUp() {
	if (level < 3 ) level++;
}

void Score::levelDown() {
	if (level > 0 ) level--;
}
