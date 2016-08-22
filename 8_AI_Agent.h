//
//  7_AI_Agent.h
//  Chess
//
//  Created by WangYuli on 29/11/2015.
//  Copyright © 2015 WangYuli. All rights reserved.
//

#ifndef __AI_Agent_h
#define __AI_Agent_h
#include "7_AI_Search_Node.h"
#include "9_Termination_Test.h"
#include <vector>
#include <algorithm>


class AI {  //The AI will lookahead 3 steps: AI move -> human move -> AI move -> evaluate
    
private:
    vector<Move> action_lib;      //Contain all the possible moved by both sides
    void Fillin_Action_Library();
    S_Node Search_alphaBeta(S_Node root, int depth, int& best_value, S_Node& best_node,
                            string player, bool maximizer, KingRook_Marker& marker);
    S_Node Decided(const int current_board[][8], KingRook_Marker marker,
                 const int& prev_p, const Move& prev_m);
public:
    AI();
    void MakeMove(int board[][8], KingRook_Marker marker, int& prev_p, Move& prev_m);
    void Print_library();   //Debug function to print out all the moves available in action_lib
};

AI::AI()
{
    Fillin_Action_Library();
}

void AI::Fillin_Action_Library()
{
    //Normal Moves
    for(int i=0; i<8; i++)
        for(int j=0; j<8; j++)
            for(int m=0; m<8; m++)
                for(int n=0; n<8; n++)
                {
                    if(!(i==m&&j==n))
                        action_lib.push_back(Move(i, j, m, n, false));
                }
    //Promotion Moves
    for(int j=0; j<8; j++)
    {
        action_lib.push_back(Move(7, j, queen));
        action_lib.push_back(Move(7, j, rook));
        action_lib.push_back(Move(7, j, bishop));
        action_lib.push_back(Move(7, j, knight));
        action_lib.push_back(Move(0, j, queen));
        action_lib.push_back(Move(0, j, rook));
        action_lib.push_back(Move(0, j, bishop));
        action_lib.push_back(Move(0, j, knight));
    }
    
    //Castling Moves
    action_lib.push_back(Move(0, 4, 0, 7, true));
    action_lib.push_back(Move(0, 4, 0, 0, true));
    action_lib.push_back(Move(7, 4, 7, 7, true));
    action_lib.push_back(Move(7, 4, 7, 7, true));
}

S_Node AI::Search_alphaBeta(S_Node root, int depth, int& best_value, S_Node& best_node,
                            string player, bool maximizer, KingRook_Marker& marker)
{
    if(depth == 0 || Terminate(root.state.board)) {    // leaf node should do reverse checking!!!
        root.SetValue_withHeuristic();
        if (!maximizer) root.alpha = root.value;
        else root.beta = root.value;
        return root;
    }
    
    if(maximizer)
    {
        vector<Move>::iterator itr;
        for(itr=action_lib.begin(); itr!=action_lib.end();itr++)
        {
            S_Node child(root,player,(*itr),marker);
            if(child.state.valid)
            {
                S_Node temp = Search_alphaBeta(child, depth-1, best_value, best_node, player, false, marker);
                //cout<<temp.alpha<<endl;
                if(temp.value > best_value && depth == 3){
                    best_value = temp.alpha;
                    best_node = temp;
                }
                root.alpha = max(root.alpha, temp.alpha);
                if(temp.alpha>root.alpha) root.alpha = temp.alpha;
                //cout<<root.alpha<<" "<<root.beta<<endl;
            }
            if(root.alpha >= root.beta)
                break;
        }
        root.value = root.alpha;
    }
    
    else
    {
        vector<Move>::iterator itr;
        for(itr=action_lib.begin(); itr!=action_lib.end();itr++)
        {
            S_Node child(root,player,(*itr),marker);
            if(child.state.valid) {
                S_Node temp = Search_alphaBeta(child, depth-1, best_value, best_node, player, false, marker);
                root.beta = min(root.beta,temp.beta);
                if(temp.beta<root.beta) root.beta = temp.beta;
                
            }
            if(root.alpha >= root.beta)
                break;
        }
        root.value = root.beta;
    }
    return root;
}

S_Node AI::Decided(const int current_board[][8], KingRook_Marker marker,
                    const int &prev_p, const Move &prev_m)
{
    S_Node root(current_board, prev_p, prev_m);
    int chosen_value = root.alpha;
    S_Node chosen_node;
    S_Node experiment = Search_alphaBeta(root, 3, chosen_value, chosen_node,"AI", true, marker);
    return chosen_node;
}

void AI:: MakeMove(int board[][8], KingRook_Marker marker, int& prev_p, Move& prev_m)
{
    S_Node target = Decided(board, marker, prev_p, prev_m);
    CopyBoard(target.state.board, board);
    prev_m = target.state.done_action;
    prev_p = target.state.done_piece;
    PrintBoard(board);
    prev_m.Print();
}


void AI::Print_library(){
    vector<Move>::iterator itr;
    for(itr=action_lib.begin(); itr!=action_lib.end();itr++){
        (*itr).Print();
        cout<<"*********Move finished*********"<<endl<<endl;
    }
}


#endif /* __AI_Agent_h */
