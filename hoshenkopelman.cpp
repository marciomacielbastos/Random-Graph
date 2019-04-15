#include "hoshenkopelman.h"

HoshenKopelman::HoshenKopelman(unsigned long int size){
    this->size = size;
    for (unsigned long int i=0; i < size; i++) {
        this->labels.push_back(i);
    }
}

//Do it twice!
std::vector<unsigned long int> HoshenKopelman::Relabel(const std::vector<Node> & nodeList){
    unsigned long int min_label;
    for (unsigned long int i=0; i<size; i++) {
        min_label = i;
        Node n = nodeList[i];
        for (unsigned long int j=0; j < n.GetAdjacencyList().size(); j++) {
            unsigned long int val = labels[n.GetAdjacencyList()[j]];
            if(min_label > val){
                min_label = val;
            }
        }
        labels[i] = min_label;
    }
    return labels;
}
