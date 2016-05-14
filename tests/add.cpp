/*  vec -- small physical vectors, complex or real
 *  Copyright (C) 2016  Jonas Greitemann <j.greitemann@lmu.de>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <cassert>
#include <cmath>
#include <limits>
#include "close.hpp"
#include "../vec.hpp"

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
        assert(CLOSE(c[i], T(N), tol));
    vec<N,T> d = c - a;
    for (size_t i = 0; i < N; ++i)
        assert(CLOSE(d[i], b[i], tol));
    d += c;
    d -= b;
    for (size_t i = 0; i < N; ++i)
        assert(CLOSE(d[i], c[i], tol));
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
