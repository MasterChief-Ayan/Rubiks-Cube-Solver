# include "main.h"

#ifndef RUBIKSCUBESOLVER_RBBitboard_H
#define RUBIKSCUBESOLVER_RBBitboard_H

class RBBitboard : public RubiksCube {

private:

    uint64_t solvedSideConfig[6]{};

    int arr[3][3] ={{0,1,2},{7,8,3},{6,5,4}}; //Circular notation to  Coz, when rotated, its effectively each bit pos= (pos+16)%64

    uint64_t one_8 = (1<<8)-1, one_16 = (1<<16)-1, one_24 = (1<<24)-1;
    
    void rotateFace(int ind){   
        uint64_t lastTwoColor = bitboard[ind];
        lastTwoColor= (lastTwoColor>>(8*6));    //getting last two colors
        bitboard[ind] = (bitboard[ind]<<(8*2)) | lastTwoColor; //appending the last 2 in the first 2 empty positiong due to shift by 16
    }

    void rotateSide (int s1, int s1_1,int s1_2,int s1_3, int s2, int s2_1,int s2_2,int s2_3){ // parameters are (face1,face1side1,face1sides2,face1side3,  face2,face2side1,face2side2,face2side3)  

        uint64_t color1= (bitboard[s2] & (one_8<<(8*s2_1))) >> (8*s2_1); //getting the 1st color of s2
        uint64_t color2= (bitboard[s2] & (one_8<<(8*s2_2))) >> (8*s2_2); //getting the 2nd color of s2
        uint64_t color3= (bitboard[s2] & (one_8<<(8*s2_3))) >> (8*s2_3); //getting the 3rd color of s2

        bitboard[s1] = (bitboard[s1] & ~(one_8<<(8*s1_1))) | (color1<<(8*s1_1));  //setting the 1st color of s2 to s1
        bitboard[s1] = (bitboard[s1] & ~(one_8<<(8*s1_2))) | (color2<<(8*s1_2));  //setting the 2nd color of s2 to s1
        bitboard[s1] = (bitboard[s1] & ~(one_8<<(8*s1_3))) | (color3<<(8*s1_3));  //setting the 3rd color of s2 to s1
    }    

    int get5bitCorner(string corner){  // 5 bit encoding of the corner
        int ret =0;  
        string actual_str;  //actual string of the corner
        for(auto i:corner){  
            if( i != 'W' && i != 'Y') continue;  //ignoring the other colors
            actual_str+=i;                       //adding the actual color to the actual string
            if(i == 'Y') ret |=(1<<2);           //setting the 3rd bit if the color is yellow
        }

        for (auto i:corner){
            if(i!= 'R' && i!= 'O') continue;    //ignoring the other colors
            if(i == 'O') ret |=(1<<1);          //setting the 2nd bit if the color is orange
        }

        for(auto i:corner){
            if(i!='B' && i!='G') continue;      //ignoring the other colors
            if(i == 'G') ret |=1;               //setting the 1st bit if the color is green
        }

        if(corner[1] == actual_str[0]) ret|=(1<<3);       //setting the 4th bit if the 2nd color is the actual 2nd color
        else if (corner[2] == actual_str[0]) ret|=(1<<4); //setting the 5th bit if the 3rd color is the actual 2nd color

        return ret;  //returning the 5 bit encoding of the corner
    }

public:
    uint64_t bitboard[6];

    RBBitboard(){
        for (int i = 0; i < 6; i++) {
            uint64_t color = 1<<i; //color of the ith face
            bitboard[i] = 0; //initial board
            for (int j = 0; j < 8; j++) {
                bitboard[i] |= color<<(8*j); // same color in all the 9 positions (8+1 @ center)
            }
            solvedSideConfig[i] = bitboard[i];
        }
    }

    COLOR getColor(FACE face, int row, int col) const override{
        int idx = arr[row][col];
        if (idx == 8) return (COLOR)((int) face);

        uint64_t side = bitboard[(int) face];
        uint64_t color = (side >> (8 * idx)) & one_8;
    
        int bit_pos = 0;
        while (color != 0) {        
            color = color >> 1;
            bit_pos++;
        }
        return (COLOR)(bit_pos - 1);
    }

