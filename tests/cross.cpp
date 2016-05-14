#include <cassert>
#include <cmath>
#include <limits>
#include "close.hpp"
#include "../vec.hpp"

using namespace Vec;


int main () {
    vec<3,double> a = {1., 2., 3.};
    vec<3,double> b = {3., 2., 1.};
    vec<3,double> c = cross(a, b);
    assert(abs(a * c) < 100. * std::numeric_limits<double>::epsilon());
    assert(abs(b * c) < 100. * std::numeric_limits<double>::epsilon());
    double sin2_theta = 1. - pow(a*b, 2) / a.norm_sq() / b.norm_sq();
    assert(CLOSE(c.norm_sq() / a.norm_sq() / b.norm_sq(), sin2_theta,
                 100. * std::numeric_limits<double>::epsilon()));

    std::complex<double> I = {0, 1};
    vec<3,std::complex<double>> d = {1.-3.*I, 2.+2.*I, 3.-I};
    vec<3,std::complex<double>> e = {3.+I, 2.-I, 1.-I};
    vec<3,std::complex<double>> f = cross(d, e);
    assert(abs(d * f) < 100. * std::numeric_limits<double>::epsilon());
    assert(abs(e * f) < 100. * std::numeric_limits<double>::epsilon());
    return 0;
}
