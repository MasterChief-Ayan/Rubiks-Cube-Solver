//CAN ALSO USE THIS AS A LAUNCHER FILE FOR TESTING******

#include "main.h"
// #include "main3dArray.cpp"
// #include "main1dArray.cpp"
// #include "mainBitboard.cpp"
// #include "../solvers/DFSSolver.h"
// #include "../solvers/BFSSolver.h"
// #include "../solvers/IDDFSSolver.h"
// #include "../solvers/IDAStarSolver.h"
// #include "../patternDatabase/CornerPatternDatabase.h"
// #include "../patternDatabase/CornerDBMaker.h"
// #include "../patternDatabase/PatternDatabase.h"

char RubiksCube::getColorLetter(COLOR color) {
    switch (color) {
        case COLOR::WHITE:
            return 'W';
        case COLOR::GREEN:
            return 'G';
        case COLOR::RED:
            return 'R';
        case COLOR::BLUE:
            return 'B';
        case COLOR::ORANGE:
            return 'O';
        case COLOR::YELLOW:
            return 'Y';
    }
}

string RubiksCube::getMove(MOVE ind) {
    switch (ind) {
        case MOVE::L:
            return "L";
        case MOVE::LPrime:
            return "L'";
        case MOVE::L2:
            return "L2";
        case MOVE::R:
            return "R";
        case MOVE::RPrime:
            return "R'";
        case MOVE::R2:
            return "R2";
        case MOVE::U:
            return "U";
        case MOVE::UPrime:
            return "U'";
        case MOVE::U2:
            return "U2";
        case MOVE::D:
            return "D";
        case MOVE::DPrime:
            return "D'";
        case MOVE::D2:
            return "D2";
        case MOVE::F:
            return "F";
        case MOVE::FPrime:
            return "F'";
        case MOVE::F2:
            return "F2";
        case MOVE::B:
            return "B";
        case MOVE::BPrime:
            return "B'";
        case MOVE::B2:
            return "B2";
    }
}

RubiksCube &RubiksCube::move(MOVE ind) {
    switch (ind) {
        case MOVE::L:
            return this->l();
        case MOVE::LPrime:  
            return this->lPrime();
        case MOVE::L2:
            return this->l2();
        case MOVE::R:
            return this->r();
        case MOVE::RPrime:
            return this->rPrime();
        case MOVE::R2:
            return this->r2();
        case MOVE::U:
            return this->u();
        case MOVE::UPrime:
            return this->uPrime();
        case MOVE::U2:
            return this->u2();
        case MOVE::D:
            return this->d();
        case MOVE::DPrime:
            return this->dPrime();
        case MOVE::D2:
            return this->d2();
        case MOVE::F:
            return this->f();
        case MOVE::FPrime:
            return this->fPrime();
        case MOVE::F2:
            return this->f2();
        case MOVE::B:
            return this->b();
        case MOVE::BPrime:
            return this->bPrime();
        case MOVE::B2:
            return this->b2();
    }
}

RubiksCube &RubiksCube::invert(MOVE ind) {
    switch (ind) {
        case MOVE::L:
            return this->lPrime();
        case MOVE::LPrime:
            return this->l();
        case MOVE::L2:
            return this->l2();
        case MOVE::R:
            return this->rPrime();
        case MOVE::RPrime:
            return this->r();
        case MOVE::R2:
            return this->r2();
        case MOVE::U:
            return this->uPrime();
        case MOVE::UPrime:
            return this->u();
        case MOVE::U2:
            return this->u2();
        case MOVE::D:
            return this->dPrime();
        case MOVE::DPrime:
            return this->d();
        case MOVE::D2:
            return this->d2();
        case MOVE::F:
            return this->fPrime();
        case MOVE::FPrime:
            return this->f();
        case MOVE::F2:
            return this->f2();
        case MOVE::B:
            return this->bPrime();
        case MOVE::BPrime:
            return this->b();
        case MOVE::B2:
            return this->b2();
    }
}

