#pragma once
#include <vector>
class knightType
{
public:
    struct position
    {
        position(int r = 0, int c = 0, int o = 0)
        {
            row = r;
            col = c;
            onwardMoves = o;
        }
        int row;
        int col;
        int onwardMoves;
    };
    //std::vector<std::vector<int>> board;
    knightType(int = 8);
    bool knightTour(int, int);
    int outputx(int n);
    int outputy(int n);
private:
    bool knightTour(int, int, int);
    std::vector<position> getAvailableMoves(int, int);
    bool fullBoard();
    std::vector<std::vector<int>> board;
};
