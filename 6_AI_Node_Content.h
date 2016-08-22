//
//  6_AI_Node_Content.h
//  Chess
//
//  Created by WangYuli on 29/11/2015.
//  Copyright © 2015 WangYuli. All rights reserved.
//

#ifndef __AI_h
#define __AI_h
#include "4_Move_Rules.h"
#include "2_KingRook_Status.h"

class Content {
private:
    int live_grade(const int& x, const int& y);
    int mobility_grade(const int& x, const int& y);
    int king_safety(const int& x, const int& y);
    int protect(const int& type);
    
public:
    int board[8][8];
    Move done_action;   //the move done to reach this board
    int  done_piece;    //the piece moved to reach this board
    bool valid;         //if the move is valid, this content is true
    
    Content();
    void PerformMove(const Content& parent, const string& player, const Move& m,KingRook_Marker& marker);
    int GetGrade();
    void operator=(const Content& c){
        CopyBoard(c.board, board);
        done_action = c.done_action;
        done_piece = c.done_piece;
        valid = c.valid;
    }
};

Content::Content(){}

void Content::PerformMove(const Content& parent, const string& player, const Move& m,KingRook_Marker& marker){  // when creating new node from a node, only changing the KR_marker!
    CopyBoard(parent.board, board);
    bool cap_p_pawn;
    bool promo_pawn;
    bool do_castle;
    valid = Move_Valid(board, player, marker, cap_p_pawn, promo_pawn, do_castle,
                       board[m.origin_x][m.origin_y], m, parent.done_piece, parent.done_action);
    if(valid){
        done_action = m;
        done_piece = board[m.origin_x][m.origin_y];
        HandleMove(board, player, m, marker, cap_p_pawn, promo_pawn, do_castle);
    }
    else done_piece = 0;
}

int Content::GetGrade(){
    int grade = 0;
    for(int i=0; i<8; i++)
        for(int j=0; j<8; j++)
            grade += 10 * live_grade(i,j) + 1 * mobility_grade(i,j) + 7 * king_safety(i,j);
    return grade;
}


int Content::live_grade(const int& x, const int& y){
    return board[x][y];
}

int Content::mobility_grade(const int& x, const int& y){     // to be updated
    int mobility = 0;
    int factor = 0;
    int piece = board[x][y];
    int piece_type = abs(board[x][y]);
    switch (piece){
        case queen:factor = 9; break;
        case -queen:factor = -9; break;
        case rook:factor = 6; break;
        case -rook:factor = -6; break;
        case bishop:factor = 4; break;
        case -bishop:factor = -4; break;
        case knight:factor = 3; break;
        case -knight:factor = -3; break;
        case pawn:factor = 1; break;
        case -pawn:factor = -1; break;
        default: break;
    }
    
    if(y==3||y==4) mobility+=5;
    else if(y==2||y==5) mobility+=3;
    else if(y==1||y==6) mobility+=1;
    
    if(piece_type==pawn){
        if(piece==pawn) mobility += x;
        else mobility += (7-x);
    }
    else {
        mobility += 7;
    }
    return mobility * factor;
}

int Content::king_safety(const int &x, const int &y){
    int king_safety = 0;
    int piece = board[x][y];
    if(abs(piece)==king)
    {
        bool myking = (piece==king)? true:false;
        for(int j = y-2; j<=x+2; j++)
            for(int i=0; i<8; i++)
                if(j>=0&&j<=7)
                {
                    int target = board[i][j];
                    bool mypiece = (target>0)? true:false;
                    if((myking && mypiece) || (!myking && mypiece))
                        king_safety += protect(abs(target));
                    else king_safety -= protect(abs(target));
                }
    }
    
    return king_safety;
}

int Content::protect(const int &type){
    if(type==queen) return 7;
    else if(type==rook) return 5;
    else if(type==bishop) return 3;
    else if(type==knight) return 2;
    
    return 0;
}




#endif /* __AI_h */
