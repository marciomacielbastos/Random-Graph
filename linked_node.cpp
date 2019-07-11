#include "linked_node.h"

Linked_node::Linked_node(){
    this->next = this;
    this->prev = this;
}

Linked_node::Linked_node(unsigned long int id){
    this->id =id;
    this->next = this;
    this->prev = this;
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
