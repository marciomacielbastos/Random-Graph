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


int main(int argc, char *argv[]){
    unsigned long int N = 100;
    qExponential qe = qExponential(N, 2 , 1.3);
//    std::vector<unsigned long int> rv = qe.Rand(100);
    qe.SetMin(2);
    Random *rd;
    rd = &qe;
    Network net = Network(N, rd);
    bool b = net.RandomLinkAA();
    while(!b){
        Node::Free();
        net = Network(N, rd);
        b = net.RandomLinkAA();
    }
    Assembler as = Assembler(net);
    as.Assemble();
//    int counter = 10000;
//    double counter2 = 0;

//    while(counter > 0){
//        Random *rd;
//        qExponential qe = qExponential(N, 2 , 1.3);
//        qe.SetMin(2);
////        std::vector<unsigned long int> rv = qe.Rand(100);
//        int i = 0;
//        rd = &qe;
//        Network net = Network(N, rd);
//        bool b = net.RandomLinkAA();
//        while(!b){
//            Node::Free();
//            net = Network(N, rd);
//            b = net.RandomLinkAA();
//        }
//        HoshenKopelman hk = HoshenKopelman(N);
//        hk.Relabel(net.GetNodeList());
//        if(hk.GetNumberOfComponents() > 2){
//            counter2++;
//        }
//        Node::Free();
//        counter--;
//    }
//    std::cout<< counter2/10000 << std::endl;
//    int counter = 1000;
//    while(counter > 0){
//        qe.SetMin(1);
//        rd = &qe;
//        Network net = Network(N, rd);
//        bool b = net.RandomLinkAA();
//        HoshenKopelman hk = HoshenKopelman(N);
//        hk.Relabel(net.GetNodeList());
//    }
//    qe.SetMin(1);
//    rd = &qe;
//    Network net = Network(N, rd);
//    bool b = net.RandomLinkAA();
//    HoshenKopelman hk = HoshenKopelman(N);
//    hk.Relabel(net.GetNodeList());
//    bool b = net.RandomLinkAA();
//    std::cout<<b<<std::endl;
//    std::ofstream myfile;
//    myfile.open ("/home/marcim/qExp13_2.txt");
////    ZipfGen zg = ZipfGen(10000000, 1.000001);
////    std::vector<unsigned long int> rv;
////    rv = zg.RandomApproxMethod(10000000);
//    for (unsigned long int i=0; i<rv.size(); i++)
//        if(i < rv.size() - 1) myfile << rv[i] << ",";
//        else {
//            myfile << rv[i];
//        }
//    std::cout << "Randon Vector Saved \n";
////    myfile.close();
}

