#pragma once
#include <initializer_list>
#include <type_traits>
#include <complex>
#include <cmath>

namespace Vec {
    template<typename S> struct is_complex : std::false_type {};
    template<typename S> struct is_complex<std::complex<S>> : std::true_type {};

    // forward declarations
    template <size_t N, typename T> class vec;

    template <size_t N, typename T>
    bool operator== (const vec<N,T>&, const vec<N,T>&);

    template <size_t N, typename T>
    typename std::enable_if<std::is_arithmetic<T>::value, T>::type
    operator*(const vec<N,T>&, const vec<N,T>&);

    template <size_t N, typename T>
    typename std::enable_if<is_complex<T>::value, T>::type
    operator*(const vec<N,T>&, const vec<N,T>&);

    // definition
    template <size_t N, typename T = double>
    class vec {
        private:
            T data[N];
        public:
            // assignment operator
            vec& operator=(const vec& x) {
                for (size_t i = 0; i < N; ++i)
                    data[i] = x.data[i];
                return *this;
            }


            // constructors
            vec() {}

            vec(const T& val) {
                for (size_t i = 0; i < N; ++i)
                    data[i] = val;
            }

            vec(const T* p) {
                for (size_t i = 0; i < N; ++i)
                    data[i] = p[i];
            }

            vec(const vec& x) {
                *this = x;
            }

            vec(std::initializer_list<T> il) {
                T *ptr = data;
                for (const T& e: il) {
                    *ptr = e;
                    ++ptr;
                }
            }


            // operators
            const T& operator[](size_t i) const {
                return data[i];
            }

            T& operator[](size_t i) {
                return data[i];
            }

            vec operator+() const {
                return vec(*this);
            }

            vec operator-() const {
                vec res;
                for (size_t i = 0; i < N; ++i)
                    res.data[i] = -data[i];
                return res;
            }

            /* vec& operator%= (const vec& rhs); */
            vec& operator+= (const vec& rhs) {
                for (size_t i = 0; i < N; ++i)
                    data[i] += rhs.data[i];
                return *this;
            }

            vec& operator-= (const vec& rhs) {
                for (size_t i = 0; i < N; ++i)
                    data[i] -= rhs.data[i];
                return *this;
            }

            /* vec& operator%= (const T& val); */
            vec& operator*= (const T& val) {
                for (size_t i = 0; i < N; ++i)
                    data[i] *= val;
                return *this;

            }

            vec& operator/= (const T& val) {
                for (size_t i = 0; i < N; ++i)
                    data[i] /= val;
                return *this;
            }

            friend bool operator== <N,T>(const vec<N,T>&, const vec<N,T>&);

            friend T operator* <N,T>(const vec<N,T>&, const vec<N,T>&);

            // norm
            template <typename..., typename S = T>
            typename std::enable_if<std::is_arithmetic<S>::value, S>::type
            norm_sq() const {
                return (*this) * (*this);
            }

            template <typename..., typename S = T>
            typename std::enable_if<is_complex<S>::value,
                                    typename S::value_type>::type
            norm_sq() const {
                return ((*this) * (*this)).real();
            }

            template <typename..., typename S = T>
            typename std::enable_if<std::is_arithmetic<S>::value, S>::type
            norm() const {
                return sqrt(norm_sq());
            }

            template <typename..., typename S = T>
            typename std::enable_if<is_complex<S>::value,
                                    typename S::value_type>::type
            norm() const {
                return sqrt(norm_sq());
            }

            template <typename..., typename S = T>
            typename std::enable_if<is_complex<S>::value, void>::type
            conj() {
                for (size_t i = 0; i < N; ++i)
                    data[i] = std::conj(data[i]);
            }
    };

    // dot product
    template <size_t N, typename T>
    typename std::enable_if<std::is_arithmetic<T>::value, T>::type
    operator*(const vec<N,T>& lhs, const vec<N,T>& rhs) {
        T sum;
        for (size_t i = 0; i < N; ++i)
            sum += lhs.data[i] * rhs.data[i];
        return sum;
    }

    template <size_t N, typename T>
    typename std::enable_if<is_complex<T>::value, T>::type
    operator*(const vec<N,T>& lhs, const vec<N,T>& rhs) {
        T sum;
        for (size_t i = 0; i < N; ++i)
            sum += conj(lhs.data[i]) * rhs.data[i];
        return sum;
    }


