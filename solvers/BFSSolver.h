#include<bits/stdc++.h>
#include "../models/main.h"

#ifndef  RUBIKSCUBESOLVER_BFSSOLVER_H
#define RUBIKSCUBESOLVER_BFSSOLVER_H

template <typename M,typename H> // M -> model & H -> Hash function

class BFSSolver{
private:
    vector<RubiksCube::MOVE> moves;
    unordered_map<M,bool,H> visited;  // to store the visited states
    unordered_map<M,RubiksCube::MOVE,H> move;  // to store the move that led to the current state

    M bfs(){
        queue<M> q;
        q.push(rubikscube);
        visited[rubikscube]=1;
        while(q.size()){
            auto cur = q.front();
            q.pop();

            if(cur.isSolved()) return cur;

            for(int i=0;i<18;i++){
                auto curMove= RubiksCube::MOVE(i);
                cur.move(curMove);
                if(!visited[cur]){
                    q.push(cur);
                    visited[cur]=1;
                    move[cur]=curMove;  //store the move that led to the current state
                }
                cur.invert(curMove);  //undo the move
            }
        }
        return rubikscube;  //no solution found a.k.a Base case
    }

public:
    M rubikscube;

    BFSSolver(M rc){
        rubikscube=rc;
    }

    vector<RubiksCube::MOVE> solve(){
        M solvedState = bfs();
        assert(solvedState.isSolved());  //assert means that the condition should be true that is "the cube should be solved"
        
        //doing !(()==()) coz, we did not defined the operation != 
        while(!(solvedState==rubikscube)){  // backtracking to check if the solved RB is matching with the original RB
            moves.push_back(move[solvedState]); //storing the move that lead to this state
            solvedState.invert(move[solvedState]);  //we attained this state via that move, so to do invert
        }

        rubikscube = solvedState;  //updating the original cube
        reverse(moves.begin(),moves.end());  
        return moves;

    }

};

#endif