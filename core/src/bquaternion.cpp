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

#include "../include/bquaternion.h"

#include "../include/bvector3f.h"
#include "../include/bmatrix4x4f.h"
#include "../include/bgoniometry.h"

BOXE_NAMESPACE_BEGIN ( Math )

BQuaternion::BQuaternion( ) {
#ifdef __SSE__
    m128 = _mm_setzero_ps();
#else
    XYZW[0] = 0.0f;
    XYZW[1] = 0.0f;
    XYZW[2] = 0.0f;
    XYZW[3] = 0.0f;
#endif /* __SSE__ */
}

BQuaternion::BQuaternion ( const BQuaternion &other ) {
#ifdef __SSE__
    m128 = other.m128;
#else
    XYZW[0] = other.XYZW[ 0 ];
    XYZW[1] = other.XYZW[ 1 ];
    XYZW[2] = other.XYZW[ 2 ];
    XYZW[3] = other.XYZW[ 3 ];
#endif
}

BQuaternion::BQuaternion ( const float x, const float y, const float z, const float w ) {
#ifdef __SSE__
    m128 = _mm_set_ps ( w, z, y, x );
#else
    XYZW[0] = x;
    XYZW[1] = y;
    XYZW[2] = z;
    XYZW[3] = w;
#endif /* __SSE__ */
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

float BQuaternion::lenghtSquared() const {
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

float BQuaternion::length() const {
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

void BQuaternion::normalize() {
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

BQuaternion BQuaternion::normalized() const {
#ifdef __SSE__
    __m128 a = _mm_mul_ps ( m128, m128 );
    a = _mm_hadd4_ps ( a );
    a = _mm_sqrt_ss ( a );

    float len;
    _mm_store_ss ( &len, a );

    a = _mm_div_ps ( m128, _mm_set_ps1 ( len ) );

    return BQuaternion ( a );
#else
    float div_coef = 1.0f / length();
    return BQuaternion ( XYZW[ 0 ] * div_coef, XYZW[ 1 ] * div_coef, XYZW[ 2 ] * div_coef, XYZW[ 3 ] * div_coef );
#endif /* __SSE__ */
}

BQuaternion &BQuaternion::operator= ( const BQuaternion &other ) {
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

BQuaternion &BQuaternion::operator *= ( const BQuaternion &other ) {
    BVector3f v1 ( XYZW[0], XYZW[1], XYZW[2] );
    BVector3f v2 ( other.XYZW[0], other.XYZW[1], other.XYZW[2] );

    BVector3f v3 = BVector3f::crossProduct ( v1, v2 ) + ( v2 * XYZW[3] ) + ( v1 * other.XYZW[3] );

    XYZW[ 0 ] = v3.XYZ[ 0 ];
    XYZW[ 1 ] = v3.XYZ[ 1 ];
    XYZW[ 2 ] = v3.XYZ[ 2 ];

    XYZW[ 3 ] = ( XYZW[3] * other.XYZW[3] ) - BVector3f::dotProduct ( v1, v2 );

    return *this;
}

const BQuaternion operator* ( const BQuaternion &q1, const BQuaternion &q2 ) {
    BVector3f v1 ( q1.XYZW[0], q1.XYZW[1], q1.XYZW[2] );
    BVector3f v2 ( q2.XYZW[0], q2.XYZW[1], q2.XYZW[2] );

    BVector3f v3 = BVector3f::crossProduct ( v1, v2 ) + ( v2 * q1.XYZW[3] ) + ( v1 * q2.XYZW[3] );

    return BQuaternion ( v3.x(), v3.y(), v3.z(), ( q1.XYZW[3] * q2.XYZW[3] ) - BVector3f::dotProduct ( v1, v2 ) );
}

void BQuaternion::rotate ( const float x, const float y, const float z, const float angle  ) {
    const float half_angle = bDeg2Rad<float> ( angle * 0.5f );
    const float sin_a = bFastSin ( half_angle );

    operator*= ( BQuaternion (  x * sin_a, y * sin_a, z * sin_a, bFastCos ( half_angle ) ) );
}

BMatrix4x4f BQuaternion::toMatrix4x4() const {
    const float xx = XYZW[0] * XYZW[0];
    const float xy = XYZW[0] * XYZW[1];
    const float xz = XYZW[0] * XYZW[2];
    const float xw = XYZW[0] * XYZW[3];
    const float yy = XYZW[1] * XYZW[1];
    const float yz = XYZW[1] * XYZW[2];
    const float yw = XYZW[1] * XYZW[3];
    const float zz = XYZW[2] * XYZW[2];
    const float zw = XYZW[2] * XYZW[3];

    BMatrix4x4f m;
    m.Row1.setXYZW ( 1.0f - 2.0f * ( yy + zz ), 2.0f * ( xy + zw ), 2.0f * ( xz - yw ), 0.0f );
    m.Row2.setXYZW ( 2.0f * ( xy - zw ), 1.0f - 2.0f * ( xx + zz ), 2.0f * ( yz + xw ), 0.0f );
    m.Row3.setXYZW ( 2.0f * ( xz + yw ), 2.0f * ( yz - xw ), 1.0f - 2.0f * ( xx + yy ), 0.0f );
    m.Row4.setXYZW ( 0.0f, 0.0f, 0.0f, 1.0f );

    return m;
}

BOXE_NAMESPACE_END ( Math )
