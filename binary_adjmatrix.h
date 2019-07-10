#ifndef BINARY_ADJLIST_H
#define BINARY_ADJLIST_H
#include <vector>

class Binary_adjlist{
private:
    std::vector<std::vector<char>> matrix;
public:
    Binary_adjlist();
    Binary_adjlist(unsigned long int d);
    void add_link(unsigned long int v, unsigned long int w);
    bool is_connected(unsigned long int v, unsigned long int w);
};

#endif // BINARY_ADJLIST_H
