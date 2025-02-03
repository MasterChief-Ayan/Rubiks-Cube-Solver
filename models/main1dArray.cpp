#include "main.h"

class RB1dArray : public RubiksCube {
private:
    static inline int getIndex (int ind,int row,int col){
        return ind*9+row*3+col; // each face-> 9 elements, each row-> 3 elements, each cell-> 1 element
    }

    void rotateFace(int ind){ //roatating of ind face
        char temp_cells[9]={};
        for(int i=0;i<9;i++){
            temp_cells[i]=cube[getIndex(ind,i/3,i%3)];
        }
                                            // RISK HERE ----------------------------------------*****
        for(int i=0;i<3;i++) cube[getIndex(ind,0,i)]=temp_cells[getIndex(0,2-i,0)];
        for(int i=0;i<3;i++) cube[getIndex(ind,1,i)]=temp_cells[getIndex(0,2-i,1)];
        for(int i=0;i<3;i++) cube[getIndex(ind,2,i)]=temp_cells[getIndex(0,2-i,2)];
    }
    
public:
    char cube[54]{}; // 54 elements in a 1D array

    RB1dArray(){
        for(int i=0;i<6;i++){
            for(int j=0;j<3;j++){
                for(int k=0;k<3;k++){
                    cube[getIndex(i,j,k)]= RubiksCube::getColorLetter(static_cast<COLOR>(i));
                }
            }
        }
    }

    COLOR getColor(FACE face, int row, int col) const override {
        char color= cube[getIndex(static_cast<int>(face),row,col)];
        switch (color) {
            case 'B':
                return COLOR::BLUE;
            case 'R':
                return COLOR::RED;
            case 'G':   
                return COLOR::GREEN;
            case 'O':
                return COLOR::ORANGE;
            case 'Y':   
                return COLOR::YELLOW;
            case 'W':  
                return COLOR::WHITE; 
        }
    }

    bool isSolved() const override{
        for(int i=0;i<6;i++){
            for(int j=0;j<3;j++){
                for(int k=0;k<3;k++){
                    if(cube[getIndex(i,j,k)]!=RubiksCube::getColorLetter(static_cast<COLOR>(i))) return 0;
                }
            }
        }
        return true;
    }

    RubiksCube &u() override{
        this->rotateFace(0);

        char a[3]={};
        for(int i=0;i<3;i++){
            a[i]=cube[getIndex(2,0,i)];
            cube[getIndex(2,0,i)]=cube[getIndex(3,0,i)];
        }
        for(int i=0;i<3;i++){
            cube[getIndex(3,0,i)]=cube[getIndex(4,0,i)];
        }
        for(int i=0;i<3;i++){
            cube[getIndex(4,0,i)]=cube[getIndex(1,0,i)];
        }
        for (int i = 0; i < 3; i++) {
            cube[getIndex(1,0,i)]=a[i];
        }

        return *this;
    }

    RubiksCube &uPrime() override{
        this->u();
        this->u();
        this->u();

        return *this;
    }

    RubiksCube &u2() override{
        this->u();
        this->u();

        return *this;
    }

    RubiksCube &l() override{
        rotateFace(1);

        char a[3];
        for(int i=0;i<3;i++){
            a[i]=cube[getIndex(5,i,0)];
            cube[getIndex(5,i,0)]=cube[getIndex(2,i,0)];
        }
        for(int i=0;i<3;i++){
            cube[getIndex(2,i,0)]=cube[getIndex(0,i,0)];  
        }
        for(int i=0;i<3;i++){
            cube[getIndex(0,i,0)]=cube[getIndex(4,2-i,2)];
        }
        for(int i=0;i<3;i++){
            cube[getIndex(4,i,2)]=a[2-i];
        }
        return *this;
    }

    RubiksCube &lPrime() override{
        this->l();
        this->l();
        this->l();

        return *this;
    }

    RubiksCube &l2() override{
        this->l();
        this->l();

        return *this;
    }

