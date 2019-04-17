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


int main(int argc, char *argv[]){
    unsigned long int N = 145;
    Random *rd;
    Zipf zg = Zipf(N, 2.5);
    rd = &zg;
    Network net = Network(N, rd);
    bool b = net.RandomLinkAA();
    std::vector<unsigned long int> test;
    HoshenKopelman hk = HoshenKopelman(N);
    hk.Relabel(net.GetNodeList());
//    bool b = net.RandomLinkAA();
//    std::cout<<b<<std::endl;
//    std::ofstream myfile;
//    myfile.open ("/home/marcim/exampleBF.txt");
//    ZipfGen zg = ZipfGen(10000000, 1.000001);
//    std::vector<unsigned long int> rv;
//    rv = zg.RandomApproxMethod(10000000);
//    for (auto x : rv)
//        myfile << x << " ";
//    std::cout << "Randon Vector Saved \n";
//    myfile.close();
}

