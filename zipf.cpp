#include "zipf.h"


Zipf::Zipf(){
    std::srand(unsigned(time(nullptr)));
}

Zipf::Zipf(unsigned long int N, double s):s(SetParameter(s)), N(static_cast<double>(N)) {
    std::srand(unsigned(time(nullptr)));
    this->xmax= this->N - 1;
    this->build_dist();
}

void Zipf::set_min(double x0){
    this->xmin = x0;
}

Zipf::Zipf(unsigned long int N, double s, double xmin):s(SetParameter(s)), N(static_cast<double>(N)) {
    std::srand(unsigned(time(nullptr)));
    this->xmax= this->N - 1;
    set_min(xmin);
    this->build_dist();
}

double Zipf::factor1(double x){
    return x;
}

double Zipf::factor2(double f1){
    double f = std::pow(f1, -(s+4));
    return f;
}

double Zipf::f(double x, double f){
    double result = x * x * x * x * f;
    return   result;
}

double Zipf::df(double x, double f){
    double result = -(s) * x * x * x * f;
    return result;
}

double Zipf::d2f(double x, double f){
    double result = s * (s + 1) * x * x * f;
    return result;
}

double Zipf::d3f(double x, double f){
    double result = -(s) * (s + 1) * (s + 2) * x * f;
    return result;
}

double Zipf::d4f(double f){
    double result = s * (s + 1) * (s + 2) * (s + 3) * f;
    return result;
}

//----------------------------------------------------------------------------------------//
//*********************************APPROXIMATION*METHOD***********************************//
//----------------------------------------------------------------------------------------//


// Euler-MacLaurin formula truncated in the 3rd order
// https://medium.com/@jasoncrease/zipf-54912d5651cc
// https://en.wikipedia.org/wiki/Euler%E2%80%93Maclaurin_formula


//----------------------------------------------------------------------------------------//
//*******************************3rd*Order*Euler-Maclaurin********************************//
//----------------------------------------------------------------------------------------//

double Zipf::integ(double f1, double f2){
    return (f1 * f1 * f1 * f1 * f1 * f2);
}

double Zipf::Harmonic(double f1, double f2, double f1_0, double f2_0){
    double I = (integ(f1, f2) - integ(f1_0, f2_0)) / (1 - s);
//    Using h = 1
    double harmonic = (720 * I) + (360 * (f(f1, f2) + f(f1_0, f2_0))) + (60 * (df(f1, f2) - df(f1_0, f2_0))) - (d3f(f1, f2) - d3f(f1_0, f2_0));
    return harmonic;
}

double Zipf::dHarmonic(double f1, double f2){
//    Using h = 1
    double harmonic_ = (720 * f(f1, f2)) + (360 * (df(f1, f2))) + (60 * (d2f(f1, f2))) - d4f(f2);
    return harmonic_;
}

double Zipf::approx_inverse_CDF(double p){
    double x = xmax / 2;
    double tol = 0.01;
    double f1 = factor1(xmax);
    double f2 = factor2(f1);
    double f1_0 = factor1(xmin);
    double f2_0 = factor2(f1_0);
    double pD = p * Harmonic(f1, f2, f1_0, f2_0);
//    Newton-Raphson method
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

double Zipf::pdf(double x){
    double f1 = factor1(x);
    double f2 = factor2(f1);
    return f(f1, f2);
}

void Zipf::build_dist(){
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

long int Zipf::quick_search(double p, unsigned long int j_min, unsigned long int j_max){
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

double Zipf::search_inverse_CDF(double p){
    return static_cast<double>(quick_search(p, 0, cum_dist.size()));
}

double Zipf::inverse_CDF(double p){
    return xmin + search_inverse_CDF(p);
}
