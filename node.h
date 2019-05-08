#ifndef NODE_H
#define NODE_H
#include <vector>
#include <algorithm>


class Node{
private:
    static unsigned long int number_of_nodes;
    unsigned long int id;
    unsigned long int degree;
    std::vector<unsigned long int> adjacency_list;

public:
    Node();
    Node(unsigned long int degree);
    unsigned long int GetId();
    unsigned long int GedDegree();
    void SetDegree(unsigned long int degree);
    bool AddNeighbor(Node n);
    bool IsConnected(Node n);
    bool  operator > (Node n);
    bool  operator < (Node n);
    std::vector<unsigned long int> GetAdjacencyList();
    static unsigned long int NumberOfNodes();
    static void Free();
    unsigned long int GetAdjacencySize();
    unsigned long int GetPosition(unsigned long int val);
    long int RemoveLink(unsigned long int);
};

#endif // NODE_H
