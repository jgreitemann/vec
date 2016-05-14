#include <cassert>
#include <cmath>
#include <limits>
#include "../vec.hpp"

using namespace Vec;

const size_t N = 10;

int main () {
    vec<N,double> a(1.);
    assert(abs(a.norm_sq() - N) < 100 * std::numeric_limits<double>::epsilon());
    vec<N,double> b = 42. * a;
    assert(abs(a.norm() * 42. - b.norm())
            < 100 * std::numeric_limits<double>::epsilon());

    std::complex<double> I = {0, 1};
    vec<N,std::complex<double>> c(exp(I / double(N)));
    for (size_t i = 0; i < N; ++i)
        c[i] = pow(c[i], i);
    assert(abs(c.norm_sq() - N) < 100 * std::numeric_limits<double>::epsilon());
    vec<N,std::complex<double>> d = std::complex<double>(42., 0.) * c;
    assert(abs(c.norm() * 42. - d.norm())
            < 100 * std::numeric_limits<double>::epsilon());

    return 0;
}
