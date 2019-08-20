#include <QCoreApplication>
#include <algorithm>
#include <node.h>
#include <iostream>
#include <stdlib.h>

#include <zipf.h>
#include <random.h>
#include <network.h>
/*write to file */
#include <fstream>
#include <sstream>

#include <hoshenkopelman.h>
#include <qexponential.h>
#include <percolation.h>

/* Show duration time of computation */
#include <chrono>
#include <time.h>

/*max / min  values of primitives */
#include <limits>

/* function pow */
#include <math.h>

#include <binary_adjmatrix.h>
#include <linked_list.h>
#include <bfs_modified.h>
#include <rede.h>

/* string manipulation */
#include <regex>


void write_random_vector(const std::string& filename, std::vector<unsigned long int> random_vector){
    std::ofstream myfile;
    myfile.open (filename);
    for (unsigned long int i=0; i < random_vector.size(); i++){
        if(i < random_vector.size() - 1) myfile << random_vector[i] << ",";
        else {
            myfile << random_vector[i];
        }
    }
    myfile.close();
}

void write_mean_l(const std::string& filename, std::vector<double> mean_l){
    std::ofstream myfile;
    myfile.open (filename);
    for (unsigned long int i = 0; i < mean_l.size(); i++){
        if(i < mean_l.size() - 1) myfile << mean_l[i] << std::endl;
        else {
            myfile << mean_l[i];
        }
    }
    myfile.close();
}

void write_uf(const std::string& filename, UnionFind uf){
    std::ofstream myfile;
    myfile.open (filename);
    myfile << uf.get_st_biggest().first << "," << uf.get_st_biggest().second << std::endl;
    myfile << uf.get_nd_biggest().first << "," << uf.get_nd_biggest().second << std::endl;
    std::vector<unsigned long int> number_of_clusters_per_size = uf.get_size_of_components();
    for(unsigned long int i=0; i < uf.get_max_comp(); i++){
        if(i < number_of_clusters_per_size.size() - 1) myfile <<i + 1<<","<<number_of_clusters_per_size[i]<<std::endl;
        else  myfile <<i + 1<<","<<number_of_clusters_per_size[i];;
    }
    myfile.close();
}

void progress_bar(float progress){
    int bar_width = 70;
    std::cout << "[";
    int pos = bar_width * progress;
    for (int i = 0; i < bar_width; ++i) {
        if (i < pos) std::cout << "=";
        else if (i == pos) std::cout << ">";
        else std::cout << " ";
    }
    std::cout << "] " << int(progress * 100.0) << " %\r";
    std::cout.flush();

}

double mean_computation(unsigned long int kmin, unsigned long int kmax, double gamma){
    double num = 0;
    double den = 0;
    double val = 0;
    for(unsigned long int i = kmin; i < kmax; i++){
        val = std::pow(static_cast<double>(i), -gamma);
        den += val;
        num += (val * static_cast<double>(i));
    }
    return num / den;
}
double q_computation(double gamma){
    return (gamma + 1) / gamma;
}

double lambda_computation(double mean, double q){
    return 1 / (mean * (3 - (2 * q)));
}

/*****************************************************/
/*         Molloy-Reed criterion <k²>/<k> >2         */
/*       q-Exponential mean defined to q < 3/2       */
/*     q-Exponential variance defined to q < 4/3     */
/*              lambda < 1 / (4 - 3*q)               */
/*****************************************************/

double lambda_mr(double q){
    return 1 / (1 / (4 - 3 * q));
}

/*****************************************************/
/*                      main()!                      */
/*****************************************************/

int main(int argc, char *argv[]){
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<double> mean_l;
    std::regex e ("[.]");
    unsigned long int N = static_cast<unsigned long int>(1E7);
    unsigned long int n = std::log10(N);

    unsigned long int clk = 1000;

    int kmin = 2;

    /*****************************/
    /*            Zipf           */
    /*****************************/

//    float gamma = 2.5;
//    ss << gamma;
//    Zipf distribution = Zipf(N, gamma);

    /*****************************/
    /*       q-Exponential       */
    /*****************************/

    double q = q_computation(3.5);
    double lambda = lambda_mr(q);
    qExponential distribution = qExponential(N, lambda , q);
    distribution.set_min(kmin);

    /*********************************************************/

    std::string out_string;
    std::stringstream ss;
    ss << "1E" << n;
    ss << "_" << q;
    ss << "_"<< lambda;
    ss << "_" << kmin;
    std::cout <<"N: 1E"<<n<<", q: "<<q<<", lambda: "<< lambda << ", kmin: "<<kmin<< std::endl;
    out_string = std::regex_replace(ss.str(), e, "-");

    /*********************************************************/

    Rede rd = Rede(N, &distribution);
    bool b = false;

//    double progress = 0.0;
//    progress_bar(progress);

    unsigned int num_rep = 1;
    for(unsigned long int i = 0; i < num_rep; i++){

//        progress += 1/static_cast<double>(num_rep);
        while(!b){
            rd.reset();
            b = rd.random_link();
        }
        Percolation num_comp = Percolation();
        num_comp.mount_component_stats(rd, clk, out_string);

        /****************************************/
        /* Mean geodesical distance computation */
        /****************************************/

        UnionFind uf = num_comp.mount_component_stats(rd, clk, out_string);
        Bfs_modified bam = Bfs_modified();
//        clk = std::min(100, uf.get_st_biggest().second);
        mean_l.push_back(bam.avg_geo_dist(100, uf.get_st_biggest().first, rd.get_adj_matrix()));

//        progress_bar(progress);

        b = false;
    }


    /**********************************************/
    /*   This write the mean geodesical distance  */
    /**********************************************/

    std::cout << std::endl;
    std::cout <<"Writing geodesical data..."<< std::endl;
    write_mean_l("/home/marcio/Projects/Random-Graph/Random-Graph/Results/Mean/mean_l_"+out_string+".txt", mean_l);


    std::cout << std::endl;
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "Done!! (" << duration.count() << " milisecond)"<< std::endl;

}
