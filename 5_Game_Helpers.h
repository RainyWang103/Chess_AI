//
//  5_Game_Helpers.h
//  Chess
//
//  Created by WangYuli on 29/11/2015.
//  Copyright © 2015 WangYuli. All rights reserved.
//

#ifndef Helpers_h
#define Helpers_h
#include "4_Move_Rules.h"
#include "2_KingRook_Status.h"

void CopyBoard(const int board[][8], int newboard[][8]){
    for (int i=0;i<8;i++)
        for (int j=0;j<8;j++)
            newboard[i][j]=board[i][j];
}

void HandleCastle(int board[][8], const Move& current)
{
    if(current.castle_short) {
        // move king
        board[current.origin_x][6]=board[current.origin_x][current.origin_y];
        // move rook
        board[current.dest_x][5]=board[current.dest_x][current.dest_y];
    }
    if (current.castle_long){
        // move king
        board[current.origin_x][2]=board[current.origin_x][current.origin_y];
        // move rook
        board[current.dest_x][3]=board[current.dest_x][current.dest_y];
    }
    board[current.origin_x][current.origin_y]=0;
    board[current.dest_x][current.dest_y]=0;
  
}

void HandleMove(int board[][8], const string& player, const Move& current, KingRook_Marker& castle,
                const bool& cap_p_pawn, const bool& promo_pawn, const bool& do_castle)
{
    if(do_castle){                // Case1: Do castling
        HandleCastle(board, current);
        castle.Set_KR_Moved(current.origin_x, current.origin_y);
        return;
    }
    if(promo_pawn){               // Case2: Promote the pawn
        board[current.origin_x][current.origin_y]=(player=="AI")? current.promoteTo:-current.promoteTo;
        return;
    }
    
                                  // Case 3: Normal move
    if(cap_p_pawn){               // if capture the passing pawn
        board[current.origin_x][current.dest_y] = 0;
    }
    //Move the selected piece
    board[current.dest_x][current.dest_y] = board[current.origin_x][current.origin_y];
    board[current.origin_x][current.origin_y] = 0;
    
}


#endif /* Helpers_h */