    RubiksCube &f() override{
        rotateFace(2);

        char a[3]={};
        for(int i=0;i<3;i++){
            a[i]=cube[getIndex(0,2,i)];
            cube[getIndex(0,2,i)]=cube[getIndex(1,2-i,2)];
        }
        for(int i=0;i<3;i++){
            cube[getIndex(1,i,2)]=cube[getIndex(5,0,i)];
        }
        for(int i=0;i<3;i++){
            cube[getIndex(5,0,i)]=cube[getIndex(3,2-i,0)];
        }
        for(int i=0;i<3;i++){
            cube[getIndex(3,i,0)]=a[i];
        }
        return *this;
    }

    RubiksCube &fPrime() override{
        this->f();
        this->f();
        this->f();

        return *this;
    }

    RubiksCube &f2() override{
        this->f();
        this->f();

        return *this;
    }

    RubiksCube &r() override{
        rotateFace(3);

        char a[3]={};
        for(int i=0;i<3;i++){
            a[i]=cube[getIndex(0,i,2)];
            cube[getIndex(0,i,2)]=cube[getIndex(2,i,2)];
        }
        for(int i=0;i<3;i++){
            cube[getIndex(2,i,2)]=cube[getIndex(5,i,2)];
        }
        for(int i=0;i<3;i++){
            cube[getIndex(5,i,2)]=cube[getIndex(4,2-i,0)];
        }
        for(int i=0;i<3;i++){
            cube[getIndex(4,i,0)]=a[2-i];
        }
        return *this;
    }

    RubiksCube &rPrime() override{
        this->r();
        this->r();
        this->r();

        return *this;
    }

    RubiksCube &r2() override{
        this->r();
        this->r();

        return *this;
    }

    RubiksCube &b() override{
        rotateFace(4);

        char a[3]={};
        for(int i=0;i<3;i++){
            a[i]=cube[getIndex(0,0,i)];
            cube[getIndex(0,0,i)]=cube[getIndex(3,i,2)];
        }
        for(int i=0;i<3;i++){
            cube[getIndex(3,i,2)]=cube[getIndex(5,2,2-i)];
        }
        for(int i=0;i<3;i++){
            cube[getIndex(5,2,i)]=cube[getIndex(1,i,0)];
        }
        for(int i=0;i<3;i++){
            cube[getIndex(1,i,0)]=a[2-i];
        }
        return *this;
    }

    RubiksCube &bPrime() override{
        this->b();
        this->b();
        this->b();

        return *this;
    }

    RubiksCube &b2() override{
        this->b();
        this->b();

        return *this;
    }

    RubiksCube &d() override{
        rotateFace(5);

        char a[3]={};
        for(int i=0;i<3;i++){
            a[i]=cube[getIndex(1,2,i)];
            cube[getIndex(1,2,i)]=cube[getIndex(4,2,i)];
        }
        for(int i=0;i<3;i++){
            cube[getIndex(4,2,i)]=cube[getIndex(3,2,i)];
        }
        for(int i=0;i<3;i++){
            cube[getIndex(3,2,i)]=cube[getIndex(2,2,i)];
        }
        for(int i=0;i<3;i++){
            cube[getIndex(2,2,i)]=a[i];
        }
        return *this;
    }

    RubiksCube &dPrime() override{
        this->d();
        this->d();
        this->d();

        return *this;
    }

    RubiksCube &d2() override{
        this->d();
        this->d();

        return *this;
    }

    bool operator==(const RB1dArray &r1) const {
        for(int i=0;i<54;i++){
            if(cube[i]!=r1.cube[i]) return false;   //.cube as its a object inside the RB1dArray class
        }
        return true;
    }

    RB1dArray &operator=(const RB1dArray &r1){
        for(int i=0;i<54;i++){
            cube[i]=r1.cube[i];     //its assigning to object and according to its variable it will get assigned
        }
        return *this;
    }

};

struct Hash1d {  // Hash function for 1D array
    size_t operator()(const RB1dArray &r1) const{  //operator overloading for hash function
        string str = "";  //hash is a string
        for(int i=0;i<54;i++){  //54 elements in a 1D array
            str+=r1.cube[i];  
        }
        return hash<string>()(str);  //returning the size of the hash
    }
};