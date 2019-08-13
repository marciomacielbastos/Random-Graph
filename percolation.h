#ifndef ASSEMBLER_H
#define ASSEMBLER_H
#include <network.h>
#include <random.h>
#include <unionfind.h>
#include <vector>
#include <rede.h>

class Percolation{
private:
//    Binary_adjmatrix ba;
//    Network net;
    std::vector<std::vector<double>> mean_component_sizes;
    std::vector<std::pair<unsigned long int, unsigned long int>> component_stats;

public:
    Percolation();
//    Percolation(Network net);
//    UnionFind  mount_component_stats();
    UnionFind  mount_component_stats(Rede rd);
//    std::vector<std::vector<double>> assembly();
};

#endif // ASSEMBLER_H
