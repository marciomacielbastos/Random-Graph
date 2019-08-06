#include "random.h"

Random::Random(){
    std::srand(unsigned(time(nullptr)));
}

Random::~Random(){
}

double Random::h() {
    double h;
    h = (xmax - xmin) / (xmax - 1);
    return h;
}

double Random::uniform(){
    return double(std::rand())/RAND_MAX; // in (0, 1)
}

double Random::inverse_CDF(double p){
    return p;
}

double Random::approx_inverse_CDF(double p){
    return p;
}

unsigned long int Random::random(){
    double p = uniform(); // p ~ U(0,1)
    double x = inverse_CDF(p);
    return static_cast<unsigned long int>(x);
}

unsigned long int Random::random_parallel(){
    double p = uniform(); // p ~ U(0,1)
    double x = approx_inverse_CDF(p);
    return static_cast<unsigned long int>(x);
}

std::vector<unsigned long int> Random::random(unsigned long int size){
    std::vector<unsigned long int> randomVector;
    unsigned long int sum = 0;
    while (size > 0) {
        unsigned long x = random();
        sum += x;
        randomVector.push_back(x);
        size--;
    }
    randomVector.push_back(sum);
    return randomVector;
}

double Random::SetParameter(double p){
    // DO NOT COMPARE FLOAT NUMBERS AS USUAL!!!!
    if(std::abs(p - 1) < std::numeric_limits<double>::epsilon()) return 1.000001;
    else return p;
}

unsigned long int Random::discrete_uniform(unsigned long int max){
    return static_cast<unsigned long int>(std::rand()) % max; // in [0, n - 1)
}

unsigned long int Random::discrete_uniform(unsigned long int min, unsigned long int max){
    return static_cast<unsigned long int>(std::rand()) %(max-min) + min; // in [min, max)
}

std::vector<unsigned long int> Random::random(unsigned long int size, unsigned long int num_threads){
    std::vector<unsigned long int> random_vector;
    random_vector.assign(size, 0);
    std::thread t[num_threads];
    unsigned long int begin = 0;
    unsigned long int end = 0;

    for (unsigned int i = 0; i < num_threads; ++i) {
        if(i < size % (num_threads + 1)){
            end += size / (num_threads + 1) + 1;
        }
        else {
            end += size / (num_threads + 1);           
        }
        t[i] = (std::thread(&Random::random_t, this, std::ref(random_vector), begin, end));
        begin = end;
    }
    random_t(std::ref(random_vector), begin, random_vector.size());
    for (unsigned int i = 0; i < num_threads; ++i){
        t[i].join();
    }
    return random_vector;
}

void Random::random_t(std::vector<unsigned long int> & random_vector, unsigned long int begin, unsigned long int end){
    for (unsigned int i = begin; i < end; ++i) {
        unsigned long int val = random_parallel();
        random_vector[i] = val;
    }
}
