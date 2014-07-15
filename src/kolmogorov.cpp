#include "kolmogorov.hpp"
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <math.h>
#include <cassert>

extern "C"
{
    #include <gsl/gsl_cdf.h>
    #include <gsl/gsl_randist.h>
    #include "mt19937ar.h"
}

KS::KS(int n)
{
	unsigned long long seed = time(NULL);
	init_genrand(seed);
    _n = n;
    std::vector<double> _genVals(_n);
}

KS::~KS()
{
}

double cAlpha(double alpha)
{
    if(alpha == 0.10)
        return 1.22;
    else if (alpha == 0.05)
        return 1.36;
    else if (alpha == 0.025)
        return 1.48;
    else if (alpha == 0.01)
        return 1.63;
}

double KS::Klim(double alpha = 0.05)
{
    return cAlpha(alpha)*sqrt(2.0);
}

int comp_func(double a, double b)
{
    double diff = a - b;
    if (diff == 0)
        return 0;
    else if (diff < 0)
        return -1;
    else
        return 1;
}

bool comp_func_2(double a, double b)
{
    return (a<b);
}
void KS::init_ks_slow()
{
    int i;
    double j,currentKp = 0.0, currentKm = 0.0;
    // First Step : Generating a pool of random numbers to test
	for(i = 0;i < _n; i++)
	{
		_genVals.push_back(genrand_real1());
	}
    // Then sorting these random numbers:
	std::sort(_genVals.begin(), _genVals.end() ,comp_func_2);

    // And finally computing the Kplus and Kminus values
    for(i =0; i< _n ; i++)
    {
        j = (double) i;
        currentKp = j/_n - gsl_cdf_flat_P (_genVals[i], 0.0, 1);
        currentKm = gsl_cdf_flat_P (_genVals[i], 0, 1) - (j-1)/_n;
        if (currentKp >= _kplus)
            _kplus = currentKp;
        if (currentKm >= _kmoins)
            _kmoins = currentKm;
    }
    _kplus = sqrt(_n)*_kplus;
    _kmoins = sqrt(_n)*_kmoins;
    _kmax = std::max(_kplus, _kmoins);

}

bool KS::test(double alpha)
{
    double limite = Klim(alpha);
    //std::cout << "K+: " <<_kplus <<"\t K-:" << _kmoins <<"\t Kmax:" << _kmax << std::endl;
    //std::cout << "Klimit : " << limite << std::endl ;
    if(_kmax >= limite)
    {
        //std::cout << "Kmax >= Klim, Null Hypothesis rejected at a level "<< alpha << std::endl;
        return false;
    }
    else
    {
        //std::cout << "Kmax < Klim, Null Hypothesis not rejected (Random numbers OK.)"<< std::endl;
        return true;
    }
}
