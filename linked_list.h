#ifndef VERICE_LINKED_LIST_H
#define VERICE_LINKED_LIST_H
#include <linked_node.h>
#include <vector>

class Linked_list{
private:
    unsigned long int number_of_nodes = 0;
    Linked_node * head;
    Linked_node * tail;
    std::vector<Linked_node> position;
public:
    Linked_list();
    Linked_list(unsigned long int size);
    void add_node();
    unsigned long int dequeue();
    void enqueue(unsigned long int v);
    unsigned long int get_number_of_nodes();
    Linked_node * get_position(unsigned long int id);
    void pop();
    void push();
    void remove(unsigned long int id);
    void set_head(Linked_node * head);
    void set_tail(Linked_node * tail);
    void set_link(unsigned long int v, unsigned long int w);

};

#endif // VERICE_LINKED_LIST_H
