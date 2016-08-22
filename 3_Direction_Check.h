//
//  3_Direction_Check.h
//  Chess
//
//  Created by WangYuli on 28/11/2015.
//  Copyright © 2015 WangYuli. All rights reserved.
//

#ifndef Direction_Check_h
#define Direction_Check_h
#include <cmath>
//#include <algorithm>

bool In_Diagonal(const int& h_move, const int& v_move){
    return (abs(h_move)==abs(v_move))? true:false;
}

bool In_Horizontal(const int& h_move, const int& v_move){
    return (h_move!=0 && v_move==0)? true:false;
}

bool In_Vertical(const int& h_move, const int& v_move){
    return (h_move==0 && v_move!=0)? true:false;
}

string Diagonal_Direct(const int& h_move, const int& v_move){
    if(v_move > 0) //move up
        return (h_move>0)? "D_UpLeft":"D_UpRight";
    else           //move down
        return (h_move>0)? "D_DownLeft":"D_DownRight";
}

string Horizontal_Direct(const int& h_move){
    return (h_move>0)? "H_Left":"H_Right";
}

string Vertical_Direct(const int& v_move){
    return (v_move>0)? "V_UP":"V_Down";
}

bool D_UpLeft_NoBarrier(const int board[][8], const Move& m){
    int i=m.origin_x-1; int j=m.origin_y-1;
    while(i>m.dest_x && j>m.dest_y){
        if(board[i][j]!=0) return false;
        i--;j--;
    }
    return true;
}

bool D_UpRight_NoBarrier(const int board[][8], const Move& m){
    int i=m.origin_x-1; int j=m.origin_y+1;
    while(i>m.dest_x && j<m.dest_y){
        if(board[i][j]!=0) return false;
        i--;j++;
    }
    return true;
}

bool D_DownLeft_NoBarrier(const int board[][8], const Move& m){
    int i=m.origin_x+1; int j=m.origin_y-1;
    while(i<m.dest_x && j>m.dest_y){
        if(board[i][j]!=0) return false;
        i++;j--;
    }
    return true;
}

bool D_DownRight_NoBarrier(const int board[][8], const Move& m){
    int i=m.origin_x+1; int j=m.origin_y+1;
    while(i<m.dest_x && j<m.dest_y){
        if(board[i][j]!=0) return false;
        i++;j++;
    }
    return true;
}

bool H_Left_NoBarrier(const int board[][8], const Move& m){
    for(int j=m.origin_y-1;j>m.dest_y;j--)
        if(board[m.origin_x][j]!=0) return false;
    return true;
}

bool H_Right_NoBarrier(const int board[][8], const Move& m){
    for(int j=m.origin_y+1;j<m.dest_y;j++)
        if(board[m.origin_x][j]!=0) return false;
    return true;
}

bool V_Up_NoBarrier(const int board[][8], const Move& m){
    for(int i=m.origin_x-1;i>m.dest_x;i--)
        if(board[i][m.origin_y]!=0) return false;
    return true;
}

bool V_Down_NoBarrier(const int board[][8], const Move& m){
    for(int i=m.origin_x+1;i<m.dest_x;i++)
        if(board[i][m.origin_y]!=0) return false;
    return true;
}


#endif /* Direction_Check_h */
