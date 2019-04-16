#ifndef RANDOMDISTRIBUTION_H
#define RANDOMDISTRIBUTION_H
#include <time.h>
#include <stdlib.h>
#include <vector>


class RandomDistribution{
public:
    RandomDistribution();
    virtual ~RandomDistribution();
    RandomDistribution(double N, double s);
    double Uniform();
    static unsigned long int DiscreteUniform(unsigned long int max);
    static unsigned long int DiscreteUniform(unsigned long int min, unsigned long int max);
//    virtual unsigned long int RandomApproxMethod();
//    virtual std::vector<unsigned long int> RandomApproxMethod(unsigned long int size);
    virtual unsigned long int Random();
    virtual std::vector<unsigned long int> Random(unsigned long int size);
    virtual void SetPDF(double N, double s);
};

#endif // RANDOMDISTRIBUTION_H