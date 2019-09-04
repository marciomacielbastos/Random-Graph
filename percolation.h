#ifndef ASSEMBLER_H
#define ASSEMBLER_H
#include <network.h>
#include <random.h>
#include <unionfind.h>
#include <rede.h>

#include <algorithm>
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
    std::vector<std::pair<double, double>> mean_cluster_size;
    std::vector<std::pair<double, double>> biggest_component;
    std::vector<std::vector<double>> mean_component_sizes;
    std::vector<std::pair<unsigned long int, unsigned long int>> component_stats;

public:
    Percolation();
    Percolation(unsigned int freq_of_reg);
    void progress_bar(float progress);
    void write_component_stats(const std::string& filename);
    void write_mean_cluster_size(const std::string& filename, double pc, double mcs, bool append);
    void write_biggest_component(const std::string& filename, double pc, unsigned long int biggest, bool append);
    UnionFind  mount_geodesical_stats(Rede rd);
    UnionFind mount_component_stats(Rede rd, unsigned int freq_of_reg, const std::string& params);
    std::vector<std::vector<std::vector<double>>> mount_component(Rede rd, unsigned long int freq_of_reg);
    void mount_component_mean(Rede rd, unsigned int freq_of_reg);
    void molloy_reed(bool &is_already_added, double &molloy_reed_k, double &molloy_reed_k2, const unsigned long int degree, double &m);
};

#endif // ASSEMBLER_H
