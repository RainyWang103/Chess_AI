//
//  1_Board_Setup.h
//  Chess
//
//  Created by WangYuli on 27/11/2015.
//  Copyright © 2015 WangYuli. All rights reserved.
//

#ifndef Board_Setup_h
#define Board_Setup_h
using namespace std;

//grade: king, queen, bishop, knight and pawn are about 200, 9, 5, 3, 3, 1,
//AI using positive values, user using negative values
const int king = 20000;
const int queen = 90;
const int rook = 60;
const int bishop = 40;
const int knight = 30;
const int pawn = 10;

//The variable should be constant!!!
const int start_board[8][8] = { rook,  knight,  bishop,  queen,  king,  bishop,  knight,  rook,
                                pawn,  pawn,    pawn,    pawn,   pawn,  pawn,    pawn,    pawn,
                                0,     0,       0,       0,      0,     0,       0,       0,
                                0,     0,       0,       0,      0,     0,       0,       0,
                                0,     0,       0,       0,      0,     0,       0,       0,
                                0,     0,       0,       0,      0,     0,       0,       0,
                                -pawn, -pawn,   -pawn,   -pawn,  -pawn, -pawn,   -pawn,   -pawn,
                                -rook, -knight, -bishop, -queen, -king, -bishop, -knight, -rook
                              };

string Piece(const int& piece)
{
    string t = "";
    switch(piece){
        case 0:
            t = "."; break;
        case rook:
            t = "r"; break;
        case knight:
            t = "n"; break;
        case bishop:
            t = "b"; break;
        case queen:
            t = "q"; break;
        case king:
            t = "k"; break;
        case pawn:
            t = "p"; break;
        case -rook:
            t = "R"; break;
        case -knight:
            t = "N"; break;
        case -bishop:
            t = "B"; break;
        case -queen:
            t = "Q"; break;
        case -king:
            t = "K"; break;
        case -pawn:
            t = "P"; break;
        case -1:
            t = "X"; break; //origin
        case -2:
            t = "Y"; break; //destination
    }
    return t;
}
struct Move {
    int origin_x, origin_y;
    int dest_x, dest_y;
    int promoteTo;   // To promote the pawn
    bool castle_short;
    bool castle_long;
    Move() {
        origin_x = origin_y = 0;
        dest_x = dest_y = 0;
        promoteTo = 0;  // handle promoting the pawn
        castle_short = castle_long = false;
    }
    
    Move(int x1, int y1, int x2, int y2, bool will_castle){   //ai: handle simple movement and castling
        origin_x = x1; origin_y = y1;
        dest_x = x2;   dest_y = y2;
        promoteTo = 0;  // handle promoting the pawn
        if(will_castle){
            castle_long  = (origin_y - dest_y == 4)? true:false;
            castle_short = (castle_long)? false:true;
        }
        else castle_short = castle_long = false;
    }
    
    Move(int x1, int y1, int target){                        // ai: handle promoting the pawn
        origin_x = x1; origin_y = y1; promoteTo = target;
        dest_x = dest_y = -22;
        castle_short = castle_long = false;
    }
    
    Move(const string& command) {                            //User: 5 digit command!! last one for Castling Uppercase
        origin_x = int('8'-command[1]); origin_y = int(command[0]-'a');
        
        if(command[4]=='c') {            // handle castling, origin:king, dest:rook
            dest_x = int('8'-command[3]); dest_y = int(command[2]-'a');
            castle_long  = (origin_y - dest_y == 4)? true:false;
            castle_short = (castle_long)? false:true;
            promoteTo = 0;
        }
        
        else if(command[2]!='t'){        // handle simple movement
            dest_x = int('8'-command[3]); dest_y = int(command[2]-'a');
            promoteTo = 0; castle_short = castle_long = false;
        }
        else {                           // handle promoting the pawn
            if (command[3]=='q') promoteTo = queen;
            else if(command[3]=='r') promoteTo = rook;
            else if(command[3]=='b') promoteTo = bishop;
            else if(command[3]=='n') promoteTo = knight;
            dest_x = dest_y = -22;
            castle_short = castle_long = false;
        }
    }
    
    void operator=(const Move& m){
        origin_x = m.origin_x; origin_y = m.origin_y;
        dest_x = m.dest_x; dest_y = m.dest_y;
        promoteTo = m.promoteTo;
        castle_short = m.castle_short; castle_long = m.castle_long;
    }
    
    void Print(){   // Debug function
        cout<<"---------THIS MOVE IS----------"<<endl;
        //cout<<"-------------------------------"<<endl;
        if(promoteTo!=0){
            cout<<"Promote pawn in "<<char('a'+origin_y)<<char('8'-origin_x)
                <<" To "<<Piece(promoteTo)<< " !!"<<endl;
        }
        else if(castle_short)
            cout<<"Short Castle !!"<<endl<<endl;
        else if(castle_long)
            cout<<"Long Castle !!"<<endl;
        else
        {
            cout<<char('a'+origin_y)<<char('8'-origin_x)<<" TO "
                <<char('a'+dest_y)<<char('8'-dest_x)<<" !!"<<endl;
        }
        cout<<endl;
    }
};


void PrintBoard(const int input_board[][8])
{
    cout<<"*****************************"<<endl
        <<"**** Current Board Below ****"<<endl
        <<"*****************************"<<endl<<endl;
    for(int i=0; i<8; i++)
    {
        cout<<""<<8-i<<" ";
        for(int j=0; j<8; j++)
            cout<<" "<<Piece(input_board[i][j])<<" ";
        cout<<endl<<endl;
    }
    cout<<"__";
    for(int i=0; i<8; i++)
        cout<<"_"<<char(i+'a')<<"_";
    cout<<"___"<<endl<<endl;
}


#endif /* Board_Setup_h */
