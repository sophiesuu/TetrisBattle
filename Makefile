quadris:  cell.o block.o board.o main.o score.o window.o
	g++ -L/usr/X11R6/lib -lX11 block.o board.o cell.o main.o score.o window.o -o quadris
cell.o: cell.h cell.cc
	g++ -c cell.cc
block.o: block.h block.cc cell.h 
	g++ -c block.cc
score.o: score.h score.cc
	g++ -c score.cc
board.o: block.h cell.h board.h score.h board.cc
	g++ -c board.cc
main.o: block.h cell.h board.h main.cc
	g++ -c main.cc
window.o: window.h window.cc
	g++ -c window.cc
