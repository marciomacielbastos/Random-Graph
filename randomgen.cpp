#include "randomgen.h"

RandomGen::RandomGen(){

}
//    return static_cast<unsigned long>(val);

double RandomGen::Random(double alpha){
    xmax= 1/2147483647;
    xmin = xmin;
    xmax = 1/xmax;
    double x, y;
    if(alpha<=1){
        return 0;
    }
    else {
        std::srand(unsigned(time(NULL)));
        y = double(std::rand())/RAND_MAX;
        x = std::pow(this->xmax, -alpha+1);
        x -= std::pow(this->xmin, -alpha+1);
        x *= y;
        x += std::pow(this->xmin, -alpha+1);
        x = std::pow(x,(1/(-alpha+1)));
    }
    return x;
}

//double RandomGen::
