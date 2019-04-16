#ifndef RANDOMGEN_H
#define RANDOMGEN_H
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <float.h>
#include <cmath>
#include <limits>


class ZipfGen{
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
    ZipfGen(double N, double s);
    void SetS(double s);
    void SetXmin(double xmin);
    void SetXmax(double xmax);
    void SetCDF();
    double H12(double x_power_s, double x);
    double H12_(double x_power_s, double x);
    double NewtonRaphson(double p);
    double Uniform();
    unsigned long int RandomApproxMethod();
    std::vector<unsigned long int> RandomApproxMethod(unsigned long int size);
    double HarmonicApprox(unsigned long int k);
    double Harmonic(unsigned long int k);
    unsigned long int RandomBFMethod();
    std::vector<unsigned long int> RandomBFMethod(unsigned long size);
};

#endif // RANDOMGEN_H
