#include "CornerPatternDatabase.h"

// CornerPatternDatabase::CornerPatternDatabase() : PatternDatabase(88179840) {}

CornerPatternDatabase::CornerPatternDatabase(uint8_t init_val) : PatternDatabase(88179840, init_val) {}

uint32_t CornerPatternDatabase::getDatabaseIndex(const RubiksCube &cube) const {
    array<uint8_t, 8> cornerPerm={      // gives what is the cubie present in idx 0, 1, 2, ... 7
        cube.getCornerIndex(0),
        cube.getCornerIndex(1),
        cube.getCornerIndex(2),
        cube.getCornerIndex(3),
        cube.getCornerIndex(4),
        cube.getCornerIndex(5),
        cube.getCornerIndex(6),
        cube.getCornerIndex(7)
    };

    uint32_t rank = permIndexer.rank(cornerPerm);   // gave us the permutation rank of the CornerPerm where rank is the number of permutations that are smaller than the given permutation

    array<uint8_t, 7> cornerOrientations = {        // to get the orientation of the corner cubies at each idx
        cube.getCornerOrientation(0),               // each return 0 OR 1 OR 2 (3 possible orientations)
        cube.getCornerOrientation(1),
        cube.getCornerOrientation(2),
        cube.getCornerOrientation(3),
        cube.getCornerOrientation(4),
        cube.getCornerOrientation(5),
        cube.getCornerOrientation(6)                // 7th corner orientation is determined by the other 6
    };

    uint32_t orientationNum = 0;  // maps the cubie to specific orientation number
    int temp_num=1;
    for(int i=6;i>=0;i--){
        orientationNum+=cornerOrientations[i]*temp_num;  //we multiply each orientation by 3^i and add it so that we get a unique number for each orientation
        temp_num*=3;                                     //we used 3^i causes shifting the all the previous i's orientation by 3 values
    }

    return (rank*2187)+orientationNum;              // for 7th cubie orientation we have 3 possibilities so we multiply rank by 3^7=2187
    // This is array index for the database
}