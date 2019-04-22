#include "qexponential.h"

qExponential::qExponential() {
    std::srand(unsigned(time(nullptr)));
}

qExponential::qExponential(unsigned long int N, double lambda, double q):N(static_cast<double>(N)), lambda(lambda), q(SetParameter(q)){
    std::srand(unsigned(time(nullptr)));
    if(this->q > 1){
        xmax = N - 1;
    } else if (this->q < 1) {
        double factor = 1 / (lambda * (this->q - 1));
        xmax = std::fmin(N - 1, factor);
    }
}

double qExponential::h() {
    double h;
    h = (xmax - xmin) / (N - 1);
    return h;
}

double qExponential::Factor1(double x){
    double f1 = 1 - ((1 - q) * lambda * x);
    return f1;
}

double qExponential::Factor2(double f1){
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

double qExponential::Harmonic(double f1, double f2, double f1_0, double f2_0){
    double I = 1 - (f1 * f1 * f1 * f1 * f2);
//    Using h = 1
    double harmonic = (720 * I) + (360 * (f(f1, f2) + f(f1_0, f2_0))) + (60 * (df(f1, f2) - df(f1_0, f2_0))) - (d3f(f1, f2) - d3f(f1_0, f2_0));
    return harmonic;
}

double qExponential::dHarmonic(double f1, double f2){
//    Using h = 1
    double harmonic_ = (720 * f(f1, f2)) + (360 * (df(f1, f2))) + (60 * (d2f(f1, f2))) - d4f(f2);
    return harmonic_;
}

double qExponential::InverseCDF(double p){
    double x = xmax / 2;
    double tol = 0.01;
    double f1 = Factor1(xmax);
    double f2 = Factor2(f1);
    double f1_0 = Factor1(0);
    double f2_0 = Factor2(f1_0);
    double pD = p * Harmonic(f1, f2, f1_0, f2_0);
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
