#ifndef NODE_H
#define NODE_H
#include <vector>
#include <algorithm>


class Node{
private:
    static unsigned long int total_number_of_nodes;
    unsigned long int id;
    unsigned long int degree;
    std::vector<unsigned long int> adjacency_list;

public:
    Node();
    Node(unsigned long int degree);
    Node(unsigned long int id, unsigned long int degree);
    unsigned long int get_id();
    unsigned long int ged_degree();
    void set_id(unsigned long int id);
    void set_degree(unsigned long int degree);
    bool add_neighbor(Node n);
    bool is_connected(Node n);
    bool  operator > (Node n);
    bool  operator < (Node n);
    std::vector<unsigned long int> get_adjacency_list();
//    static unsigned long int total_number_of_nodes();
    static void free();
    unsigned long int get_adjacency_list_size();
    unsigned long int get_position_in_adjacency_list(unsigned long int val);
    long int remove_link(unsigned long int);
};

#endif // NODE_H
