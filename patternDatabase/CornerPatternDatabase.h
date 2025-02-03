#ifndef RUBIKSCUBE_SOLVER_CORNERPATTERNDATABASE_H
#define RUBIKSCUBE_SOLVER_CORNERPATTERNDATABASE_H

#include "../models/main.h"
#include "PatternDatabase.h"
#include  "PermutationIndexer.h"
using namespace std;

class CornerPatternDatabase : public PatternDatabase {

    typedef RubiksCube::FACE F;  // now we can use F::U, F::R, etc. in place of RubiksCube::FACE::U, etc.

    PermutationIndexer<8>  permIndexer;     // size 8 because we have 8 corner cubies

    public:

        CornerPatternDatabase();

        CornerPatternDatabase(uint8_t init_val);

        uint32_t getDatabaseIndex(const RubiksCube& cube) const;
        
};
#endif