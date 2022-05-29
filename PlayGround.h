#ifndef PlayGround_h
#define PlayGround_h

#include <vector>
#include <cstdlib>

using namespace std;

typedef vector<vector<int>> Board;

class PlayGround {
    Board board;
    Board boardCheck;
    Board boardBom;
public:
    PlayGround();
    ~PlayGround();
    void addGem(int i, int j);
    void addBomGem(int i, int j, int time);
    void addGems();
    void addNewBomGem(int turn);
    void swapGem(int x1, int y1, int x2, int y2);
    int getGem(int i, int j);
    int getBomGem(int i, int j);
    void resetBoardCheck();
    bool explode();
    void findGems(bool &correct);
    void deleteGems();
    void newGame();
};

#endif