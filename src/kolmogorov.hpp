#include <vector>

class KS
{
private:
    int _n;
    double _kplus;
    double _kmoins;
    double _kmax;
    std::vector<double> _genVals;

public:
    KS(int n);
    ~KS();
    double Klim(double );
    bool test(double alpha =0.10);
    void init_ks_slow();
};
