#include "CornerDBMaker.h"

using namespace std;

CornerDBMaker::CornerDBMaker(string fileName_temp) {    //setting the filename
    fileName = fileName_temp;                           
}

CornerDBMaker::CornerDBMaker(string fileName_temp, uint8_t init_val) {      //setting the filename and the initial value of the database
    fileName = fileName_temp;
    cornerDB = CornerPatternDatabase(init_val);
}

bool CornerDBMaker::bfsAndStore() {     //BFS to find the minimum moves to solve the cube
    RBBitboard cube;
    queue<RBBitboard> q;
    q.push(cube);

    cornerDB.setNumMoves(cube,0);
    int cur_depth = 0;

    while(q.size()){
        int n = q.size();
        cur_depth++;        

        if(cur_depth == 8) break;    // hyperparameter

        for(int i = 0; i < n; i++){     // iterating over the queue at once
            RBBitboard node = q.front();
            q.pop();

            for(int j=0;j<18;j++){
                auto cur_move = RubiksCube::MOVE(j);

                node.move(cur_move);

                if((int)cornerDB.getNumMoves(node) > cur_depth){  // if more moves are required to solve the cube than the current depth, then update the number of moves
                    cornerDB.setNumMoves(node,cur_depth);  
                    q.push(node);       // its possibilities are not yet explored
                } 
                node.invert(cur_move);  // undo the move
            }
        }
    }
    cornerDB.toFile(fileName);      // write the database to a file
    return true;        // return true if the database is successfully created
}