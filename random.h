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
    virtual ~Random();
    Random(double N, double s);
    double Uniform();
    unsigned long int Rand();
    std::vector<unsigned long int> Rand(unsigned long int size);
    void SetMin(unsigned long int xmin);
    static unsigned long int DiscreteUniform(unsigned long int max);
    static unsigned long int DiscreteUniform(unsigned long int min, unsigned long int max);
    virtual double InverseCDF(double p);
    virtual double SetParameter(double p);
};

#endif // RANDOMDISTRIBUTION_H
