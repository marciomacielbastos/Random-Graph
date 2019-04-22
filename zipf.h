#ifndef RANDOMGEN_H
#define RANDOMGEN_H
#include <random.h>
#include <vector>
#include <float.h>

class Zipf: public Random{
private:
    double xmax;
    double xmin = 2;
    double s;
    double tol = 0.01;
    double x0 = 1;
    double N;
    double Zeta;
    std::vector<double> cdf;

public:
    Zipf();
    Zipf(unsigned long int N, double s);

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
};

#endif // RANDOMGEN_H
