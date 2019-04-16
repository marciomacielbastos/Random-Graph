#include "randomdistribution.h"

RandomDistribution::RandomDistribution(){
    std::srand(unsigned(time(nullptr)));
}

RandomDistribution::~RandomDistribution(){
}

double RandomDistribution::Uniform(){
    return double(std::rand())/RAND_MAX; // in (0, 1)
}

unsigned long int RandomDistribution::Random(){
    return 0;
}

std::vector<unsigned long int> RandomDistribution::Random(unsigned long int size){
    std::vector<unsigned long int> zero;
    return zero;
}

void RandomDistribution::SetPDF(double N, double s){
}

unsigned long int RandomDistribution::DiscreteUniform(unsigned long int max){
    return static_cast<unsigned long int>(std::rand()) % max; // in (0, n - 1)
}

unsigned long int RandomDistribution::DiscreteUniform(unsigned long int min, unsigned long int max){
    return static_cast<unsigned long int>(std::rand()) %(max-min) + min; // in [min, max)
}
