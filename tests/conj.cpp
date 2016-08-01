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
#include "../vec.hpp"

using namespace Vec;

const size_t N = 10;

int main ()
{
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
