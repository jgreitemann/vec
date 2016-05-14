#include <cassert>
#include <cmath>
#include <limits>
#include "../vec.hpp"

using namespace Vec;

const size_t N = 10;

int main () {
    std::complex<double> I = {0, 1};
    vec<N,std::complex<double>> c(exp(I / double(N)));
    for (size_t i = 0; i < N; ++i)
        c[i] = pow(c[i], i);
    vec<N,std::complex<double>> c_star = conj(c);
    for (size_t i = 0; i < N; ++i)
        assert(c_star[i] == conj(c[i]));
    c.conj();
    assert(c == c_star);

    return 0;
}
