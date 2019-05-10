#ifndef UNIONFIND_H
#define UNIONFIND_H
#include <network.h>
#include <components.h>
#include <map>

class UnionFind{
private:
    std::vector<unsigned long int> id;
    std::vector<unsigned long int> sizes;
    std::map<unsigned long int, Components> components;
    unsigned long int count;
public:
    UnionFind(unsigned long int N);
    void Union(unsigned long int v, unsigned long int w);
    unsigned long int Find(unsigned long int v);
    unsigned long int GetNumberOfComponents();
    unsigned long int GetMaxSize();
    std::map<unsigned long int, Components> GetComponents();
    std::vector<unsigned long int> GetComponentsSize();
    std::map<unsigned long int, unsigned long int> GetNumSize();
    bool Connected(unsigned long int v, unsigned long int w);
};

#endif // UNIONFIND_H
