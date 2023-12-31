#include "ticTacToe.hpp"
#include <iostream>
#include <ctype.h>
#include <algorithm>
#include <array>
#include <vector>
#include <map>
#define S std::

template <typename T, int N>

bool elementExists(S array<T, N> array, T element) {
    return S find(array.begin(), array.end(), element) != array.end() ? true : false;
}

// private area

template <typename T>

ticTacToeGame::ticTacToeGame(S array<T, 9> gameStateN) {
    for (int i = 0; i < 9; i++) play(i, (char)gameStateC[i]);
}

float ticTacToeGame::ratingGameState(ticTacToeGame game, char AIC, S map<int, float>& ratings) {
    float rating = 0;
    int ID = createID(game.gameStateC);
    char playerC = AIC == 'x' ? 'o' : 'x';
    report reportForGS = game.gameReport();
    // getting the rating
    if (ratings.contains(ID)) return ratings[ID];
    else {
        int winR = 0, AICanWinR = 0;
        float depth = 9 - game.emptySpacesSize;

        if (AIC == reportForGS.win) winR = 5;
        else if (playerC == reportForGS.win) winR = -5;
        if (AIC == 'x') AICanWinR = reportForGS.xCanWin.size() + (-reportForGS.oCanWin.size());
        else if (AIC == 'o') AICanWinR = reportForGS.oCanWin.size() + (-reportForGS.xCanWin.size());
        rating = (10 - depth) * 10 / 100 * (winR + AICanWinR);
    }
    if (game.emptySpacesSize == 0 || AIC == reportForGS.win || playerC == reportForGS.win) return rating;
    //recursion time beby!
    else {
        S vector<int> emptySpaces = game.getEmptySpaces();
        for (int i = 0; i < game.emptySpacesSize; i++) {
            ticTacToeGame temp = game;
            temp.play(emptySpaces[i]);
            rating += game.ratingGameState(temp, AIC, ratings);
        }
        if (!ratings.contains(ID)) ratings[ID] = rating;
    }
    return 0;
}

int ticTacToeGame::createID(S array<char, 9> gameStateC) {
    int key = 0;
    S array<int, 9> map = { 1, 3, 9, 27, 81, 27, 9, 3, 1 };
    for (int i = 0; i < 9; i++) key += (int)gameStateC[i] + map[i];
    return key;
}

// public area

ticTacToeGame::ticTacToeGame() { gameStateC.fill('-'); }

ticTacToeGame::ticTacToeGame(S array<char, 9> gameStateC) {
    for (int i = 0; i < 9; i++) play(i, gameStateC[i]);
}

S array<char, 9> ticTacToeGame::getGameStateC() { return gameStateC; }

S vector<int> ticTacToeGame::getEmptySpaces() {
    S vector<int> temp;
    for (int i = 0; i < 9; i++) if (gameStateC[i] == '-') temp.push_back(i);
    return temp;
}

void ticTacToeGame::play(int SpaceIndex, char player) {
    switch (tolower(player)) {
    case 'a': gameStateC[SpaceIndex] = emptySpacesSize % 2 == 1 ? 'x' : 'o'; break;
    case 'x': gameStateC[SpaceIndex] = 'x'; break;
    case 'o': gameStateC[SpaceIndex] = 'o'; break;
    default: gameStateC[SpaceIndex] = '-'; emptySpacesSize++; break;
    }
    emptySpacesSize--;
}

report ticTacToeGame::gameReport() {
    report returnVal;
    S array<int, 16> patterns = { 0, 1, 3, 1, 6, 1, 0, 3, 1, 3, 2, 3, 0, 4, 2, 2 };
    for (int i = 0; i < 8; i++) {
        int empty, x = 0, o = 0;
        for (int y = 0; y < 3; y++) {
            int point = (patterns[(i * 2) + 1] * y) + (patterns[i * 2]);
            switch (gameStateC[point]) {
            case 'x': x += 1; break;
            case 'o': o += 1; break;
            default: empty = point; break;
            }
        }
        if (x == 3 || o == 3) returnVal.win = x == 3 ? 'x' : 'o';
        else if (x == 2 && o == 0) returnVal.xCanWin.push_back(empty);
        else if (o == 2 && x == 0) returnVal.oCanWin.push_back(empty);
    }
    return returnVal;
}

moves ticTacToeGame::playersMoves(char player) {
    moves returnVal;
    S array<int, 4> corners = { 0, 2, 6, 8 };
    S array<int, 4> edges = { 1, 3, 5, 7 };
    for (int i = 0; i < 9; i++) {
        if ((gameStateC[i] == player) && elementExists<int, 4>(corners, i)) {
            returnVal.corners.push_back(i);
        }
        else if ((gameStateC[i] == player) && elementExists<int, 4>(edges, i)) {
            returnVal.edges.push_back(i);
        }
        else if ((gameStateC[i] == player) && (i == 5)) {
            returnVal.center = 5;
        }
    }
    return returnVal;
}

int ticTacToeGame::AI(char AIC) {
    int AIMove = 0, bestMoveRating = 0;
    char playerC = AIC == 'x' ? 'o' : 'x';
    // first two moves
    if (9 - emptySpacesSize <= 1) {
        if (playersMoves(playerC).corners.size() != 0) AIMove = 5;
    }
    else {
        if (AIActivated == false) {
            AIActivated = true;

        }

    }
    return AIMove;
}
