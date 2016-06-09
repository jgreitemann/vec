# vec
C++ class for handling physical low-dimensional real or complex vectors.

Features / properties:
 * fixed-size,
 * stack-allocated,
 * much faster for physical dimensions (N=2, 3) than `std::valarray` (break-even dimension is somewhere between N=10 and 20 on my system),
 * linear operations, dot product via operator overloading
 * cross product as a template specialization for `vec<3,T>`,
 * `vec<N,T>`s of different data types `T` may be added, dotted, crossed, etc. if the underlying types support the corresponding arithmetic operations,
 * supports automatic implicit conversion with respect to data type for non-template function calls,
 * complex number-aware: conjugation in apropriate places using type traits,
 * provides `Vec::is_complex<T>` type trait for external use,
 * modulo operation for real integral and floating point (sic!) types: useful e.g. in Umklapp scattering

## Usage
```cxx
// default data type assumes double
vec<3> a = {1., 2., 3.};
// 2-norm
cout << "||a|| = " << a.norm() << endl;
// 1-norm
cout << "||a||_1 = " << a.norm(1) << endl;

vec<3,int> b = {3, 2, 1};
cout << "dot product: a * b = " << a * b << endl;
// cross product is defined on vec<3,T> only
cout << "cross product: a x b = " << cross(a, b) << endl;

// linear operations are overloaded, naturally
auto d = a - b;
d /= 2;
cout << "d = " << d << endl;


complex<int> I(0, 1);
// data type may be complex and integral
vec<2, complex<int>> c = {1+I, 2-I};

// norm, dot product, and cross product are complex-aware
cout << "||c||^2 = " << c.norm2_sq() << endl;
cout << "conjugate: c* = " << conj(c) << endl;
```

Output:
```
||a|| = 3.74166
dot product: a * b = 10
cross product: a x b = (-4, 8, -4)
d = (-1, 0, 1)
||c||^2 = 7
conjugate: c* = ((1,-1), (2,1))
```

## Testing
This project uses CMake and CTest. After cloning the repo, create a `build` directory, run CMake and `make` to build the tests and run `make test`:

```
$ mkdir build && cd build
$ cmake ..
$ make
$ make test
```

## Installation
The header `vec.hpp` is copied to the default include directory upon `make install`. You'll most likely want to run this as root. You can change the default install location by passing `-DCMAKE_INSTALL_PREFIX=/place/to/install` to `cmake` (but skip the trailing `/include` in the prefix path). CMake will also install a `vecConfig.cmake` file to be used with the CMake directive `find_package` in your projects.
