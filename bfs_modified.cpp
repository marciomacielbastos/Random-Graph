#include "bfs_modified.h"

Bfs_modified::Bfs_modified(){

}

Bfs_modified::Bfs_modified(Network net){
    std::vector<std::vector<unsigned long int>> lon(net.get_list_of_nodes().size());
    Linked_list ll = Linked_list(lon.size());
    ll.set_ids();
    this->ll = ll;
    for(Node n : net.get_list_of_nodes()){
        lon[n.get_id()] = n.get_adjacency_list();
        ll.enqueue(n.get_id());
    }
    this->ll = ll;
    this->lon = lon;
    Distance_matrix dm = Distance_matrix(ll.get_total_number_of_nodes());
    this->distance_matrix = dm;
}

void Bfs_modified::mount_dist_matrix(){
    unsigned long int count = ll.get_total_number_of_nodes();
    //Create tree method
    Linked_list bfs_ll = Linked_list(count);
    Linked_list queue = Linked_list(count);
    count = (count * (count - 1)) / 2;
    //Iterate while all the distance cells are not filled
    while(count > 0){
        std::vector<bool> marked(bfs_ll.get_total_number_of_nodes(), false);
        unsigned long int s = ll.dequeue();
        Linked_node * current = bfs_ll.get_position(s);
        bfs_ll.set_head(current);
        marked[s] = true;
        queue.enqueue(s);
        while(!queue.is_empty()){
            unsigned long int v = queue.dequeue();
            for(unsigned long int w : lon[v]){
                bfs_ll.get_position(w)->set_prev(current);
                if(!marked[w]){
                    marked[w] = true;
                    queue.enqueue(w);
                    unsigned long int d = 0;
                    current = bfs_ll.get_position(w);
                    while(current->get_id() != current->get_prev()->get_id()){
                        d++;
                        if (distance_matrix.get_distance(current->get_id(), current->get_prev()->get_id()) == 0) {
                            distance_matrix.set_distance(current->get_id(), current->get_prev()->get_id(), d);
                            count--;
                        }
                        current = current->get_prev();
                    }
                } else if (distance_matrix.get_distance(v, w) == 0) {
                    distance_matrix.set_distance(v, w, 1);
                    count--;
                }
            }
        }
    }
}
