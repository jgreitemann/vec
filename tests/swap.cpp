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
#include <limits>
#include <utility>
#include "../vec.hpp"

using namespace Vec;

const size_t N = 10;

int main ()
{
    vec<N,double> a, b;
    for (size_t i = 0; i < N; ++i) {
        a[i] = double(i);
        b[i] = double(N-i);
    }
    vec<N,double> c(a), d(b);
    std::swap(a, b);
    assert(a == d);
    assert(b == c);

    return 0;
}
