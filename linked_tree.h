#ifndef LINKED_TREE_H
#define LINKED_TREE_H
#include <linked_node.h>
#include <vector>


class Linked_tree{
private:
    unsigned long int number_of_nodes = 0;
    std::vector<Linked_node> position;
    Linked_node * root = NULL;
public:
    Linked_tree();
    Linked_tree(unsigned long int size);
    void add(unsigned long int v, unsigned long int w);
    unsigned long int get_number_of_nodes();
    Linked_node * get_position(unsigned long int id);
    unsigned long int get_total_number_of_nodes();
    unsigned long int remove(unsigned long int v);
    void set_root(Linked_node *root);

};

#endif // LINKED_TREE_H
