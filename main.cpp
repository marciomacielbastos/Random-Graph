#include <QCoreApplication>
#include <node.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <zipfgen.h>
#include <fstream>
double getRandom()
{
    return double(std::rand())/RAND_MAX;
}

int main(int argc, char *argv[]){
//    Node n = Node();
//    double val;
    std::srand(unsigned(time(nullptr)));
    ZipfGen zg = ZipfGen(100, 4);
//    std::cout<<zg.HarmonicApprox(20)/12 - zg.HarmonicApprox(10)/12<<" "<<zg.Harmonic(20)-zg.Harmonic(10);
//    unsigned long int rvs
    std::vector<unsigned long int> rv;
    rv = zg.RandomBFMethod(10000);
    std::ofstream myfile;
    myfile.open ("/home/marcio/example.txt");
//    std::sort(rv.begin(), rv.end());
    for (auto x : rv)
        myfile << x << " ";
//        std::cout << x << " ";
    std::cout << "Randon Vector Saved \n";
    myfile.close();
//    std::cout<<(0.5)*std::pow(2.5, -2);
//    RandomGen rg = RandomGen();
//    val =RAND_MAX;
//    std::cout<<rg.Random(10)<<std::endl;
//    std::cout<<RAND_MAX<<std::endl;
//    std::srand(time(NULL));
//    val = double(std::rand())/RAND_MAX;
//    for (int i = 0;i<10;i++) {

//        std::cout<<static_cast<unsigned long>(val)<<std::endl;
//    }
}
