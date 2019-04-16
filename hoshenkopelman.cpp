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
    bool key = false;
    unsigned long int adjacent_list_position;
    for (unsigned long int i=0; i<size; ++i) {
        min_label = labels[i];
        Node n = nodeList[i];
        std::vector<unsigned long int> adjL = n.GetAdjacencyList();
        for (adjacent_list_position = 0; adjacent_list_position < adjL.size(); adjacent_list_position++) {
            unsigned long int val = labels[adjL[adjacent_list_position]];
            if(min_label < val){
                labels[adjL[adjacent_list_position]] = min_label;
                if(i > adjL[adjacent_list_position]){
                    key = true;
                    break;
                }
            } else if(min_label > val){
                min_label = labels[adjL[adjacent_list_position]];
                adjacent_list_position = 0;
            }
        }
        labels[i] = min_label;
        if(key){
            i = adjacent_list_position - 1;
            key = false;
        }
    }
}
