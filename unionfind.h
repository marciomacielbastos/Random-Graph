#ifndef UNIONFIND_H
#define UNIONFIND_H
#include <network.h>
#include <components.h>
#include <map>

class UnionFind{
private:
    std::vector<unsigned long int> root;
    std::vector<unsigned long int> sizes;
    std::vector<unsigned long int> number_of_clusters_per_size;
    //<node id, size of the component>
    std::pair<unsigned long int, unsigned long int> st_biggest;
    std::pair<unsigned long int, unsigned long int> nd_biggest;
    unsigned long int count;
public:
    UnionFind();
    UnionFind(unsigned long int N);
    void union_(unsigned long int v, unsigned long int w);
    unsigned long int find(unsigned long int v);
    bool is_connected(unsigned long int v, unsigned long int w);
    std::vector<unsigned long int> get_size_of_components();
    unsigned long int get_number_of_components();
    unsigned long int get_max_comp();
    std::pair<unsigned long int, unsigned long int> get_st_biggest();
    std::pair<unsigned long int, unsigned long int> get_nd_biggest();
//    unsigned long int GetMaxSize();
//    std::map<unsigned long int, Components> GetComponents();
//    std::map<unsigned long int, unsigned long int> GetSizeQuantity();
};

#endif // UNIONFIND_H
