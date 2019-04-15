#ifndef HOSHENKOPELMAN_H
#define HOSHENKOPELMAN_H
#include <vector>
#include <node.h>

class HoshenKopelman{
private:
    unsigned long int size;
    unsigned long int cl_order = 0;
    std::vector<unsigned long int> labels;
public:
    HoshenKopelman(unsigned long int size);
    std::vector<unsigned long int> Relabel(const std::vector<Node> &nodeList);
};

#endif // HOSHENKOPELMAN_H
