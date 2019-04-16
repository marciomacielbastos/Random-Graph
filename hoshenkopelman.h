#ifndef HOSHENKOPELMAN_H
#define HOSHENKOPELMAN_H
#include <vector>
#include <map>
#include <node.h>

class HoshenKopelman{
private:
    unsigned long int size;
    unsigned long int cl_order = 0;
    std::map<unsigned long int, std::vector<unsigned long int>> components;

public:
    HoshenKopelman(unsigned long int size);
    void Relabel(const std::vector<Node> &nodeList);
    unsigned long int GetNumberOfComponents();
};

#endif // HOSHENKOPELMAN_H
