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
#include <iostream>
#include <complex>
#include "vec.hpp"

using namespace std;
using namespace Vec;

int main(int argc, char *argv[]) {
    // default data type assumes double
    vec<3> a = {1, 2, 3};
    // 2-norm
    cout << "||a|| = " << a.norm() << endl;
    vec<3> b = {3, 2, 1};
    cout << "dot product: a * b = " << a * b << endl;
    // cross product is defined on vec<3,T> only
    cout << "cross product: a x b = " << cross(a, b) << endl;
    // linear operations are overloaded, naturally
    vec<3> d = a - b;
    d /= 2;
    cout << "d = " << d << endl;

    complex<int> I(0, 1);
    // data type may be complex and integral
    vec<2, complex<int>> c = {1+I, 2-I};
    // norm, dot product, and cross product are complex-aware
    cout << c.norm() << endl;
    cout << "conjugate: " << conj(c) << endl;
    return 0;
}
