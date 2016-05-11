#include <cassert>
#include <cmath>
#include <limits>
#include "vec.hpp"

using namespace Vec;

template <size_t N, typename T, typename S = T>
void add_test(S tol) {
    vec<N,T> a, b;
    for (size_t i = 0; i < N; ++i) {
        a[i] = T(i);
        b[i] = T(N - i);
    }
    vec<N,T> c = a + b;
    for (size_t i = 0; i < N; ++i)
        assert(abs(c[i] - T(N)) <= tol);
    vec<N,T> d = c - a;
    for (size_t i = 0; i < N; ++i)
        assert(abs(d[i] - b[i]) <= tol);
    d += c;
    d -= b;
    for (size_t i = 0; i < N; ++i)
        assert(abs(d[i] - c[i]) <= tol);
}

int main () {
    add_test<10, int>(0);
    add_test<10, float>(100 * std::numeric_limits<float>::epsilon());
    add_test<10, double>(100 * std::numeric_limits<double>::epsilon());
    add_test<10, std::complex<int>, int>(0);
    add_test<10, std::complex<float>, float>(
            100 * std::numeric_limits<float>::epsilon()
    );
    add_test<10, std::complex<double>, double>(
            100 * std::numeric_limits<double>::epsilon()
    );
    return 0;
}
