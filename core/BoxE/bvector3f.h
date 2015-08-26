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

#ifndef BVECTOR3F_H
#define BVECTOR3F_H

#include "../../core/include/BGlobal"

//#include <immintrin.h>

#undef __SSE__

BOXE_NAMESPACE_BEGIN ( Math )

class BVector4f;
class BQuaternion;

/*!
 * Mathematic 3 component vector.
 */
class BVector3f {
    public:
        /*!
         * Up vector ( 0, 1, 0 ).
         */
        static const BVector3f UP;

        /*!
         * Down vector ( 0, -1, 0 ).
         */
        static const BVector3f DOWN;

        /*!
         * Left vector ( -1, 0, 0 ).
         */
        static const BVector3f LEFT;

        /*!
         * Right vector ( 1, 0, 0 ).
         */
        static const BVector3f RIGHT;

        /*!
         * Forward vector ( 0, 0, -1 ).
         */
        static const BVector3f FORWARD;

        /*!
         * Backward vector ( 0, 0, 1 ).
         */
        static const BVector3f BACKWARD;

    public:
        /*!
         * Create zero vector
         */
        BVector3f();

        /*!
         * Create vector from other vector.
         * \param other Reference to other vector.
         */
        BVector3f ( const BVector3f &other );

        /*!
         * Create vector with X = Y = Z = xyz.
         * \param xyz xyz.
         */
        BVector3f ( const float xyz );

        /*!
         * Create vector.
         * \param x X.
         * \param y Y.
         * \param z Z.
         */
        BVector3f ( const float x, const float y, const float z );

        BVector3f ( const BVector4f &vector );

        BVector3f &operator= ( const BVector3f &other );

        /*!
         * V = this + vector.
         * \param vector Vector.
         * \return Final vector.
         */
        BVector3f operator + ( const BVector3f &vector ) const;

        /*!
         * This += v.
         * \param vector Vector.
         * \return This vector.
         */
        BVector3f &operator += ( const BVector3f &vector );

        /*!
         * V = this - vector.
         * \param vector Vector.
         * \return Final vector.
         */
        BVector3f operator - ( const BVector3f &vector ) const;

        /*!
         * Get inverse vector.
         * \param vector Vector.
         * \return inverse vector.
         */
        friend inline const BVector3f operator- ( const BVector3f &vector );

        /*!
         * This -= v.
         * \param vector Vector.
         * \return This vector.
         */
        BVector3f &operator -= ( const BVector3f &vector );

        /*!
         * V = this * scalar.
         * \param scalar Vector.
         * \return Final vector.
         */
        BVector3f operator * ( const float scalar ) const;

        /*!
         * V *= scalar.
         * \param scalar Vector.
         * \return This vector.
         */
        BVector3f &operator *= ( const float scalar );

        /*!
         * V = this / scalar.
         * \param scalar Vector.
         * \return Final vector.
         */
        BVector3f operator / ( const float scalar ) const;

        /*!
         * V /= scalar.
         * \param scalar Vector.
         * \return This vector.
         */
        BVector3f &operator /= ( const float scalar );

        /*!
         * Is vector null?
         * \return True if vector is null, else return false.
         */
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

        inline void setXYZ ( const float x, const float y, const float z );

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
        BVector3f normalized() const;

        /*!
         * Dot product.
         * \param v1 Vector 1.
         * \param v2 Vector 2.
         * \return Dot product.
         */
        static float dotProduct ( const BVector3f &v1, const BVector3f &v2 );

        /*!
         * Vector cross product.
         * \param v1 Vector1.inclu
         * \param v2 Vector2.
         * \return Cross product.
         */
        static BVector3f crossProduct ( const BVector3f &v1, const BVector3f &v2 );

        static BVector3f reflection ( const BVector3f &dir, const BVector3f &normal );
        static BVector3f refraction ( const BVector3f &dir, const BVector3f &normal, float n1, float n2 );

        friend inline bool bFuzzyCompare ( const BVector3f &v1, const BVector3f &v2 );

        BVector4f toVector4f() const;
    private:

#ifdef __SSE__
        B_ALIGN_16 union {
            __m128 m128;  //!< For SSE.
            float XYZ[4]; //!< XYZ component.
        };

        BVector3f ( __m128 m ) : m128 ( m ) {

        }
#else
        float XYZ[3]; //!< XYZ component.
#endif

    private:
        friend class BVector4f;
        friend class BQuaternion;
};

inline void BVector3f::x ( const float x ) {
    XYZ[0] = x;
}

inline void BVector3f::y ( const float y ) {
    XYZ[1] = y;
}

inline void BVector3f::z ( const float z ) {
    XYZ[2] = z;
}

inline void BVector3f::setXYZ ( const float x, const float y, const float z ) {
    XYZ[ 0 ] = x;
    XYZ[ 1 ] = y;
    XYZ[ 2 ] = z;
}

inline float BVector3f:: x() const {
    return XYZ[0];
}

inline float BVector3f::y() const {
    return XYZ[1];
}


inline float BVector3f::z() const {
    return XYZ[2];
}

inline bool BVector3f::isNull() const {
    return ( Core::bFuzzyCompare ( XYZ[0], 0.0f ) &&
             Core::bFuzzyCompare ( XYZ[1], 0.0f ) &&
             Core::bFuzzyCompare ( XYZ[2], 0.0f ) );
}

inline const BVector3f operator- ( const BVector3f &vector ) {
    return ( vector * -1.0f );
}

inline bool bFuzzyCompare ( const BVector3f &v1, const BVector3f &v2 ) {
    return ( Core::bFuzzyCompare ( v1.XYZ[0], v2.XYZ[0] ) &&
             Core::bFuzzyCompare ( v1.XYZ[1], v2.XYZ[1] ) &&
             Core::bFuzzyCompare ( v1.XYZ[2], v2.XYZ[2] ) );

}


BOXE_NAMESPACE_END ( Math )

#endif // BVECTOR3F_H
