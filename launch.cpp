
#include <bits/stdc++.h>
#include "models/main3dArray.cpp"
#include "models/main1dArray.cpp"
#include "models/mainBitboard.cpp"
#include "solvers/DFSSolver.h"
#include "solvers/BFSSolver.h"
#include "solvers/IDDFSSolver.h"
#include "solvers/IDAstarSolver.h"
#include "patternDatabase/CornerPatternDatabase.h"
#include "patternDatabase/CornerDBMaker.h"

using namespace std;

int main() {
//    RB3dArray object3DArray;
//    RB1dArray object1dArray;
//    RBBitboard objectBitboard;

//    object3DArray.print();

//    if (object3DArray.isSolved()) cout << "SOLVED\n\n";
//    else cout << "NOT SOLVED\n\n";

//    if (object1dArray.isSolved()) cout << "SOLVED\n\n";
//    else cout << "NOT SOLVED\n\n";

//    if (objectBitboard.isSolved()) cout << "SOLVED\n\n";
//    else cout << "NOT SOLVED\n\n";

//    objectBitboard.u();
//    object3DArray.u();
//    object1dArray.u();
//    objectBitboard.print();
//    object3DArray.print();
//    object1dArray.print();

//    objectBitboard.l();
//    object3DArray.l();
//    object1dArray.l();
//    objectBitboard.print();
//    object3DArray.print();
//    object1dArray.print();

//    objectBitboard.f();
//    object3DArray.f();
//    object1dArray.f();
//    objectBitboard.print();
//    object3DArray.print();
//    object1dArray.print();

//    objectBitboard.r();
//    object3DArray.r();
//    object1dArray.r();
//    objectBitboard.print();
//    object3DArray.print();
//    object1dArray.print();

//    objectBitboard.b();
//    object3DArray.b();
//    object1dArray.b();
//    objectBitboard.print();
//    object3DArray.print();
//    object1dArray.print();

//    objectBitboard.d();
//    object3DArray.d();
//    object1dArray.d();
//    objectBitboard.print();
//    object3DArray.print();
//    object1dArray.print();

//    if (object3DArray.isSolved()) cout << "SOLVED\n\n";
//    else cout << "NOT SOLVED\n\n";

//    if (object1dArray.isSolved()) cout << "SOLVED\n\n";
//    else cout << "NOT SOLVED\n\n";

//    if (objectBitboard.isSolved()) cout << "SOLVED\n\n";
//    else cout << "NOT SOLVED\n\n";

//    objectBitboard.dPrime();
//    object3DArray.dPrime();
//    object1dArray.dPrime();
//    objectBitboard.print();
//    object3DArray.print();
//    object1dArray.print();

//    objectBitboard.bPrime();
//    object3DArray.bPrime();
//    object1dArray.bPrime();
//    objectBitboard.print();
//    object3DArray.print();
//    object1dArray.print();

//    objectBitboard.rPrime();
//    object3DArray.rPrime();
//    object1dArray.rPrime();
//    objectBitboard.print();
//    object3DArray.print();
//    object1dArray.print();

//    objectBitboard.fPrime();
//    object3DArray.fPrime();
//    object1dArray.fPrime();
//    objectBitboard.print();
//    object3DArray.print();
//    object1dArray.print();

//    objectBitboard.lPrime();
//    object3DArray.lPrime();
//    object1dArray.lPrime();
//    objectBitboard.print();
//    object3DArray.print();
//    object1dArray.print();

//    objectBitboard.uPrime();
//    object3DArray.uPrime();
//    object1dArray.uPrime();
//    objectBitboard.print();
//    object3DArray.print();
//    object1dArray.print();

//    if (object3DArray.isSolved()) cout << "SOLVED\n\n";
//    else cout << "NOT SOLVED\n\n";

//    if (object1dArray.isSolved()) cout << "SOLVED\n\n";
//    else cout << "NOT SOLVED\n\n";

//    if (objectBitboard.isSolved()) cout << "SOLVED\n\n";
//    else cout << "NOT SOLVED\n\n";

//     // Create two Cubes ------------------------------------------------------------------------------------------

//    RB3dArray cube1;
//    RB3dArray cube2;

//    RB1dArray cube1;
//    RB1dArray cube2;

//    RBBitboard cube1;
//    RBBitboard cube2;


// //  Equality and assignment of cubes --------------------------------------------------------------------------

//    if(cube1 == cube2) cout << "Is equal\n";
//    else cout << "Not Equal\n";

//    cube1.randomShuffleCube(1);

//    if(cube1 == cube2) cout << "Is equal\n";
//    else cout << "Not Equal\n";

//    cube2 = cube1;

//    if(cube1 == cube2) cout << "Is equal\n";
//    else cout << "Not Equal\n";


// //  Unordered_map of Cubes  ------------------------------------------------------------------------------------


//    unordered_map<RB3dArray, bool, Hash3d> mp1;

//    unordered_map<RB1dArray, bool, Hash1d> mp1;

//    unordered_map<RBBitboard, bool, HashBitboard> mp1;

//    mp1[cube1] = true;
//    cube2.randomShuffleCube(8);
//    if (mp1[cube1]) cout << "Cube1 is present\n";
//    else cout << "Cube1 is not present\n";

//    if (mp1[cube2]) cout << "Cube2 is present\n";
//    else cout << "Cube2 is not present\n";


// // DFS Solver Testing __________________________________________________________________________________________
//    RBBitboard cube;
//    cube.print();

//    vector<RubiksCube::MOVE> shuffle_moves = cube.randomShuffleCube(6);
//    for (auto move: shuffle_moves) cout << cube.getMove(move) << " ";
//    cout << "\n";
//    cube.print();

//    DFSSolver<RBBitboard, Hash3d> dfsSolver(cube, 8);
//    vector<RubiksCube::MOVE> solve_moves = dfsSolver.solve();

//    for (auto move: solve_moves) cout << cube.getMove(move) << " ";
//    cout << "\n";
//    dfsSolver.rubiksCube.print();


// // BFS Solver -----------------------------------------------------------------------------------------------------
//    RBBitboard cube;
//    cube.print();

//    vector<RubiksCube::MOVE> shuffle_moves = cube.randomShuffleCube(6);
//    for(auto move: shuffle_moves) cout << cube.getMove(move) << " ";
//    cout << "\n";
//    cube.print();

//    BFSSolver<RBBitboard, HashBitboard> bfsSolver(cube);
//    vector<RubiksCube::MOVE> solve_moves = bfsSolver.solve();

//    for(auto move: solve_moves) cout << cube.getMove(move) << " ";
//    cout << "\n";
//    bfsSolver.rubikscube.print();

// // IDDFS Solver ----------------------------------------------------------------------------------------------------
//    RBBitboard cube;
//    cube.print();

//    vector<RubiksCube::MOVE> shuffle_moves = cube.randomShuffleCube(7);
//    for (auto move: shuffle_moves) cout << cube.getMove(move) << " ";
//    cout << "\n";
//    cube.print();

//    IDDFSSolver<RBBitboard, HashBitboard> iddfsSolver(cube, 7);
//    vector<RubiksCube::MOVE> solve_moves = iddfsSolver.solve();

//    for (auto move: solve_moves) cout << cube.getMove(move) << " ";
//    cout << "\n";
//    iddfsSolver.rubiksCube.print();

// // IDA* SOLVER ---------------------------------------------------------------------------------------------------
//    RBBitboard cube;
//    cube.print();

//    vector<RubiksCube::MOVE> shuffle_moves = cube.randomShuffleCube(5);
//    for (auto move: shuffle_moves) cout << cube.getMove(move) << " ";
//    cout << "\n";
//    cube.print();
//     string s1="Database\\cornerDepth5V1.txt";
//    IDAStarSolver<RBBitboard, HashBitboard> idAstarSolver(cube,s1);
//    vector<RubiksCube::MOVE> solve_moves = idAstarSolver.solve();
//    for (auto move: solve_moves) cout << cube.getMove(move) << " ";
//    cout << "\n";
//    idAstarSolver.rubiksCube.print();

// // CornerPatternDatabase Testing ---------------------------------------------------------------------------------

//    CornerPatternDatabase cornerDB;
//    RBBitboard cube;
//    cube.print();

//    cout << (int)cornerDB.getNumMoves(cube) << "\n";

//    cornerDB.setNumMoves(cube, 5);

//    cout << (int)cornerDB.getNumMoves(cube) << "\n";

//    cube.randomShuffleCube(1);
//    cube.print();
//    cout << (int)cornerDB.getNumMoves(cube) << "\n";

//    cornerDB.setNumMoves(cube, 6);

//    cout << (int)cornerDB.getNumMoves(cube) << "\n";


// // CornerDBMaker Testing --------------------------------------------------------------------------
//     string fileName = "Database\\cornerDepth5V1.txt";

// //    Code to create Corner Database
// //    CornerDBMaker dbMaker(fileName, 0x99);
// //    dbMaker.bfsAndStore();

//     RBBitboard cube;
//     auto shuffleMoves = cube.randomShuffleCube(13);
//     cube.print();
//     for (auto move: shuffleMoves) cout << cube.getMove(move) << " ";
//     cout << "\n";

//     IDAStarSolver<RBBitboard, HashBitboard> idaStarSolver(cube, fileName);
//     auto moves = idaStarSolver.solve();

//     idaStarSolver.rubiksCube.print();
//     for (auto move: moves) cout << cube.getMove(move) << " ";
//     cout << "\n";


    return 0;
}