#include <bits/stdc++.h>
#include "../models/main.h"
#include "../patternDatabase/CornerPatternDatabase.h"

#ifndef RUBIKSCUBESOLVER_IDASTARSOLVER_H
#define RUBIKSCUBESOLVER_IDASTARSOLVER_H

template<typename M, typename H>

class IDAStarSolver {
private:
    CornerPatternDatabase cornerDB;
    vector<RubiksCube::MOVE> moves;
    unordered_map<M,RubiksCube::MOVE,H> moves_done;
    unordered_map<M,bool,H> visited;

    struct Node{
        M cube;
        int depth;
        int estimate;

        Node(M temp_cube, int temp_depth, int temp_estimate) 
            : cube(temp_cube), depth(temp_depth), estimate(temp_estimate) {}
    };

    struct compareCube{
        bool operator()(pair<Node,int> const &a, pair<Node,int> const &b){
            auto n1 = a.first, n2 = b.first;
            if(n1.estimate + n1.depth == n2.estimate + n2.depth){
                return n1.depth < n2.depth;   //  we send higher depth because we want to go deeper
            }
            else return n1.estimate + n1.depth > n2.estimate + n2.depth;  //  here we send lower distance because we want to go closer to the solution
        }
    };

    void resetStructure(){
        moves.clear();
        moves_done.clear();
        visited.clear();
    }

    pair<M,int> IDAStar(int limit){
        // returns {solved cube, bound}: if the cube was solved as soln was found within the bound
        // returns {rubiksCube, next_bound}, if the cube was not solved

        priority_queue<pair<Node,int>, vector<pair<Node,int>>, compareCube> pq; // for custom compare -> Type of pq is <X,vector<x>,CompFunc>
    
        Node start= Node (rubiksCube,0, cornerDB.getNumMoves(rubiksCube) );
        pq.push({start,0});

        int next_bound=INT_MAX;  // any number >20 (max moves req to solve any RB) will suffice

        while(!pq.empty()){
            
            auto top = pq.top();
            Node node= top.first;
            pq.pop();

            if(visited[node.cube]) continue;  //pruning the visited nodes

            visited[node.cube]=true;
            moves_done[node.cube]= RubiksCube::MOVE(top.second); // update the current move in the moves_done map

            if(node.cube.isSolved()) return {node.cube, limit}; // base  case
            node.depth++;
            for(int i=0;i<18;i++){
                auto cur_move = RubiksCube::MOVE(i);
                node.cube.move(cur_move); // mentioning the move required to get to this state

                if(!visited[node.cube]){
                    node.estimate = cornerDB.getNumMoves(node.cube); // getting the estimate of the current node
                    if(node.depth + node.estimate > limit) next_bound = min(next_bound, node.depth + node.estimate);  // finding the minimum next limit value to make repeat the IDA* untill the solution
                    else pq.push({node, i});        // else dijkstra's algo
                }
                node.cube.invert(cur_move);
            }
        }
        return {rubiksCube, next_bound};
    }

public:
    M rubiksCube;

    IDAStarSolver(M temp_rubiksCube, string fileName) {
        rubiksCube = temp_rubiksCube;
        cornerDB.fromFile(fileName);
    }

    vector<RubiksCube::MOVE> solve() {

        int bound = 1;                  // -----------> try it with 0
        auto p = IDAStar(bound);

        while(p.second != bound){
            resetStructure();
            bound = p.second;
            p = IDAStar(bound);
        } 

        M solved_cube = p.first;

        assert(solved_cube.isSolved());  //assert is used when the output is false then it will throw an error

        M cur_cub = solved_cube;
        while(!(cur_cub == rubiksCube)){
            RubiksCube::MOVE move = moves_done[cur_cub];  // getting the move from the moves_done map
            moves.push_back(move);
            cur_cub.invert(move);  // inverting the move to get the previous cube and finnaly the rubiksCube in  a state of solved_cube
        }

        rubiksCube = solved_cube;
        reverse(moves.begin(), moves.end());
        return moves;
    }

};

#endif