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
#pragma once
#include <iostream>
#include <initializer_list>
#include <type_traits>
#include <complex>
#include <cmath>

namespace Vec {
    template<typename S> struct is_complex : std::false_type {};
    template<typename S> struct is_complex<std::complex<S>> : std::true_type {};

    // definition
    template <size_t N, typename T = double>
    class vec {
        static_assert(N > 0, "vec may not be zero-dimensional");
        private:
            T data[N];
        public:
            // assignment operator
            template <typename T2,
                     typename = typename std::enable_if<
                         std::is_convertible<T2, T>::value, T2>::type>
            vec& operator=(const vec<N, T2>& x) {
                for (size_t i = 0; i < N; ++i)
                    data[i] = x[i];
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

            template <typename T2,
                     typename = typename std::enable_if<
                         std::is_convertible<T2, T>::value, T2>::type>
            vec(const vec<N, T2>& x) {
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

            // unary sign operators
            vec operator+() const {
                return vec(*this);
            }

            vec operator-() const {
                vec res;
                for (size_t i = 0; i < N; ++i)
                    res.data[i] = -data[i];
                return res;
            }

            template <typename..., typename S = T>
            typename std::enable_if<std::is_integral<S>::value, vec&>::type
            operator%= (const vec& rhs) {
                for (size_t i = 0; i < N; ++i)
                    data[i] %= rhs.data[i];
            }

            template <typename..., typename S = T>
            typename std::enable_if<std::is_floating_point<S>::value,vec&>::type
            operator%= (const vec& rhs) {
                for (size_t i = 0; i < N; ++i)
                    data[i] = std::fmod(data[i], rhs.data[i]);
            }

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

            template <typename..., typename S = T>
            typename std::enable_if<std::is_integral<S>::value, vec&>::type
            operator%= (const T& val) {
                for (size_t i = 0; i < N; ++i)
                    data[i] %= val;
            }

            template <typename..., typename S = T>
            typename std::enable_if<std::is_floating_point<S>::value,vec&>::type
            operator%= (const T& val) {
                for (size_t i = 0; i < N; ++i)
                    data[i] = std::fmod(data[i], val);
            }

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

            // friends
            template <size_t N_, typename A, typename B>
            friend bool operator== (const vec<N_,A>&, const vec<N_,B>&);

            template <size_t N_, typename A, typename B, typename C>
            friend typename std::enable_if<std::is_arithmetic<A>::value,C>::type
            operator* (const vec<N_,A>&, const vec<N_,B>&);

            template <size_t N_, typename A, typename B, typename C>
            friend typename std::enable_if<is_complex<A>::value,C>::type
            operator* (const vec<N_,A>&, const vec<N_,B>&);

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
    template <size_t N, typename A, typename B, typename C = decltype(A()*B())>
    typename std::enable_if<std::is_arithmetic<A>::value, C>::type
    operator*(const vec<N,A>& lhs, const vec<N,B>& rhs) {
        C sum;
        for (size_t i = 0; i < N; ++i)
            sum += lhs.data[i] * rhs.data[i];
        return sum;
    }

    template <size_t N, typename A, typename B, typename C = decltype(A()*B())>
    typename std::enable_if<is_complex<A>::value, C>::type
    operator*(const vec<N,A>& lhs, const vec<N,B>& rhs) {
        C sum;
        for (size_t i = 0; i < N; ++i)
            sum += conj(lhs.data[i]) * rhs.data[i];
        return sum;
    }


    // cross product
    template <typename A, typename B, typename C = decltype(A()*B())>
    typename std::enable_if<std::is_arithmetic<A>::value, vec<3,C>>::type
    cross(const vec<3,A>& lhs, const vec<3,B>& rhs) {
        return {lhs[1] * rhs[2] - lhs[2] * rhs[1],
                lhs[2] * rhs[0] - lhs[0] * rhs[2],
                lhs[0] * rhs[1] - lhs[1] * rhs[0]};
    }

    template <typename A, typename B, typename C = decltype(A()*B())>
    typename std::enable_if<is_complex<A>::value, vec<3,C>>::type
    cross(const vec<3,A>& lhs, const vec<3,B>& rhs) {
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
    template <size_t N, typename T, typename S, typename C = decltype(S()*T())>
    vec<N,C> operator* (const S& val, const vec<N,T>& rhs) {
        vec<N,C> res(rhs);
        res *= val;
        return res;
    }

    template <size_t N, typename T, typename S, typename C = decltype(S()*T())>
    vec<N,C> operator* (const vec<N,T>& lhs, const S& val) {
        vec<N,C> res(lhs);
        res *= val;
        return res;
    }

    template <size_t N, typename T, typename S, typename C = decltype(S()*T())>
    vec<N,C> operator/ (const vec<N,T>& lhs, const S& val) {
        vec<N,C> res(lhs);
        res /= val;
        return res;
    }


    // modulo operator
    template <size_t N, typename T>
    vec<N,T> operator% (const vec<N,T>& lhs, const vec<N,T>& rhs) {
        vec<N,T> res(lhs);
        res %= rhs;
        return res;
    }

    template <size_t N, typename T>
    vec<N,T> operator% (const vec<N,T>& lhs, const T& val) {
        vec<N,T> res(lhs);
        res %= val;
        return res;
    }


    // addition & subtraction operators
    template <size_t N, typename A, typename B, typename C = decltype(A()+B())>
    vec<N,C> operator+ (const vec<N,A>& lhs, const vec<N,B>& rhs) {
        vec<N,C> res(lhs);
        res += rhs;
        return res;
    }

    template <size_t N, typename A, typename B, typename C = decltype(A()-B())>
    vec<N,C> operator- (const vec<N,A>& lhs, const vec<N,B>& rhs) {
        vec<N,C> res(lhs);
        res -= rhs;
        return res;
    }


    // (in)equality operators
    template <size_t N, typename A, typename B>
    bool operator== (const vec<N,A>& lhs, const vec<N,B>& rhs) {
        for (size_t i = 0; i < N; ++i)
            if (lhs.data[i] != rhs.data[i])
                return false;
        return true;
    }

    template <size_t N, typename A, typename B>
    bool operator!= (const vec<N,A>& lhs, const vec<N,B>& rhs) {
        return !(lhs == rhs);
    }


    // stream operators
    template <size_t N, typename T>
    std::ostream& operator<< (std::ostream& os, const vec<N,T>& rhs) {
        os << "(" << rhs[0];
        for (size_t i = 1; i < N; ++i)
            os << ", " << rhs[i];
        os << ")";
        return os;
    }
}
