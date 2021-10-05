#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <queue>
#include <climits>
#include <iostream>
#include <cassert>
#include "Timer.h"

class Queen{
	public:
	int posx;
	int posy;
	int queennumber;
	Queen(int x,int y)
	{
		posx = x;
		posy = y;
	}

};
class Board{
public:
    Board(int r,int c); // construct a nRows by nColumns board
	int GetValue(); // get value of the current board, aka how many queens are in the wrong spot
    void insertQueen(Queen q);
    void printBoard();
	void testQueensList();
    std::vector<Queen> getQueensList();
	std::vector<Board> getSuccesor(Queen q);
	std::vector<Board> getAllSuccessors(std::vector<Queen> QueensList);
	Board getNextLowest();
	Board hillClimbing();
	Board getSmallest();
	Board RandomRestart();
	// Queen GetRandomSuccessor();
	 //void GetAllSuccessors(std::vector<Queen> & successors);
	//void Print(bool printStatistics = true);

private:
	int value;
	int nRows;
	int nColumns;
    std::vector<std::vector<int> > BoardSpaces;
	std::vector<Queen> QueensList;
	Timer timer;
	double maxtime;
};
