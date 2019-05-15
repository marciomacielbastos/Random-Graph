#include "node.h"

unsigned long int Node::total_number_of_nodes = 0;


Node::Node(){
    this->id = this->total_number_of_nodes;
    this->total_number_of_nodes++;
}

Node::Node(unsigned long int degree){
    this->id = this->total_number_of_nodes;
    this->total_number_of_nodes++;
    this->degree = degree;
}

Node::Node(unsigned long int id, unsigned long int degree){
    this->id = id;
    this->total_number_of_nodes++;
    this->degree = degree;
}

//This must be optimized!!!
bool Node::is_connected(Node n){
    for (auto x : this->adjacency_list){
        if(x == n.get_id()){
            return true;
        }
    }
    return false;
}

void Node::set_id(unsigned long int id){
    this->id = id;
}

unsigned long int Node::get_id(){
    return this->id;
}

bool Node::add_neighbor(Node n){
    if(this->adjacency_list.size() < this->degree){
        this->adjacency_list.push_back(n.get_id());
        return true;
    } else {
        return false;
    }
}

unsigned long int Node::ged_degree(){
    return this->degree;
}

void Node::set_degree(unsigned long int degree){
    this->degree = degree;
}

bool  Node::operator>(Node n){
    if(this->ged_degree() > n.ged_degree()){
        return true;
    } else {
        return false;
    }
}

bool  Node::operator<(Node n){
    if(this->ged_degree() < n.ged_degree()){
        return true;
    } else {
        return false;
    }
}

std::vector<unsigned long int> Node::get_adjacency_list(){
    return this->adjacency_list;
}

//unsigned long int Node::total_number_of_nodes(){
//    return total_number_of_nodes;
//}

void Node::free(){
    total_number_of_nodes = 0;
}

unsigned long int Node::get_adjacency_list_size(){
    return this->adjacency_list.size();
}

unsigned long int Node::get_position_in_adjacency_list(unsigned long int val){
    std::vector<unsigned long int>::iterator it = std::find(adjacency_list.begin(), adjacency_list.end(), val);
    return *it;
}

long int Node::remove_link(unsigned long int position){
    if(get_adjacency_list_size() > position){
        long int node_id = static_cast<long int>(this->adjacency_list[position]);
        this->adjacency_list.erase (this->adjacency_list.begin() + static_cast<long int >(position));
        return node_id;
    } else {
        return -1;
    }
}
