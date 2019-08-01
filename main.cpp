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
#include <percolation.h>
#include <chrono>
#include <limits>
#include <math.h>
#include <binary_adjmatrix.h>
#include <linked_list.h>
#include <bfs_modified.h>

void write_random_vector(const std::string& filename, std::vector<unsigned long int> random_vector){
    std::ofstream myfile;
    myfile.open (filename);
    for (unsigned long int i=0; i < random_vector.size(); i++){
        if(i < random_vector.size() - 1) myfile << random_vector[i] << ",";
        else {
            myfile << random_vector[i];
        }
    }
    myfile.close();
}

void write_mean_l(const std::string& filename, std::vector<double> mean_l){
    std::ofstream myfile;
    myfile.open (filename);
    for (unsigned long int i = 0; i < mean_l.size(); i++){
        if(i < mean_l.size() - 1) myfile << mean_l[i] << std::endl;
        else {
            myfile << mean_l[i];
        }
    }
    myfile.close();
}

int main(int argc, char *argv[]){
    std::vector<unsigned long int> random_vector;
    unsigned long int N = std::numeric_limits<long int>::max();
    N = 1000;
    float gamma = 5;
    std::cout << "Number of nodes: " << N << std::endl;
//    qExponential qe = qExponential(N, 2 , 1.33);
//    qe.set_min(0);
//    random_vector = qe.random(N);
//    write_random_vector("/home/marcio/Projects/Random-Graph/Random-Graph/Results/qExp133_2.txt", random_vector);
    auto start = std::chrono::high_resolution_clock::now();
    Zipf ps = Zipf(N, gamma);
    ps.set_min(2);
    random_vector = ps.random(N);
//    write_random_vector("/home/marcio/Projects/Random-Graph/Random-Graph/Results/Zipf_3.txt", random_vector);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Generate random vector with " << N << " elements: " << duration.count() << " microseconds" << std::endl;
    start = std::chrono::high_resolution_clock::now();
    Network net = Network(random_vector, 16);
    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Create the network's nodes: " << duration.count() << " microseconds" << std::endl;
    std::vector<double> mean_l;
    unsigned long int num_of_rep = 1;
    Bfs_modified bam;
    for(unsigned long int i = 0; i < num_of_rep; i++){
        bool b = net.random_link_AA_algorithm();
        while(!b){
            random_vector = ps.random(N);
            net = Network(random_vector, 16);
            b = net.random_link_AA_algorithm();
        }
        bam = Bfs_modified(net);
        mean_l.push_back(bam.avg_geo_dist(999));
    }
    std::cout << "Create the network's links randomly: " << duration.count() << " microseconds" << std::endl;
    start = std::chrono::high_resolution_clock::now();
//    std::cout<< "Average distance: "<<bam.avg_geo_dist()<<std::endl;
    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Avg dist process 2: " << duration.count() << " microseconds" << std::endl;
    net.get_map_id_order();
    write_mean_l("/home/marcio/Projects/Random-Graph/Random-Graph/Results/Mean/mean_l_Z5_E3.txt", mean_l);
//    start = std::chrono::high_resolution_clock::now();
//    Percolation pc = Percolation(net);
//    pc.assembly();
//    stop = std::chrono::high_resolution_clock::now();
//    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
//    std::cout << "Compute the link-by-link adding statistics: " << duration.count() << " microseconds" << std::endl;
//    std::vector<std::pair<unsigned long int, unsigned long int>> get_list_of_links = net.get_list_of_links();
//    std::ofstream myfile;
//    myfile.open ("/home/marcio/Projects/Random-Graph/Random-Graph/Results/mean_l3_10E7.txt");
//    for (unsigned long int i = 0; i < num_of_rep; i++){
//        if(i < num_of_rep - 1) myfile << mean_l[i] << std::endl;
//        else {
//            myfile << mean_l[i];
//        }
//    }
//    myfile.close();
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

