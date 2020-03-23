#ifndef QEXPONENTIAL_H
#define QEXPONENTIAL_H
#include "random.h"
//#include <exponential.h>

class qExponential: public Random{
private:
    double N;
    double lambda;
    double q;
    double xmin = 0;
    double xmax;
    std::vector<double> cum_dist;
    
public:
    qExponential();
    qExponential(unsigned long int N, double lambda, double q);

    void build_dist();
    double inverse_CDF(double p);
    double eq(double x);
    double pdf(double x);
    long int quick_search(double u, unsigned long int j_min, unsigned long int j_max);
    double search_inverse_CDF(double p);
    void set_min(double x0);

};

#endif // QEXPONENTIAL_H
