#ifndef RANDOMDISTRIBUTION_H
#define RANDOMDISTRIBUTION_H
#include <time.h>
#include <stdlib.h>
#include <vector>
#include <limits>
#include <cmath>


class Random{
private:
    double xmin;
    double xmax;
public:
    Random();
    Random(double N, double s);
    virtual ~Random();   
    double h();
    double Uniform();
    unsigned long int Rand();
    std::vector<unsigned long int> Rand(unsigned long int size);
    static unsigned long int DiscreteUniform(unsigned long int max);
    static unsigned long int DiscreteUniform(unsigned long int min, unsigned long int max);
    virtual double InverseCDF(double p);
    virtual double SetParameter(double p);
};

#endif // RANDOMDISTRIBUTION_H
