#include "distance_matrix.h"

Distance_matrix::Distance_matrix(){

}

Distance_matrix::Distance_matrix(unsigned long int dim){
    dim--;
    while(dim > 0){
        std::vector<unsigned long int> row(dim, 0);
        matrix.push_back(row);
        dim--;
    }
}

unsigned long int Distance_matrix::get_distance(unsigned long v, unsigned long w){
    if(v < w){
        return matrix[v][(w - v)];
    }
    else {
        return matrix[w][(v - w)];
    }
}

void Distance_matrix::set_distance(unsigned long v, unsigned long w, unsigned long distance){
    if(v < w){
        matrix[v][(w - v)] = distance;
    }
    else {
        matrix[w][(v - w)] = distance;
    }
}

bool Distance_matrix::is_set(unsigned long v, unsigned long w){
    if(v < w){
        return (matrix[v][(w - v)] > 0);
    }
    else {
        return (matrix[v][(v - w)] > 0);
    }
}
