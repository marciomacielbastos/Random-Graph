#ifndef NETWORK_H
#define NETWORK_H
#include <algorithm>
#include <binary_adjmatrix.h>
#include <functional>
#include <map>
#include <node.h>
#include <random.h>
#include <stdlib.h>
#include <time.h>
#include <thread>
#include <vector>

class Network{
private:
    std::vector<unsigned long int> algorithm_list;
    Random *distribution;
    bool is_sorted;
    std::vector<Node> list_of_nodes;
    std::vector<std::pair<unsigned long int, unsigned long int>> list_of_links;
    std::vector<unsigned long int> map_to_sorted_list_of_nodes;    
public:
    Network(unsigned long int number_of_nodes, Random *random_distribution);
    Network(std::vector<unsigned long int> &degrees, unsigned int num_threads);
//    ~Network();    
    bool add_node(Node n);
    std::vector<Node> get_list_of_nodes();
    std::map<unsigned long int, unsigned long int> get_map_id_order();
    unsigned long int get_next_value_of_algorithm_list(unsigned long int head, unsigned long int it);
    unsigned long int get_sum_of_degrees(const std::vector<unsigned long int> &  degrees, std::vector<unsigned long int> &  vector_sum_of_degrees, unsigned long int num_threads);
    std::vector<std::pair<unsigned long int, unsigned long int>> get_list_of_links();
    bool link(Node *v, Node *w);
    void multithread_set_list_of_nodes(const std::vector<unsigned long int> & degrees, unsigned int num_threads);
    bool random_link_AA_algorithm();
    bool random_link_AA_algorithm(bool LinkList);
    bool RandomLinkNuno();
    void set_algotithm_list();
    void set_list_of_nodes(unsigned long int number_of_nodes);
    void set_list_of_nodes_t(std::vector<unsigned long int> & degrees, unsigned long int begin, unsigned long int end);
    void sort_list_of_nodes();
};

#endif // NETWORK_H
