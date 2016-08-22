//
//  9_Termination_Test.h
//  Chess
//
//  Created by WangYuli on 29/11/2015.
//  Copyright © 2015 WangYuli. All rights reserved.
//

#ifndef __Termination_Test_h
#define __Termination_Test_h
#include "4_Move_Rules.h"

bool AI_Win(const int board[][8])
{
    for(int i=0; i<8; i++)
        for(int j=0; j<8; j++)
            if(board[i][j]==-king) return false;
    return true;
}

bool Human_Win(const int board[][8])
{
    for(int i=0; i<8; i++)
        for(int j=0; j<8; j++)
            if(board[i][j]==king) return false;
    return true;
}

bool Terminate(const int board[][8]){
    bool human_win = true;
    bool ai_win = true;
    for(int i=0; i<8; i++)
        for(int j=0; j<8; j++)
        {
            if(board[i][j]==king) human_win=false;
            else if(board[i][j]==-king) ai_win=false;
        }
    return (human_win||ai_win);
    
}

#endif /* __Termination_Test_h */
