#include <iostream>
#include "kolmogorov.hpp"
#include <cassert>
extern "C"
{
    #include "mt19937ar.h"
}

static int passedTests = 0;
using namespace std;


bool kolmogorov_smirnov()
{
    std::cout << "Starting Kolmogorov-Smirnov test... ";
    KS ks(1000000);
    ks.init_ks_slow();
    if(ks.test())
    {
        passedTests++ ;
        std::cout << "OK."<< std::endl;
    }
    else
    {
        std::cout << "NOK."<< std::endl;
    }

}

int main(void)
{
    kolmogorov_smirnov();

    std::cout << passedTests << " tests passed." << std::endl;
	return 0;
}

