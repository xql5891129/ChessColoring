#include "pch.h"
#include "knightType.h"



//.......................................................................................//
//.................................����Ϊ��ʿ�����㷨....................................//
//.......................................................................................//
#include<iostream>
knightType::knightType(int dim) {
    std::vector<std::vector<int>> fun(dim, std::vector<int>(dim, 0));
    board = fun;
}

std::vector<knightType::position> knightType::getAvailableMoves(int r, int c) {
    std::vector<position> knightMoves;
    //��ʿ�������ϵĸ���������� 8 �ֿ��ܵ��ƶ����������ǲ鿴 8 �ֿ��ܵ��ƶ�
    //���������Ƿ�û�б����ʹ������������ϡ�
    //��������������ǽ�������ӵ� knightmoves �����С�
     //���ܵ��ƶ������(1,2),(2,1)(-1,2),(-2,1),(-1,-2),(-2,-1),(-2,1),(2,-1��
     //�������Ǳ�����ÿһ����
    int rmoves[] = { 1,2,1,-2,-1,-2,-1,2 };
    int cmoves[] = { 2,1,-2,-1,-2,1,2,-1 };
    //�������п��ܵ���ʿ�ƶ��������������������Ƿ�Ϸ����Ҹõص���δ�����ʹ�    
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
            //ֻ�����push_back�������ҾͲ��ᶪʧ������Ū��̫��    
        }
    }
    return knightMoves;
}



bool knightType::fullBoard() {
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board.size(); j++) {
            if (board[i][j] == 0) {
                return false;
                //�ҵ�δ�����
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
    //����functionscalled��tourindex������fullboard��δ�������
    tourIndex++;
    if (fullBoard() == true) {
        return true;
    }
    std::vector<position> knightMoves = getAvailableMoves(r, c);
    bool fun = false;
    //��ȡ�ƶ���ͨ�������ҵ���С���ƶ���
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
            // ���������true�����Ϊ��С�ģ����²��ң��ٴεݹ���øú���            
            knightMoves.erase(knightMoves.begin() + index);
            continue;
        }
    }
    return false;
}