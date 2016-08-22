
//
//  7_AI_Search_Node.h
//  Chess
//
//  Created by WangYuli on 29/11/2015.
//  Copyright © 2015 WangYuli. All rights reserved.
//

#ifndef Header_h
#define Header_h
#include "6_AI_Node_Content.h"

struct S_Node{
    Content state;
    int alpha, beta;
    int value;
    bool valid;
    
    S_Node(){}
    
    S_Node(const int parent_board[][8], const int& prev_p, const Move& prev_m){ // create root node
        CopyBoard(parent_board, state.board); state.valid = true;
        state.done_action = prev_m; state.done_piece = prev_p;
        alpha = -100000000;
        beta  =  100000000;
        valid = true;
    }
    S_Node(const S_Node& parent, const string& player, const Move& m,KingRook_Marker& marker){
        state.PerformMove(parent.state, player, m, marker);
        alpha = parent.alpha;
        beta = parent.beta;
        valid = state.valid;
    }
    
    void SetValue_withHeuristic(){
        value = state.GetGrade();
    }
    
    void Print() {
        PrintBoard(state.board);
        state.done_action.Print();
        cout<<"moving piece: "<<state.done_piece<<endl;
        cout<<"alpha = "<<alpha<<endl;
        cout<<"beta = "<<beta<<endl;
        cout<<"value = "<<value<<endl;
        cout<<"valid = "<<valid<<endl;
    }
};

#endif /* Header_h */
