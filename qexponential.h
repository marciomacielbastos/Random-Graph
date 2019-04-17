#ifndef QEXPONENTIAL_H
#define QEXPONENTIAL_H
#include <random.h>

class qExponential: public Random{
private:
    double N;
    double lambda;
    double q;
    double xmin;
    double xmax;
    
public:
    qExponential();
    qExponential(unsigned long int N, double lambda, double q);
    double h();
    double factor(double x);
    double f(double f1, double f2);
    double df(double f1, double f2);
    double d3f(double f1);
};

#endif // QEXPONENTIAL_H
