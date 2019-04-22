#include "zipf.h"


Zipf::Zipf(){
    std::srand(unsigned(time(nullptr)));
}

Zipf::Zipf(unsigned long int N, double s):s(SetParameter(s)), N(static_cast<double>(N)) {
    std::srand(unsigned(time(nullptr)));
    this->xmax= this->N - 1;
}

double Zipf::h(){
    double h;
    h = (xmax - xmin) / (N - 1);
    return h;
}

double Zipf::Factor1(double x){
    return x;
}

double Zipf::Factor2(double f1){
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

double Zipf::Harmonic(double f1, double f2, double f1_0, double f2_0){
    double I = (f1 * f1 * f1 * f1 * f1 * f2 - 1) / (1 - s);
//    Using h = 1
    double harmonic = (720 * I) + (360 * (f(f1, f2) + f(f1_0, f2_0))) + (60 * (df(f1, f2) - df(f1_0, f2_0))) - (d3f(f1, f2) - d3f(f1_0, f2_0));
    return harmonic;
}

double Zipf::dHarmonic(double f1, double f2){
//    Using h = 1
    double harmonic_ = (720 * f(f1, f2)) + (360 * (df(f1, f2))) + (60 * (d2f(f1, f2))) - d4f(f2);
    return harmonic_;
}

double Zipf::InverseCDF(double p){
    double x = xmax / 2;
    double tol = 0.01;
    double f1 = Factor1(xmax);
    double f2 = Factor2(f1);
    double f1_0 = Factor1(1);
    double f2_0 = Factor2(f1_0);
    double pD = p * Harmonic(f1, f2, f1_0, f2_0);
//    Newton-Raphson method
    while (true) {
        double f1 = Factor1(x);
        double f2 = Factor2(f1);
        double H = Harmonic(f1, f2, f1_0, f2_0);
        double dH = dHarmonic(f1, f2);
        double factor = (H - pD) / dH;
        double newx = std::fmax(1, x - factor);
        if(std::abs(newx - x) <= tol){
            return newx + this->xmin - 1;
        }
        x = newx;
    }
}
