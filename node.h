#ifndef NODE_H
#define NODE_H
#include <vector>
#include <algorithm>


class Node{
private:
    std::vector<unsigned long int> adjacency_list;
    unsigned long int degree;
    unsigned long int id;
    static unsigned long int total_number_of_nodes;

public:
    Node();
    Node(unsigned long int degree);
    Node(unsigned long int id, unsigned long int degree);
    bool add_neighbor(Node n);
    static void free();
    unsigned long int ged_degree();
    unsigned long int get_id();
    bool is_connected(Node n);
    std::vector<unsigned long int> get_adjacency_list();
    unsigned long int get_adjacency_list_size();
    unsigned long int get_position_in_adjacency_list(unsigned long int val);
    long int remove_link(unsigned long int);
    void set_degree(unsigned long int degree);
    void set_id(unsigned long int id); 
    bool  operator > (Node n);
    bool  operator < (Node n);   
//    static unsigned long int total_number_of_nodes();   
};

#endif // NODE_H
