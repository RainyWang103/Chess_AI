//
//  4_Move_Rules.h
//  Chess
//
//  Created by WangYuli on 27/11/2015.
//  Copyright © 2015 WangYuli. All rights reserved.
//

#ifndef Move_Rules_h
#define Move_Rules_h
#include "1_Board_Setup.h"
#include "3_Direction_Check.h"
#include "2_KingRook_Status.h"
#include <iostream>
//#include <string>

#define PIECEDEBUG 0
#define R1R2_DEBUG 0
#define SIDE_DEBUG 0
#define CASTLE_DEBUG 0
#define PAWN_DEBUG 0


using namespace std;

// Functions to check all the rules
bool r1_InBound(const Move& m);                                           // Rule1: within boundary
bool r2_OriginDest_Ok(const int board[][8], const Move& m);               // Rule2: origin and destination ok, also not equal
bool r3_NoBarrier(const int board[][8], const Move& m, string direction); // Rule3: no barrier in the route for queen/bishop/rook

// for castling
bool KR_NoSpace(const int board[][8], const Move& m);
bool Castle_Validation(const int board[][8], const Move& current, KingRook_Marker castle, bool& do_castle);

// for pawn's move
bool Pawn_CanBePromote(const Move& m, const int& piece, bool& promo_pawn);
bool Pawn_NormalMove(const Move& m, const int& piece, const int& v_move);
bool Pawn_ToCapture(const int board[][8], const int& piece, const int& prev_piece,
                const Move& current_m, const Move& prev_m, bool& cap_p_pawn);

//// final function to check everything valid and update 3 special flags
//bool Move_Valid(const int board[][8], string player, KingRook_Marker castle,
//                bool& cap_p_pawn, bool& promo_pawn, bool& do_castle,
//                const int& piece, const Move& m, const int& prev_piece, const Move& prev_m);


bool r1_InBound(const Move& m){                              // Rule1: within boundary
    if(m.origin_x>=0 && m.origin_x<=7 && m.origin_y>=0&&m.origin_y<=7){
        if(m.dest_x>=0 && m.dest_x<=7 && m.dest_y>=0 && m.dest_y<=7)
            return true;
        if(m.promoteTo!=0) return true; // if doing promoting, no need to check destination
    }
    if(R1R2_DEBUG) cout<<"R1R2_DEBUG: R1 NOT OK"<<endl;
    return false;
}

bool r2_OriginDest_Ok(const int board[][8], const Move& m){ //Rule2: origin have piecedestination empty or contain other sides'piece
    if(m.origin_x==m.dest_x && m.origin_y==m.dest_y){
        if (R1R2_DEBUG) cout<<"R1R2_DEBUG: R2 NOT OK - positions are same"<<endl;
        return false;   // return false when two positions are the same
    }
    if(board[m.origin_x][m.origin_y]>0)             // check to eat opponents' piece or to empty place
        return (board[m.dest_x][m.dest_y]<=0 || m.promoteTo!=0)? true:false;
    else if(board[m.origin_x][m.origin_y]<0)
        return (board[m.dest_x][m.dest_y]>=0 || m.promoteTo!=0)? true:false;
    return false;   // return false when no piece in original position
}

bool r3_NoBarrier(const int board[][8], const Move& m, string direction){
    if (direction=="D_UpLeft") return D_UpLeft_NoBarrier(board, m);
    else if(direction=="D_UpRight") return D_UpRight_NoBarrier(board, m);
    else if(direction=="D_DownLeft") return D_DownLeft_NoBarrier(board, m);
    else if(direction=="D_DownRight") return D_DownRight_NoBarrier(board, m);
    else if(direction=="H_Left") return H_Left_NoBarrier(board, m);
    else if(direction=="H_Right") return H_Right_NoBarrier(board, m);
    else if(direction=="V_UP") return V_Up_NoBarrier(board, m);
    else if(direction=="V_Down") return V_Down_NoBarrier(board, m);
    return false;
}

bool KR_NoSpace(const int board[][8], const Move& m)
{
    if(m.castle_long && H_Left_NoBarrier(board, m)) return true;
    else if(m.castle_short && H_Right_NoBarrier(board, m)) return true;
    return false;
}

bool Castle_Validation(const int board[][8], const Move& current, KingRook_Marker castle, bool& do_castle)
{
    if(current.castle_short || current.castle_long)                // if trying to move king & rook
        if(r1_InBound(current) && abs(board[current.origin_x][current.origin_y]) == king
           && abs(board[current.dest_x][current.dest_y]) == rook)        // pieces are king & rook
            if(KR_NoSpace(board, current))                               // condition 1: no space between
                if(!castle.Get_KR_Moved(current.origin_x,current.origin_y) &&
                   !castle.Get_KR_Moved(current.dest_x,current.dest_y))      // condition 2: never moved
                {
                    if(CASTLE_DEBUG) cout<<"CASTLE_DEBUG: can do castle"<<endl;
                    do_castle=true;
                }
    if(CASTLE_DEBUG) cout<<"CASTLE_DEBUG: cannot do castle"<<endl;
    do_castle = false;
    return do_castle;
}


bool Pawn_CanBePromote(const Move& m, const int& piece, bool& promo_pawn){
    int target = abs(m.promoteTo);
    if(target!=king && target!=pawn)
        if( (m.origin_x==0 && piece == -pawn) || // promoting the pawn, when in line x=0 or x=7
           (m.origin_x==7 && piece == pawn)
           )
            promo_pawn = true; return true;
    return false;
}

bool Pawn_NormalMove(const Move& m, const int& piece, const int& v_move){
    if(piece == -pawn) { // -pawn, at down side
        if(v_move == 1) return true;
        else if(v_move == 2 && m.origin_x == 6) return true;
        return false;
    }
    else {  //pawn at upper side
        if(v_move == -1) return true;
        else if(v_move == -2 && m.origin_x == 1) return true;
        return false;
    }
}

