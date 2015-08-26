/*
    <one line to give the library's name and an idea of what it does.>
    Copyright (C) <year>  <name of author>

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

#include "../include/bvector4f.h"

#include "../include/bvector3f.h"

#include <cmath>

BOXE_NAMESPACE_BEGIN ( Math )

const BVector4f BVector4f::UP       (  0.0f,  1.0f,  0.0f, 0.0f );
const BVector4f BVector4f::DOWN     (  0.0f, -1.0f,  0.0f, 0.0f );
const BVector4f BVector4f::LEFT     ( -1.0f,  0.0f,  0.0f, 0.0f );
const BVector4f BVector4f::RIGHT    (  1.0f,  0.0f,  0.0f, 0.0f );
const BVector4f BVector4f::FORWARD  (  0.0f,  0.0f, -1.0f, 0.0f );
const BVector4f BVector4f::BACKWARD (  0.0f,  0.0f,  1.0f, 0.0f  );

BVector4f::BVector4f() {
#ifdef __SSE__
    m128 = _mm_setzero_ps();
#else
    XYZW[0] = 0.0f;
    XYZW[1] = 0.0f;
    XYZW[2] = 0.0f;
    XYZW[3] = 0.0f;
#endif /* __SSE__ */
}

BVector4f::BVector4f ( const BVector4f &other ) {
#ifdef __SSE__
    m128 = other.m128;
#else
    XYZW[0] = other.XYZW[ 0 ];
    XYZW[1] = other.XYZW[ 1 ];
    XYZW[2] = other.XYZW[ 2 ];
    XYZW[3] = other.XYZW[ 3 ];
#endif
}

BVector4f::BVector4f ( const float xyzw ) {
#ifdef __SSE__
    m128 = _mm_set_ps1 ( xyzw );
#else
    XYZW[0] = xyzw;
    XYZW[1] = xyzw;
    XYZW[2] = xyzw;
    XYZW[3] = xyzw;
#endif /* __SSE__ */

}

BVector4f::BVector4f ( const float x, const float y, const float z, const float w ) {
#ifdef __SSE__
    m128 = _mm_set_ps ( w, z, y, x );
#else
    XYZW[0] = x;
    XYZW[1] = y;
    XYZW[2] = z;
    XYZW[3] = w;
#endif /* __SSE__ */
}

BVector4f::BVector4f ( const BVector3f &vector, const float w ) {
#ifdef __SSE__
    m128 = _mm_set_ps ( w, vector.XYZ[2], vector.XYZ[1], vector.XYZ[0] );
#else
    XYZW[0] = vector.XYZ[0];
    XYZW[1] = vector.XYZ[1];
    XYZW[2] = vector.XYZ[2];
    XYZW[3] = w;
#endif /* __SSE__ */
}

BVector4f &BVector4f::operator= ( const BVector4f &other ) {
#ifdef __SSE__
    m128 = other.m128;
#else
    XYZW[0] = other.XYZW[ 0 ];
    XYZW[1] = other.XYZW[ 1 ];
    XYZW[2] = other.XYZW[ 2 ];
    XYZW[3] = other.XYZW[ 3 ];
#endif

    return *this;
}

BVector4f BVector4f::operator + ( const BVector4f &vector ) const {
#ifdef __SSE__
    return BVector4f ( _mm_add_ps ( m128, vector.m128 ) );
#else
    return BVector4f ( XYZW[0] + vector.XYZW[0],
                       XYZW[1] + vector.XYZW[1],
                       XYZW[2] + vector.XYZW[2],
                       XYZW[3] + vector.XYZW[3] );
#endif /* __SSE__ */
}

BVector4f &BVector4f::operator += ( const BVector4f &vector ) {
#ifdef __SSE__
    m128 = _mm_add_ps ( m128, vector.m128 );
#else
    XYZW[ 0 ] += vector.XYZW[ 0 ];
    XYZW[ 1 ] += vector.XYZW[ 1 ];
    XYZW[ 2 ] += vector.XYZW[ 2 ];
    XYZW[ 3 ] += vector.XYZW[ 3 ];
#endif /* __SSE__ */

    return *this;
}

BVector4f BVector4f::operator - ( const BVector4f &vector ) const {
#ifdef __SSE__
    return BVector4f ( _mm_sub_ps ( m128, vector.m128 ) );
#else
    return BVector4f ( XYZW[0] - vector.XYZW[0],
                       XYZW[1] - vector.XYZW[1],
                       XYZW[2] - vector.XYZW[2],
                       XYZW[3] - vector.XYZW[3] );
#endif /* __SSE__ */
}

BVector4f &BVector4f::operator -= ( const BVector4f &vector ) {
#ifdef __SSE__
    m128 = _mm_sub_ps ( m128, vector.m128 );
#else
    XYZW[ 0 ] -= vector.XYZW[ 0 ];
    XYZW[ 1 ] -= vector.XYZW[ 1 ];
    XYZW[ 2 ] -= vector.XYZW[ 2 ];
    XYZW[ 3 ] -= vector.XYZW[ 3 ];
#endif /* __SSE__ */

    return *this;
}

