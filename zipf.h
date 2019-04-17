#ifndef RANDOMGEN_H
#define RANDOMGEN_H
#include <random.h>
#include <vector>
#include <float.h>
#include <cmath>
#include <limits>


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
    void SetS(double s);
    void SetXmin(double xmin);
    void SetXmax(double xmax);
    void SetCDF();
    void SetPDF(double N, double s);
    double H12(double x_power_s, double x);
    double H12_(double x_power_s, double x);
    double NewtonRaphson(double p);
    unsigned long int Rand();
    std::vector<unsigned long int> Rand(unsigned long int size);
    unsigned long int RandomApproxMethod();
    std::vector<unsigned long int> RandomApproxMethod(unsigned long int size);
    double HarmonicApprox(unsigned long int k);
    double Harmonic(unsigned long int k);
    unsigned long int RandomBFMethod();
    std::vector<unsigned long int> RandomBFMethod(unsigned long size);
};

#endif // RANDOMGEN_H
