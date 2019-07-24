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
    std::vector<unsigned long int> random_vector;
    unsigned long int N = std::numeric_limits<long int>::max();
    N = 100000000;
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
    std::vector<double> mean_l;
    unsigned long int num_of_rep = 10;
    for(unsigned long int i = 0; i < num_of_rep; i++){
        bool b = net.random_link_MM_algorithm();
        while(!b){
            random_vector = qe.random(N, 16);
            net = Network(random_vector, 16);
            b = net.random_link_MM_algorithm();
        }
        Bfs_modified bam = Bfs_modified(net);
        mean_l.push_back(bam.avg_geo_dist(33));
    }
    std::cout << "Create the network's links randomly: " << duration.count() << " microseconds" << std::endl;
//    start = std::chrono::high_resolution_clock::now();
//    std::cout<< "Average distance: "<<bam.avg_geo_dist()<<std::endl;
//    stop = std::chrono::high_resolution_clock::now();
//    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
//    std::cout << "Avg dist process 2: " << duration.count() << " microseconds" << std::endl;
//    net.get_map_id_order();
//    start = std::chrono::high_resolution_clock::now();
//    Assembler as = Assembler(net);
//    stop = std::chrono::high_resolution_clock::now();
//    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
//    std::cout << "Compute the link-by-link adding statistics: " << duration.count() << " microseconds" << std::endl;
//    std::vector<std::pair<unsigned long int, unsigned long int>> get_list_of_links = net.get_list_of_links();
    std::ofstream myfile;
    myfile.open ("/home/marcio/Projects/Random-Graph/Results/mean_l_10E8.txt");
    for (unsigned long int i = 0; i < num_of_rep; i++){
        if(i < num_of_rep - 1) myfile << mean_l[i] << std::endl;
        else {
            myfile << mean_l[i];
        }
    }
    myfile.close();
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

