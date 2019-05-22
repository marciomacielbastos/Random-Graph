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


int main(int argc, char *argv[]){
    std::vector<unsigned long int> random_vector;
    unsigned long int N = 10000000;
    std::cout << "Number of nodes: " << N << std::endl;
    qExponential qe = qExponential(N, 2 , 1.3);
    qe.SetMin(2);
    auto start = std::chrono::high_resolution_clock::now();
    random_vector = qe.random(N, 16);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Generate random vector with " << N << " elements: " << duration.count() << " microseconds" << std::endl;
    start = std::chrono::high_resolution_clock::now();
    Network net = Network(random_vector, 16);
    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Create the network's nodes: " << duration.count() << " microseconds" << std::endl;
    start = std::chrono::high_resolution_clock::now();
    bool b = net.random_link_AA_algorithm();
    while(!b){
        random_vector = qe.random(N, 16);
        net = Network(random_vector, 16);
        b = net.random_link_AA_algorithm();
    }
    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Create the network's links randomly: " << duration.count() << " microseconds" << std::endl;
    start = std::chrono::high_resolution_clock::now();
    Assembler as = Assembler(net);
    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Compute the link-by-link adding statistics: " << duration.count() << " microseconds" << std::endl;
//    std::ofstream myfile;
//    myfile.open ("/home/marcim/qExp13_2.txt");
//    for (unsigned long int i=0; i<rv.size(); i++)
//        if(i < rv.size() - 1) myfile << rv[i] << ",";
//        else {
//            myfile << rv[i];
//        }
//    std::cout << "Randon Vector Saved \n";
//    myfile.close();
}

