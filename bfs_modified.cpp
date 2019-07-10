#include "bfs_modified.h"

Bfs_modified::Bfs_modified(){

}


Bfs_modified::Bfs_modified(Network net){
    net.sort_list_of_nodes();
    std::vector<std::vector<unsigned long int>> lon(net.get_list_of_nodes().size());
    Linked_list ll = Linked_list(lon.size());
    this->ll = ll;
    for(Node n : net.get_list_of_nodes()){
        lon[n.get_id()] = n.get_adjacency_list();
        ll.enqueue(n.get_id());
    }
    Distance_matrix dm = Distance_matrix(ll.get_number_of_nodes());
}

void Bfs_modified::mount_dist_matrix(){
    unsigned long int count = ll.get_number_of_nodes();
    count = (count * (count - 1)) / 2;
    // Iterate while all the distance cells are not filled
//    while(count > 0){
//        for(unsigned long int w : lon)
//    }
}