bool Pawn_ToCapture(const int board[][8], const int& piece, const int& prev_piece,
                const Move& current_m, const Move& prev_m, bool& cap_p_pawn) {
    if(board[current_m.dest_x][current_m.dest_y]!=0) return true;   // capture the piece at destination
    
    else if(!prev_m.castle_short && !prev_m.castle_long &&
            abs(prev_piece) == pawn &&                             // capture the passing pawn
            abs(prev_m.origin_x - prev_m.dest_x) == 2) {
        if (board[current_m.origin_x][current_m.dest_y] == prev_piece) {
            cap_p_pawn = true;  // mark if capture the passing pawn
            return true;
        }
        else return false;
    }
    return false; // not in diagonal
}


bool Move_Valid(const int board[][8], string player, KingRook_Marker castle,
                bool& cap_p_pawn, bool& promo_pawn, bool& do_castle,
                const int& piece, const Move& m, const int& prev_piece, const Move& prev_m)
{
    //Resetting the 3 flags of this move
    cap_p_pawn = promo_pawn = do_castle = false;
    
    if(!(r1_InBound(m) && r2_OriginDest_Ok(board, m))) {
        if(R1R2_DEBUG) cout<<"R1R2_DEBUG: NOT VALID"<<endl;
        return false;
    }
    if(R1R2_DEBUG) cout<<"R1R2_DEBUG: VALID"<<endl;
    
    if(!
       (                                                        // check if moving certain player's piece
        (player=="HUMAN" && board[m.origin_x][m.origin_y]<0) ||
        (player=="AI" && board[m.origin_x][m.origin_y]>0)
        )
       )  {
        if(SIDE_DEBUG) cout<<"SIDE_DEBUG: SIDE NotMatch"<<endl;
        return false;
    }
    
    if((player=="HUMAN" && board[m.dest_x][m.dest_y]<0) ||      // check king & rook castling
       (player=="AI" && board[m.dest_x][m.dest_y]>0)){
        if(CASTLE_DEBUG) cout<<"CASTLE_DEBUG: check if doing castling"<<endl;
        return Castle_Validation(board, m, castle, do_castle);
    }
    
    int horizontal_move = m.origin_y - m.dest_y;    //_move = original - destination
    int vertical_move = m.origin_x - m.dest_x;
    string direction = "";
    bool valid = false;
    int piece_type = abs(piece);
    
    switch (piece_type) {   //only check the piece type!!!!!
        case king:  { // will never need to check r3
            if(PIECEDEBUG) cout<<"PIECE DEBUG: king"<<endl;
            if(max(abs(horizontal_move),abs(vertical_move))<=1) valid=true;
            break;
        }
        case queen: {
            if(PIECEDEBUG) cout<<"PIECE DEBUG: queen"<<endl;
            if(In_Diagonal(horizontal_move, vertical_move))
                direction=Diagonal_Direct(horizontal_move, vertical_move);
            else if(In_Horizontal(horizontal_move, vertical_move))
                direction=Horizontal_Direct(horizontal_move);
            else if(In_Vertical(horizontal_move, vertical_move))
                direction=Vertical_Direct(vertical_move);
            if(direction!="" && r3_NoBarrier(board, m, direction)) valid = true;
            break;
        }
        case rook: {
            if(PIECEDEBUG) cout<<"PIECE DEBUG: rook"<<endl;
            if(In_Horizontal(horizontal_move, vertical_move))
                direction=Horizontal_Direct(horizontal_move);
            else if(In_Vertical(horizontal_move, vertical_move))
                direction=Vertical_Direct(vertical_move);
            if(direction!="" && r3_NoBarrier(board, m, direction)) valid = true;
            break;
        }
        case bishop: {
            if(PIECEDEBUG) cout<<"PIECE DEBUG: bishop"<<endl;
            if(In_Diagonal(horizontal_move, vertical_move))
                direction=Diagonal_Direct(horizontal_move, vertical_move);
            if(direction!="" && r3_NoBarrier(board, m, direction)) valid = true;
            break;
        }
        case knight: {
            if(PIECEDEBUG) cout<<"PIECE DEBUG: knight"<<endl;
            int h_diff = abs(horizontal_move); int v_diff = abs(vertical_move);
            if( (h_diff==1&&v_diff==2) || (h_diff==2&&v_diff==1)) valid=true;
            break;
        }
        case pawn: {        //To be filled in!!! move and eat different!! can promote
            if(PIECEDEBUG) cout<<"PIECE DEBUG: pawn"<<endl;
            
            if(m.promoteTo==0) { // not promotting the pawn
                
                if(horizontal_move==0)  {//moving in vertical direction, not eat
                    if(PAWN_DEBUG) cout<<"PAWN_DEBUG: Vertical Move"<<endl;
                    valid = Pawn_NormalMove(m, piece, vertical_move);
                }
                
                else if(In_Diagonal(horizontal_move, vertical_move) &&
                        abs(horizontal_move)==1 && abs(vertical_move)==1)  {//move to eat
                    if(PAWN_DEBUG) cout<<"PAWN_DEBUG: Move To Eat"<<endl;
                    valid = Pawn_ToCapture(board, piece, prev_piece, m, prev_m, cap_p_pawn);
                }
            }
            else   { // promoting the pawn
                if(PAWN_DEBUG) cout<<"PAWN_DEBUG: Promotion"<<endl;
                valid = Pawn_CanBePromote(m, piece, promo_pawn);
            }

            break;
        }

            
        default:
            break;
    }
    
    return valid;
}




#endif /* Move_Rules_h */
