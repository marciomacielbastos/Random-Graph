#ifndef RANDOMGEN_H
#define RANDOMGEN_H
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <float.h>
#include <cmath>


class RandomGen{
private:
    double xmax = double(RAND_MAX);
    double xmin = 1/xmax;

public:
    RandomGen();
    double Random(double alpha);
    double Random(double alpha, unsigned long int size);
};

#endif // RANDOMGEN_H