    bool isSolved() const override{
        for (int i = 0; i < 6; i++) {
            if (bitboard[i] != solvedSideConfig[i]) return false;
        }
        return true;
    }

    RubiksCube &u() override{
        rotateFace(0);

        uint64_t temp = bitboard[2] & (one_24); //getting the 1st 3 colors of the 2nd face
        bitboard[2] = (bitboard[2] & ~one_24) | (bitboard[3] & one_24); //setting the 1st 3 colors of the 2nd face from 1st 3 colors of the 3rd face
        bitboard[3] = (bitboard[3] & ~one_24) | (bitboard[4] & one_24); //setting the 1st 3 colors of the 3rd face from 1st 3 colors of the 4th face
        bitboard[4] = (bitboard[4] & ~one_24) | (bitboard[1] & one_24); //setting the 1st 3 colors of the 4th face from 1st 3 colors of the 1st face
        bitboard[1] = (bitboard[1] & ~one_24) | temp; //setting the 1st 3 colors of the 1st face from the temp(aka stored 2nd face colors)
        return *this;
    }

    RubiksCube &uPrime() override{
        this -> u();
        this -> u();
        this -> u();
        return *this;
    }

    RubiksCube &u2() override{
        this -> u();
        this -> u();
        return *this;
    }

    RubiksCube &l() override{
        rotateFace(1);
        
        uint64_t color1 = (bitboard[2] & (one_8<<(0))) >> (0); //getting the 1st color of the 2nd face a.k.a top left
        uint64_t color2 = (bitboard[2] & (one_8<<(8*6))) >> (8*6); //getting the 7th color of the 2nd face a.k.a bottom left
        uint64_t color3 = (bitboard[2] & (one_8<<(8*7))) >> (8*7); //getting the 8th color of the 2nd face a.k.a middle left

        rotateSide(2,0,7,6,0,0,7,6);  //rotating the 2nd face 
        rotateSide(0,0,7,6,4,4,3,2);  //rotating the 0th face
        rotateSide(4,4,3,2,5,0,7,6);  //rotating the 4th face

        bitboard[5] = (bitboard[5] & ~(one_8<<( 0 ))) | (color1<<( 0 )); //setting the 1st color of the 5th face from the 1st color of the 2nd face
        bitboard[5] = (bitboard[5] & ~(one_8<<(8*6))) | (color2<<(8*6)); //setting the 7th color of the 5th face from the 7th color of the 2nd face
        bitboard[5] = (bitboard[5] & ~(one_8<<(8*7))) | (color3<<(8*7)); //setting the 8th color of the 5th face from the 8th color of the 2nd face
    
        return *this;
    }

    RubiksCube &lPrime() override{
        this -> l();
        this -> l();
        this -> l();
        return *this;
    }

    RubiksCube &l2() override{
        this -> l();
        this -> l();
        return *this;
    }

    RubiksCube &f() override{
        rotateFace(2);

        uint64_t color1 = (bitboard[0] & (one_8<<(8*4))) >> (8*4); //getting the 5th color of the 0th face a.k.a bottom right
        uint64_t color2 = (bitboard[0] & (one_8<<(8*5))) >> (8*5); //getting the 6th color of the 0th face a.k.a bottom middle
        uint64_t color3 = (bitboard[0] & (one_8<<(8*6))) >> (8*6); //getting the 7th color of the 0th face a.k.a bottom left

        rotateSide(0,4,5,6,1,2,3,4);  //rotating the 0th face
        rotateSide(1,2,3,4,5,0,1,2);  //rotating the 1st face
        rotateSide(5,0,1,2,3,6,7,0);  //rotating the 5th face

        bitboard[3] = (bitboard[3] & ~(one_8<<(8*6))) | (color1<<(8*6));  //setting the 7th color of the 3rd face from the 5th color of the 0th face
        bitboard[3] = (bitboard[3] & ~(one_8<<(8*7))) | (color2<<(8*7));  //setting the 8th color of the 3rd face from the 6th color of the 0th face
        bitboard[3] = (bitboard[3] & ~(one_8<<(8*0))) | (color3<<(8*0));  //setting the 1st color of the 3rd face from the 7th color of the 0th face
    
        return *this;
    }


