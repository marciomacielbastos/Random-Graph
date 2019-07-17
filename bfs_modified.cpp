#include "bfs_modified.h"

Bfs_modified::Bfs_modified(){

}

Bfs_modified::Bfs_modified(Network net){
    average_path = 0;
    std::vector<std::vector<unsigned long int>> neighbors(net.get_list_of_nodes().size());
    this->linked_lists = Linked_list(neighbors.size(), 3);
    for(Node n : net.get_list_of_nodes()){
        neighbors[n.get_id()] = n.get_adjacency_list();
        linked_lists.enqueue(n.get_id(), 0);
    }
    this->neighbors = neighbors;
//    Distance_matrix dm = Distance_matrix(linked_lists.get_total_number_of_nodes());
//    binary_adjmatrix = Binary_adjmatrix(linked_lists.get_total_number_of_nodes());
}

void Bfs_modified::mount_dist_matrix(){
    //While the whole distance matrix is not filled
    unsigned long int count = linked_lists.get_total_number_of_nodes();
    count = (count * (count - 1)) / 2;
    unsigned long int sum = 0;
    unsigned long int s = linked_lists.dequeue(0);
    linked_lists.enqueue(s, 1);
    linked_lists.enqueue(s, 2);
    Linked_node * current = linked_lists.get_position(s);
    binary_adjmatrix.mark(s);
    std::vector<bool> marked(linked_lists.get_total_number_of_nodes(), false);
    marked[s] = true;
    while(!linked_lists.is_empty(2)){
        unsigned long int v = linked_lists.dequeue(2);
        for(unsigned long int w : neighbors[v]){
            if(!marked[w]){
                marked[w] = true;
                linked_lists.enqueue(w, 2);
                linked_lists.get_position(w)->set_prev(linked_lists.get_position(v), 1);
                current = linked_lists.get_position(w);
                unsigned long int d = 1;
                while (current->get_id() != linked_lists.get_head(1)->get_id()) {
                    if (!binary_adjmatrix.is_connected(current->get_prev(1)->get_id(), w)) {
                        binary_adjmatrix.add_link(current->get_prev(1)->get_id(), w);
                        sum += d;
                        count--;
                        d++;
                    }
                    current = current->get_prev(1);
                }
            }
        }
    }
}


//void Bfs_modified::mount_dist_matrix(){
//    unsigned long int count = ll.get_total_number_of_nodes();
//    //Create tree method
//    Linked_list bfs_ll = Linked_list(count);
//    bfs_ll.set_ids();
//    Linked_list queue = Linked_list(count);
//    queue.set_ids();
//    //count turns out to number the unfilled distance matrix cells
//    count = (count * (count - 1)) / 2;
//    //Iterate while all the distance cells are not filled
//    unsigned long int num_cell = count;
//    while(count > 0){
//        std::vector<bool> marked(bfs_ll.get_total_number_of_nodes(), false);
//        unsigned long int s = ll.dequeue();
//        Linked_node * current = bfs_ll.get_position(s);
//        bfs_ll.set_head(current);
//        marked[s] = true;
//        queue.enqueue(s);
//        while(!queue.is_empty()){
//            unsigned long int v = queue.dequeue();
//            for(unsigned long int w : lon[v]){
//                current = bfs_ll.get_position(v);
//                bfs_ll.get_position(w)->set_prev(current);
//                if(!marked[w]){
//                    marked[w] = true;
//                    queue.enqueue(w);
//                    current = bfs_ll.get_position(w);
//                    Linked_node * ref = current;
//                    unsigned long int d = 0;
//                    while(ref->get_id() != bfs_ll.get_head()->get_id()){
//                        d++;
//                        if (!distance_matrix.is_set(current->get_id(), ref->get_prev()->get_id())) {
//                            distance_matrix.set_distance(current->get_id(), ref->get_prev()->get_id(), d);
//                            average_path += d;
//                            count--;
//                        }
//                        ref = ref->get_prev();
//                    }
//                } else if (!distance_matrix.is_set(v, w)) {
//                    distance_matrix.set_distance(v, w, 1);
//                    average_path += static_cast<double>(1);
//                    count--;
//                }
//            }
//        }
//    }
//    average_path /= static_cast<double>(num_cell);
//}

double Bfs_modified::get_average_path(){
    return this->average_path;
}
