#ifndef VERICE_LINKED_LIST_H
#define VERICE_LINKED_LIST_H
#include "linked_node.h"
#include <vector>

class Linked_list{
private:
    unsigned long int number_of_nodes = 0;
    std::vector<unsigned long int> number_of_nodes_v;
    Linked_node * head = NULL;
    std::vector<Linked_node *> head_v;
    Linked_node * tail = NULL;
    std::vector<Linked_node *> tail_v;
    std::vector<Linked_node> position;
public:
    Linked_list();
    Linked_list(unsigned long int size);
    void add_node();
    unsigned long int dequeue();
    void enqueue(unsigned long int v);
    Linked_node * get_head();
    unsigned long int get_number_of_nodes();
    Linked_node * get_position(unsigned long int id);
    unsigned long int get_total_number_of_nodes();
    bool is_empty();
    void pop();
    void push();
    void remove(unsigned long int id);
    void set_ids();
    void set_head(Linked_node * head);
    void set_tail(Linked_node * tail);
    void set_link(unsigned long int v, unsigned long int w);
//**************Multi-Linked**************//
    Linked_list(unsigned long int size, unsigned int q);
    unsigned long int dequeue(unsigned int q);
    void enqueue(unsigned long int v, unsigned int q);
    Linked_node * get_head(unsigned int q);
    unsigned long int get_number_of_nodes(unsigned int q);
    bool is_empty(unsigned int q);
    void remove(unsigned long id, unsigned long int q);
    void set_link(unsigned long v, unsigned long w, unsigned long int q);
    void set_head(Linked_node * head, unsigned int q);
    void set_tail(Linked_node * tail, unsigned int q);

};

#endif // VERICE_LINKED_LIST_H
