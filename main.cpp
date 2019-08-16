#include <QCoreApplication>
#include <algorithm>
#include <node.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <zipf.h>
#include <random.h>
#include <network.h>
#include <fstream>
#include <sstream>
#include <hoshenkopelman.h>
#include <qexponential.h>
#include <percolation.h>
#include <chrono>
#include <limits>
#include <math.h>
#include <binary_adjmatrix.h>
#include <linked_list.h>
#include <bfs_modified.h>
#include <rede.h>
#include <regex>


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

void write_uf(const std::string& filename, UnionFind uf){
    std::ofstream myfile;
    myfile.open (filename);
    myfile << uf.get_st_biggest().first << "," << uf.get_st_biggest().second << std::endl;
    myfile << uf.get_nd_biggest().first << "," << uf.get_nd_biggest().second << std::endl;
    std::vector<unsigned long int> number_of_clusters_per_size = uf.get_size_of_components();
    for(unsigned long int i=0; i < uf.get_max_comp(); i++){
        if(i < number_of_clusters_per_size.size() - 1) myfile <<i + 1<<","<<number_of_clusters_per_size[i]<<std::endl;
        else  myfile <<i + 1<<","<<number_of_clusters_per_size[i];;
    }
    myfile.close();
}

void progress_bar(float progress){
    int bar_width = 70;
    std::cout << "[";
    int pos = bar_width * progress;
    for (int i = 0; i < bar_width; ++i) {
        if (i < pos) std::cout << "=";
        else if (i == pos) std::cout << ">";
        else std::cout << " ";
    }
    std::cout << "] " << int(progress * 100.0) << " %\r";
    std::cout.flush();

}

int main(int argc, char *argv[]){
    auto start = std::chrono::high_resolution_clock::now();
    std::string out_string;
    std::stringstream ss;
    std::vector<double> mean_l;
    std::regex e ("[.]");
    double mean = -1;
    unsigned long int N = static_cast<unsigned long int>(1E1);
    unsigned long int n = std::log10(N);
    ss << "1E" << n;
    unsigned long int clk = 9;
    float gamma = 4.5;
    ss << gamma;
    Zipf distribution = Zipf(N, gamma);
//    double q = 1.22;
//    ss << "_" << q;
//    double lambda;
//    if(mean > 0){
//        lambda = 1/ (mean * (3 - 2*q));
//    } else {
//        lambda = 2;
//    }
//    qExponential distribution = qExponential(N, lambda , q);
//    ss << "_"<< lambda;
    int kmin = 2;
    ss << "_" << kmin;
    std::cout <<"N: 1E"<<n<<", gamma: "<< gamma << ", kmin: "<<kmin<< std::endl;
    out_string = std::regex_replace(ss.str(), e, "-");
    distribution.set_min(kmin);
    Rede rd = Rede(N, &distribution);
    bool b = false;
    float progress = 0.0;
    progress_bar(progress);
    unsigned int num_rep = 10;
    for(unsigned long int i = 0; i < num_rep; i++){
        progress += 1/static_cast<double>(num_rep);
        while(!b){
            rd.reset();
            b = rd.random_link();
        }
        Percolation num_comp = Percolation();
        UnionFind uf = num_comp.mount_component_stats(rd);
        Bfs_modified bam = Bfs_modified();
        clk = std::min(clk, uf.get_st_biggest().second);
        mean_l.push_back(bam.avg_geo_dist(clk, uf.get_st_biggest().first, rd.get_adj_matrix()));
        b = false;
        progress_bar(progress);
    }
    std::cout << std::endl;
    std::cout <<"Writing..."<< std::endl;
    if(mean > -1){
        write_mean_l("/home/marcio/Projects/Random-Graph/Random-Graph/Results/Mean/mean_l_q_st_moment"+out_string+".txt", mean_l);
    } else {
        write_mean_l("/home/marcio/Projects/Random-Graph/Random-Graph/Results/Mean/mean_l_z_"+out_string+".txt", mean_l);
    }


    std::cout << std::endl;
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "Done!! (" << duration.count() << " milisecond)"<< std::endl;



//    std::vector<unsigned long int> random_vector;
//    unsigned long int N = std::numeric_limits<long int>::max();
//    N = 10000000;
//    int kmin = 2;
//    std::string out_string;
//    std::stringstream ss;
//    ss << kmin;
//    out_string = ss.str();
//    ss.str(std::string());
//    ss << N;
//    out_string += ss.str();
//    ss.str(std::string());
//    float gamma = 2.5;
//    ss << 25;
//    out_string += ss.str();
//    std::cout << "Number of nodes: " << N << std::endl;
////    qExponential qe = qExponential(N, 2 , 1.33);
////    qe.set_min(0);
////    random_vector = qe.random(N);
////    write_random_vector("/home/marcio/Projects/Random-Graph/Random-Graph/Results/qExp133_2.txt", random_vector);
//    auto start = std::chrono::high_resolution_clock::now();
//    Zipf ps = Zipf(N, gamma);
//    ps.set_min(kmin);
//    random_vector = ps.random(N);
////    write_random_vector("/home/marcio/Projects/Random-Graph/Random-Graph/Results/Zipf_3.txt", random_vector);
//    auto stop = std::chrono::high_resolution_clock::now();
//    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
//    std::cout << "Generate random vector with " << N << " elements: " << duration.count() << " microseconds" << std::endl;
//    start = std::chrono::high_resolution_clock::now();
//    Network net = Network(random_vector, 16);
//    Percolation num_comp = Percolation(net);
//    stop = std::chrono::high_resolution_clock::now();
//    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
//    std::cout << "Create the network's nodes: " << duration.count() << " microseconds" << std::endl;
//    std::vector<double> mean_l;
//    unsigned long int num_of_rep = 10;
//    Bfs_modified bam;
//    for(unsigned long int i = 0; i < num_of_rep; i++){
//        bool b = net.random_links();
//        while(!b){
//            random_vector = ps.random(N);
//            net = Network(random_vector, 16);
//            b = net.random_links();
//        }
//        bam = Bfs_modified(net);
//        UnionFind uf = num_comp.mount_component_stats();
//        std::vector<unsigned long int> big_component = bam.bfs_component_return(uf.get_st_biggest().first);
//        mean_l.push_back(bam.avg_geo_dist(big_component, 100));
////        mean_l.push_back(bam.avg_geo_dist(9));
//    }

////    UnionFind uf = numcomp.mount_component_stats();
////    bam = Bfs_modified(net);
////    std::vector<unsigned long int> big_component = bam.bfs_component_return(uf.get_st_biggest().first);
////    bam = Bfs_modified(net);
////    mean_l.push_back(bam.avg_geo_dist(big_component, big_component.size()));
////    write_uf("/home/marcio/Projects/Random-Graph/Random-Graph/Results/stats_zipf_bc_"+out_string+".txt", uf);
//    std::cout << "Create the network's links randomly: " << duration.count() << " microseconds" << std::endl;
//    start = std::chrono::high_resolution_clock::now();
////    std::cout<< "Average distance: "<<bam.avg_geo_dist()<<std::endl;
//    stop = std::chrono::high_resolution_clock::now();
//    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
//    std::cout << "Avg dist process 2: " << duration.count() << " microseconds" << std::endl;
//    net.get_map_id_order();
//    write_mean_l("/home/marcio/Projects/Random-Graph/Random-Graph/Results/Mean/mean_l_Z"+out_string+".txt", mean_l);
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

