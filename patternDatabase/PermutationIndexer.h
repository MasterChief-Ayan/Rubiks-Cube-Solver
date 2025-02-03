#ifndef RUBIKSCUBE_SOLVER_PERMUTATION_INDEXER_H
#define RUBIKSCUBE_SOLVER_PERMUTATION_INDEXER_H

#include <bits/stdc++.h>
#include "math.h"
using namespace std;

template<size_t N,size_t K=N>

class PermutationIndexer{
private:

    /*PreComputer Table containing the number of ones in binart representation 
        size -> 2^(N) -1  for N number of set bits
    */
    array<uint32_t,(1<<N)-1> onesCountLookup;

    /*
    Precomputing the factorials or permute in reverse order
    */
    array<uint32_t,K> factorials;

public:
    // To populate the factorials and ones-count table
    PermutationIndexer(){
        for (uint32_t i = 0; i < (1 << N) - 1; i++) {
            bitset<N> bits(i);
            onesCountLookup[i] = bits.count();      // count() gives the number of set bits
        }
        for(uint32_t i=0;i<K;i++){
            factorials[i]=pick(N-1-i, K-1-i);    // N-1-i and K-1-i because we are calculating the factorial in reverse order
        }
    }

    // Calc LEXO rank of permutation in O(N)

    uint32_t rank(const array<uint8_t,K> &perm) const{

        // Store the lehmer code of the permutation
        array <uint32_t,K> lehmer;

        // Store the seen bits in the permutation
        bitset<N> seen;

        // 1st Digit of Lehmer code => 1st digit of permutation
        lehmer[0]=perm[0];

        // Mark the {via right to left idxing} digit as seen
        seen[N-1-perm[0]]=1;

        for(uint32_t i=1;i<K;i++){

            seen[N-1-perm[i]]=1;

            //No. of seend digits to the left of this digit is the count of ones left of this digit
            uint32_t numOnes = onesCountLookup[seen.to_ulong()] >> (N-perm[i]);

            lehmer[i]=perm[i]-numOnes;
        }

        //Convert Lehmer code to base 10
        uint32_t index =0;

        for(uint32_t i=0;i<K;i++){
            index+=lehmer[i]*factorials[i];
        }

        return index;
    } 

};


#endif