#include "bfs_modified.h"

Bfs_modified::Bfs_modified(){

}


Bfs_modified::Bfs_modified(Network net){
    net.sort_list_of_nodes();
    std::vector<std::vector<unsigned long int>> lon(net.get_list_of_nodes().size());
    Linked_list ll = Linked_list(lon.size());
    ll.set_ids();
    this->ll = ll;
    for(Node n : net.get_list_of_nodes()){
        lon[n.get_id()] = n.get_adjacency_list();
        ll.enqueue(n.get_id());
    }
    this->ll = ll;
    Distance_matrix dm = Distance_matrix(ll.get_total_number_of_nodes());
}

void Bfs_modified::mount_dist_matrix(){
    unsigned long int count = ll.get_total_number_of_nodes();
    //Create tree method
    Linked_list bfs_ll = Linked_list(count);
    Linked_list queue = Linked_list(count);
    std::vector<bool> marked(count, false);
    count = (count * (count - 1)) / 2;
    //Iterate while all the distance cells are not filled
    while(count > 0){
        unsigned long int s = ll.dequeue();
        marked[s] = true;
        queue.enqueue(s);
        while(!queue.is_empty()){
            for(unsigned long int w : lon[v]){
                if(!marked[w]){
                    marked[w] = true;
                    queue.enqueue(w);
                    d = 0;
                    while(current->id != prev->id){
                        d++;
                    }
                }
            }
        }
    }
}
