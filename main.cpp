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
    unsigned long int N = 1000000;
    qExponential qe = qExponential(N, 2 , 1.3);
    qe.SetMin(2);
    auto start = std::chrono::high_resolution_clock::now();
    random_vector = qe.random(N, 6);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << duration.count() << " microseconds" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    Network net = Network(random_vector, 6);
    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << duration.count() << " microseconds" << std::endl;
    start = std::chrono::high_resolution_clock::now();
    bool b = net.random_link_AA_algorithm();
    while(!b){
        random_vector = qe.random(N, 6);
        net = Network(random_vector, 6);
        b = net.random_link_AA_algorithm();
    }
    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << duration.count() << " microseconds" << std::endl;
    start = std::chrono::high_resolution_clock::now();
    Assembler as = Assembler(net);
    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << duration.count() << " microseconds" << std::endl;

//    start = std::chrono::high_resolution_clock::now();
//    as.assembly();
//    stop = std::chrono::high_resolution_clock::now();
//    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
//    std::cout << duration.count() << " microseconds" << std::endl;

    int k = 0;

//    unsigned long int N = 100;
//    qExponential qe = qExponential(N, 2 , 1.3);
//    qe.SetMin(2);
//    Random *rd;
//    rd = &qe;
//    Network net = Network(N, rd);
//    bool b = net.RandomLinkAA();
//    while(!b){
//        Node::Free();
//        net = Network(N, rd);
//        b = net.RandomLinkAA();
//    }
//    Assembler as = Assembler(net);
//    as.Assemble();

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

