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

#ifndef BQUATERNION_H
#define BQUATERNION_H

#include "../../core/include/BGlobal"

//#include <immintrin.h>

BOXE_NAMESPACE_BEGIN ( Math )

class BMatrix4x4f;

class BQuaternion {
    public:
        BQuaternion();
        BQuaternion ( const BQuaternion &other );
        BQuaternion ( const float x, const float y, const float z, const float w );

        inline bool isNull() const;

        BQuaternion &operator= ( const BQuaternion &other );
        BQuaternion &operator *= ( const BQuaternion &other );

        friend const BQuaternion operator* ( const BQuaternion &q1, const BQuaternion &q2 );

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

        BQuaternion normalized() const;

        void rotate ( const float x, const float y, const float z, const float angle  );

        BMatrix4x4f toMatrix4x4() const;

    private:
#ifdef __SSE__
        B_ALIGN_16 union {
            __m128 m128;  //!< For SSE.
            float XYZW[4]; //!< XYZW component.
        };

        BQuaternion ( __m128 m ) : m128 ( m ) {
        }
#else
        float XYZW[4]; //!< XYZW component.
#endif
};

inline bool BQuaternion::isNull() const {
    return ( Core::bFuzzyCompare ( XYZW[0], 0.0f ) &&
             Core::bFuzzyCompare ( XYZW[1], 0.0f ) &&
             Core::bFuzzyCompare ( XYZW[2], 0.0f ) &&
             Core::bFuzzyCompare ( XYZW[3], 0.0f ) );
}

inline void BQuaternion::x ( const float x ) {
    XYZW[0] = x;
}

inline void BQuaternion::y ( const float y ) {
    XYZW[1] = y;
}

inline void BQuaternion::z ( const float z ) {
    XYZW[2] = z;
}

inline void BQuaternion::w ( const float w ) {
    XYZW[3] = w;
}

inline void BQuaternion::setXYZW ( const float x, const float y, const float z, const float w ) {
    XYZW[ 0 ] = x;
    XYZW[ 1 ] = y;
    XYZW[ 2 ] = z;
    XYZW[ 3 ] = w;
}

inline float BQuaternion::x() const {
    return XYZW[0];
}

inline float BQuaternion::y() const {
    return XYZW[1];
}

inline float BQuaternion::z() const {
    return XYZW[2];
}

inline float BQuaternion::w() const {
    return XYZW[3];
}

BOXE_NAMESPACE_END ( Math )

#endif // BQUATERNION_H
