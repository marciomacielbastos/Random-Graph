#include "binary_adjlist.h"
#include <bitset>
#include <iostream>

Binary_adjlist::Binary_adjlist(){

}

Binary_adjlist::Binary_adjlist(unsigned long int dim){
    dim--;
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
    this->matrix = matrix;
}

void Binary_adjlist::add_link(unsigned long v, unsigned long w){
    char bit = 1;
    if(v < w){
        matrix[v][w/8] |= (bit << (w%8));
    }
    else {
        matrix[w][v/8] |= (bit << (v%8));
    }
}

bool Binary_adjlist::is_connected(unsigned long v, unsigned long w){
    char bit = 1;
    if(v < w){
        return matrix[v][w/8] & (bit << (w%8));
    }
    else {
        return matrix[w][v/8] & (bit << (v%8));
    }
}
