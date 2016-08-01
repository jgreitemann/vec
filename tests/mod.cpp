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
#include "../vec.hpp"

using namespace Vec;

template <size_t N, typename T>
void mod_test()
{
    vec<N,T> a, b(T(3)), c;
    for (size_t i = 0; i < N; ++i) {
        a[i] = T(i);
        c[i] = T(i % 3);
    }
    assert((a % b) == c);
    assert((a % T(3)) == c);
    vec<N,T> d(a);
    a %= b;
    assert(a == c);
    d %= T(3);
    assert(d == c);
}

int main ()
{
    mod_test<10, int>();
    mod_test<10, long>();
    mod_test<10, float>();
    mod_test<10, double>();
    mod_test<10, long double>();
    return 0;
}
