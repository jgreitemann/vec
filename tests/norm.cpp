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

const size_t N = 10;

int main ()
{
    vec<N,double> a(1.);
    assert(CLOSE(a.norm2_sq(), N, 100 * std::numeric_limits<double>::epsilon()));
    vec<N,double> b = 42 * a;
    assert(CLOSE(a.norm() * 42, b.norm(),
                 100 * std::numeric_limits<double>::epsilon()));

    std::complex<double> I = {0, 1};
    vec<N,std::complex<double>> c(exp(I / double(N)));
    for (size_t i = 0; i < N; ++i)
        c[i] = pow(c[i], i);
    assert(CLOSE(c.norm2_sq(), N, 100 * std::numeric_limits<double>::epsilon()));
    assert(CLOSE(c.norm(1), N, 100 * std::numeric_limits<double>::epsilon()));
    vec<N,std::complex<double>> d = 42. * c;
    assert(CLOSE(c.norm() * 42., d.norm(),
                 100 * std::numeric_limits<double>::epsilon()));

    return 0;
}
