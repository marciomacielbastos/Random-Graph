#include "hoshenkopelman.h"

HoshenKopelman::HoshenKopelman(unsigned long int size){
    this->size = size;
}


void HoshenKopelman::Relabel(const std::vector<Node> & nodeList){
    unsigned long int min_label;
    std::vector<unsigned long int> labels;
    for (unsigned long int i=0; i < size; i++) {
        labels.push_back(i);
    }
    bool key = false;
    unsigned long int adjacent_list_position;
    for (unsigned long int i=0; i<size; ++i) {
        min_label = labels[i];
        Node n = nodeList[i];
        std::vector<unsigned long int> adjL = n.GetAdjacencyList();
        for (adjacent_list_position = 0; adjacent_list_position < adjL.size(); adjacent_list_position++) {
            unsigned long int val = labels[adjL[adjacent_list_position]];
            /* If the current minimum label value (at node 'i' running through its adjacency list)
               is lower than the label of its j-th adjacent node, then replace the label of the j-th adjacent node. */
            if(min_label < val){
                labels[adjL[adjacent_list_position]] = min_label;
                /* Also, if the j-th adjacent node has lower id, update its label and go back to its position in the outer loop */
                if(i > adjL[adjacent_list_position]){
                    key = true;
                    break;
                }
            }
            /* If the current minimum label value (at node 'i' running through its adjacency list)
               is bigger than the label of its j-th adjacent node, then update the minimum label
               and start again the label update of the i-th adjacency list */
            else if(min_label > val){
                min_label = labels[adjL[adjacent_list_position]];
                adjacent_list_position = 0;
            }
        }
        labels[i] = min_label;
        /* Resetting the i-th position to the position where the break was called. */
        if(key){
            i = adjacent_list_position - 1;
            key = false;
        }
    }

    /*Build the map of labels and connected components. */
    for (unsigned long int i=0; i < labels.size(); i++) {
        if ( this->components.find(labels[i]) == this->components.end() ){
            std::vector<unsigned long int> component;
            component.push_back(i);
            components[labels[i]] = component;
        } else {
            components[labels[i]].push_back(i);
        }
    }
}

unsigned long int HoshenKopelman::GetNumberOfComponents() {
    return this->components.size();
}
