#ifndef ticTacToeGame_hpp
#define ticTacToeGame_hpp
#include <array>
#include <ctype.h>
#include <map>
#include <string>
#include <vector>
#include "tools.hpp"
#define S std::

struct report {
  char win = ' ';
  S vector<int> xCanWin;
  S vector<int> oCanWin;
};

class ticTacToeGame {

  bool AIActivated = false;
  S map<S string, int> ratings;
  S array<char, 9> gameState;
  S vector<int> emptySpaces;

public:
  ticTacToeGame() {
    for (int i = 0; i < 9; i++) {
      play(i, ' ');
    }
  }
  ticTacToeGame(S array<char, 9> gameState) {
    for (int i = 0; i < 9; i++) {
      play(i, gameState[i]);
    }
  }

  S array<char, 9> getGameState() { return this->gameState; }

  S vector<int> getEmptySpaces() { return this->emptySpaces; }

  int ratingGameState(S array<char, 9> gameState, char AIPlayerChar, int depth) {
    // 0 - setting up befor getting starting
    int rating = 0;
    S string key = arrayToString<9>(gameState);
    ticTacToeGame newGame(gameState);
    // 1 - getting rating
    if (ratings.find(key) != ratings.end()) {
      rating = ratings[key];
    } else {
      report gameReport = newGame.gameReport();
      int winR = gameReport.win = AIPlayerChar ? 5 : -5;
      int AICanWinR = AIPlayerChar == 'x' ? gameReport.xCanWin.size() : gameReport.oCanWin.size();
      rating = ((10 - (9 - newGame.emptySpaces.size())) * 10 / 100) * (winR + AICanWinR);
      ratings[key] = rating;
    }
    // 2 - Recursion time baby!!
    if (9 - newGame.emptySpaces.size() == depth) {
      for (int i = 0; i < newGame.emptySpaces.size(); i++) {
        S array<char, 9> gameState = newGame.getGameState();
        gameState[newGame.emptySpaces[i]] = newGame.emptySpaces.size() % 2 == 0 ? 'o' : 'x';
        rating += ratingGameState(newGame.getGameState(), AIPlayerChar, depth);
      }
      return rating;
    } else {
      return rating;
    }
  }

  void play(int SpaceIndex, char player = '\0') {
    switch (tolower(player)) {
    case '\0':
      gameState[SpaceIndex] = emptySpaces.size() % 2 == 0 ? 'o' : 'x';
      break;
    case 'x':
      gameState[SpaceIndex] = 'x';
      break;
    case 'o':
      gameState[SpaceIndex] = 'o';
      break;
    default:
      gameState[SpaceIndex] = ' ';
      emptySpaces.push_back(SpaceIndex);
      break;
    }
  }

  report gameReport() {
    report returnVal;
    S array<int, 16> patterns = {0, 1, 3, 1, 6, 1, 0, 3, 1, 3, 2, 3, 0, 4, 2, 2};
    for (int i = 0; i < 8; i++) {
      int empty, x = 0, o = 0;
      for (int y = 0; y < 3; y++) {
        int point = (patterns[(i * 2) + 1] * y) + (patterns[i * 2]);
        switch (gameState[point]) {
        case 'x':
          x += 1;
          break;
        case 'o':
          o += 1;
          break;
        default:
          empty = point;
          break;
        }
      }
      if (x == 3 || o == 3) {
        returnVal.win = x == 3 ? 'x' : 'o';
      } else if (x == 2 && o == 0) {
        returnVal.xCanWin.push_back(empty);
      } else if (o == 2 && x == 0) {
        returnVal.oCanWin.push_back(empty);
      }
    }
    return returnVal;
  }

  int AI(char player, int depth = 7) {
    int AImove = 0, bestMoveRating = 0;
    if (9 - emptySpaces.size() <= 1) {
      if (!gameState[0] == 'x' || !gameState[0] == 'o') {
        AImove = 0;
      } else {
        AImove = 4;
      }
    } else {
    }
    return AImove;
  }
};

#endif