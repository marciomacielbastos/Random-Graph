#ifndef LINKED_NODE_H
#define LINKED_NODE_H
#include <vector>


class Linked_node{
private:
    unsigned long int id;
    Linked_node *next;
    Linked_node *prev;
    std::vector<Linked_node *> next_v;
    std::vector<Linked_node *> prev_v;
    std::vector<Linked_node *> sons;
public:
    Linked_node();
    Linked_node(unsigned long int id);
    unsigned long int get_id();
    Linked_node * get_next();
    Linked_node * get_prev();
    void set_id(unsigned long int id);
    void set_next(Linked_node *next);
    void set_prev(Linked_node *prev);
    void add_son(Linked_node *son);
//**************Multi-Linked**************//
    Linked_node(unsigned long int id, unsigned int q);
    Linked_node * get_next(unsigned int q);
    Linked_node * get_prev(unsigned int q);
    void set_next(Linked_node *next, unsigned int q);
    void set_prev(Linked_node *prev, unsigned int q);
};

#endif // LINKED_NODE_H
