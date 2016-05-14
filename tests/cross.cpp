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
