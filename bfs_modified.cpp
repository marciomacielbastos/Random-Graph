#include "bfs_modified.h"
#include <iostream>

Bfs_modified::Bfs_modified(){

}

Bfs_modified::Bfs_modified(Network net){
    average_path = 0;
    std::vector<std::vector<unsigned long int>> neighbors(net.get_list_of_nodes().size());
    this->linked_lists = Linked_list(neighbors.size(), 2);
    for(Node n : net.get_list_of_nodes()){
        neighbors[n.get_id()] = n.get_adjacency_list();
        linked_lists.enqueue(n.get_id(), 0);
    }
    this->neighbors = neighbors;
//    Distance_matrix dm = Distance_matrix(linked_lists.get_total_number_of_nodes());
//    binary_adjmatrix = Binary_adjmatrix(linked_lists.get_total_number_of_nodes());
}

double Bfs_modified::avg_geo_dist(){
    double dsum = 0;
    double count = 0;
    unsigned long int verify = 0;
    while(!linked_lists.is_empty(0)){
        double dist = 0;
        unsigned long int d1 = 0;
        unsigned long int d2 = 1;
        unsigned long int s = linked_lists.dequeue(0);
        linked_lists.enqueue(s, 1);
        std::vector<bool> marked(linked_lists.get_total_number_of_nodes(), false);
        marked[s] = true;
        while(!linked_lists.is_empty(1)){
            if(d1 == 0){
                d1 = d2;
                d2 = 0;
                dist++;
            }
            unsigned long int v = linked_lists.dequeue(1);
            d1--;
            for(unsigned long int w : neighbors[v]){
                if(!marked[w]){
                    d2++;
                    dsum += dist;
                    count++;
                    marked[w] = true;
                    linked_lists.enqueue(w, 1);
                }
            }
        }
        if(verify == 0){
            verify++;
            std::cout<<"chefao: "<<dsum/count<<std::endl;
        }
    }
    return dsum/count;
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
