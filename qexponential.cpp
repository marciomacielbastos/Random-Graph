#include "qexponential.h"

qExponential::qExponential() {
    std::srand(unsigned(time(nullptr)));
}

qExponential::qExponential(unsigned long int N, double lambda, double q):N(static_cast<double>(N)), lambda(lambda), q(SetParameter(q)){
    std::srand(unsigned(time(nullptr)));
    if(this->q > 1){
        xmax = N - 1;
    } else if (this->q < 1) {
        double factor = 1 / (lambda * (1 - this->q));
        xmax = std::fmin(N - 1, factor);
    }
    this->build_dist();
}

void qExponential::SetMin(double x0){
    this->xmin = x0;
}

qExponential::qExponential(unsigned long int N, double lambda, double q, double xmin):N(static_cast<double>(N)), lambda(lambda), q(SetParameter(q)){
    std::srand(unsigned(time(nullptr)));
    if(this->q > 1){
        xmax = N - 1;
    } else if (this->q < 1) {
        double factor = 1 / (lambda * (this->q - 1));
        xmax = std::fmin(N - 1, factor);
    }
    SetMin(xmin);
}

double qExponential::factor1(double x){
    double f1 = 1 - ((1 - q) * lambda * x);
    return f1;
}

double qExponential::factor2(double f1){
    double exponent = ((4 * q) - 3) / (1 - q);
    double f2 = std::pow(f1, exponent);
    return f2;
}

double qExponential::f(double f1, double f2){
    double result = (2 - q) * lambda * f1 * f1 * f1 * f1 * f2;
    return   result;
}

double qExponential::df(double f1, double f2){
    double result = -(lambda * lambda) * (2 - q) * f1 * f1 * f1 * f2;
    return result;
}

double qExponential::d2f(double f1, double f2){
    double result = (lambda * lambda * lambda) * (2 - q) * q * f1 * f1 * f2;
    return result;
}

double qExponential::d3f(double f1, double f2){
    double result = -(lambda * lambda * lambda * lambda) * (2 - q) * q * ((2 * q) - 1) * f1 * f2;
    return result;
}

double qExponential::d4f(double f2){
    double result = (lambda * lambda * lambda * lambda * lambda) * (2 - q) * q * ((2 * q) - 1) * (3 * q - 2) * f2;
    return result;
}

double qExponential::Integ(double f1, double f2){
    return (f1 * f1 * f1 * f1 * f1 * f2);
}

double qExponential::Harmonic(double f1, double f2, double f1_0, double f2_0){
    double I = Integ(f1_0, f2_0) - Integ(f1, f2);
//    Using h = 1
    double harmonic = (720 * I) + (360 * (f(f1, f2) + f(f1_0, f2_0))) + (60 * (df(f1, f2) - df(f1_0, f2_0))) - (d3f(f1, f2) - d3f(f1_0, f2_0));
    return harmonic;
}

double qExponential::dHarmonic(double f1, double f2){
//    Using h = 1
    double harmonic_ = (720 * f(f1, f2)) + (360 * (df(f1, f2))) + (60 * (d2f(f1, f2))) - d4f(f2);
    return harmonic_;
}

double qExponential::approx_inverse_CDF(double p){
    double x = xmin;
    double tol = 0.001;
    double f1 = factor1(xmax);
    double f2 = factor2(f1);
    double f1_0 = factor1(xmin);
    double f2_0 = factor2(f1_0);
    double pD = p * Harmonic(f1, f2, f1_0, f2_0);
    while (true) {
        double f1 = factor1(x);
        double f2 = factor2(f1);
        double H = Harmonic(f1, f2, f1_0, f2_0);
        double dH = dHarmonic(f1, f2);
        double factor = (H - pD) / dH;
        double newx = std::fmax(xmin, x - factor);
        if(std::abs(newx - x) <= tol){
            return newx;
        }
        x = newx;
    }
}

double qExponential::pdf(double x){
    double f1 = factor1(x);
    double f2 = factor2(f1);
    return f(f1, f2);
}

void qExponential::build_dist(){
    double sum = 0;
    for(unsigned long int i = xmin; i < xmax; i++){
        double val = pdf(i);
        sum += val;
        this->cum_dist.push_back(val);
    }

    for(unsigned long int i = 0; i < cum_dist.size(); i++){
        cum_dist[i] = cum_dist[i] / sum;
    }

    for(unsigned long int i = 1; i < cum_dist.size(); i++){
        cum_dist[i] += cum_dist[i - 1];
    }
}



long int qExponential::quick_search(double p, unsigned long int j_min, unsigned long int j_max){
    unsigned long int mid =  j_min + ((j_max - j_min) / 2);

    if(std::abs(this->cum_dist[mid] - p) < std::numeric_limits<double>::epsilon()){
        return (mid + 1);
    }

    else if(this->cum_dist[0] > p){
        return j_min;
    }

    else if((this->cum_dist[j_min] < p) && (this->cum_dist[j_min + 1] > p)){
        return j_min + 1;
    }

    // DO NOT COMPARE FLOAT NUMBERS AS USUAL!!!!
    else if (this->cum_dist[mid] < p) {
        j_min = mid;
        quick_search(p, j_min, j_max);
    } else {
        j_max = mid;
        quick_search(p, j_min, j_max);
    }
}

double qExponential::search_inverse_CDF(double p){
//    unsigned long int pmax = (static_cast<unsigned long int>(xmax) - static_cast<unsigned long int>(xmin));
    return static_cast<double>(quick_search(p, 0, cum_dist.size()));
}

double qExponential::inverse_CDF(double p){
    return xmin + search_inverse_CDF(p);
}
