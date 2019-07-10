#ifndef DISTANCE_MATRIX_H
#define DISTANCE_MATRIX_H
#include <vector>


class Distance_matrix{
private:
    std::vector<std::vector<unsigned long int>> matrix;
public:
    Distance_matrix();
    Distance_matrix(unsigned long int distance);
    void set_distance(unsigned long int v, unsigned long int w, unsigned long int distance);
    bool is_set(unsigned long int v, unsigned long int w);
};

#endif // DISTANCE_MATRIX_H
