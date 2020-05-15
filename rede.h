#ifndef REDE_H
#define REDE_H

#include <iostream>
#include "random.h"
#include <new>
#include <vector>

class Rede{
private:
    unsigned long int N;
    Random *distribution;
    std::vector<std::vector<unsigned long int>> adj_matrix;
    std::vector<unsigned long int> degrees;
    std::vector<std::pair<unsigned long int, unsigned long int>> list_of_links;
public:
    Rede(unsigned long int  N, Random *rd);
    std::vector<unsigned long int> mount_algorithm_list();
    void reset();
    bool random_link();
    bool is_connected(unsigned long int v, unsigned long int w);
    void link(unsigned long int v, unsigned long int w);
    std::vector<std::vector<unsigned long int>> get_adj_matrix();
    unsigned long int get_degree(unsigned long int i);
    unsigned long int get_number_of_nodes();
    std::vector<std::pair<unsigned long int, unsigned long int>> get_list_of_links();
    double first_momment(std::vector<unsigned long int> sample);
    double second_moment(std::vector<unsigned long int> sample);
    double molloy_reed(std::vector<unsigned long int> sample);
};

#endif // REDE_H
