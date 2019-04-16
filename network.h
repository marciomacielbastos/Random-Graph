#ifndef NETWORK_H
#define NETWORK_H
#include <node.h>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <randomdistribution.h>
#include <algorithm>

class Network{
private:
    std::vector<Node> nodeList;
    RandomDistribution *distribution;
    std::vector<unsigned long int> algoList;
public:
    Network(unsigned long int numberOfNodes, double s, RandomDistribution *rd);
    bool AddNode(Node n);
    bool AddLink(Node *v, Node *w);
    void SetNodeLists(unsigned long int numberOfNodes, double s);
    void SetAlgoList(unsigned long int numberOfNodes);
    unsigned long int GetNext(unsigned long int head, unsigned long int it);
    bool RandomLinkAA();
    bool RandomLinkNuno();
    std::vector<Node> GetNodeList();
};

#endif // NETWORK_H
