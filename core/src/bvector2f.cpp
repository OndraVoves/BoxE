/*
    <one line to give the library's name and an idea of what it does.>
    Copyright (C) 2011  Ondra Voves <email>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/


#include "../include/bvector2f.h"

#include <cmath>

BOXE_NAMESPACE_BEGIN ( Math )

BVector2f::BVector2f() {
#ifdef __SSE__
    m128 = _mm_setzero_ps();
#else
    XY[0] = 0.0f;
    XY[1] = 0.0f;
#endif /* __SSE__ */
}

BVector2f::BVector2f ( const BVector2f &other ) {
#ifdef __SSE__
    m128 = other.m128;

#else
    XY[0] = other.XY[ 0 ];
    XY[1] = other.XY[ 1 ];
#endif
}

BVector2f::BVector2f ( const float xy ) {
#ifdef __SSE__
    m128 = _mm_set_ps ( 0.0f, 0.0f, xy, xy );
#else
    XY[0] = xy;
    XY[1] = xy;
#endif /* __SSE__ */

}

BVector2f::BVector2f ( const float x, const float y ) {
#ifdef __SSE__
    m128 = _mm_set_ps ( 0.0f, 0.0f, y, x );
#else
    XY[0] = x;
    XY[1] = y;
#endif /* __SSE__ */
}


BVector2f &BVector2f::operator= ( const BVector2f &other ) {
#ifdef __SSE__
    m128 = other.m128;
#else
    XY[0] = other.XY[ 0 ];
    XY[1] = other.XY[ 1 ];
#endif
    return *this;
}

BVector2f BVector2f::operator + ( const BVector2f &vector ) const {
#ifdef __SSE__
    return BVector2f ( _mm_add_ps ( m128, vector.m128 ) );
#else
    return BVector2f ( XY[0] + vector.XY[0],
                       XY[1] + vector.XY[1] );
#endif /* __SSE__ */
}

BVector2f &BVector2f::operator += ( const BVector2f &vector ) {
#ifdef __SSE__
    m128 = _mm_add_ps ( m128, vector.m128 );
#else
    XY[ 0 ] += vector.XY[ 0 ];
    XY[ 1 ] += vector.XY[ 1 ];
#endif /* __SSE__ */

    return *this;
}

BVector2f BVector2f::operator - ( const BVector2f &vector ) const {
#ifdef __SSE__
    return BVector2f ( _mm_sub_ps ( m128, vector.m128 ) );
#else
    return BVector2f ( XY[0] - vector.XY[0],
                       XY[1] - vector.XY[1] );
#endif /* __SSE__ */
}

BVector2f &BVector2f::operator -= ( const BVector2f &vector ) {
#ifdef __SSE__
    m128 = _mm_sub_ps ( m128, vector.m128 );
#else
    XY[ 0 ] -= vector.XY[ 0 ];
    XY[ 1 ] -= vector.XY[ 1 ];
#endif /* __SSE__ */

    return *this;
}

BVector2f BVector2f::operator * ( const float scalar ) const {
#ifdef __SSE__
    return BVector2f ( _mm_mul_ps ( m128, _mm_set_ps1 ( scalar ) ) );
#else
    return BVector2f ( XY[0] * scalar,
                       XY[1] * scalar );
#endif /* __SSE__ */
}

BVector2f &BVector2f::operator *= ( const float scalar ) {
#ifdef __SSE__
    m128 = _mm_mul_ps ( m128, _mm_set_ps1 ( scalar ) );
#else
    XY[ 0 ] *= scalar;
    XY[ 1 ] *= scalar;
#endif /* __SSE__ */

    return *this;
}

BVector2f BVector2f::operator / ( const float scalar ) const {
#ifdef __SSE__
    return BVector2f ( _mm_div_ps ( m128, _mm_set_ps1 ( scalar ) ) );
#else
    return BVector2f ( XY[0] / scalar,
                       XY[1] / scalar );
#endif /* __SSE__ */
}

BVector2f &BVector2f::operator /= ( const float scalar ) {
#ifdef __SSE__
    m128 = _mm_div_ps ( m128, _mm_set_ps1 ( scalar ) );
#else
    XY[ 0 ] /= scalar;
    XY[ 1 ] /= scalar;
#endif /* __SSE__ */

    return *this;
}

#ifdef __SSE__
inline __m128 _mm_hadd4_ps ( __m128 i ) {
    __m128   t = _mm_setzero_ps();
    t = _mm_movehl_ps ( t, i );
    i = _mm_add_ps ( i, t );
    t = _mm_shuffle_ps ( i, i, 0x55 );
    i = _mm_add_ps ( i, t );
    return i;
}
#endif

float BVector2f::lenghtSquared() const {
    float return_val;
#ifdef __SSE__
    __m128 a = _mm_mul_ps ( m128, m128 );
    a = _mm_hadd4_ps ( a );

    _mm_store_ss ( &return_val, a );
#else
    return_val =  XY[ 0 ] * XY[ 0 ];
    return_val += XY[ 1 ] * XY[ 1 ];
#endif /* __SSE__ */

    return return_val;
}

float BVector2f::length() const {
    float return_val;
#ifdef __SSE__
    __m128 a = _mm_mul_ps ( m128, m128 );
    a = _mm_hadd4_ps ( a );
    a = _mm_sqrt_ss ( a );

    _mm_store_ss ( &return_val, a );

    return return_val;
#else
    return_val  = XY[ 0 ] * XY[ 0 ];
    return_val += XY[ 1 ] * XY[ 1 ];

    return sqrt ( return_val );
#endif
}

void BVector2f::normalize() {
#ifdef __SSE__
    __m128 a = _mm_mul_ps ( m128, m128 );
    a = _mm_hadd4_ps ( a );
    a = _mm_sqrt_ss ( a );

    float len;
    _mm_store_ss ( &len, a );

    m128 = _mm_div_ps ( m128, _mm_set_ps1 ( len ) );
#else
    float div_coef = 1.0f / length();

    XY[ 0 ] *= div_coef;
    XY[ 1 ] *= div_coef;
#endif /* __SSE__ */
}

BVector2f BVector2f::normalized() const {
#ifdef __SSE__
    __m128 a = _mm_mul_ps ( m128, m128 );
    a = _mm_hadd4_ps ( a );
    a = _mm_sqrt_ss ( a );

    float len;
    _mm_store_ss ( &len, a );

    a = _mm_div_ps ( m128, _mm_set_ps1 ( len ) );

    return BVector2f ( a );
#else
    float div_coef = 1.0f / length();
    return BVector2f ( XY[ 0 ] * div_coef, XY[ 1 ] * div_coef );
#endif /* __SSE__ */
}

float BVector2f::dotProduct ( const BVector2f &v1, const BVector2f &v2 ) {
    float dot;

#ifdef __SSE__
    __m128 a = _mm_mul_ps ( v1.m128, v2.m128 );
    a = _mm_hadd4_ps ( a );

    _mm_store_ss ( &dot, a );
#else
    dot  = v1.XY[ 0 ] * v2.XY[ 0 ];
    dot += v1.XY[ 1 ] * v2.XY[ 1 ];
#endif /* __SSE__ */

    return dot;
}

BOXE_NAMESPACE_END ( Math )
