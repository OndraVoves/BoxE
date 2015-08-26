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

#include "../include/bvector3f.h"

#include <cmath>

#include "../include/bvector4f.h"

BOXE_NAMESPACE_BEGIN ( Math )

const BVector3f BVector3f::UP       (  0.0f,  1.0f,  0.0f );
const BVector3f BVector3f::DOWN     (  0.0f, -1.0f,  0.0f );
const BVector3f BVector3f::LEFT     ( -1.0f,  0.0f,  0.0f );
const BVector3f BVector3f::RIGHT    (  1.0f,  0.0f,  0.0f );
const BVector3f BVector3f::FORWARD  (  0.0f,  0.0f, -1.0f );
const BVector3f BVector3f::BACKWARD (  0.0f,  0.0f,  1.0f );

BVector3f::BVector3f() {
#ifdef __SSE__
    m128 = _mm_setzero_ps();
#else
    XYZ[0] = 0.0f;
    XYZ[1] = 0.0f;
    XYZ[2] = 0.0f;
#endif /* __SSE__ */
}

BVector3f::BVector3f ( const BVector3f &other ) {
#ifdef __SSE__
    m128 = other.m128;

#else
    XYZ[0] = other.XYZ[ 0 ];
    XYZ[1] = other.XYZ[ 1 ];
    XYZ[2] = other.XYZ[ 2 ];
#endif
}

BVector3f::BVector3f ( const float xyz ) {
#ifdef __SSE__
    m128 = _mm_set_ps ( 0.0f, xyz, xyz, xyz );
#else
    XYZ[0] = xyz;
    XYZ[1] = xyz;
    XYZ[2] = xyz;
#endif /* __SSE__ */

}

BVector3f::BVector3f ( const float x, const float y, const float z ) {
#ifdef __SSE__
    m128 = _mm_set_ps ( 0.0f, z, y, x );
#else
    XYZ[0] = x;
    XYZ[1] = y;
    XYZ[2] = z;
#endif /* __SSE__ */
}

BVector3f::BVector3f ( const BVector4f &vector ) {
#ifdef __SSE__
    m128 = vector.m128;
#else
    XYZ[0] = vector.XYZW[ 0 ];
    XYZ[1] = vector.XYZW[ 1 ];
    XYZ[2] = vector.XYZW[ 2 ];
#endif /* __SSE__ */
}

BVector3f &BVector3f::operator= ( const BVector3f &other ) {
#ifdef __SSE__
    m128 = other.m128;
#else
    XYZ[0] = other.XYZ[ 0 ];
    XYZ[1] = other.XYZ[ 1 ];
    XYZ[2] = other.XYZ[ 2 ];
#endif
    return *this;
}

BVector3f BVector3f::operator + ( const BVector3f &vector ) const {
#ifdef __SSE__
    return BVector3f ( _mm_add_ps ( m128, vector.m128 ) );
#else
    return BVector3f ( XYZ[0] + vector.XYZ[0],
                       XYZ[1] + vector.XYZ[1],
                       XYZ[2] + vector.XYZ[2] );
#endif /* __SSE__ */
}

BVector3f &BVector3f::operator += ( const BVector3f &vector ) {
#ifdef __SSE__
    m128 = _mm_add_ps ( m128, vector.m128 );
#else
    XYZ[ 0 ] += vector.XYZ[ 0 ];
    XYZ[ 1 ] += vector.XYZ[ 1 ];
    XYZ[ 2 ] += vector.XYZ[ 2 ];
#endif /* __SSE__ */

    return *this;
}

BVector3f BVector3f::operator - ( const BVector3f &vector ) const {
#ifdef __SSE__
    return BVector3f ( _mm_sub_ps ( m128, vector.m128 ) );
#else
    return BVector3f ( XYZ[0] - vector.XYZ[0],
                       XYZ[1] - vector.XYZ[1],
                       XYZ[2] - vector.XYZ[2] );
#endif /* __SSE__ */
}

