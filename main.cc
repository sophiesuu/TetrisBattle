#include <iostream>
#include <fstream>
#include <sstream>
#include "block.h"
#include "board.h"

using namespace std;

int main(int argc, char** argv) {
	string cmd;
	int seed;
	Board board;
	board.setSeed(20);
	board.textonly = false;
	for (int i=0; i<argc; ++i)
	{
		string s(argv[i]);
		if (s == "-text"){
			board.textonly = true;
		}
		if (s == "-seed"){
			istringstream ss(argv[++i]);
			ss >> seed;
			board.setSeed(seed);
		}
	}	board.newGame();
	board.init();
	board.drawBuffer();
	cout << board;
	while (cin >> cmd) {
		int n;
		istringstream iss(cmd);
		board.init();
		board.drawBoard();
		if ( cmd.find("lef") != string::npos) {
			if(iss >> n){
				board.moveLeft (n);
			}else{
				board.moveLeft( 1 );
			}
		} else if ( cmd.find("ri") != string::npos) {
			if(iss >> n){
				board.moveRight (n);
			}else{
				board.moveRight( 1 );
			}
		} else if ( cmd.find("do") != string::npos) {
			if(iss >> n){
				for (int i=0; i<n; ++i){
					board.bufferDownOne();
				}
			}else{
				board.bufferDownOne();
			}
		} else if ( cmd.find("dr") != string::npos) {
			if(iss >> n){
				for (int i=0; i<n; ++i){
					board.downBuffer();
				}
			}else{
				board.downBuffer();
			}
		} else if ( cmd.find("cl") != string::npos ) {
			if(iss >> n){
				for (int i=0; i<n; ++i){
					board.clock();
				}
			}else{
				board.clock();
			}
		} else if ( cmd.find("co") != string::npos ) {
			if(iss >> n){
				for (int i=0; i<n; ++i){
					board.counterClock();
				}
			}else{
				board.counterClock();
			}
		} else if ( cmd.find("re") != string::npos ) {
			board.newGame();
		} else if ( cmd.find("levelu") != string::npos) {
			if(iss >> n){
				for (int i=0; i<n; ++i){
					board.levelUp();
				}
			}else{
				board.levelUp();	
			}	
		} else if ( cmd.find("leveld") != string::npos) {
			if(iss >> n){
				for (int i=0; i<n; ++i){
					board.levelDown();
				}
			}else{
				board.levelDown();
			}	
		} //  if
		if ( board.gameOver() ) {
			cout << "game over" << endl;
			board.newGame();
		}
		board.init();
		board.drawBuffer();
		board.drawBoard();
		cout << board;
	} // while		
				
	return 0;
}	
