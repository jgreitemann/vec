# vec
C++ class for handling physical low-dimensional real or complex vectors

## Usage
```
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
```

```
||a|| = 3.74166
dot product: a * b = 10
cross product: a x b = (-4, 8, -4)
d = (-1, 0, 1)
2
conjugate: ((1,-1), (2,1))
```
