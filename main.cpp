#include <QCoreApplication>
#include <node.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <zipfgen.h>
#include <network.h>
#include <fstream>


int main(int argc, char *argv[]){
    std::vector<int> a={1,2,3};
    a.erase(a.begin()+1);
    Network net = Network(1000,2);
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

