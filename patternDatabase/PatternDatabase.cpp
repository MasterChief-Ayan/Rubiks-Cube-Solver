#include "PatternDatabase.h"
using namespace std;

PatternDatabase::PatternDatabase(const size_t size) : 
    database(size, 0xFF), size(size), numItems(0) {}   

PatternDatabase::PatternDatabase(const size_t size, uint8_t init_val) :
    database(size, init_val), size(size), numItems(0) {}


// If the idx is alreay set, it does nothing and returns false
// Else it sets ind and return true

bool PatternDatabase::setNumMoves(const uint32_t ind, const uint8_t numMoves) {  // func to set the number of moves
    uint8_t oldMoves = getNumMoves(ind);

    //New item addition
    if(oldMoves == 0xFF) {  // if the number of moves is 0xFF, then it is not set
        ++this->numItems;
    }   

    if(oldMoves > numMoves) {  // Set the number of moves
        this->database.set(ind, numMoves);
        return true;
    }
    return false; // if the number of moves is already set, then return false

}

bool PatternDatabase::setNumMoves(const RubiksCube &cube, const uint8_t numMoves) {
    return setNumMoves(getDatabaseIndex(cube), numMoves);  // set the number of moves for the cube
}

uint8_t PatternDatabase::getNumMoves(const uint32_t ind) const {
    return this->database.get(ind); // returns the number of moves for the index
}

uint8_t PatternDatabase::getNumMoves(const RubiksCube &cube) const {
    return getNumMoves(getDatabaseIndex(cube));  // returns the number of moves for the cube
}

size_t PatternDatabase::getSize() const {
    return this->size;
}

size_t PatternDatabase::getNumItems() const {
    return this->numItems;
}

bool PatternDatabase::isFull() const {
    return this->numItems == this->size;
}

void PatternDatabase::toFile(const string &filePath) const {  // func to write the database to a file
    ofstream writer(filePath, ios::out | ios::binary | ios::trunc);

    if(!writer.is_open()) {
        throw "Failed to open file";
    }
    writer.write(
        reinterpret_cast<const char *>(this->database.data()), 
        this->database.storageSize()
    );
    writer.close();
}

// Returns true if DB is loaded successfully  ELSE false

bool PatternDatabase::fromFile(const string &filePath) {  // func to read the database from a file

    ifstream reader(filePath, ios::in | ios::ate);

    if(!reader.is_open()) {
        return false;
    }

    size_t fileSize = reader.tellg();

    if(fileSize != this->database.storageSize()) {
        reader.close();
        throw "Database corrupted";
    }

    reader.seekg(0, ios::beg);
    reader.read(
        reinterpret_cast<char *>(this->database.data()),
        this->database.storageSize()
    );
    reader.close();
    numItems = size;
    return true;
}

vector<uint8_t> PatternDatabase::inflate() const{  // inflat means to expand the database inorder to store it in a file
    vector<uint8_t> inflated;
    database.inflate(inflated);
    return inflated;
}

void PatternDatabase::reset() { 

    if(numItems != 0){
        database.reset(0xFF);
        numItems = 0;
    }
}