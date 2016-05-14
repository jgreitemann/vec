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
    vec<3,double> a = {1., 2., 3.};
    vec<3,double> b = {3,  2,  1 };
    cout << a.norm() << endl;
    vec<3,double> d = a - b;
    d /= 2;
    cout << "d = (" << d[0] << "," << d[1] << "," << d[2] << ")" << endl;
    cout << d.norm() << endl;
    vec<3> e(a);
    cout << (a == b) << endl;
    cout << (a != b) << endl;
    cout << (a == e) << endl;
    cout << (a != e) << endl;
    vec<3> f = cross(a, b);
    cout << "(" << f[0] << ", " << f[1] << ", " << f[2] << ")" << endl;
    cout << (f * a) << endl;

    complex<int> I(0, 1);
    vec<2,complex<int>> c {1+I, 2-I};
    cout << c.norm() << endl;
    c.conj();
    cout << "(" << c[0] << "," << c[1] << ")" << endl;
    cout << c.norm() << endl;
    return 0;
}