void RubiksCube::print() const {
    cout<<endl;
    cout<<"Rubiks Cube:"<<endl<<endl;
    for (int i = 0; i < 3; i++) {
        cout << "      ";
        for (int j = 0; j < 3; j++) {
            cout << " "<<getColorLetter(getColor(FACE::UP, i, j)) ;
        }
        cout << endl;
    }cout<<endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << getColorLetter(getColor(FACE::LEFT, i, j)) << " ";
        }
        cout << " ";
        for (int j = 0; j < 3; j++) {
            cout << getColorLetter(getColor(FACE::FRONT, i, j)) << " ";
        }
        cout << " ";
        for (int j = 0; j < 3; j++) {
            cout << getColorLetter(getColor(FACE::RIGHT, i, j)) << " ";
        }
        cout << " ";
        for (int j = 0; j < 3; j++) {
            cout << getColorLetter(getColor(FACE::BACK, i, j)) << " ";
        }
        cout << endl;
    }cout<<endl;
    for (int i = 0; i < 3; i++) {
        cout << "      ";
        for (int j = 0; j < 3; j++) {
            cout <<" "<< getColorLetter(getColor(FACE::DOWN, i, j)) ;
        }
        cout << endl;
    }
}

vector<RubiksCube::MOVE> RubiksCube:: randomShuffleCube (unsigned int times){
    vector<RubiksCube::MOVE> moves;
    srand(time(0));
    for (int i = 0; i < times; i++){
        unsigned int move = rand() % 18;
        moves.push_back(static_cast<RubiksCube::MOVE>(move));
        this->move(static_cast<RubiksCube::MOVE>(move));
    } 
    return moves;
}

// returns string of corner

string RubiksCube::getCornerColorString(uint8_t ind)const {
    string str = "";
    
    switch (ind){
        //TFR
        case 0:
            str += getColorLetter(getColor(FACE::UP, 2,2));
            str += getColorLetter(getColor(FACE::FRONT, 0,2));
            str += getColorLetter(getColor(FACE::RIGHT, 0,0));
            break;
        //TFL
        case 1:
            str += getColorLetter(getColor(FACE::UP, 2,0));
            str += getColorLetter(getColor(FACE::FRONT, 0,0));
            str += getColorLetter(getColor(FACE::LEFT, 0,2));
            break;
        //TBL
        case 2:
            str += getColorLetter(getColor(FACE::UP, 0,0));
            str += getColorLetter(getColor(FACE::BACK, 0,2));
            str += getColorLetter(getColor(FACE::LEFT, 0,0));
            break;
        //TBR
        case 3:
            str += getColorLetter(getColor(FACE::UP, 0,2));
            str += getColorLetter(getColor(FACE::BACK, 0,0));
            str += getColorLetter(getColor(FACE::RIGHT, 0,2));
            break;
        //BFR
        case 4:
            str += getColorLetter(getColor(FACE::DOWN, 0,2));
            str += getColorLetter(getColor(FACE::FRONT, 2,2));
            str += getColorLetter(getColor(FACE::RIGHT, 2,0));
            break;
        //BFL
        case 5:
            str += getColorLetter(getColor(FACE::DOWN, 0,0));
            str += getColorLetter(getColor(FACE::FRONT, 2,0));
            str += getColorLetter(getColor(FACE::LEFT, 2,2));
            break;
        //BBR
        case 6:
            str += getColorLetter(getColor(FACE::DOWN, 2,2));
            str += getColorLetter(getColor(FACE::BACK, 2,0));
            str += getColorLetter(getColor(FACE::RIGHT, 2,2));
            break;
        //BBL
        case 7:
            str += getColorLetter(getColor(FACE::DOWN, 2,0));
            str += getColorLetter(getColor(FACE::BACK, 2,2));
            str += getColorLetter(getColor(FACE::LEFT, 2,0));
            break;

        
    }   
    return str;          
}

uint8_t RubiksCube::getCornerIndex(uint8_t ind) const{
    string  corner = getCornerColorString(ind);

    uint8_t ret=0;

    for(auto c:corner){
        if(c!='W' && c!= 'Y') continue;
        if(c=='Y') ret |=(1<<2);
    }
    for( auto c:corner){
        if( c!='R' && c!='O') continue;
        if(c=='O') ret |=(1<<1);
    }
    for(auto c:corner){
        if(c!='B' && c!='G') continue;
        if(c=='G') ret |=(1<<0);
    }
    return ret;
}

uint8_t RubiksCube::getCornerOrientation(uint8_t ind) const{

    string corner = getCornerColorString(ind);
    
    string str="";

    for(auto c:corner){
        if(c!='W' && c!= 'Y') continue;
        str+=c;
    }

    if(corner[1] == str[0]) return 1;
    if(corner[2] == str[0]) return 2;
    return 0;
}

