#include "random.h"

Random::Random(){
    std::srand(unsigned(time(nullptr)));
}

Random::~Random(){
}

double Random::Uniform(){
    return double(std::rand())/RAND_MAX; // in (0, 1)
}

unsigned long int Random::Rand(){
    return 0;
}

std::vector<unsigned long int> Random::Rand(unsigned long int size){
    std::vector<unsigned long int> zero;
    return zero;
}

double Random::SetParameter(double p){
    // DO NOT COMPARE FLOAT NUMBERS AS USUAL!!!!
    if(std::abs(p - 1) < std::numeric_limits<double>::epsilon()) return 1.000001;
    else return p;
}

void Random::SetPDF(double N, double s){
}

unsigned long int Random::DiscreteUniform(unsigned long int max){
    return static_cast<unsigned long int>(std::rand()) % max; // in (0, n - 1)
}

unsigned long int Random::DiscreteUniform(unsigned long int min, unsigned long int max){
    return static_cast<unsigned long int>(std::rand()) %(max-min) + min; // in [min, max)
}
