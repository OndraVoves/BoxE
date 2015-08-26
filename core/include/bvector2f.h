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


#ifndef BVECTOR2F_H
#define BVECTOR2F_H

#include "../../core/include/BGlobal"

//#include <immintrin.h>

#undef __SSE__

BOXE_NAMESPACE_BEGIN ( Math )

class BVector2f {
    public:
        /*!
         * Create zero vector
         */
        BVector2f();

        /*!
         * Create vector from other vector.
         * \param other Reference to other vector.
         */
        BVector2f ( const BVector2f &other );

        /*!
         * Create vector with X = Y = xy.
         * \param xy xy.
         */
        BVector2f ( const float xy );

        /*!
         * Create vector.
         * \param x X.
         * \param y Y.
         */
        BVector2f ( const float x, const float y );

        //BVector2f ( const BVector4f &vector );

        BVector2f &operator= ( const BVector2f &other );

        /*!
         * V = this + vector.
         * \param vector Vector.
         * \return Final vector.
         */
        BVector2f operator + ( const BVector2f &vector ) const;

        /*!
         * This += v.
         * \param vector Vector.
         * \return This vector.
         */
        BVector2f &operator += ( const BVector2f &vector );

        /*!
         * V = this - vector.
         * \param vector Vector.
         * \return Final vector.
         */
        BVector2f operator - ( const BVector2f &vector ) const;

        /*!
         * Get inverse vector.
         * \param vector Vector.
         * \return inverse vector.
         */
        friend inline const BVector2f operator- ( const BVector2f &vector );

        /*!
         * This -= v.
         * \param vector Vector.
         * \return This vector.
         */
        BVector2f &operator -= ( const BVector2f &vector );

        /*!
         * V = this * scalar.
         * \param scalar Vector.
         * \return Final vector.
         */
        BVector2f operator * ( const float scalar ) const;

        /*!
         * V *= scalar.
         * \param scalar Vector.
         * \return This vector.
         */
        BVector2f &operator *= ( const float scalar );

        /*!
         * V = this / scalar.
         * \param scalar Vector.
         * \return Final vector.
         */
        BVector2f operator / ( const float scalar ) const;

        /*!
         * V /= scalar.
         * \param scalar Vector.
         * \return This vector.
         */
        BVector2f &operator /= ( const float scalar );

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

        inline void setXY ( const float x, const float y );

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
        BVector2f normalized() const;

        /*!
         * Dot product.
         * \param v1 Vector 1.
         * \param v2 Vector 2.
         * \return Dot product.
         */
        static float dotProduct ( const BVector2f &v1, const BVector2f &v2 );


        friend inline bool bFuzzyCompare ( const BVector2f &v1, const BVector2f &v2 );

        //BVector4f toVector4f() const;
    private:

#ifdef __SSE__
        B_ALIGN_16 union {
            __m128 m128;  //!< For SSE.
            float XY[4]; //!< XY component.
        };

        BVector2f ( __m128 m ) : m128 ( m ) {

        }
#else
        float XY[2]; //!< XY component.
#endif

};

inline void BVector2f::x ( const float x ) {
    XY[0] = x;
}

inline void BVector2f::y ( const float y ) {
    XY[1] = y;
}

inline void BVector2f::setXY ( const float x, const float y ) {
    XY[ 0 ] = x;
    XY[ 1 ] = y;
}

inline float BVector2f:: x() const {
    return XY[0];
}

inline float BVector2f::y() const {
    return XY[1];
}

inline bool BVector2f::isNull() const {
    return ( Core::bFuzzyCompare ( XY[0], 0.0f ) &&
             Core::bFuzzyCompare ( XY[1], 0.0f )  );
}

inline const BVector2f operator- ( const BVector2f &vector ) {
    return ( vector * -1.0f );
}

inline bool bFuzzyCompare ( const BVector2f &v1, const BVector2f &v2 ) {
    return ( Core::bFuzzyCompare ( v1.XY[0], v2.XY[0] ) &&
             Core::bFuzzyCompare ( v1.XY[1], v2.XY[1] ) );

}

BOXE_NAMESPACE_END ( Math )

#endif // BVECTOR2F_H
