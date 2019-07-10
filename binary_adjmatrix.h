#ifndef BINARY_ADJLIST_H
#define BINARY_ADJLIST_H
#include <vector>

class Binary_adjmatrix{
private:
    std::vector<std::vector<char>> matrix;
public:
    Binary_adjmatrix();
    Binary_adjmatrix(unsigned long int dim);
    void add_link(unsigned long int v, unsigned long int w);
    bool is_connected(unsigned long int v, unsigned long int w);
};

#endif // BINARY_ADJLIST_H
