#include <QCoreApplication>
#include <node.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <zipfgen.h>
#include <fstream>

int main(int argc, char *argv[]){
    std::srand(unsigned(time(nullptr)));
    ZipfGen zg = ZipfGen(10000, 1.000001);
    std::vector<unsigned long int> rv;
//    rv = zg.RandomBFMethod(10000000);
    std::ofstream myfile;
//    myfile.open ("/home/marcim/exampleA.txt");
////    std::sort(rv.begin(), rv.end());
//    for (auto x : rv)
//        myfile << x << " ";
//    std::cout << "Randon Vector Saved \n";
//    myfile.close();
    rv = zg.RandomApproxMethod(1000000);
    myfile.open ("/home/marcim/exampleBF.txt");
//    std::sort(rv.begin(), rv.end());
    for (auto x : rv)
        myfile << x << " ";
    std::cout << "Randon Vector Saved \n";
    myfile.close();
}

