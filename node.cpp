#include "node.h"

unsigned long int Node::number_of_nodes = 0;


Node::Node(){
    this->id = this->number_of_nodes;
    this->number_of_nodes++;

}

unsigned long int Node::non(){
    return this->number_of_nodes;
}
