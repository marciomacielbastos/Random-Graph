#ifndef NETWORK_H
#define NETWORK_H
#include <node.h>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <zipfgen.h>
#include <algorithm>

class Network{
private:
    std::vector<Node> nodeList;
    std::vector<unsigned long int> algoList;
public:
    Network(unsigned long int numberOfNodes, double degree);
    bool AddNode(Node n);
    bool AddLink(Node v, Node w);
    void SetNodeLists(unsigned long int numberOfNodes);
    void SetAlgoList(unsigned long int numberOfNodes);
    unsigned long int GetNext(unsigned long int head, unsigned long int it);
    bool RandomLinkAA();
    bool RandomLinkNuno();
    unsigned long int Uniform(unsigned long int n);
    unsigned long int Uniform(unsigned long int max, unsigned long int min);
};

#endif // NETWORK_H