    // cross product
    template <typename T>
    typename std::enable_if<std::is_arithmetic<T>::value, vec<3,T>>::type
    cross(const vec<3,T>& lhs, const vec<3,T>& rhs) {
        return {lhs[1] * rhs[2] - lhs[2] * rhs[1],
                lhs[2] * rhs[0] - lhs[0] * rhs[2],
                lhs[0] * rhs[1] - lhs[1] * rhs[0]};
    }

    template <typename T>
    typename std::enable_if<is_complex<T>::value, vec<3,T>>::type
    cross(const vec<3,T>& lhs, const vec<3,T>& rhs) {
        return {std::conj(lhs[1] * rhs[2] - lhs[2] * rhs[1]),
                std::conj(lhs[2] * rhs[0] - lhs[0] * rhs[2]),
                std::conj(lhs[0] * rhs[1] - lhs[1] * rhs[0])};
    }


    // complex conjugation
    template <size_t N, typename T>
    typename std::enable_if<is_complex<T>::value, vec<N,T>>::type
    conj(const vec<N,T>& c) {
        vec<N,T> res(c);
        res.conj();
        return res;
    }


    // scalar multiplication
    template <size_t N, typename T>
    vec<N,T> operator* (const T& val, const vec<N,T>& rhs) {
        vec<N,T> res(rhs);
        res *= val;
        return res;
    }

    template <size_t N, typename T>
    vec<N,T> operator* (const vec<N,T>& lhs, const T& val) {
        vec<N,T> res(lhs);
        res *= val;
        return res;
    }

    template <size_t N, typename T>
    vec<N,T> operator/ (const vec<N,T>& lhs, const T& val) {
        vec<N,T> res(lhs);
        res /= val;
        return res;
    }

    /* template <size_t N, typename T> */
    /* vec<N,T> operator% (const vec<N,T>& lhs, const vec<N,T>& rhs) { */

    /* } */
    /* template <size_t N, typename T> vec<N,T> operator% (const vec<N,T>& lhs, const T& val); */

    template <size_t N, typename T>
    vec<N,T> operator+ (const vec<N,T>& lhs, const vec<N,T>& rhs) {
        vec<N,T> res(lhs);
        res += rhs;
        return res;
    }

    template <size_t N, typename T>
    vec<N,T> operator- (const vec<N,T>& lhs, const vec<N,T>& rhs) {
        vec<N,T> res(lhs);
        res -= rhs;
        return res;
    }

    template <size_t N, typename T>
    bool operator== (const vec<N,T>& lhs, const vec<N,T>& rhs) {
        for (size_t i = 0; i < N; ++i)
            if (lhs.data[i] != rhs.data[i])
                return false;
        return true;
    }

    template <size_t N, typename T>
    bool operator!= (const vec<N,T>& lhs, const vec<N,T>& rhs) {
        return !(lhs == rhs);
    }

    /* template <size_t N, typename T> bool operator< (const vec<N,T>& lhs, const vec<N,T>& rhs); */
    /* template <size_t N, typename T> bool operator< (const T& val, const vec<N,T>& rhs); */
    /* template <size_t N, typename T> bool operator< (const vec<N,T>& lhs, const T& val); */

    /* template <size_t N,typename T> bool operator> (const vec<N,T>& lhs, const vec<N,T>& rhs); */
    /* template <size_t N,typename T> bool operator> (const T& val, const vec<N,T>& rhs); */
    /* template <size_t N,typename T> bool operator> (const vec<N,T>& lhs, const T& val); */

    /* template <size_t N,typename T> bool operator<= (const vec<N,T>& lhs, const vec<N,T>& rhs); */
    /* template <size_t N,typename T> bool operator<= (const T& val, const vec<N,T>& rhs); */
    /* template <size_t N,typename T> bool operator<= (const vec<N,T>& lhs, const T& val); */

    /* template <size_t N,typename T> bool operator>= (const vec<N,T>& lhs, const vec<N,T>& rhs); */
    /* template <size_t N,typename T> bool operator>= (const T& val, const vec<N,T>& rhs); */
    /* template <size_t N,typename T> bool operator>= (const vec<N,T>& lhs, const T& val); */
}
