#include <bits/stdc++.h>
#include "../models/main.h"
#include "./DFSSolver.h"

#ifndef RUBIKSCUBESOLVER_IDDFSSOLVER_H
#define RUBIKSCUBESOLVER_IDDFSSOLVER_H

template <typename M, typename H>

class IDDFSSolver{      //Iterative Deepening Depth First Search 

        //IDDFS calls DFS for different depths starting from an initial value. 
        //In every call, DFS is restricted from going beyond given depth. So basically we do DFS in a BFS fashion.

private:
    int maxDepth;
    vector<RubiksCube:: MOVE> moves;

public:
    M rubiksCube;

    IDDFSSolver(M temp_rubiksCube, int temp_maxDepth = 7){
        rubiksCube = temp_rubiksCube;
        maxDepth = temp_maxDepth;
    }

    vector<RubiksCube::MOVE> solve(){
        for(int i=1;i<=maxDepth;i++){       // for each allowable maxDepth
            DFSSolver<M,H> dfsSolver(rubiksCube,i);     // call dfs with MAXDEPTH =maxDepth accordingly
            moves = dfsSolver.solve();
            if(dfsSolver.rubiksCube.isSolved()){
                rubiksCube = dfsSolver.rubiksCube;
                break;
            }
        }
        return moves;
    }


};

#endif