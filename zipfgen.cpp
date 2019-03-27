#include "zipfgen.h"

void ZipfGen::SetCDF(){
    unsigned long int N = static_cast<unsigned long int>(this->N);
    if(N < 1000){
        this->Zeta = Harmonic(N);
        for(unsigned long int k = 0; k < N; k++){
            this->cdf.push_back(Harmonic(k)/this->Zeta);
        }
    }
    else {
        this->Zeta = HarmonicApprox(N);
        for(unsigned long int k = 0; k < N; k++){
            this->cdf.push_back(HarmonicApprox(k)/this->Zeta);
        }
    }
}

ZipfGen::ZipfGen(double N, double s): N(N), s(s){
    std::srand(unsigned(time(0)));
    this->xmax= this->N - 1;
    SetCDF();
}

void ZipfGen::SetS(double s){
    this->s = s;
}

void ZipfGen::SetXmin(double xmin){
    this->xmin = xmin;
}

void ZipfGen::SetXmax(double xmax){
    this->xmax = xmax;
}

double ZipfGen::Uniform(){
    return double(std::rand())/RAND_MAX; // in (0, 1)
}

//----------------------------------------------------------------------------------------//
//*********************************APPROXIMATION*METHOD***********************************//
//----------------------------------------------------------------------------------------//

//THIS METHOD IS UNSTABLE!!!!

//H_(x,s) * 12 obtained by approximation by the Euler-MacLaurin formula truncated in the 2nd order
// https://medium.com/@jasoncrease/zipf-54912d5651cc
double ZipfGen::H12(double m, unsigned long int x){
    double H12 = 12*(((m * x * x * x) - 1)/(1 - s)) + 6 + (6 * m * x * x) + s - (s * (m * x));
    return H12;
}



//Derivative of H_(x,s) * 12
double ZipfGen::H12_(double m, unsigned long int x){
    double H12_ = (12 * m * x * x) - ( 6 * s * (m * x)) + (s * (s + 1) * (m));
    return H12_;
}

double ZipfGen::NewtonRaphson(double p){
    double powN = std::pow(N, -(s+2));
    double D = H12(powN, this->N);
    double x = this->x0;
    int test = 1000;
    while (true) {
//        MacGyver method to avoid to get stuck in non convergence
        if(test == 0){
            double new_p = Uniform();
            return NewtonRaphson(new_p);
        }
        double pow_x = std::pow(x, -(s+2));
        double f = H12(pow_x, x) - (p * D); // f(x)
        double f_ = H12_(pow_x, x); //f'(x)
        double factor = (f/f_);
        double newx = std::fmax(1, x - factor);
        if(std::abs(newx - x) <= tol){
            return newx + this->xmin - 1;
        }
        x = newx;
        test --;
    }
}

unsigned long int ZipfGen::RandomApproxMethod(){
    double p = Uniform(); // p ~ U(0,1)
    double x = NewtonRaphson(p);
    return static_cast<unsigned long int>(x);
}

std::vector<unsigned long int> ZipfGen::RandomApproxMethod(unsigned long size){
    std::vector<unsigned long int> randomVector;
    for(unsigned long int i = 0; i < size; i++){
        randomVector.push_back(RandomApproxMethod());
    }
    return randomVector;
}

double ZipfGen::HarmonicApprox(unsigned long int k){
    double powN = std::pow(N, -(s+2));
    double a = H12(powN, this->N);
    double pow_k = std::pow(k, -(s+2));
    double b = H12(pow_k, k);
    return b;
}

//----------------------------------------------------------------------------------------//
//***********************************BRUTE-FORCE*METHOD***********************************//
//----------------------------------------------------------------------------------------//

//Inverse Transform Method applied to discrete random variable (Zipf distributed)

double ZipfGen::Harmonic(unsigned long int k){
    double summ = 0;
    double kpow;
    for(unsigned long int i = 1; i < k; i++){
        kpow = static_cast<double>(i);
        kpow = std::pow(kpow, s);
        summ += 1.0 / kpow;
    }
    return summ;
}

//http://www.columbia.edu/~ks20/4404-Sigman/4404-Notes-ITM.pdf
unsigned long int ZipfGen::RandomBFMethod(){
    double U = Uniform();
    unsigned long int N = static_cast<unsigned long int>(this->N);
    for(unsigned long int k = 0; k < N; k++){
        double j = this->cdf[k];
        if(this->cdf[k] < U && U <= this->cdf[k+1]){
            return k;
        }
    }
}

std::vector<unsigned long int> ZipfGen::RandomBFMethod(unsigned long size){
    std::vector<unsigned long int> randomVector;
    for(unsigned long int i = 0; i < size; i++){
        randomVector.push_back(RandomBFMethod());
    }
    return randomVector;
}
