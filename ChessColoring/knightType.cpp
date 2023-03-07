#include "pch.h"
#include "knightType.h"



//.......................................................................................//
//.................................下面为骑士游历算法....................................//
//.......................................................................................//
#include<iostream>
knightType::knightType(int dim) {
    std::vector<std::vector<int>> fun(dim, std::vector<int>(dim, 0));
    board = fun;
}

std::vector<knightType::position> knightType::getAvailableMoves(int r, int c) {
    std::vector<position> knightMoves;
    //骑士从棋盘上的给定点最多有 8 种可能的移动，所以我们查看 8 种可能的移动
    //看看它们是否还没有被访问过并且在棋盘上。
    //如果是这样，我们将它们添加到 knightmoves 向量中。
     //可能的移动组合是(1,2),(2,1)(-1,2),(-2,1),(-1,-2),(-2,-1),(-2,1),(2,-1）
     //所以我们必须检查每一个。
    int rmoves[] = { 1,2,1,-2,-1,-2,-1,2 };
    int cmoves[] = { 2,1,-2,-1,-2,1,2,-1 };
    //尝试所有可能的骑士移动，看看它们在棋盘上是否合法并且该地点尚未被访问过    
    for (int i = 0; i < 8; i++) {
        int rnext = r + rmoves[i];
        int cnext = c + cmoves[i];
        if (rnext < board.size() && rnext >= 0 && cnext < board.size() && cnext >= 0 && board[rnext][cnext] == 0) {
            position newMove;
            newMove.row = rnext;
            newMove.col = cnext;
            for (int j = 0; j < 8; j++) {
                int rnextsub = rnext + rmoves[j];
                int cnextsub = cnext + cmoves[j];
                if (rnextsub < board.size() && rnextsub >= 0 && cnextsub < board.size() && cnextsub >= 0 && board[rnextsub][cnextsub] == 0) {
                    newMove.onwardMoves += 1;
                }
            }
            knightMoves.push_back(newMove);
            //只在最后push_back，这样我就不会丢失索引或弄乱太多    
        }
    }
    return knightMoves;
}



bool knightType::fullBoard() {
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board.size(); j++) {
            if (board[i][j] == 0) {
                return false;
                //找到未走棋格
            }
        }
    }
    return true;
}

//
int knightType::outputx(int n) {
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board.size(); j++) {
            if (board[i][j] == n)
            {
                return i;
                break;
            }
                
        }
    }
}
int knightType::outputy(int n) {
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board.size(); j++) {
            if (board[i][j] == n)
            {
                return j;
                break;
            }
                
        }
    }
}



bool knightType::knightTour(int r, int c) {
    return knightTour(r, c, 1);
}




bool knightType::knightTour(int r, int c, int tourIndex) {
    board[r][c] = tourIndex;
    //自增functionscalled和tourindex，调用fullboard，未满则继续
    tourIndex++;
    if (fullBoard() == true) {
        return true;
    }
    std::vector<position> knightMoves = getAvailableMoves(r, c);
    bool fun = false;
    //获取移动并通过搜索找到最小的移动。
    for (int f = 0; f < knightMoves.size(); f++) {
        int smallestmove = knightMoves[0].onwardMoves;
        int index = 0;
        for (int i = 1; i < knightMoves.size(); i++) {
            if (smallestmove > knightMoves[i].onwardMoves) {
                smallestmove = knightMoves[i].onwardMoves;
                index = i;
            }
        }
        fun = knightTour(knightMoves[index].row, knightMoves[index].col, tourIndex);
        if (fun == true) {
            return true;
        }
        else {
            // 如果不返回true，清除为最小的，重新查找，再次递归调用该函数            
            knightMoves.erase(knightMoves.begin() + index);
            continue;
        }
    }
    return false;
}