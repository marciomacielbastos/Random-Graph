#ifndef NETWORK_H
#define NETWORK_H
#include <node.h>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <random.h>
#include <algorithm>

class Network{
private:
    std::vector<Node> nodeList;
    Random *distribution;
    std::vector<unsigned long int> algoList;
    unsigned long int linkCounter;
public:
    Network(unsigned long int numberOfNodes, Random *rd);
    bool AddNode(Node n);
    bool AddLink(Node *v, Node *w);
    void SetNodeLists(unsigned long int numberOfNodes);
    void SetAlgoList(unsigned long int numberOfNodes);
    unsigned long int GetNext(unsigned long int head, unsigned long int it);
    bool RandomLinkAA();
    bool RandomLinkNuno();
    std::vector<Node> GetNodeList();
    long int RandomPop(unsigned long int);
    unsigned long int GetLinkCounter();
    std::vector<std::pair<unsigned long int, unsigned long int>> GetLinkList();
};

#endif // NETWORK_H
