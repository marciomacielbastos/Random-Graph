#ifndef UNIONFIND_H
#define UNIONFIND_H
#include <network.h>


class UnionFind{
private:
    std::vector<unsigned long int> id;
    std::vector<unsigned long int> sizes;
    unsigned int count;
public:
    UnionFind(unsigned long int N);
    void Union(unsigned long int v, unsigned long int w);
    unsigned long int Find(unsigned long int v);
    unsigned long int GetCount();
    bool Connected(unsigned long int v, unsigned long int w);
};

#endif // UNIONFIND_H