BVector3f &BVector3f::operator -= ( const BVector3f &vector ) {
#ifdef __SSE__
    m128 = _mm_sub_ps ( m128, vector.m128 );
#else
    XYZ[ 0 ] -= vector.XYZ[ 0 ];
    XYZ[ 1 ] -= vector.XYZ[ 1 ];
    XYZ[ 2 ] -= vector.XYZ[ 2 ];
#endif /* __SSE__ */

    return *this;
}

BVector3f BVector3f::operator * ( const float scalar ) const {
#ifdef __SSE__
    return BVector3f ( _mm_mul_ps ( m128, _mm_set_ps1 ( scalar ) ) );
#else
    return BVector3f ( XYZ[0] * scalar,
                       XYZ[1] * scalar,
                       XYZ[2] * scalar );
#endif /* __SSE__ */
}

BVector3f &BVector3f::operator *= ( const float scalar ) {
#ifdef __SSE__
    m128 = _mm_mul_ps ( m128, _mm_set_ps1 ( scalar ) );
#else
    XYZ[ 0 ] *= scalar;
    XYZ[ 1 ] *= scalar;
    XYZ[ 2 ] *= scalar;
#endif /* __SSE__ */

    return *this;
}

BVector3f BVector3f::operator / ( const float scalar ) const {
#ifdef __SSE__
    return BVector3f ( _mm_div_ps ( m128, _mm_set_ps1 ( scalar ) ) );
#else
    return BVector3f ( XYZ[0] / scalar,
                       XYZ[1] / scalar,
                       XYZ[2] / scalar );
#endif /* __SSE__ */
}

