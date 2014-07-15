#include <iostream>
#include "kolmogorov.hpp"

extern "C"
{
    #include "mt19937ar.h"
}

using namespace std;

int main(void)
{
    KS ks(10000000);
    ks.init_ks_slow();
    ks.test();
	return 0;
}

