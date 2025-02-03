#include "NibbleArray.h"
using namespace std;

NibbleArray::NibbleArray(const size_t size, const uint8_t val) :
        size(size), arr(size / 2 + 1, val) {}

uint8_t NibbleArray::get(const size_t pos) const {
    size_t i = pos / 2;
    assert(pos <= this->size);
    uint8_t val = this->arr.at(i);

    if (pos % 2) {      // Odd pos i.e. last 4 bit
        return val & 0x0F;
    } else {            // Even pos i.e. first 4 bit
        return val >> 4;
    }
}

void NibbleArray::set(const size_t pos, const uint8_t val) {
    size_t i = pos / 2;
    uint8_t cur_val = this->arr.at(i);
    assert(pos <= this->size);

    if (pos % 2) {    
        this->arr.at(i) = (cur_val & 0xF0) | (val & 0x0F);  // Clear last 4 bits and set new value = (val & 0x0F)
    } else {          
        this->arr.at(i) = (cur_val & 0x0F) | (val << 4);    // Clear first 4 bits and set new value = val << 4
    }
}

uint8_t *NibbleArray::data() {
    return this->arr.data();  // Returns pointer to the underlying array serving as element storage.
}

const uint8_t *NibbleArray::data() const {
    return this->arr.data();  // it differs from previous function as it returns a pointer to constant data.
}

size_t NibbleArray::storageSize() const {
    return this->arr.size();  // Returns the number of elements in the array container.
}

// Move all the moves to a vector. This double the size, but is faster to access coz no bitwise operations are needed.

void NibbleArray::inflate(vector<uint8_t> &dest) const {  // dest is passed by reference so that the changes are reflected in the original vector.
    dest.reserve(this->size);
    for (unsigned i = 0; i < this->size; i++) {
        dest.push_back(this->get(i));
    }
}

// Reset the array to a specific value.

void NibbleArray::reset(const uint8_t val) {
    fill(this->arr.begin(), this->arr.end(), val);  // Fills the range [first, last) with val. 
}