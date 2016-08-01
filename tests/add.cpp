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

template <size_t N, typename T1, typename T2, typename S = T1,
          typename T3 = decltype(T1()+T2())>
void add_test(S tol)
{
    vec<N,T1> a;
    vec<N,T2> b;
    for (size_t i = 0; i < N; ++i) {
        a[i] = T1(i);
        b[i] = T2(N - i);
    }
    vec<N,T3> c = a + b;
    for (size_t i = 0; i < N; ++i)
        assert(CLOSE(c[i], T1(N), tol));
    vec<N,T3> d = c - a;
    for (size_t i = 0; i < N; ++i)
        assert(CLOSE(d[i], b[i], tol));
    d += c;
    d -= b;
    for (size_t i = 0; i < N; ++i)
        assert(CLOSE(d[i], c[i], tol));
}

int main ()
{
    // tests with same types
    add_test<10, int, int>(0);
    add_test<10, float, float>(100 * std::numeric_limits<float>::epsilon());
    add_test<10, double, double>(100 * std::numeric_limits<double>::epsilon());
    add_test<10, std::complex<int>, std::complex<int>, int>(0);
    add_test<10, std::complex<float>, std::complex<float>, float>(
            100 * std::numeric_limits<float>::epsilon()
    );
    add_test<10, std::complex<double>, std::complex<double>, double>(
            100 * std::numeric_limits<double>::epsilon()
    );

    // tests with different types
    add_test<10, int, double, double>(
            100 * std::numeric_limits<double>::epsilon());
    add_test<10, int, std::complex<int>, int>(0);
    return 0;
}
