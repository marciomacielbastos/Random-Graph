#ifndef RANDOMGEN_H
#define RANDOMGEN_H
#include <random.h>
#include <vector>
#include <float.h>

class Zipf: public Random{
private:
    double N;
    double s;
    double xmax;
    double xmin = 1;
    double Zeta;
    std::vector<double> cdf;
    std::vector<double> cum_dist;

public:
    Zipf();
    Zipf(unsigned long int N, double s);
    Zipf(unsigned long int N, double s, double xmin);

    double approx_inverse_CDF(double p);
    void build_dist();
    double integ(double f1, double f2);
    double dHarmonic(double f1, double f2);
    double df(double f1, double f2);
    double d2f(double f1, double f2);
    double d3f(double f1, double f2);
    double d4f(double f1);
    double factor1(double x);
    double factor2(double f1);
    double f(double f1, double f2);
    double Harmonic(double f1, double f2, double f1_0, double f2_0);
    double inverse_CDF(double p);
    double pdf(double x);
    long int quick_search(double u, unsigned long int j_min, unsigned long int j_max);
    double search_inverse_CDF(double p);
    void set_min(double x0);
};

#endif // RANDOMGEN_H
