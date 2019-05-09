#include "assembler.h"

Assembler::Assembler(Network net): net(net){

}


//This method iterate through a network's links adding them step by step through the Union-Find algorithm.
//In each step the size of the biggest component is added to a vector.
void Assembler::Assemble(){
    unsigned long int size = net.GetNodeList().size();
    UnionFind uf = UnionFind(size);
    std::vector<std::pair<unsigned long int, unsigned long int>> list = net.GetLinkList();
    while (list.size() > 0) {
        unsigned long int position = Random::DiscreteUniform(list.size());
        std::pair<unsigned long int, unsigned long int> pair = list[position];
        uf.Union(pair.first, pair.second);
        list.erase(list.begin() + static_cast<long int>(position));
    }
    uf = uf;
}