    RubiksCube &fPrime() override{
        this -> f();
        this -> f();
        this -> f();
        return *this;
    }

    RubiksCube &f2() override{
        this -> f();
        this -> f();
        return *this;
    }


    RubiksCube &r() override{
        rotateFace(3);

        uint64_t color1 = (bitboard[0] & (one_8<<(8*2))) >> (8*2); //getting the 3rd color of the 0th face a.k.a top right
        uint64_t color2 = (bitboard[0] & (one_8<<(8*3))) >> (8*3); //getting the 4th color of the 0th face a.k.a middle right
        uint64_t color3 = (bitboard[0] & (one_8<<(8*4))) >> (8*4); //getting the 5th color of the 0th face a.k.a bottom right

        rotateSide(0,2,3,4,2,2,3,4);  //rotating the 0th face
        rotateSide(2,2,3,4,5,2,3,4);  //rotating the 2nd face
        rotateSide(5,2,3,4,4,7,6,0);  //rotating the 5th face

        bitboard[4] = (bitboard[4] & ~(one_8<<(8*7))) | (color1<<(8*7));   //setting the 8th color of the 4th face from the 3rd color of the 0th face
        bitboard[4] = (bitboard[4] & ~(one_8<<(8*6))) | (color2<<(8*6));   //setting the 7th color of the 4th face from the 4th color of the 0th face
        bitboard[4] = (bitboard[4] & ~(one_8<<(8*0))) | (color3<<(8*0));   //setting the 1st color of the 4th face from the 5th color of the 0th face

        return *this;
    }

    RubiksCube &rPrime() override{
        this -> r();
        this -> r();
        this -> r();
        return *this;
    }

    RubiksCube &r2() override{
        this -> r();
        this -> r();
        return *this;
    }   

    RubiksCube &b() override {
        rotateFace(4);

        uint64_t color1 = (bitboard[0] & (one_8<<(0))) >> (0); //getting the 1st color of the 0th face a.k.a top left
        uint64_t color2 = (bitboard[0] & (one_8<<(8))) >> (8); //getting the 2nd color of the 0th face a.k.a top middle
        uint64_t color3 = (bitboard[0] & (one_8<<(8*2))) >> (8*2); //getting the 3rd color of the 0th face a.k.a top right

        rotateSide(0,0,1,2,3,2,3,4);  //rotating the 0th face
        rotateSide(3,2,3,4,5,4,5,6);  //rotating the 3rd face
        rotateSide(5,4,5,6,1,6,7,0);  //rotating the 5th face

        bitboard[1] = (bitboard[1] & ~(one_8<<(8*6))) | (color1<<(8*6));  //setting the 7th color of the 1st face from the 1st color of the 0th face
        bitboard[1] = (bitboard[1] & ~(one_8<<(8*7))) | (color2<<(8*7));  //setting the 8th color of the 1st face from the 2nd color of the 0th face
        bitboard[1] = (bitboard[1] & ~(one_8<<(8*0))) | (color3<<(8*0));  //setting the 1st color of the 1st face from the 3rd color of the 0th face

        return *this;
    }

    RubiksCube &bPrime() override{
        this -> b();
        this -> b();
        this -> b();
        return *this;
    }

    RubiksCube &b2() override{
        this -> b();
        this -> b();
        return *this;
    }

    RubiksCube &d() override{
        rotateFace(5);

        uint64_t color1 = (bitboard[2] & (one_8<<(8*4))) >> (8*4);  //getting the 5th color of the 2nd face a.k.a bottom right
        uint64_t color2 = (bitboard[2] & (one_8<<(8*5))) >> (8*5);  //getting the 6th color of the 2nd face a.k.a bottom middle
        uint64_t color3 = (bitboard[2] & (one_8<<(8*6))) >> (8*6);  //getting the 7th color of the 2nd face a.k.a bottom left

        rotateSide(2,4,5,6,1,4,5,6);  //rotating the 2nd face
        rotateSide(1,4,5,6,4,4,5,6);  //rotating the 1st face
        rotateSide(4,4,5,6,3,4,5,6);  //rotating the 4th face

        bitboard[3] = (bitboard[3] & ~(one_8<<(8*4))) | (color1<<(8*4));  //setting the 5th color of the 3rd face from the 5th color of the 2nd face
        bitboard[3] = (bitboard[3] & ~(one_8<<(8*5))) | (color2<<(8*5));  //setting the 6th color of the 3rd face from the 6th color of the 2nd face
        bitboard[3] = (bitboard[3] & ~(one_8<<(8*6))) | (color3<<(8*6));  //setting the 7th color of the 3rd face from the 7th color of the 2nd face

        return *this;
    }
    
