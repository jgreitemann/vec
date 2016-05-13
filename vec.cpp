#include <iostream>
#include <complex>
#include "vec.hpp"

using namespace std;
using namespace Vec;

int main(int argc, char *argv[]) {
    vec<3,double> a = {1., 2., 3.};
    vec<3,double> b = {3,  2,  1 };
    cout << a.norm() << endl;
    vec<3,double> d = a - b;
    d /= 2;
    cout << "d = (" << d[0] << "," << d[1] << "," << d[2] << ")" << endl;
    cout << d.norm() << endl;
    vec<3> e(a);
    cout << (a == b) << endl;
    cout << (a != b) << endl;
    cout << (a == e) << endl;
    cout << (a != e) << endl;
    vec<3> f = cross(a, b);
    cout << "(" << f[0] << ", " << f[1] << ", " << f[2] << ")" << endl;
    cout << (f * a) << endl;

    complex<int> I(0, 1);
    vec<2,complex<int>> c {1+I, 2-I};
    cout << c.norm() << endl;
    return 0;
}
