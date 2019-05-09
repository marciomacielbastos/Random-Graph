#ifndef ASSEMBLER_H
#define ASSEMBLER_H
#include <random.h>
#include <network.h>
#include <unionfind.h>
#include <vector>

class Assembler{
private:
    Network net;
    std::vector<unsigned long int> component_sizes;

public:
    Assembler(Network net);
    void Assemble();

};

#endif // ASSEMBLER_H
