#ifndef NODE_H
#define NODE_H
#include <vector>


class Node{
private:
    static unsigned long int number_of_nodes;
    unsigned long int id;
    unsigned long int degree;
    std::vector<unsigned long int> adjacency_list;

public:
    Node();
    Node(unsigned long int degree);
    unsigned long int NumberOfNodes();
    unsigned long int GetId();
    bool AddNeighbor(Node n);
};

#endif // NODE_H
