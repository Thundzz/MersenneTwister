#include "kolmogorov.hpp"
#include <iostream>
#include <cstdlib>
#include <math.h>

extern "C"
{
    #include <gsl/gsl_cdf.h>
    #include <gsl/gsl_randist.h>
    #include "mt19937ar.h"
}

KS::KS(int n)
{
    _n = n;
}


int comp_func(double const * a, double const * b)
{
	return (int) (*a - *b);
}

void KS::init_ks_slow()
{
    int i;
    double _genVals[_n], currentKp, currentKm;
    // First Step : Generating a pool of random numbers to test
	unsigned long long seed = time(NULL);
	init_genrand(seed);
	for(i = 0;i < _n; i++)
	{
		_genVals[i] = genrand_real1();
	}
    // Sort these random numbers:
	qsort(_genVals, _n, sizeof(double), (int (*) (const void*, const void*)) comp_func);

    // Compute the Kplus and Kminus values
    for(i =0; i< _n ; i++)
    {
		std::cout<< _genVals[i]<< std::endl;
        currentKp = i/_n - gsl_cdf_flat_P (_genVals[i], 0, 1);
        currentKm = gsl_cdf_flat_P (_genVals[i], 0, 1) - (i-1)/_n;
        if (currentKp >= _kplus)
            _kplus = currentKp;
        if (currentKm >= _kmoins)
            _kmoins = currentKm;
    }
    _kplus = sqrt(_n)*_kplus;
    _kmoins = sqrt(_n)*_kmoins;
    _kmax = std::max(_kplus, _kmoins);
    std::cout << _kplus <<" " << _kmoins <<" " << _kmax << std::endl;
}
