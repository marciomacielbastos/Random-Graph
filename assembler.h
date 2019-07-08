#ifndef ASSEMBLER_H
#define ASSEMBLER_H
#include <network.h>
#include <random.h>
#include <unionfind.h>
#include <vector>

class Assembler{
private:
    Binary_adjlist ba;
    Network net;
    std::vector<std::vector<double>> mean_component_sizes;

public:
    Assembler(Network net);
    std::vector<std::vector<double>> assembly();

};

#endif // ASSEMBLER_H
