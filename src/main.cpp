#include <iostream>
#include "kolmogorov.hpp"

extern "C"
{
    #include "mt19937ar.h"
}

using namespace std;

int main(void)
{
    KS ks(1000);
    ks.init_ks_slow();
	return 0;
}

