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
    } else {
        return false;
    }
}

unsigned long int Node::GedDegree(){
    return this->degree;
}

void Node::SetDegree(unsigned long int degree){
    this->degree = degree;
}

bool  Node::operator>(Node n){
    if(this->GedDegree() > n.GedDegree()){
        return true;
    } else {
        return false;
    }
}

bool  Node::operator<(Node n){
    if(this->GedDegree() < n.GedDegree()){
        return true;
    } else {
        return false;
    }
}

std::vector<unsigned long int> Node::GetAdjacencyList(){
    return this->adjacency_list;
}

unsigned long int Node::NumberOfNodes(){
    return number_of_nodes;
}

void Node::Free(){
    number_of_nodes = 0;
}

unsigned long int Node::GetAdjacencySize(){
    return this->adjacency_list.size();
}

unsigned long int Node::GetPosition(unsigned long int val){
    std::vector<unsigned long int>::iterator it = std::find(adjacency_list.begin(), adjacency_list.end(), val);
    return *it;
}

long int Node::RemoveLink(unsigned long int position){
    if(GetAdjacencySize() > position){
        long int node_id = static_cast<long int>(this->adjacency_list[position]);
        this->adjacency_list.erase (this->adjacency_list.begin() + static_cast<long int >(position));
        return node_id;
    } else {
        return -1;
    }
}
