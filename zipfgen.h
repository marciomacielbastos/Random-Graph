#ifndef RANDOMGEN_H
#define RANDOMGEN_H
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <float.h>
#include <cmath>


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
    ZipfGen(unsigned long int xmax, double s);
    ZipfGen(unsigned long int xmin, unsigned long int xmax, double s);
    void setCDF();
    double H12(double x_power_s, unsigned long int x);
    double H12_(double x_power_s, unsigned long int x);
    double NewtonRaphson(double p);
    double Uniform();
    unsigned long int RandomApproxMethod();
    std::vector<unsigned long int> RandomApproxMethod(unsigned long int size);
    double Harmonic(unsigned long int k);
    unsigned long int RandomBFMethod();
    std::vector<unsigned long int> RandomBFMethod(unsigned long size);
};

#endif // RANDOMGEN_H
