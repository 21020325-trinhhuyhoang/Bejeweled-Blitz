#include "PlayGround.h"

PlayGround::PlayGround()
    : board(10, vector<int>(10)), boardCheck(10, vector<int>(10)), boardBom(10, vector<int>(10))
{
    newGame();
}

PlayGround::~PlayGround()
{
}

void PlayGround::addGem(int i, int j)
{
    board[i][j] = (rand() % 7) + 1;
}

void PlayGround::addBomGem(int i, int j, int time)
{
    boardBom[i][j] = time;
}

void PlayGround::addGems()
{
    for (int i = 0; i < 10; i++)
    for (int j = 0; j < 10; j++) {
        addGem(i, j);
        addBomGem(i, j, -1);
    }
}

void PlayGround::addNewBomGem(int turn)
{
    int j;
    if (turn < 20) {
    if (turn % 2 == 0) {
        do {
            j = (rand() % 8)+1;
        } while (boardBom[0][j] >= 0);
        addBomGem(0, j, 20 - turn/4);
    }
    } else {
        do {
            j = (rand() % 8)+1;
        } while (boardBom[0][j] >= 0);
        addBomGem(0, j, 15);
    }
}
    
void PlayGround::swapGem(int x1, int y1, int x2, int y2)
{
    int temp = board[x1][y1];
    board[x1][y1] = board[x2][y2];
    board[x2][y2] = temp;
    temp = boardBom[x1][y1];
    boardBom[x1][y1] = boardBom[x2][y2];
    boardBom[x2][y2] = temp;
}

int PlayGround::getGem(int i, int j)
{
    return board[i][j];
}

int PlayGround::getBomGem(int i, int j)
{
    return boardBom[i][j];
}

void PlayGround::resetBoardCheck()
{
    for (int i = 0; i < 10; i++)
    for (int j = 0; j < 10; j++) boardCheck[i][j] = 0;
}

bool PlayGround::explode()
{
    for (int i = 0; i < 10; i++)
    for (int j = 0; j < 10; j++) {
        boardBom[i][j]--;
        if (boardBom[i][j] == 0) return true;
    }
    return false;
}

void PlayGround::findGems(bool &correct)
{
    for (int i = 0; i < 10; i++)
    for (int j = 1; j < 9; j++)
        if (board[i][j] == board[i][j-1] && board[i][j] == board[i][j+1]) {
            boardCheck[i][j]++;
            boardCheck[i][j-1] += 2;
            boardCheck[i][j+1] += 2;
            correct = true;
        }
    for (int i = 1; i < 9; i++)
    for (int j = 0; j < 10; j++)
        if (board[i][j] == board[i-1][j] && board[i][j] == board[i+1][j]) {
            boardCheck[i][j]++;
            boardCheck[i-1][j] += 2;
            boardCheck[i+1][j] += 2;
            correct = true;
        }
}

void PlayGround::deleteGems()
{
    for (int i = 0; i < 10; i++)
    for (int j = 0; j < 10; j++)
        switch (boardCheck[i][j]) {
        case 0:
            break;
        case 1: case 2:
            board[i][j] = 0;
            boardBom[i][j] = -1;
            break;
        case 3:
            for (int i0 = 0; i0 < 10; i0++) {
                board[i0][j] = 0;
                boardBom[i0][j] = -1;
            }
            for (int j0 = 0; j0 < 10; j0++) {
                board[i][j0] = 0;
                boardBom[i][j0] = -1;
            }
            break;
        case 4:
            for (int i0 = i-2; i0 <= i+2; i0++)
            for (int j0 = j-2; j0 <= j+2; j0++)
                if ((i0 >= 0 && i0 < 10) && (j0 >=0 && j0 < 10)) {
                    board[i0][j0] = 0;
                    boardBom[i0][j0] = -1;
                }
            break;
        default:
            for (int i0 = i-2; i0 <= i+2; i0++)
            for (int j0 = 0; j0 < 10; j0++) 
                if (i0 >= 0 && i0 < 10) {
                    board[i0][j0] = 0;
                    boardBom[i0][j0] = -1;
                }
            for (int j0 = j-2; j0 <= j+2; j0++)
            for (int i0 = 0; i0 < 10; i0++) {
                if (j0 >=0 && j0 < 10) {
                    board[i0][j0] = 0;
                    boardBom[i0][j0] = -1;
                }
            }
            break;
        }
}

void PlayGround::newGame()
{
    addGems();
    bool k = true;
    while (k) {
        k = false;
        resetBoardCheck();
        findGems(k);
        deleteGems();
        for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            if (getGem(i, j) == 0) {
                for (int i0 = i; i0 > 0; i0--) {
                    swapGem(i0, j, i0-1, j);
                }
                addGem(0, j);
            }
    }
    addNewBomGem(0);
}