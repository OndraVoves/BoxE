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

#ifndef BVECTOR4F_H
#define BVECTOR4F_H


#include "../../core/include/BGlobal"

//#include <immintrin.h>
#undef __SSE__

BOXE_NAMESPACE_BEGIN ( Math )

class BVector3f;
class BMatrix4x4f;

class BVector4f {
    public:
        /*!
         * Up vector ( 0, 1, 0 ).
         */
        static const BVector4f UP;

        /*!
         * Down vector ( 0, -1, 0 ).
         */
        static const BVector4f DOWN;

        /*!
         * Left vector ( -1, 0, 0 ).
         */
        static const BVector4f LEFT;

        /*!
         * Right vector ( 1, 0, 0 ).
         */
        static const BVector4f RIGHT;

        /*!
         * Forward vector ( 0, 0, -1 ).
         */
        static const BVector4f FORWARD;

        /*!
         * Backward vector ( 0, 0, 1 ).
         */
        static const BVector4f BACKWARD;

    public:
        /*!
         * Create zero vector
         */
        BVector4f();

        /*!
         * Create vector from other vector.
         * \param other Reference to other vector.
         */
        BVector4f ( const BVector4f &other );

        /*!
         * Create vector with X = Y = Z = W = xyzw.
         * \param xyz xyzw.
         */
        BVector4f ( const float xyzw );

        /*!
         * Create vector.
         * \param x X.
         * \param y Y.
         * \param z Z.
         * \param w W.
         */
        BVector4f ( const float x, const float y, const float z, const float w );

        BVector4f ( const BVector3f &vector, const float w );

        BVector4f &operator= ( const BVector4f &other );

        /*!
         * V = this + vector.
         * \param vector Vector.
         * \return Final vector.
         */
        BVector4f operator + ( const BVector4f &vector ) const;

        /*!
         * This += v.
         * \param vector Vector.
         * \return This vector.
         */
        BVector4f &operator += ( const BVector4f &vector );


        /*!
         * V = this - vector.
         * \param vector Vector.
         * \return Final vector.
         */
        BVector4f operator - ( const BVector4f &vector ) const;

        friend inline const BVector4f operator - ( const BVector4f &vector );

        /*!
         * This -= v.
         * \param vector Vector.
         * \return This vector.
         */
        BVector4f &operator -= ( const BVector4f &vector );

        /*!
         * V = this * scalar.
         * \param scalar Vector.
         * \return Final vector.
         */
        BVector4f operator * ( const float scalar ) const;

        /*!
         * V *= scalar.
         * \param scalar Vector.
         * \return This vector.
         */
        BVector4f &operator *= ( const float scalar );

        /*!
         * V = this / scalar.
         * \param scalar Vector.
         * \return Final vector.
         */
        BVector4f operator / ( const float scalar ) const;

        /*!
         * V /= scalar.
         * \param scalar Vector.
         * \return This vector.
         */
        BVector4f &operator /= ( const float scalar );

        inline bool isNull() const;

        /*!
         * Set x component.
         * \param x X component.
         */
        inline void x ( const float x );

        /*!
         * Set y component.
         * \param y Y component.
         */
        inline void y ( const float y );

        /*!
         * Set z component.
         * \param z Z component.
         */
        inline void z ( const float z );

        /*!
         * Set w component.
         * \param w W component.
         */
        inline void w ( const float w );

        inline void setXYZW ( const float x, const float y, const float z, const float w );

        /*!
         * Get x component.
         * \return X component.
         */
        inline float x() const;

        /*!
         * Get y component.
         * \return Y component.
         */
        inline float y() const;

        /*!
         * Get z component.
         * \return Z component.
         */
        inline float z() const;

        /*!
         * Get w component.
         * \return W component.
         */
        inline float w() const;

        /*!
         * Squared length
         * \return Squared length.
         */
        float lenghtSquared() const;

        /*!
         * Vector length.
         * \return Vector len.
         */
        float length() const;

        /*!
         * Normalize me.
         */
        void normalize();

        /*!
         * Return this vector as unit vector.
         * \return this vector as unit vector.
         */
        BVector4f normalized() const;

        /*!
         * Dot product.
         * \param v1 Vector 1.
         * \param v2 Vector 2.
         * \return Dot product.
         */
        static float dotProduct ( const BVector4f &v1, const BVector4f &v2 );

        inline friend bool bFuzzyCompare ( const BVector4f &v1, const BVector4f &v2 );

        BVector3f toVector3f() const;
    private:

#ifdef __SSE__
        B_ALIGN_16 union {
            __m128 m128;  //!< For SSE.
            float XYZW[4]; //!< XYZW component.
        };

        BVector4f ( __m128 m ) : m128 ( m ) {
        }
#else
        float XYZW[4]; //!< XYZW component.
#endif

    private:
        friend class BVector3f;
        friend class BMatrix4x4f;
};

inline bool BVector4f::isNull() const {
    return ( Core::bFuzzyCompare ( XYZW[0], 0.0f ) &&
             Core::bFuzzyCompare ( XYZW[1], 0.0f ) &&
             Core::bFuzzyCompare ( XYZW[2], 0.0f ) &&
             Core::bFuzzyCompare ( XYZW[3], 0.0f ) );
}


inline void BVector4f::x ( const float x ) {
    XYZW[0] = x;
}

inline void BVector4f::y ( const float y ) {
    XYZW[1] = y;
}

inline void BVector4f::z ( const float z ) {
    XYZW[2] = z;
}


inline void BVector4f::w ( const float w ) {
    XYZW[3] = w;
}

inline void BVector4f::setXYZW ( const float x, const float y, const float z, const float w ) {
    XYZW[ 0 ] = x;
    XYZW[ 1 ] = y;
    XYZW[ 2 ] = z;
    XYZW[ 3 ] = w;
}

inline float BVector4f::x() const {
    return XYZW[0];
}

inline float BVector4f::y() const {
    return XYZW[1];
}

inline float BVector4f::z() const {
    return XYZW[2];
}

inline float BVector4f::w() const {
    return XYZW[3];
}

inline const BVector4f operator - ( const BVector4f &vector ) {
    return ( vector * -1.0f );
}

inline bool bFuzzyCompare ( const BVector4f &v1, const BVector4f &v2 ) {
    return ( Core::bFuzzyCompare ( v1.XYZW[0], v2.XYZW[0] ) &&
             Core::bFuzzyCompare ( v1.XYZW[1], v2.XYZW[1] ) &&
             Core::bFuzzyCompare ( v1.XYZW[2], v2.XYZW[2] ) &&
             Core::bFuzzyCompare ( v1.XYZW[3], v2.XYZW[3] ) );
}

BOXE_NAMESPACE_END ( Math )
#endif // BVECTOR4F_H
