#include <QCoreApplication>
#include <node.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <zipfgen.h>
#include <network.h>
#include <fstream>
#include <hoshenkopelman.h>


int main(int argc, char *argv[]){
    unsigned long int s = 145;
    Network net = Network(s,2);
    bool b = net.RandomLinkAA();
    std::vector<unsigned long int> test;
    HoshenKopelman hk = HoshenKopelman(s);
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

