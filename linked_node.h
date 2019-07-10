#ifndef LINKED_NODE_H
#define LINKED_NODE_H


class Linked_node{
private:
    unsigned long int id;
    Linked_node *next;
    Linked_node *prev;
public:
    Linked_node();
    Linked_node(unsigned long int id);
    unsigned long int get_id();
    Linked_node * get_next();
    Linked_node * get_prev();
    void set_id(unsigned long int id);
    void set_next(Linked_node *next);
    void set_prev(Linked_node *prev);
};

#endif // LINKED_NODE_H
