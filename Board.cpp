#include "Board.h"
#include <ctime>

Board::Board(int r, int c) {
  nRows = r;
  nColumns = c;
  std::vector<std::vector<int> > matrix(nRows, std::vector<int> (nColumns, 0));
  BoardSpaces = matrix;
  for (int i = 0;i<nRows;i++) {
    int posx = rand() % nRows;
    int posy = rand() % nColumns;
    while (BoardSpaces[posx][posy] == -1) {
      posx = rand() % nRows;
      posy = rand() % nColumns;
    }
    Queen q = Queen(posx, posy);
    q.queennumber = i;
    insertQueen(q);

  }
  value = 0;

}

std::vector<Queen> Board::getQueensList() {
  return QueensList;
}
void Board::testQueensList() {
  for (int i = 0;i<QueensList.size();i++) {
    printf("%u| %u \n", QueensList[i].posx, QueensList[i].posy);
  }
}
std::vector<Board> Board::getSuccesor(Queen q) {
  Board b(*this);
  std::vector<Board> boards;
  for (int i = 0;i<nRows;i++) {
    Board test = b;
    if (test.BoardSpaces[i][q.posy] != -1) {
      Queen newQueen = Queen(i, q.posy);
      newQueen.queennumber = q.queennumber;
      test.BoardSpaces[q.posx][q.posy] = 0;
      test.BoardSpaces[newQueen.posx][newQueen.posy] = -1;
      test.QueensList[q.queennumber] = newQueen;
      boards.push_back(test);

    }

  }
  return boards;
}
std::vector <Board> Board::getAllSuccessors(std::vector<Queen> QueensList) {
  std::vector < Board > succesors;
  succesors = getSuccesor(QueensList[0]);
  for (int i = 1; i < QueensList.size(); i++) {
    std::vector < Board > tempsuccesors = getSuccesor(QueensList[i]);
    succesors.insert(succesors.end(), tempsuccesors.begin(), tempsuccesors.end());
  }

  return succesors;
}
int Board::GetValue() {
  value = 0;
  for (int i = 0;i<QueensList.size();i++) {
    for (int j = i+1;j<QueensList.size();j++) {
      //Case 1 Same Row
      if (QueensList[i].posx == QueensList[j].posx) {
        value++;
      }
      // Case 2 Same Column
      if (QueensList[i].posy == QueensList[j].posy) {
        value++;
      }
      // Case 3 Diagonal 
      // Slope of 1 indicates a diagonal between the queens
      int valx = abs(QueensList[i].posx - QueensList[j].posx);
      int valy = abs(QueensList[i].posy - QueensList[j].posy);
      if (valy == valx) {
        value++;
      }
    }
  }
  return value;
}
void Board::insertQueen(Queen q) {
  QueensList.push_back(q);
  BoardSpaces[q.posx][q.posy] = -1;
}
void Board::printBoard() {
  for (int i = 0;i<BoardSpaces.size(); i++) {
    for (int j = 0; j< BoardSpaces[0].size(); j++) {
      if (BoardSpaces[i][j] == 0) {
        printf("- "); //Makes it easier to read
      } else {
        printf("Q ");
      }

    }
    printf("\n");
  }
  //printf ( "\033[1;");
  // printf("%d \n",GetValue());
}
Board Board::getNextLowest() {
  Board b(*this);
  std::vector<Board> lists = b.getAllSuccessors(b.getQueensList());
  int value = b.GetValue();
  for (int i = 0;i<lists.size(); i++) {
    if (value - lists[i].GetValue() == 1) {
      b = lists[i];
      break;
    }
  }
  return b;
}
Board Board::RandomRestart() {

  Board b = Board(nRows, nColumns);
  return b;
}
Board Board::getSmallest() {
  int min = INT_MAX;
  Board b(*this);
  std::vector < Board > lists = b.getAllSuccessors(b.getQueensList());
  for (int i = 0;i<lists.size(); i++) {
    if (min > lists[i].GetValue()) {
      b = lists[i];
      min = lists[i].GetValue();
    }
  }
  return b;
}
Board Board::getRandomSuccessor()
{
  Board b(*this);
  std::vector<Board> boards;
  // get a random queen
  Queen q  = b.QueensList[rand()%b.QueensList.size()];
  Timer t;
  t.StartTimer();
  int x = rand()%nRows;
  int y = rand()%nColumns;
  while(BoardSpaces[x][y] == -1)
  {
      if(t.GetElapsedTime()>2)
      {
        q  = b.QueensList[rand()%b.QueensList.size()];
      }
      x = rand()%nRows;
      y = rand()%nColumns;
  }
  Board test = b;
  Queen newQueen = Queen(x, y);
  newQueen.queennumber = q.queennumber;
  test.BoardSpaces[q.posx][q.posy] = 0;
  test.BoardSpaces[newQueen.posx][newQueen.posy] = -1;
  test.QueensList[q.queennumber] = newQueen;
  return test;
}
// Hill Climbing Algorithm of the Queens Problem
Board Board::hillClimbing() {
  Board b(*this);
  Board smallestfound = b;
  timer.StartTimer();
  double timelap = 0;
  maxtime =20.0;
  while (timer.GetElapsedTime() < maxtime - 0.1) {
    b = b.getSmallest();
    if (b.GetValue() < smallestfound.GetValue()) {
      smallestfound = b;
      timelap = timer.GetElapsedTime();
    }
    if (abs(timelap - timer.GetElapsedTime()) > 2) {
      b = b.RandomRestart();
    }
  }
  return smallestfound;

}
Board Board::simulatedAnnealing() {
  //srand((unsigned int)time(NULL));
  Board b(*this);
  Board smallestfound = b;
  timer.StartTimer();
  double timelap = 0;
  maxtime = 20.0;
  int count1 = 0;
  int count2 = 0;
  while(timer.GetElapsedTime() < maxtime - 0.1) {
    Board successor = smallestfound.getRandomSuccessor();
    double compareprob = (smallestfound.GetValue()-successor.GetValue())/(maxtime-timer.GetElapsedTime());
		double expon = exp(compareprob);
    if (successor.GetValue() < smallestfound.GetValue()) {
      smallestfound = successor;
      count1++;
    }
    else if (expon>(rand()/(double)RAND_MAX))
		{
			smallestfound = successor;
		}
  }
  return smallestfound;

}