    RubiksCube &dPrime() override{
        this -> d();
        this -> d();
        this -> d();
        return *this;
    }

    RubiksCube &d2() override{
        this -> d();
        this -> d();
        return *this;
    }

    bool operator==(const RBBitboard &x) const{
        for (int i = 0; i < 6; i++) {
            if (bitboard[i] != x.bitboard[i]) return false;
        }
        return true;
    }

    RBBitboard &operator=(const RBBitboard &x){
        for (int i = 0; i < 6; i++) {
            bitboard[i] = x.bitboard[i];
        }
        return *this;
    }

    uint64_t getCorners() {
        uint64_t ret = 0;
        
        string TFR ="";
        TFR += getColorLetter(getColor(FACE::UP, 2,2));
        TFR += getColorLetter(getColor(FACE::FRONT, 0,2));
        TFR += getColorLetter(getColor(FACE::RIGHT, 0,0));

        string TFL ="";
        TFL += getColorLetter(getColor(FACE::UP, 2,0));
        TFL += getColorLetter(getColor(FACE::FRONT, 0,0));
        TFL += getColorLetter(getColor(FACE::LEFT, 0,2));

        string TBL ="";
        TBL += getColorLetter(getColor(FACE::UP, 0,0));
        TBL += getColorLetter(getColor(FACE::BACK, 0,2));
        TBL += getColorLetter(getColor(FACE::LEFT, 0,0));

        string TBR ="";
        TBR += getColorLetter(getColor(FACE::UP, 0,2));
        TBR += getColorLetter(getColor(FACE::BACK, 0,0));
        TBR += getColorLetter(getColor(FACE::RIGHT, 0,2));

        string BFR ="";
        BFR += getColorLetter(getColor(FACE::DOWN, 0,2));
        BFR += getColorLetter(getColor(FACE::FRONT, 2,2));
        BFR += getColorLetter(getColor(FACE::RIGHT, 2,0));

        string BFL ="";
        BFL += getColorLetter(getColor(FACE::DOWN, 0,0));
        BFL += getColorLetter(getColor(FACE::FRONT, 2,0));
        BFL += getColorLetter(getColor(FACE::LEFT, 2,2));

        string BBR ="";
        BBR += getColorLetter(getColor(FACE::DOWN, 2,2));
        BBR += getColorLetter(getColor(FACE::BACK, 2,0));
        BBR += getColorLetter(getColor(FACE::RIGHT, 2,2));

        string BBL ="";
        BBL += getColorLetter(getColor(FACE::DOWN, 2,0));
        BBL += getColorLetter(getColor(FACE::BACK, 2,2));
        BBL += getColorLetter(getColor(FACE::LEFT, 2,0));

        ret |= get5bitCorner(TFR);
        ret = ret << 5;

        ret |= get5bitCorner(TFL);
        ret = ret << 5;

        ret |= get5bitCorner(TBR);
        ret = ret << 5;

        ret |= get5bitCorner(TBL);
        ret = ret << 5;

        ret |= get5bitCorner(BFR);
        ret = ret << 5;

        ret |= get5bitCorner(BFL);
        ret = ret << 5;

        ret |= get5bitCorner(BBR);
        ret = ret << 5;

        ret |= get5bitCorner(BBL);
        ret = ret << 5;

        return ret;


    }
};

struct HashBitboard {
    size_t operator()(const RBBitboard &r1) const {
        uint64_t finalHash = r1.bitboard[0];
        for (int i = 1; i < 6; i++) {
            finalHash ^= r1.bitboard[i];  //a common practice to XOR the hash of all the faces
        }
        return (size_t) finalHash;
    }
};

#endif