// int main (){

    
    // DFS Solver Testing __________________________________________________________________________________________
//    RBBitboard cube;
//    cube.print();

//    vector<RubiksCube::MOVE> shuffle_moves = cube.randomShuffleCube(6);
//    cout<<"Shuffle Moves: ";
//    for (auto move: shuffle_moves) cout << cube.getMove(move) << " ";
//    cout << "\n";
//    cube.print();

//    DFSSolver<RBBitboard, HashBitboard> dfsSolver(cube, 6);
//    vector<RubiksCube::MOVE> solve_moves = dfsSolver.solve();

//    cout<<"Solve Moves: ";
//    for (auto move: solve_moves) cout << cube.getMove(move) << " ";
//    cout << "\n";
//    dfsSolver.rubiksCube.print();
    // ______________________________________________________________________________________________________________
   
   //BFS Solver -----------------------------------------------------------------------------------------------------
//    RBBitboard cube;
//    cube.print();

//    vector<RubiksCube::MOVE> shuffle_moves = cube.randomShuffleCube(3);
//    for(auto move: shuffle_moves) cout << cube.getMove(move) << " ";
//    cout << "\n";
//    cube.print();

//     cube.move(RubiksCube::MOVE::F);
//     cube.move(RubiksCube::MOVE::LPrime);
//     cube.move(RubiksCube::MOVE::F2);
//     cube.move(RubiksCube::MOVE::U);

//    BFSSolver<RBBitboard, HashBitboard> bfsSolver(cube);
//    vector<RubiksCube::MOVE> solve_moves = bfsSolver.solve();

//    for(auto move: solve_moves) cout << cube.getMove(move) << " ";
//    cout << "\n";
//    bfsSolver.rubikscube.print();
//--------------------------------------------------------------------------------------------------------------------

// IDDFS Solver ----------------------------------------------------------------------------------------------------
//    RBBitboard cube;

//    vector<RubiksCube::MOVE> shuffle_moves = cube.randomShuffleCube(5);
//    for (auto move: shuffle_moves) cout << cube.getMove(move) << " ";
//    cout << "\n";
//    cube.print();

//    IDDFSSolver<RBBitboard, HashBitboard> iddfsSolver(cube, 7);
//    vector<RubiksCube::MOVE> solve_moves = iddfsSolver.solve();

//    for (auto move: solve_moves) cout << cube.getMove(move) << " ";
//    cout << "\n";
//    iddfsSolver.rubiksCube.print();

//--------------------------------------------------------------------------------------------------------------------

// IDA* SOLVER ---------------------------------------------------------------------------------------------------
//    RBBitboard cube;
//    cube.print();

//    vector<RubiksCube::MOVE> shuffle_moves = cube.randomShuffleCube(5);
//    for (auto move: shuffle_moves) cout << cube.getMove(move) << " ";
//    cout << "\n";
//    cube.print();

//    IDAStarSolver<RBBitboard, HashBitboard> idAstarSolver(cube);
//    vector<RubiksCube::MOVE> solve_moves = idAstarSolver.solve();
//    for (auto move: solve_moves) cout << cube.getMove(move) << " ";
//    cout << "\n";
//    idAstarSolver.rubiksCube.print();

//--------------------------------------------------------------------------------------------------------------------

    // CornerPatternDatabase Testing ---------------------------------------------------------------------------------

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

//--------------------------------------------------------------------------------------------------------------------

// CornerDBMaker Testing --------------------------------------------------------------------------
//     string fileName = "C:\\Users\\ayana\\Downloads\\cornerDepth5V1.txt";

// //    Code to create Corner Database
//    CornerDBMaker dbMaker(fileName, 0x99);
//    dbMaker.bfsAndStore();

    // RBBitboard cube;
    // auto shuffleMoves = cube.randomShuffleCube(13);
    // cube.print();
    // for (auto move: shuffleMoves) cout << cube.getMove(move) << " ";
    // cout << "\n";

    // IDAStarSolver<RBBitboard, HashBitboard> idaStarSolver(cube, fileName);
//     auto moves = idaStarSolver.solve();

//     idaStarSolver.rubiksCube.print();
//     for (auto move: moves) cout << cube.getMove(move) << " ";
    // cout << "\n";

//     return 0;
// }
