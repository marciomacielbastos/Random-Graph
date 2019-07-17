#include "binary_adjmatrix.h"
#include <bitset>
#include <iostream>

Binary_adjmatrix::Binary_adjmatrix(){

}

Binary_adjmatrix::Binary_adjmatrix(unsigned long int dim){
    this->dim = dim;
    unsigned long int r = dim % 8;
    unsigned long int d = dim / 8 + static_cast<bool>(r);
    while(d > 0){
        std::vector<char> row(d, 0);
        matrix.push_back(row);
        dim--;
        if(!(dim % 8)){
            d--;
        }
    }
}

void Binary_adjmatrix::add_link(unsigned long v, unsigned long w){
    char bit = 1;
    if(v < w){
        matrix[v][(w - v)/8] |= (bit << (w%8));
    }
    else {
        matrix[w][(v - w)/8] |= (bit << (v%8));
    }
}

bool Binary_adjmatrix::is_connected(unsigned long v, unsigned long w){
    char bit = 1;
    if(v < w){
        return matrix[v][(w - v)/8] & (bit << (w%8));
    }
    else {
        return matrix[w][(v - w)/8] & (bit << (v%8));
    }
}

bool Binary_adjmatrix::is_marked(unsigned long v){
    return is_connected(v, v);
}

void Binary_adjmatrix::mark(unsigned long v){
    add_link(v, v);
}
