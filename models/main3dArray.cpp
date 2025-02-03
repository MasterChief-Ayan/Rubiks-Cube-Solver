#include "main.h"

class RB3dArray : public RubiksCube {
private:
    //only allowing rotation from this class itself via encapsulation
    void rotateFace(int ind){//roatating of ind face
        char temp[3][3];
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                temp[i][j] = cube[ind][i][j];
            }
        }
        for (int i = 0; i < 3; i++) {
            cube[ind][0][i]=temp[2-i][0];
        }
        for (int i = 0; i < 3; i++) {
            cube[ind][i][2]= temp[0][i];
        }
        for(int i=2;i>=0;i--){
            cube[ind][2][i]=temp[2-i][2];
        }
        for(int i=2;i>=0;i--){
            cube[ind][i][0]=temp[2][i];
        }

    }

public:
    char cube[6][3][3];

    RB3dArray(){
        for(int i=0;i<6;i++){
            for(int j=0;j<3;j++){
                for(int k=0;k<3;k++){
                    cube[i][j][k]= RubiksCube::getColorLetter(static_cast<COLOR>(i));
                }
            }
        }
    }

    COLOR getColor(FACE face, int row, int col) const override {
        char color= cube[static_cast<int>(face)][row][col];
        switch (color) {
            case 'W':
                return COLOR::WHITE;
            case 'G':
                return COLOR::GREEN;
            case 'R':
                return COLOR::RED;
            case 'B':
                return COLOR::BLUE;
            case 'O':
                return COLOR::ORANGE;
            case 'Y':
                return COLOR::YELLOW;
        }
    }

    bool isSolved() const override{
        for(int i=0;i<6;i++){
            for(int j=0;j<3;j++){
                for(int k=0;k<3;k++){
                    if(cube[i][j][k]!=getColorLetter(COLOR(i))) return 0;
                }
            }
        }
        return true;
    }
    // as its a virtial function, we are mentioning the base class and not as a kind of return type
    // also the return type is the object of derived class and not the base class

    RubiksCube &uPrime() override{
        rotateFace(0);
        char a[3];
        for(int i=0;i<3;i++){
            a[i]=cube[1][0][i];
            cube[1][0][i]=cube[4][0][i];
        }
        for(int i=0;i<3;i++){
            cube[4][0][i]=cube[3][0][i];
        }
        for(int i=0;i<3;i++){
            cube[3][0][i]=cube[2][0][i];
        }
        for(int i=0;i<3;i++){
            cube[2][0][i]=a[i];
        }

        return *this;
    }
    RubiksCube &u() override{
        this->uPrime();
        this->uPrime();
        this->uPrime();
        return *this;
    }
    RubiksCube &u2() override{
        this->uPrime();
        this->uPrime();
        return *this;
    }

    RubiksCube &l() override{
        rotateFace(1);
        char a[3];
        for(int i=0;i<3;i++){
            a[i]=cube[5][i][0];
            cube[5][i][0]=cube[2][i][0];
        }
        for(int i=0;i<3;i++){
            cube[2][i][0]=cube[0][i][0];  
        }   
        for(int i=0;i<3;i++){
            cube[0][i][0]=cube[4][2-i][2];
        }
        for(int i=0;i<3;i++){
            cube[4][i][2]=a[2-i];
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
        char a[3];
        for(int i=0;i<3;i++){
            a[i]=cube[0][2][i];
            cube[0][2][i]=cube[1][2-i][2];
        }
        for(int i=0;i<3;i++){
            cube[1][i][2]=cube[5][0][i];
        }
        for(int i=0;i<3;i++){
            cube[5][0][i]=cube[3][2-i][0];
        }
        for(int i=0;i<3;i++){
            cube[3][i][0]=a[i];
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

    RubiksCube &r()override {
        rotateFace(3);
        char a[3];
        for(int i=0;i<3;i++){
            a[i]=cube[0][i][2];
            cube[0][i][2]=cube[2][i][2];
        }
        for(int i=0;i<3;i++){
            cube[2][i][2]=cube[5][i][2];
        }
        for(int i=0;i<3;i++){
            cube[5][i][2]=cube[4][2-i][0];
        }
        for(int i=0;i<3;i++){
            cube[4][i][0]=a[2-i];
        }
        return *this;
    }

    RubiksCube &rPrime() override{
        this-> r();
        this-> r();
        this-> r();
    
        return *this;
    }

    RubiksCube &r2() override{
        this-> r();
        this-> r();

        return *this;
    }

    RubiksCube &b() override{
        rotateFace(4);

        char a[3];

        for(int i=0;i<3;i++){
            a[i]=cube[0][0][i];
            cube[0][0][i]=cube[3][i][2];
        }
        for(int i=0;i<3;i++){
            cube[3][i][2]=cube[5][2][2-i];
        }
        for(int i=0;i<3;i++){
            cube[5][2][i]=cube[1][i][0];
        }
        for(int i=0;i<3;i++){
            cube[1][i][0]=a[2-i];
        }

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

        char a[3];
        for(int i=0;i<3;i++){
            a[i]=cube[1][2][i];
            cube[1][2][i]=cube[4][2][i];
        }
        for(int i=0;i<3;i++){
            cube[4][2][i]=cube[3][2][i];
        }
        for(int i=0;i<3;i++){
            cube[3][2][i]=cube[2][2][i];
        }
        for(int i=0;i<3;i++){
            cube[2][2][i]=a[i];
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

    bool operator==(const RB3dArray &x) {
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 3; j++) {
                for (int k = 0; k < 3; k++) {
                    if (x.cube[i][j][k] != cube[i][j][k]) return false;
                }
            }
        }
        return true;
    }

    RubiksCube &operator=(const RB3dArray &x){
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 3; j++) {
                for (int k = 0; k < 3; k++) {
                    cube[i][j][k] = x.cube[i][j][k];
                }
            }
        }
        return *this;
    }
};

struct  Hash3d{
    size_t operator()(const RB3dArray &x) const{
        string str = "";
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 3; j++) {
                for (int k = 0; k < 3; k++) {
                    str += x.cube[i][j][k];
                }
            }
        }
        return hash<string>()(str);
    }
};
