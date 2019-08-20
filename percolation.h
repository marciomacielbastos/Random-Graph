#ifndef ASSEMBLER_H
#define ASSEMBLER_H
#include <network.h>
#include <random.h>
#include <unionfind.h>
#include <rede.h>

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>
#include <cmath>

class Percolation{
private:
//    Binary_adjmatrix ba;
//    Network net;
    std::vector<std::vector<double>> mean_component_sizes;
    std::vector<std::pair<unsigned long int, unsigned long int>> component_stats;

public:
    Percolation();
    void progress_bar(float progress);
    void write_mean_cluster_size(const std::string& filename, double pc, double mcs, bool append);
    void write_biggest_component(const std::string& filename, double pc, unsigned long int biggest, bool append);
    UnionFind  mount_geodesical_stats(Rede rd);
    UnionFind mount_component_stats(Rede rd, unsigned int freq_of_reg, const std::string& params);
};

#endif // ASSEMBLER_H
