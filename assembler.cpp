#include "assembler.h"

Assembler::Assembler(Network net){
    unsigned long int size = net.GetNodeList().size();
    UnionFind uf = UnionFind(size);
    while (net.GetLinkCounter() > 0) {
        unsigned long int node1 = Random::DiscreteUniform(size);
        unsigned long int node2 = static_cast<unsigned long int>(net.RandomPop(node1));
        uf.Union(node1, node2);
    }

}
