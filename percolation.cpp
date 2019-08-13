#include "percolation.h"
#include <iostream>

Percolation::Percolation(){

}

UnionFind Percolation::mount_component_stats(Rede rd){
    std::vector<std::pair<unsigned long int, unsigned long int>> list = rd.get_list_of_links();
    UnionFind uf = UnionFind(rd.get_number_of_nodes());
    while (list.size() > 0) {
        std::pair<unsigned long int, unsigned long int> pair = list[list.size() - 1];
        // Union the nodes of this link
        uf.union_(pair.first, pair.second);
        // Remove the link from the list of links
        list.pop_back();
    }
    return uf;
}

/***************************************************************/
/*                         Working                             */
/***************************************************************/


//This method iterate through a network's links adding them step by step through the Union-Find algorithm.
//In each step the size of the biggest component is added to a vector.

//std::vector<std::vector<double>> Percolation::assembly(){
//    unsigned long int size = net.get_list_of_nodes().size();
//    std::vector<std::pair<unsigned long int, unsigned long int>> list = net.get_list_of_links();
//    UnionFind uf = UnionFind(size);
//    this->mean_component_sizes.push_back({1, 1, 0});
//    unsigned long int initial_number_of_links = list.size();
//    while (list.size() > 0) {
//        // Get random link of the network
//        unsigned long int position = Random::discrete_uniform(list.size());
//        std::pair<unsigned long int, unsigned long int> pair = list[position];
//        // Union the nodes of this link
//        uf.union_(pair.first, pair.second);
//        // Get the pair (number of nodes in the component, number of components with this number of nodes)
//        std::vector<unsigned long int> number_of_clusters_per_size = uf.get_size_of_components();
//        // Mean value of the square of the number of nodes in each component
//        double Sc2 = 0;
//        double Tm = 0;
//        for (unsigned long int  i = 0;  i < size; i++) {
//            if(number_of_clusters_per_size[i]) {
//                Tm = (i+1);
//                Sc2 += static_cast<double>((i+1) * (i+1));
//            }
//        }
//        // Remove the link from the list of links
//        list.erase(list.begin() + static_cast<long int>(position));
//        double f = 1 - static_cast<double>(list.size())/initial_number_of_links;
//        this->mean_component_sizes.push_back({Sc2, Tm, f});
//    }
//    std::vector<unsigned long int> number_of_clusters_per_size = uf.get_size_of_components();
//    for(unsigned long int i=0; i < uf.get_max_comp(); i++){
//        std::cout<<i<<", "<<number_of_clusters_per_size[i]<<std::endl;
//    }
//    return this->mean_component_sizes;
//}
