#include <QCoreApplication>

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

#include <math.h> //pow
#include <algorithm> //min, max functions

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
    std::cout <<"[Writing geodesical data...]"<< std::endl;
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

void write_percolation_series(const std::string& filename, std::vector<std::vector<double>> mean_component, unsigned int num_rep){
    std::ofstream myfile;
    myfile.open (filename);
    for (unsigned long int i = 0; i < mean_component.size(); i++){
        myfile << mean_component[i][0] << "," << mean_component[i][1] << "," << std::sqrt(mean_component[i][2] / num_rep) << std::endl;
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

void write_lambda(const std::string& filename, double q, double lambda, bool append=false){
    std::ofstream myfile;
    if (append){
        myfile.open(filename, std::ios_base::app);
    }
    else{
        myfile.open(filename);
        myfile << q << "," << lambda << std::endl;
    }
    myfile.close();
}

/*******************************************************************************/

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

double first_momment(std::vector<unsigned long int> sample){
    double sum = 0;
    for(unsigned long int i=0; i < sample.size() - 1; i++){
        sum += static_cast<double>(sample[i]);
    }
    return sum;
}

double second_moment(std::vector<unsigned long int> sample){
    for(unsigned long int i=0; i < sample.size() - 1; i++){
        sample[i] *= sample[i];
    }
    return first_momment(sample);
}

double molloy_reed(std::vector<unsigned long int> sample){
    double m1 = sample[sample.size() - 1];
    double m2 = second_moment(sample);
    return m2 / m1;
}

double lambda_mr(double q){
    return 1 / (1 / (4 - 3 * q));
}



double search_lambda(unsigned long int N, double q, double k, double k_min, double lambda){
    double tol = 0.05;
    double error = 1;
    double gamma = 0.5;
    qExponential distribution;
    std::vector<unsigned long int> sample;
    double k_new;
    int count = 0;
    while(std::abs(error) > tol){
        distribution = qExponential(N, lambda , q);
        distribution.set_min(k_min);
        sample = distribution.random(N);
        k_new = molloy_reed(sample);
        error = ( k_new - k );
        lambda = std::abs((1 + gamma*( error / k )) * lambda);
        count++;
    }
    return lambda;
}

void lambda_analysis(unsigned long int N){
    int kmin = 2;
    double gamma_values[5] = {2.5, 3.0, 3.5, 4.0 , 4.5};
    double q = 1.4;
    double lambda = 2;
    std::string filename = "/home/marcio/pCloudDrive//Physics/Thesis/Andre/Results/lambda/lambda.txt";
    write_lambda(filename, q, lambda);
    for ( auto gamma : gamma_values ){
        q = q_computation(gamma);
        for(int i = 0; i < 100; i++){
            lambda = search_lambda(N, q, 2, kmin, lambda);
            write_lambda(filename, q, lambda, true);
        }
    }
}

UnionFind geodesical_distance_computation(unsigned int num_rep, Rede &rd, unsigned long int lower_bound, std::string out_string){
    std::cout <<"[Mean geodesical distance computation...]"<< std::endl;

    std::vector<double> mean_l;
    unsigned long int clk = 1000;
    UnionFind uf;
    Percolation num_comp;
    bool b = false;

    double progress = 0.0;
    progress_bar(progress);

    for(unsigned long int i = 0; i < num_rep; i++){
        progress += 1/static_cast<double>(num_rep);
        while(!b){
            rd.reset();
            b = rd.random_link();
        }
        num_comp = Percolation();

        uf = num_comp.mount_geodesical_stats(rd);
        Bfs_modified bam = Bfs_modified();
        clk = std::min(lower_bound, uf.get_st_biggest().second);
        mean_l.push_back(bam.avg_geo_dist(clk, uf.get_st_biggest().first, rd.get_adj_matrix()));

        progress_bar(progress);

        b = false;
    }

    std::cout << std::endl;

    /**********************************************/
    /*   This write the mean geodesical distance  */
    /**********************************************/
    write_mean_l("/home/marcio/pCloudDrive/Physics/Thesis/Andre/Results/Mean/mean_l_"+out_string+".txt", mean_l);
    return uf;
}

std::vector<std::vector<double>> percolation_computation(unsigned int num_rep, Rede &rd){
    std::cout <<"[Percolation computation...]"<< std::endl;

    unsigned long int N = rd.get_number_of_nodes();
    unsigned long int clk = std::min(N, static_cast<unsigned long int>(1000));
    Percolation num_comp = Percolation(clk);
    bool b = false;
    double bc_mu = 0;
    std::vector<std::vector<double>> biggest_component(clk + 1, {0, 0, 0}); // (Fraction of nodes, size of biggest component)

    for(unsigned long int n = 0; n < num_rep; n++){
        std::cout <<"[Connecting vertices...]"<< std::endl;
        while(!b){
            rd.reset();
            b = rd.random_link();
        }
        std::cout << "\e[A";
        std::cout<< "[" << n + 1 << "/" << num_rep << "]                  " << std::endl;
        std::vector<std::vector<double>> input = num_comp.mount_component(rd, clk); // (Fraction of nodes, size of biggest component)
        for(unsigned int j = 0; j < clk; ++j){
            biggest_component[j][0] = input[j][0]; //edge fraction added
            bc_mu = biggest_component[j][1];
            biggest_component[j][1] = biggest_component[j][1] + ((input[j][1] - biggest_component[j][1]) / (n + 1));
            biggest_component[j][2] = biggest_component[j][2] + (input[j][1] - bc_mu) * (input[j][1] - biggest_component[j][1]);
        }

        if(input[clk][0] >= 0){
            biggest_component[clk][0] = biggest_component[clk][0] + ((input[clk][0] - biggest_component[clk][0]) / (n + 1));
            bc_mu = biggest_component[clk][1];
            biggest_component[clk][1] = biggest_component[clk][1] + ((input[clk][1] - biggest_component[clk][1]) / (n + 1));
            biggest_component[clk][2] = biggest_component[clk][2] + (input[clk][1] - bc_mu) * (input[clk][1] - biggest_component[clk][1]);
        }

        b = false;
        // Take carriage 2 alines above to count / progress without messy newlines
        if(n < num_rep -1){
            std::cout << "\e[A";
            std::cout << "\e[A";
        }
    }
    return biggest_component;
}
/*****************************************************/
/*                      main()!                      */
/*****************************************************/

int main(int argc, char *argv[]){
    auto start = std::chrono::high_resolution_clock::now();
    std::regex e ("[.]");
    unsigned long int f = 5;
    unsigned long int N = static_cast<unsigned long int>(1E6);
    N *= f;
    unsigned long int n = std::log10(N);

    /*****************************/
    /*            Zipf           */
    /*****************************/

//    float gamma = 2.5;
//    ss << gamma;
//    Zipf distribution = Zipf(N, gamma);

    /*****************************/
    /*       q-Exponential       */
    /*****************************/

    int kmin = 1;
    unsigned int i = 1;
    double gamma_values[5] = {2.5, 3.0, 3.5, 4.0 , 4.5};
    double q = q_computation(gamma_values[i]);
    double lambda_values[5] = {17.51, 5.51, 3.34, 2.6, 2.23};
    double lambda = 0.1 * lambda_values[i];

    qExponential distribution = qExponential(N, lambda , q);
    distribution.set_min(kmin);

    /***********************************************************/
    /*                  Set Paremeters String                  */
    /***********************************************************/

    std::string out_string;
    std::stringstream ss;
    ss << f;
    ss << "E" << n;
    ss << "_" << i;
    ss << "_" << kmin;
    std::cout <<"N: "<<f<<"E"<<n<< ", i: "<< i <<"(q="<< q <<", lambda="<< lambda << "), kmin: "<<kmin<< std::endl;
    out_string = std::regex_replace(ss.str(), e, "-");

    /*********************************************************/

    Rede rd = Rede(N, &distribution);

    unsigned int num_rep = 50;

    /****************************************/
    /* Mean geodesical distance computation */
    /****************************************/
    UnionFind uf;
    unsigned long int lower_bound = 100;
    uf = geodesical_distance_computation(num_rep, rd, lower_bound, out_string);

    /***********************************************/
    /*            write component sizes            */
    /***********************************************/
    std::cout <<"[Writing component sizes...]"<< std::endl;
    write_uf("/home/marcio/pCloudDrive/Physics/Thesis/Andre/Results/Components/c_"+out_string+".txt", uf);

    /*************************************/
    /*      Percolation computation      */
    /*************************************/

    std::vector<std::vector<double>> biggest_component = percolation_computation(num_rep, rd);

    /*************************************************/
    /*    This write the percolation series stats    */
    /*************************************************/

    std::cout <<"[Writing percolation series stats...]"<< std::endl;
    write_percolation_series("/home/marcio/pCloudDrive/Physics/Thesis/Andre/Results/Mean/Biggest_component_" + out_string + ".txt", biggest_component, num_rep);

    std::cout << std::endl;
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "Done!! (" << duration.count() << " milisecond)"<< std::endl;

}