BVector4f BVector4f::operator * ( const float scalar ) const {
#ifdef __SSE__
    return BVector4f ( _mm_mul_ps ( m128, _mm_set_ps1 ( scalar ) ) );
#else
    return BVector4f ( XYZW[0] * scalar,
                       XYZW[1] * scalar,
                       XYZW[2] * scalar,
                       XYZW[3] * scalar );
#endif /* __SSE__ */
}

BVector4f &BVector4f::operator *= ( const float scalar ) {
#ifdef __SSE__
    m128 = _mm_mul_ps ( m128, _mm_set_ps1 ( scalar ) );
#else
    XYZW[ 0 ] *= scalar;
    XYZW[ 1 ] *= scalar;
    XYZW[ 2 ] *= scalar;
    XYZW[ 3 ] *= scalar;
#endif /* __SSE__ */

    return *this;
}

BVector4f BVector4f::operator / ( const float scalar ) const {
#ifdef __SSE__
    return BVector4f ( _mm_div_ps ( m128, _mm_set_ps1 ( scalar ) ) );
#else
    return BVector4f ( XYZW[0] / scalar,
                       XYZW[1] / scalar,
                       XYZW[2] / scalar,
                       XYZW[3] / scalar );
#endif /* __SSE__ */
}

BVector4f &BVector4f::operator /= ( const float scalar ) {
#ifdef __SSE__
    m128 = _mm_div_ps ( m128, _mm_set_ps1 ( scalar ) );
#else
    XYZW[ 0 ] /= scalar;
    XYZW[ 1 ] /= scalar;
    XYZW[ 2 ] /= scalar;
    XYZW[ 3 ] /= scalar;
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
#endif /* __SSE__ */

float BVector4f::lenghtSquared() const {
    float return_val;
#ifdef __SSE__
    __m128 a = _mm_mul_ps ( m128, m128 );
    a = _mm_hadd4_ps ( a );

    _mm_store_ss ( &return_val, a );
#else
    return_val =  XYZW[ 0 ] * XYZW[ 0 ];
    return_val += XYZW[ 1 ] * XYZW[ 1 ];
    return_val += XYZW[ 2 ] * XYZW[ 2 ];
    return_val += XYZW[ 3 ] * XYZW[ 3 ];
#endif /* __SSE__ */

    return return_val;
}

float BVector4f::length() const {
    float return_val;
#ifdef __SSE__
    __m128 a = _mm_mul_ps ( m128, m128 );
    a = _mm_hadd4_ps ( a );
    a = _mm_sqrt_ss ( a );

    _mm_store_ss ( &return_val, a );

    return return_val;
#else
    return_val  = XYZW[ 0 ] * XYZW[ 0 ];
    return_val += XYZW[ 1 ] * XYZW[ 1 ];
    return_val += XYZW[ 2 ] * XYZW[ 2 ];
    return_val += XYZW[ 3 ] * XYZW[ 3 ];

    return sqrt ( return_val );
#endif
}

void BVector4f::normalize() {
#ifdef __SSE__
    __m128 a = _mm_mul_ps ( m128, m128 );
    a = _mm_hadd4_ps ( a );
    a = _mm_sqrt_ss ( a );

    float len;
    _mm_store_ss ( &len, a );

    m128 = _mm_div_ps ( m128, _mm_set_ps1 ( len ) );
#else
    float div_coef = 1.0f / length();

    XYZW[ 0 ] *= div_coef;
    XYZW[ 1 ] *= div_coef;
    XYZW[ 2 ] *= div_coef;
    XYZW[ 3 ] *= div_coef;
#endif /* __SSE__ */
}

BVector4f BVector4f::normalized() const {
#ifdef __SSE__
    __m128 a = _mm_mul_ps ( m128, m128 );
    a = _mm_hadd4_ps ( a );
    a = _mm_sqrt_ss ( a );

    float len;
    _mm_store_ss ( &len, a );

    a = _mm_div_ps ( m128, _mm_set_ps1 ( len ) );

    return BVector4f ( a );
#else
    float div_coef = 1.0f / length();
    return BVector4f ( XYZW[ 0 ] * div_coef, XYZW[ 1 ] * div_coef, XYZW[ 2 ] * div_coef, XYZW[ 3 ] * div_coef );
#endif /* __SSE__ */
}

float BVector4f::dotProduct ( const BVector4f &v1, const BVector4f &v2 ) {
    float dot;

#ifdef __SSE__
    __m128 a = _mm_mul_ps ( v1.m128, v2.m128 );
    a = _mm_hadd4_ps ( a );

    _mm_store_ss ( &dot, a );
#else
    dot  = v1.XYZW[ 0 ] * v2.XYZW[ 0 ];
    dot += v1.XYZW[ 1 ] * v2.XYZW[ 1 ];
    dot += v1.XYZW[ 2 ] * v2.XYZW[ 2 ];
    dot += v1.XYZW[ 3 ] * v2.XYZW[ 3 ];
#endif /* __SSE__ */

    return dot;
}

BVector3f BVector4f::toVector3f() const {
    return BVector3f ( *this );
}

BOXE_NAMESPACE_END ( Math )
