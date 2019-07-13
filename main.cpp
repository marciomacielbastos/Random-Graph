#include <QCoreApplication>
#include <node.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <zipf.h>
#include <random.h>
#include <network.h>
#include <fstream>
#include <hoshenkopelman.h>
#include <qexponential.h>
#include <assembler.h>
#include <chrono>
#include <limits>
#include <math.h>
#include <binary_adjmatrix.h>
#include <linked_list.h>
#include <bfs_modified.h>

int main(int argc, char *argv[]){
    Binary_adjmatrix ba = Binary_adjmatrix(25);
    ba.add_link(1, 2);
    Linked_list vll = Linked_list();
    vll.add_node();
    std::vector<unsigned long int> random_vector;
    vll.add_node();
    unsigned long int N = std::numeric_limits<long int>::max();
    vll.add_node();
    N = 5;
    std::cout << "Number of nodes: " << N << std::endl;
    qExponential qe = qExponential(N, 2 , 1.3);
    qe.SetMin(2);
    auto start = std::chrono::high_resolution_clock::now();
    random_vector = qe.random(N);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Generate random vector with " << N << " elements: " << duration.count() << " microseconds" << std::endl;
    start = std::chrono::high_resolution_clock::now();
    Network net = Network(random_vector, 16);
    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Create the network's nodes: " << duration.count() << " microseconds" << std::endl;
    start = std::chrono::high_resolution_clock::now();
    bool b = net.random_link_MM_algorithm();
    while(!b){
        random_vector = qe.random(N, 16);
        net = Network(random_vector, 16);
        b = net.random_link_MM_algorithm();
    }
    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Create the network's links randomly: " << duration.count() << " microseconds" << std::endl;
    Bfs_modified bam = Bfs_modified(net);
    bam.mount_dist_matrix();
    unsigned int g = 0;
    g =1;
//    net.get_map_id_order();
//    start = std::chrono::high_resolution_clock::now();
//    Assembler as = Assembler(net);
//    stop = std::chrono::high_resolution_clock::now();
//    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
//    std::cout << "Compute the link-by-link adding statistics: " << duration.count() << " microseconds" << std::endl;
//    std::vector<std::pair<unsigned long int, unsigned long int>> get_list_of_links = net.get_list_of_links();
//    std::ofstream myfile;
//    myfile.open ("/home/marcio/rede13_2.txt");
//    for (unsigned long int i=0; i < get_list_of_links.size(); i++){
//        if(i < get_list_of_links.size() - 1) myfile << get_list_of_links[i].first << ", " << get_list_of_links[i].second << std::endl;
//        else {
//            myfile << get_list_of_links[i].first << ", " << get_list_of_links[i].second;
//        }
//    }
////    std::cout << "Randon Vector Saved \n";
//    myfile.close();

//    myfile.open ("/home/marcio/qExp13_2.txt");
//    for (unsigned long int i=0; i<random_vector.size(); i++){
//        if(i < random_vector.size() - 1) myfile << random_vector[i] << ",";
//        else {
//            myfile << random_vector[i];
//        }
//    }
//    std::cout << "Randon Vector Saved \n";
//    myfile.close();
}

