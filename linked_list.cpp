#include "linked_list.h"

Linked_list::Linked_list(){

}

Linked_list::Linked_list(unsigned long int size){
    for(unsigned long int i = 0; i < size; i++){
        Linked_node ln = Linked_node(i);
        this->position.push_back(ln);
    }
}

void Linked_list::add_node(){
    unsigned long int id = this->number_of_nodes++;
    Linked_node n = Linked_node(id);
    this->position.push_back(n);
    if(id == 0){
        set_head(&n);
    } else{
        set_tail(&n);
    }
}

unsigned long int Linked_list::dequeue(){
    if(number_of_nodes > 0){
        unsigned long int val = this->head->get_id();
        set_head(this->head->get_next());
        number_of_nodes--;
        return val;
    }
    else{
        return -1;
    }
}

void Linked_list::enqueue(unsigned long int v){
    if(number_of_nodes == 0){
        set_head(this->get_position(v));
        set_tail(this->get_position(v));

    }
    tail->set_next(this->get_position(v));
    this->get_position(v)->set_prev(tail);
    set_tail(this->get_position(v));
    number_of_nodes++;
}

Linked_node * Linked_list::get_head(){
    return this->head;
}

unsigned long int Linked_list::get_number_of_nodes(){
    return this->number_of_nodes;
}

Linked_node * Linked_list::get_position(unsigned long id){
    return &this->position[id];
}

unsigned long int Linked_list::get_total_number_of_nodes(){
    return this->position.size();
}

bool Linked_list::is_empty(){
    return (number_of_nodes==0);
}

void Linked_list::remove(unsigned long id){
    set_link(get_position(id)->get_prev()->get_id(), get_position(id)->get_next()->get_id());
}

void Linked_list::set_head(Linked_node *head){
    this->head = head;
    this->head->set_prev(this->head);
}

void Linked_list::set_ids(){
    for(unsigned long int i = 0; i < this->position.size(); i++){
        position[i].set_id(i);
    }
}

void Linked_list::set_link(unsigned long v, unsigned long w){
    this->get_position(v)->set_next(this->get_position(w));
    this->get_position(w)->set_prev(this->get_position(v));
    set_tail(this->get_position(w));
}

void Linked_list::set_tail(Linked_node * tail){
    this->tail = tail;
    this->tail->set_next(this->tail);
}


//**************Multi-Linked**************//


Linked_list::Linked_list(unsigned long int size, unsigned int q){
    std::vector<unsigned long int> number_of_nodes_v(q);
    this->number_of_nodes_v = number_of_nodes_v;
    std::vector<Linked_node *> head_v(q);
    this->head_v = head_v;
    std::vector<Linked_node *> tail_v(q);
    this->tail_v = tail_v;
    for(unsigned long int i = 0; i < size; i++){
        Linked_node ln = Linked_node(i, q);
        this->position.push_back(ln);
    }
}

unsigned long int Linked_list::dequeue(unsigned int q){
    if(number_of_nodes_v[q] > 0){
        unsigned long int val = this->head_v[q]->get_id();
        set_head(this->head_v[q]->get_next(q), q);
        number_of_nodes_v[q]--;
        return val;
    }
    else{
        return -1;
    }
}

void Linked_list::enqueue(unsigned long int v, unsigned int q){
    if(number_of_nodes_v[q] == 0){
        set_head(this->get_position(v), q);
        set_tail(this->get_position(v), q);

    }
    tail_v[q]->set_next(this->get_position(v), q);
    this->get_position(v)->set_prev(tail, q);
    set_tail(this->get_position(v), q);
    number_of_nodes_v[q]++;
}

Linked_node * Linked_list::get_head(unsigned int q){
    return this->head_v[q];
}

unsigned long int Linked_list::get_number_of_nodes(unsigned int q){
    return this->number_of_nodes_v[q];
}

bool Linked_list::is_empty(unsigned int q){
    return (number_of_nodes_v[q]==0);
}

void Linked_list::set_head(Linked_node *head, unsigned int q){
    this->head_v[q] = head;
    this->head_v[q]->set_prev(this->head_v[q]);
}

void Linked_list::set_tail(Linked_node * tail, unsigned int q){
    this->tail_v[q] = tail;
    this->tail_v[q]->set_next(this->tail_v[q], q);
}
