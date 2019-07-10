#include "linked_node.h"

Linked_node::Linked_node(){
    this->next = nullptr;
    this->prev = nullptr;
}

Linked_node::Linked_node(unsigned long int id){
    this->id =id;
    this->next = nullptr;
    this->prev = nullptr;
}

unsigned long int Linked_node::get_id(){
    return this->id;
}

Linked_node * Linked_node::get_next(){
    return this->next;
}

Linked_node * Linked_node::get_prev(){
    return this->prev;
}

void Linked_node::set_id(unsigned long id){
    this->id=id;
}

void Linked_node::set_next(Linked_node *next){
    this->next = next;
}

void Linked_node::set_prev(Linked_node *prev){
    this->prev = prev;
}
