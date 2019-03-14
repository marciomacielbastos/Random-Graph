#ifndef NETWORK_H
#define NETWORK_H
#include <node.h>
#include <vector>
#include <time.h>
#include <stdlib.h>

class Network{
private:
    std::vector<Node> NodeList;
    unsigned long int GetRandomDegree();
public:
    Network(unsigned long int numberOfNodes);
    void AddNode();
    void AddLink(Node v, Node w);
};

#endif // NETWORK_H
