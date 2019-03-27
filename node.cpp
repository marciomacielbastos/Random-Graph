#include "node.h"

unsigned long int Node::number_of_nodes = 0;


Node::Node(){
    this->id = this->number_of_nodes;
    this->number_of_nodes++;
}

Node::Node(unsigned long int degree){
    this->id = this->number_of_nodes;
    this->number_of_nodes++;
    this->degree = degree;
}

//This must be optimized!!!
bool Node::IsConnected(Node n){
    for (auto x : this->adjacency_list){
        if(x == n.GetId()){
            return true;
        }
    }
    return false;
}

unsigned long int Node::GetId(){
    return this->id;
}

bool Node::AddNeighbor(Node n){
    if(this->adjacency_list.size() < this->degree){
        this->adjacency_list.push_back(n.GetId());
        return true;
    }
    else {
        return false;
    }
}
