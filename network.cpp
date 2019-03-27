#include "network.h"

bool Network::AddNode(Node n){
    this->nodeList.push_back(n);
    return true;
}

bool Network::AddLink(Node v, Node w){
    bool isLinked;
    isLinked = v.AddNeighbor(w);
    if(!isLinked){
        return false;
    }
    isLinked = w.AddNeighbor(v);
    if(!isLinked){
        return false;
    }
    return true;
}

Network::Network(unsigned long int numberOfNodes, double degree){
    double N = static_cast<double>(numberOfNodes);
    ZipfGen zg = ZipfGen(N, degree);
    std::vector<unsigned long int> rv;
    rv = zg.RandomApproxMethod(numberOfNodes);
    for (unsigned long int i = 0; i < numberOfNodes; i++) {
        unsigned long int n = rv[i];
        Node node = Node(n);
        AddNode(node);
        std::vector<unsigned long int> links(n, node.GetId());
        this->algoList.insert(algoList.end(), links.begin(), links.end());
    }
}

bool Network::RandomLink(){
    return true;
}

