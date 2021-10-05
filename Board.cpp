#include "Board.h"
#include <ctime>

Board::Board(int r, int c) {
  nRows = r;
  nColumns = c;
  std::vector<std::vector<int> > matrix(nRows, std::vector<int> (nColumns, 0));
  BoardSpaces = matrix;
  //srand((unsigned int)time(NULL));

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
  //sleep(1);
  value = 0;
  // sleep(1);

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
std::vector<Board> Board::getAllSuccessors(std::vector<Queen> QueensList) {
  std::vector <Board> succesors;
  if (QueensList.size() > 0) {
    succesors = getSuccesor(QueensList[0]);
    // printf("%lu -----\n",succesors.size());
    for (int i = 1;i<QueensList.size();i++) {
      std::vector<Board> tempsuccesors = getSuccesor(QueensList[i]);
      //printf("%lu -----\n",tempsuccesors.size());
      succesors.insert(succesors.end(), tempsuccesors.begin(), tempsuccesors.end());
    }
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
      // 
      int valx = abs(QueensList[i].posx - QueensList[j].posx);
      int valy = abs(QueensList[i].posy - QueensList[j].posy);
      if ((valx == 1) && (valy == 1)) {
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
        printf("%u ", BoardSpaces[i][j]);
      } else {
        printf("Q ");
      }

    }
    printf("\n");
  }
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
// Hill Climbing Algorithm of the Queens Problem
Board Board::hillClimbing() {
  Board b(*this);
  Board smallestfound = b;
  timer.StartTimer();
  double timelap = 0;
  maxtime = 20.0;
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