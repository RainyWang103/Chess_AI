//
//  main.cpp
//  Chess
//
//  Created by WangYuli on 27/11/2015.
//  Copyright © 2015 WangYuli. All rights reserved.
//

#include <iostream>
//#include "Board_Setup.h"
#include "5_Game_Helpers.h"
#include "Debug_Tests.h"
#include "8_AI_Agent.h"
#include "9_Termination_Test.h"


void PrintNotice()
{
    cout<<"------------Your Turn------------------------- "<<endl;
    cout<<"Notice: Enter move in 5 digits lowecase"<<endl
    <<"The last digit indicates casting(C)"<<endl
    <<"1. Normal move include En Passent: a2a3x"<<endl
    <<"   To move the pawn in (a2) to (a3)"<<endl
    <<"2. Castling: king and rook location"<<endl
    <<"   with king's position first: e8a8c"<<endl
    <<"   Castling king(e8) and rook(a8)"<<endl
    <<"3. Promoting: pawn location and target"<<endl
    <<"   specify piece promote to: a1tqx"<<endl
    <<"   promote pawn(a1) to queen"<<endl<<endl;
}

void Play_Human_vs_AI(int myBoard[][8], KingRook_Marker& castle_reg)
{
    AI myAI;
    string user_command;
    bool cap_p_pawn = false;
    bool promo_pawn = false;
    bool do_castle = false;
    Move prev_move; int prev_piece = 0;
    string player = "HUMAN";
    
    PrintNotice(); cout<<"Type in your command: "; cin>>user_command;
    Move m(user_command);
    bool validmove = Move_Valid(myBoard, player, castle_reg, cap_p_pawn, promo_pawn, do_castle,
                                myBoard[m.origin_x][m.origin_y], m, prev_piece, prev_move);
    while(!validmove){
        cout<<"Move Not valid!!!!"<<endl;
        cout<<"Type in your command: "; cin>>user_command;
        Move new_move(user_command); m = new_move;
        validmove = Move_Valid(myBoard, player, castle_reg, cap_p_pawn, promo_pawn, do_castle,
                               myBoard[m.origin_x][m.origin_y], m, prev_piece, prev_move);
    }
    cout<<"Valid Move ---- Handle below: "<<endl;
    prev_move = m;
    prev_piece = myBoard[m.origin_x][m.origin_y];
    HandleMove(myBoard, player, m, castle_reg, cap_p_pawn, promo_pawn, do_castle);
    PrintBoard(myBoard);
    m.Print();
    player="AI";
    
    while(!Terminate(myBoard))
    {
        
        if(player=="HUMAN" && !AI_Win(myBoard))
        {
            PrintNotice(); cout<<"Type in your command: "; cin>>user_command;
            Move temp_move(user_command); m = temp_move;
            validmove = Move_Valid(myBoard, player, castle_reg, cap_p_pawn, promo_pawn, do_castle,
                                   myBoard[m.origin_x][m.origin_y], m, prev_piece, prev_move);
            while(!validmove){
                cout<<"Move Not valid!!!!"<<endl;
                cout<<"Type in your command: "; cin>>user_command;
                Move again_move(user_command); m = again_move;
                validmove = Move_Valid(myBoard, player, castle_reg, cap_p_pawn, promo_pawn, do_castle,
                                       myBoard[m.origin_x][m.origin_y], m, prev_piece, prev_move);
            }
            cout<<"Valid Move ---- Handle below: "<<endl;
            prev_move = m;
            prev_piece = myBoard[m.origin_x][m.origin_y];
            HandleMove(myBoard, player, m, castle_reg, cap_p_pawn, promo_pawn, do_castle);
            PrintBoard(myBoard);
            m.Print();
            player="AI";
        }
        
        if(player=="AI" && !Human_Win(myBoard))
        {
            cout<<"------------AI's Turn------------------------- "<<endl;
            myAI.MakeMove(myBoard, castle_reg, prev_piece, prev_move);
            player="HUMAN";
        }
    }
    
    if(AI_Win(myBoard)) cout<<"AI WIN!"<<endl;
    else if(Human_Win(myBoard)) cout<<"YOU WIN!"<<endl;
    
    
    
}

//void Test_AI_Decision(int myBoard[][8], KingRook_Marker& castle_reg)
//{
//    AI myAI;
//    //    bool cap_p_pawn = false;
//    //    bool promo_pawn = false;
//    //    bool do_castle = false;
//    Move prev_move; int prev_piece = 0;
//    string player = "AI";
//    cout<<"------------AI's Turn------------------------- "<<endl;
//    myAI.MakeMove(myBoard, castle_reg, prev_piece, prev_move);
//    player="HUMAN";
//}


int main() {
    
    
    int myBoard[8][8];
    KingRook_Marker castle_register;
    CopyBoard(start_board, myBoard);
    cout<<"****************************************"<<endl
        <<"******** Welcome To Chess Game *********"<<endl
        <<"****************************************"<<endl<<endl;
    cout<<"Notice: Enter move in 5 digits lowecase"<<endl
        <<"The last digit indicates casting(C)"<<endl
        <<"1. Normal move include En Passent: a2a3x"<<endl
        <<"   To move the pawn in (a2) to (a3)"<<endl
        <<"2. Castling: king and rook location"<<endl
        <<"   with king's position first: e8a8c"<<endl
        <<"   Castling king(e8) and rook(a8)"<<endl
        <<"3. Promoting: pawn location and target"<<endl
        <<"   specify piece promote to: a1tqx"<<endl
        <<"   promote pawn(a1) to queen"<<endl;
    cout<<endl;
    PrintBoard(myBoard);
    Play_Human_vs_AI(myBoard, castle_register);
    
    //Test_AI_Decision(myBoard,castle_register);
    //TEST_AI_Move_Library(); //PASS
    //TEST_S_Node();//Pass
    
    
    
    return 0;
}
