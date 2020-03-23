#include "qexponential.h"

qExponential::qExponential() {
    std::srand(unsigned(time(nullptr)));
}

qExponential::qExponential(unsigned long int N, double lambda, double q):N(static_cast<double>(N)), lambda(lambda), q(SetParameter(q)){
    std::srand(unsigned(time(nullptr)));
    if(this->q > 1){
        this->xmax = N - 1;
    } else if (this->q < 1) {
        double factor = 1 / (lambda * (1 - this->q));
        this->xmax = std::fmin(N - 1, factor);
    }
    this->build_dist();
}

void qExponential::set_min(double x0){
    this->xmin = x0;
}

double qExponential::eq(double x){
    return std::pow((1 + (1 - this->q) * x), (1 / (1-this->q)));
}

double qExponential::pdf(double x){
    return (2 - this->q) * this->lambda * eq((-this->lambda) * x);
}

void qExponential::build_dist(){
    double sum = 0;

    for(unsigned long int i = 0; i < xmax; i++){
        double val = pdf(i);
        sum += val;
        this->cum_dist.push_back(val);
    }

    cum_dist[0] = cum_dist[0] / sum;
    for(unsigned long int i = 1; i < cum_dist.size(); i++){
        cum_dist[i] = cum_dist[i - 1] + (cum_dist[i] / sum);
    }
    int a = 0;
}

long int qExponential::quick_search(double p, unsigned long int j_min, unsigned long int j_max){
    unsigned long int mid =  j_min + static_cast<unsigned long int>((j_max - j_min) / 2);

    if (mid == j_min){
        return mid;
    }
    else if (p < this->cum_dist[mid]){
        return quick_search(p, j_min, mid);
    }
    else if (p > this->cum_dist[mid]){
        return quick_search(p, mid, j_max);
    }
}

double qExponential::search_inverse_CDF(double p){
//    unsigned long int pmax = (static_cast<unsigned long int>(xmax) - static_cast<unsigned long int>(xmin));
    return static_cast<double>(quick_search(p, 0, cum_dist.size()));
}

double qExponential::inverse_CDF(double p){
    return xmin + search_inverse_CDF(p);
}
