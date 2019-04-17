#include "qexponential.h"

qExponential::qExponential() {
    std::srand(unsigned(time(nullptr)));
}

qExponential::qExponential(unsigned long int N, double lambda, double q):N(static_cast<double>(N)), lambda(lambda), q(SetParameter(q)){
    std::srand(unsigned(time(nullptr)));
}

double qExponential::h() {
    double h;
    h = (xmax - xmin)/(N - 1);
    return h;
}

double qExponential::factor(double x){
    double f1 = 1 - ((1 - q) * lambda * x);
    return f1;
}

double qExponential::f(double f1, double f2){
    return  (1 - f1 * f2 * f2);
}

double qExponential::df(double f1, double f2){
    return -lambda * f1 * f2;
}

double qExponential::d2f(double f1){
    return q * (lambda * lambda) * f1;
}
