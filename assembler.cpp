#include "assembler.h"
#include <iostream>

Assembler::Assembler(Network net): net(net){

}

//This method iterate through a network's links adding them step by step through the Union-Find algorithm.
//In each step the size of the biggest component is added to a vector.
std::vector<std::vector<double>> Assembler::Assemble(){
    unsigned long int size = net.GetNodeList().size();
    std::vector<std::pair<unsigned long int, unsigned long int>> list = net.GetLinkList();
    UnionFind uf = UnionFind(size);
    this->mean_component_sizes.push_back({1, 1, 0});
    unsigned long int initial_number_of_links = list.size();
    while (list.size() > 0) {
        // Get random link of the network
        unsigned long int position = Random::DiscreteUniform(list.size());
        std::pair<unsigned long int, unsigned long int> pair = list[position];
        // Union the nodes of this link
        uf.Union(pair.first, pair.second);
        // Get the pair (number of nodes in the component, number of components with this number of nodes)
        std::map<unsigned long int, unsigned long int> numSize = uf.GetNumSize();
        // Mean value of the square of the number of nodes in each component
        double Sc2 = 0;
        double num_comp = 0;
        for (auto it = numSize.begin(); it != numSize.end(); it++) {
            Sc2 += static_cast<double>(it->first * it->first * it->second);
            num_comp += static_cast<double>(it->second);
        }
        // Remove the link from the list of links
        list.erase(list.begin() + static_cast<long int>(position));
        // Add to the list of mean values
        Sc2 = Sc2 / num_comp;
        auto it = numSize.end();
        it--;
        double Tm = it->first;
        double f = 1 - static_cast<double>(list.size())/initial_number_of_links;
        this->mean_component_sizes.push_back({Sc2, Tm, f});

    }
    return this->mean_component_sizes;
}
