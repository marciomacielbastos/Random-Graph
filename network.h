#ifndef NETWORK_H
#define NETWORK_H
#include <node.h>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <random.h>
#include <algorithm>
#include <thread>
#include <functional>

class Network{
private:
    std::vector<Node> list_of_nodes;
    Random *distribution;
    std::vector<unsigned long int> algorithm_list;
public:
    Network(unsigned long int number_of_nodes, Random *random_distribution);
    Network(std::vector<unsigned long int> &degrees, unsigned int num_threads);
//    ~Network();
    unsigned long int get_sum_of_degrees(const std::vector<unsigned long int> &  degrees, std::vector<unsigned long int> &  vector_sum_of_degrees, unsigned long int num_threads);
    bool add_node(Node n);
    bool link(Node *v, Node *w);
    void multithread_set_list_of_nodes(const std::vector<unsigned long int> & degrees, unsigned int num_threads);
    void set_list_of_nodes_t(std::vector<unsigned long int> & degrees, unsigned long int begin, unsigned long int end);
    void set_list_of_nodes(unsigned long int number_of_nodes);
    void set_algotithm_list();
    unsigned long int get_next_value_of_algorithm_list(unsigned long int head, unsigned long int it);
    bool random_link_AA_algorithm();
    bool RandomLinkNuno();
    std::vector<Node> get_list_of_nodes();
    std::vector<std::pair<unsigned long int, unsigned long int>> get_list_of_links();
};

#endif // NETWORK_H
