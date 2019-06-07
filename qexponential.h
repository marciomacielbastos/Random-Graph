#ifndef QEXPONENTIAL_H
#define QEXPONENTIAL_H
#include <random.h>
#include <exponential.h>

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
    qExponential(unsigned long int N, double lambda, double q, double xmin);
    void SetMin(double x0);
    double factor1(double x);
    double factor2(double f1);
    double f(double f1, double f2);
    double df(double f1, double f2);
    double d2f(double f1, double f2);
    double d3f(double f1, double f2);
    double d4f(double f1);
    double Harmonic(double f1, double f2, double f1_0, double f2_0);
    double dHarmonic(double f1, double f2);
    double Integ(double f1, double f2);
    double InverseCDF(double p);
//    unsigned long int PickRand();
//    std::vector<unsigned long int> PickRand(unsigned long int size);
};

#endif // QEXPONENTIAL_H
