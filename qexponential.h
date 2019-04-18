#ifndef QEXPONENTIAL_H
#define QEXPONENTIAL_H
#include <random.h>

class qExponential: public Random{
private:
    double N;
    double lambda;
    double q;
    double xmin = 0;
    double xmax;
    
public:
    qExponential();
    qExponential(unsigned long int N, double lambda, double q);
    double h();
    double Factor1(double x);
    double Factor2(double f1);
    double f(double f1, double f2);
    double df(double f1, double f2);
    double d2f(double f1, double f2);
    double d3f(double f1, double f2);
    double d4f(double f1);
    double Harmonic(double f1, double f2, double f1_0, double f2_0);
    double dHarmonic(double f1, double f2);
    double InverseCDF(double p);
    unsigned long int  Rand();
    std::vector<unsigned long int> Rand(unsigned long int size);
};

#endif // QEXPONENTIAL_H
