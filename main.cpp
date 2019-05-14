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
    std::vector<unsigned long int> test;
    unsigned long int N = 100000;
    qExponential qe = qExponential(N, 2 , 1.3);
    qe.SetMin(2);
    auto start = std::chrono::high_resolution_clock::now();
    test = qe.random(N);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << duration.count() << std::endl;

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

