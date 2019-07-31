#ifndef QEXPONENTIAL_H
#define QEXPONENTIAL_H
#include <random.h>
#include <exponential.h>

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
    qExponential(unsigned long int N, double lambda, double q, double xmin);

    double approx_inverse_CDF(double p);
    void build_dist();
    double df(double f1, double f2);
    double d2f(double f1, double f2);
    double d3f(double f1, double f2);
    double d4f(double f1);
    double dHarmonic(double f1, double f2);
    double factor1(double x);
    double factor2(double f1);
    double f(double f1, double f2);
    double Harmonic(double f1, double f2, double f1_0, double f2_0);   
    double integ(double f1, double f2);
    double inverse_CDF(double p);
    double pdf(double x);
    long int quick_search(double u, unsigned long int j_min, unsigned long int j_max);
    double search_inverse_CDF(double p);
    void set_min(double x0);
//    unsigned long int PickRand();
//    std::vector<unsigned long int> PickRand(unsigned long int size);
};

#endif // QEXPONENTIAL_H
