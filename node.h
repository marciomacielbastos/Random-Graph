#ifndef NODE_H
#define NODE_H
#include <vector>


class Node{
private:
    static unsigned long int number_of_nodes;
    unsigned long int id;
    std::vector<Node> adjacency_list;

public:
    Node();
    unsigned long int non();
};

#endif // NODE_H
