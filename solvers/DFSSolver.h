#include<bits/stdc++.h>

#include "../models/main.h"

#ifndef RUBIKSCUBESOLVER_DFSSOLVER_H
#define RUBIKSCUBESOLVER_DFSSOLVER_H

template <typename M, typename H> // M -> model & H -> Hash function

class DFSSolver{
private:

    vector<RubiksCube::MOVE> moves;
    int maxSearchDepth;

    bool dfs(int depth){                        // NOTE : we are not maintaining the visited array to guarantee the solution (given depth is below specific value)
        if(rubiksCube.isSolved()) return 1;     //base case
        if(depth > maxSearchDepth)  return 0;     //base case

        for(int i=0;i<18;i++){
            rubiksCube.move(RubiksCube::MOVE(i));           //make a move
            moves.push_back(RubiksCube::MOVE(i));           //store the move
            if( dfs(depth + 1))  return 1;      //recursive call
            moves.pop_back();                   //undo the moves
            rubiksCube.invert(RubiksCube::MOVE(i));         //undo the RB config
        }
        return 0;                              //no solution found
    }
public:
    M rubiksCube;

    DFSSolver(M rubiksCube, int maxSearchDepth = 8){  //Max depth allowed is 8 by default
        this->rubiksCube = rubiksCube;                //initialize the cube
        this->maxSearchDepth = maxSearchDepth;        //initialize the max depth
    }

    vector<RubiksCube::MOVE> solve(){              //solve the cube
        dfs(1);
        return moves;
    }
};

#endif
