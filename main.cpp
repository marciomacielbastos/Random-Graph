#include <QCoreApplication>
#include <node.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <zipfgen.h>
#include <network.h>
#include <fstream>

int main(int argc, char *argv[]){
    Network net = Network(1000,2);
//    std::srand(unsigned(time(nullptr)));
//    ZipfGen zg = ZipfGen(10000000, 1.000001);
//    std::vector<unsigned long int> rv;
////    rv = zg.RandomBFMethod(10000000);
////    std::ofstream myfile;
////    myfile.open ("/home/marcim/exampleBF.txt");
//////    std::sort(rv.begin(), rv.end());
////    for (auto x : rv)
////        myfile << x << " ";
////    std::cout << "Randon Vector Saved \n";
////    myfile.close();
//    rv = zg.RandomApproxMethod(10000000);
//    myfile.open ("/home/marcim/exampleA.txt");
////    std::sort(rv.begin(), rv.end());
//    for (auto x : rv)
//        myfile << x << " ";
//    std::cout << "Randon Vector Saved \n";
//    myfile.close();
}