BVector3f &BVector3f::operator /= ( const float scalar ) {
#ifdef __SSE__
    m128 = _mm_div_ps ( m128, _mm_set_ps1 ( scalar ) );
#else
    XYZ[ 0 ] /= scalar;
    XYZ[ 1 ] /= scalar;
    XYZ[ 2 ] /= scalar;
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

float BVector3f::lenghtSquared() const {
    float return_val;
#ifdef __SSE__
    __m128 a = _mm_mul_ps ( m128, m128 );
    a = _mm_hadd4_ps ( a );

    _mm_store_ss ( &return_val, a );
#else
    return_val =  XYZ[ 0 ] * XYZ[ 0 ];
    return_val += XYZ[ 1 ] * XYZ[ 1 ];
    return_val += XYZ[ 2 ] * XYZ[ 2 ];
#endif /* __SSE__ */

    return return_val;
}

float BVector3f::length() const {
    float return_val;
#ifdef __SSE__
    __m128 a = _mm_mul_ps ( m128, m128 );
    a = _mm_hadd4_ps ( a );
    a = _mm_sqrt_ss ( a );

    _mm_store_ss ( &return_val, a );

    return return_val;
#else
    return_val  = XYZ[ 0 ] * XYZ[ 0 ];
    return_val += XYZ[ 1 ] * XYZ[ 1 ];
    return_val += XYZ[ 2 ] * XYZ[ 2 ];

    return_val = sqrt ( return_val );

    return return_val;
#endif
}

void BVector3f::normalize() {
#ifdef __SSE__
    __m128 a = _mm_mul_ps ( m128, m128 );
    a = _mm_hadd4_ps ( a );
    a = _mm_sqrt_ss ( a );

    float len;
    _mm_store_ss ( &len, a );

    m128 = _mm_div_ps ( m128, _mm_set_ps1 ( len ) );
#else
    float div_coef = 1.0f / length();

    XYZ[ 0 ] *= div_coef;
    XYZ[ 1 ] *= div_coef;
    XYZ[ 2 ] *= div_coef;
#endif /* __SSE__ */
}

BVector3f BVector3f::normalized() const {
#ifdef __SSE__
    __m128 a = _mm_mul_ps ( m128, m128 );
    a = _mm_hadd4_ps ( a );
    a = _mm_sqrt_ss ( a );

    float len;
    _mm_store_ss ( &len, a );

    a = _mm_div_ps ( m128, _mm_set_ps1 ( len ) );

    return BVector3f ( a );
#else
    float div_coef = 1.0f / length();
    return BVector3f ( XYZ[ 0 ] * div_coef, XYZ[ 1 ] * div_coef, XYZ[ 2 ] * div_coef );
#endif /* __SSE__ */
}

float BVector3f::dotProduct ( const BVector3f &v1, const BVector3f &v2 ) {
    float dot;

#ifdef __SSE__
    __m128 a = _mm_mul_ps ( v1.m128, v2.m128 );
    a = _mm_hadd4_ps ( a );

    _mm_store_ss ( &dot, a );
#else
    dot  = v1.XYZ[ 0 ] * v2.XYZ[ 0 ];
    dot += v1.XYZ[ 1 ] * v2.XYZ[ 1 ];
    dot += v1.XYZ[ 2 ] * v2.XYZ[ 2 ];
#endif /* __SSE__ */

    return dot;
}

BVector3f BVector3f::crossProduct ( const BVector3f &v1, const BVector3f &v2 ) {
#ifdef __SSE__
    __m128 U1 = _mm_shuffle_ps ( v1.m128, v1.m128, _MM_SHUFFLE ( 3, 1, 0, 2 ) );
    __m128 V1 = _mm_shuffle_ps ( v2.m128, v2.m128, _MM_SHUFFLE ( 3, 0, 2, 1 ) );

    __m128 V2 = _mm_shuffle_ps ( v2.m128, v2.m128, _MM_SHUFFLE ( 3, 1, 0, 2 ) );
    __m128 U2 = _mm_shuffle_ps ( v1.m128, v1.m128, _MM_SHUFFLE ( 3, 0, 2, 1 ) );

    U1 = _mm_mul_ps ( U1, V1 );
    V1 = _mm_mul_ps ( V2, U2 );

    return BVector3f ( _mm_sub_ps ( V1, U1 ) );
#else
    BVector3f cross;

    cross.XYZ[ 0 ] = v1.XYZ[ 1 ] * v2.XYZ[ 2 ];
    cross.XYZ[ 1 ] = v1.XYZ[ 2 ] * v2.XYZ[ 0 ];
    cross.XYZ[ 2 ] = v1.XYZ[ 0 ] * v2.XYZ[ 1 ];

    cross.XYZ[ 0 ] -= v2.XYZ[ 1 ] * v1.XYZ[ 2 ];
    cross.XYZ[ 1 ] -= v2.XYZ[ 2 ] * v1.XYZ[ 0 ];
    cross.XYZ[ 2 ] -= v2.XYZ[ 0 ] * v1.XYZ[ 1 ];

    return cross;
#endif /* __SSE__ */
}

BVector3f BVector3f::reflection ( const BVector3f &dir, const BVector3f &normal ) {
#ifdef __SSE__
    __m128 a = _mm_set1_ps ( 2.0f * dotProduct ( normal, dir ) );

    return BVector3f ( _mm_sub_ps ( dir.m128, _mm_mul_ps ( normal.m128, a ) ) );
#else
    return BVector3f ( dir - ( normal * ( 2.0f * dotProduct ( normal, dir ) ) ) );
#endif /* __SSE__ */
}

BVector3f BVector3f::refraction ( const BVector3f &dir, const BVector3f &normal, float n1, float n2 ) {
    const float n = n1 / n2;
    const float cosI = dotProduct ( normal, dir );

    const float sinT2 = ( n * n ) * ( 1.0 - ( cosI * cosI ) );
    if ( sinT2 > 1.0f ) {
        return BVector3f();
    }

    return ( dir * n ) - ( normal * ( n + sqrt ( 1.0 - sinT2 ) ) );
}

BVector4f BVector3f::toVector4f() const {
    return BVector4f ( *this, 0.0f );
}

BOXE_NAMESPACE_END ( Math )
