#include <QCoreApplication>
#include <node.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <zipfgen.h>
#include <network.h>
#include <fstream>


int main(int argc, char *argv[]){
    Network net = Network(100,2);
    bool b = net.RandomLinkAA();
    std::cout<<b<<std::endl;
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

