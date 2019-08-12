#ifndef REDE_H
#define REDE_H
#include <random.h>
#include <vector>


class Rede{
private:
    unsigned long int N;
    Random *distribution;
    std::vector<std::vector<unsigned long int>> adj_matrix;
    std::vector<unsigned long int> degrees;
public:
    Rede(unsigned long int  N, Random *rd);
    std::vector<unsigned long int> mount_algorithm_list();
    void reset();
    bool random_link();
    bool is_connected(unsigned long int v, unsigned long int w);
    void link(unsigned long int v, unsigned long int w);
};

#endif // REDE_H
