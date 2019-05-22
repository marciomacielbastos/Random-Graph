#ifndef ASSEMBLER_H
#define ASSEMBLER_H
#include <random.h>
#include <network.h>
#include <unionfind.h>
#include <vector>

class Assembler{
private:
    Network net;
    std::vector<std::vector<double>> mean_component_sizes;

public:
    Assembler(Network net);
    std::vector<std::vector<double>> assembly();

};

#endif // ASSEMBLER_H
