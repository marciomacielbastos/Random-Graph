#ifndef RANDOMDISTRIBUTION_H
#define RANDOMDISTRIBUTION_H
#include <time.h>
#include <stdlib.h>
#include <vector>
#include <limits>
#include <cmath>
#include <thread>
#include <functional>


class Random{
private:
    double xmin;
    double xmax;
public:
    Random();
    Random(double N, double s);
    virtual ~Random();   
    double h();
    double uniform();
    unsigned long int random();
    std::vector<unsigned long int> random(unsigned long int size);
    std::vector<unsigned long int> random(unsigned long int size, unsigned long int num_threads);
    void random_t(std::vector<unsigned long int> & random_vector, unsigned long int begin, unsigned long int end);
    static unsigned long int DiscreteUniform(unsigned long int max);
    static unsigned long int DiscreteUniform(unsigned long int min, unsigned long int max);
    virtual double InverseCDF(double p);
    virtual double SetParameter(double p);
};

#endif // RANDOMDISTRIBUTION_H
