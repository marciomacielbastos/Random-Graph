#include <QCoreApplication>
#include <node.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <randomgen.h>

int main(int argc, char *argv[]){
    Node n = Node();
    double val;
    RandomGen rg = RandomGen();
    val =RAND_MAX;
    std::cout<<rg.Random(10)<<std::endl;
    std::cout<<RAND_MAX<<std::endl;
//    std::srand(time(NULL));
//    val = double(std::rand())/RAND_MAX;
//    for (int i = 0;i<10;i++) {

//        std::cout<<static_cast<unsigned long>(val)<<std::endl;
//    }
}
