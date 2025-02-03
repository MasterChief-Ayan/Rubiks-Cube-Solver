#ifndef RubiksCubeSolver_MAIN_H
#define RubiksCubeSolver_MAIN_H

#include "bits/stdc++.h"
using namespace std;

class RubiksCube {
public:
    enum class FACE{
        UP, LEFT, FRONT, RIGHT, BACK, DOWN
    };

    enum class COLOR{
        WHITE, GREEN, RED, BLUE, ORANGE, YELLOW
    };

    enum class MOVE{        // because the RB 20 move law is based on these 18 moves  ****
        L, LPrime, L2,
        R, RPrime, R2,
        U, UPrime, U2,
        D, DPrime, D2,
        F, FPrime, F2,
        B, BPrime, B2
    };

    virtual COLOR getColor(FACE face, int row, int col) const= 0;

    static char getColorLetter(COLOR color);

    virtual bool isSolved() const =0;

    static string getMove(MOVE ind);

    void print() const;

    vector<RubiksCube::MOVE> randomShuffleCube (unsigned int times);

    /*The & before the function name in RubiksCube &move(MOVE ind);
     means the function returns a reference to a RubiksCube object,
      not a duplicate.*/

    RubiksCube &move(MOVE ind);

    RubiksCube &invert(MOVE ind);

    virtual RubiksCube &f() = 0;

    virtual RubiksCube &fPrime() = 0;

    virtual RubiksCube &f2() = 0;

    virtual RubiksCube &u() = 0;

    virtual RubiksCube &uPrime() = 0;

    virtual RubiksCube &u2() = 0;

    virtual RubiksCube &l() = 0;

    virtual RubiksCube &lPrime() = 0;

    virtual RubiksCube &l2() = 0;

    virtual RubiksCube &r() = 0;

    virtual RubiksCube &d() = 0;

    virtual RubiksCube &dPrime() = 0;

    virtual RubiksCube &d2() = 0;

    virtual RubiksCube &rPrime() = 0;

    virtual RubiksCube &r2() = 0;

    virtual RubiksCube &b() = 0;

    virtual RubiksCube &bPrime() = 0;

    virtual RubiksCube &b2() = 0;

    string getCornerColorString(uint8_t ind) const;

    uint8_t getCornerIndex(uint8_t ind) const;

    uint8_t getCornerOrientation(uint8_t ind) const;

};


#endif // RubiksCubeSolver_MAIN_H
