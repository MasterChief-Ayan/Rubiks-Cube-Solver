#ifndef RUBIKSCUBE_SOLVER_CORNERDBMAKER_H
#define RUBIKSCUBE_SOLVER_CORNERDBMAKER_H

#include "CornerPatternDatabase.h"
#include "PatternDatabase.h"
#include "../models/mainBitboard.cpp"

using namespace std;

class CornerDBMaker {
private:

    string fileName;
    CornerPatternDatabase cornerDB;

public:
    CornerDBMaker (string fileName_temp);
    CornerDBMaker (string fileName_temp, uint8_t init_val);

    bool bfsAndStore();

};


#endif