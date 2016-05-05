#pragma once
#include <initializer_list>
#include <type_traits>
#include <complex>
#include <cmath>

namespace shortvec {
    template<typename S> struct is_complex : std::false_type {};
    template<typename S> struct is_complex<std::complex<S>> : std::true_type {};

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

            // dot product
            template <typename..., typename S = T>
            typename std::enable_if<std::is_arithmetic<S>::value, S>::type
            operator*(const vec<N,T>& rhs) const {
                T sum;
                for (size_t i = 0; i < N; ++i)
                    sum += data[i] * rhs.data[i];
                return sum;
            }

            template <typename..., typename S = T>
            typename std::enable_if<is_complex<S>::value, S>::type
            operator*(const vec<N,T>& rhs) const {
                T sum;
                for (size_t i = 0; i < N; ++i)
                    sum += conj(data[i]) * rhs.data[i];
                return sum;
            }

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
    };

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


    /* template <size_t N, typename T> vec<N,T> operator== (const vec<N,T>& lhs, const vec<N,T>& rhs); */

    /* template <size_t N, typename T> vec<N,T> operator!= (const vec<N,T>& lhs, const vec<N,T>& rhs); */

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
