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

#ifndef BMATRIX4X4F_H
#define BMATRIX4X4F_H

#include "../../core/include/BGlobal"

#include "bvector3f.h"
#include "bvector4f.h"

//#include <immintrin.h>
#undef __SSE__

BOXE_NAMESPACE_BEGIN ( Math )

class BVector3f;
class BMatrix3x3f;
class BQuaternion;

class BMatrix4x4f {
    public:
        static const BMatrix4x4f IDENTITY;

    public:

        BMatrix4x4f();
        BMatrix4x4f ( const BMatrix4x4f &other );
        BMatrix4x4f ( const float a11, const float a12, const float a13, const float a14,
                      const float a21, const float a22, const float a23, const float a24,
                      const float a31, const float a32, const float a33, const float a34,
                      const float a41, const float a42, const float a43, const float a44 );

        BMatrix4x4f ( const BVector4f &row1, const BVector4f &row2, const BVector4f &row3, const BVector4f &row4 );

        inline bool isNull() const;

        float getDeterminant() const;
        BMatrix4x4f getInverse() const;


        BMatrix4x4f &operator= ( const BMatrix4x4f &matrix  );
        BMatrix4x4f &operator*= ( const BMatrix4x4f &matrix );

        inline const BVector4f &constRow1() const;
        inline const BVector4f &constRow2() const;
        inline const BVector4f &constRow3() const;
        inline const BVector4f &constRow4() const;

        bool isIdentity() const;

        void setToIdentity();

        BMatrix4x4f transpose() const;

        void translate ( const BVector3f &translate );
        void rotateX ( const float angle );
        void rotateY ( const float angle );
        void rotateZ ( const float angle );
        void scale ( const BVector3f &scale );

        void setOrthographic ( float left, float right, float bottom, float top, float near, float far );
        void setPerspective ( float fovy, float aspect, float near, float far );

        void setLookAt ( const BVector3f &eye, const BVector3f &center, const BVector3f &up );

        friend inline const BMatrix4x4f operator* ( const BMatrix4x4f &m1, const BMatrix4x4f &m2 );
        friend inline const BVector3f operator* ( const BMatrix4x4f &m1, const BVector3f &vector );
        friend inline const BVector4f operator* ( const BMatrix4x4f &m1, const BVector4f &vector );
        friend inline bool bFuzzyCompare ( const BMatrix4x4f &m1, const BMatrix4x4f &m2 );

        BMatrix3x3f toMatrix3x3() const;


    private:
        BVector4f Row1;
        BVector4f Row2;
        BVector4f Row3;
        BVector4f Row4;

    private:
        friend class BMatrix3x3f;
        friend class BQuaternion;
};

inline bool BMatrix4x4f::isNull() const {
    return ( Row1.isNull() &&
             Row2.isNull() &&
             Row3.isNull() &&
             Row4.isNull() );
}

inline const BVector4f &BMatrix4x4f::constRow1() const {
    return Row1;
}

inline const BVector4f &BMatrix4x4f::constRow2() const {
    return Row2;
}

inline const BVector4f &BMatrix4x4f::constRow3() const {
    return Row3;
}

inline const BVector4f &BMatrix4x4f::constRow4() const {
    return Row4;
}

inline const BMatrix4x4f operator* ( const BMatrix4x4f &m1, const BMatrix4x4f &m2 ) {
    const BMatrix4x4f &matrixT = m2.transpose();

    return BMatrix4x4f ( BVector4f::dotProduct ( m1.Row1, matrixT.Row1 ),
                         BVector4f::dotProduct ( m1.Row1, matrixT.Row2 ),
                         BVector4f::dotProduct ( m1.Row1, matrixT.Row3 ),
                         BVector4f::dotProduct ( m1.Row1, matrixT.Row4 ),

                         BVector4f::dotProduct ( m1.Row2, matrixT.Row1 ),
                         BVector4f::dotProduct ( m1.Row2, matrixT.Row2 ),
                         BVector4f::dotProduct ( m1.Row2, matrixT.Row3 ),
                         BVector4f::dotProduct ( m1.Row2, matrixT.Row4 ),

                         BVector4f::dotProduct ( m1.Row3, matrixT.Row1 ),
                         BVector4f::dotProduct ( m1.Row3, matrixT.Row2 ),
                         BVector4f::dotProduct ( m1.Row3, matrixT.Row3 ),
                         BVector4f::dotProduct ( m1.Row3, matrixT.Row4 ),

                         BVector4f::dotProduct ( m1.Row4, matrixT.Row1 ),
                         BVector4f::dotProduct ( m1.Row4, matrixT.Row2 ),
                         BVector4f::dotProduct ( m1.Row4, matrixT.Row3 ),
                         BVector4f::dotProduct ( m1.Row4, matrixT.Row4 ) );
}

inline const BVector3f operator* ( const BMatrix4x4f &m1, const BVector3f &vector ) {
    BVector4f v ( vector, 0.0f );

    return BVector3f ( BVector3f::dotProduct ( m1.Row1, v ),
                       BVector3f::dotProduct ( m1.Row2, v ),
                       BVector3f::dotProduct ( m1.Row3, v ) );
}

inline const BVector4f operator* ( const BMatrix4x4f &m1, const BVector4f &vector ) {
    return BVector4f ( BVector4f::dotProduct ( m1.Row1, vector ),
                       BVector4f::dotProduct ( m1.Row2, vector ),
                       BVector4f::dotProduct ( m1.Row3, vector ),
                       BVector4f::dotProduct ( m1.Row4, vector ) );
}

inline bool bFuzzyCompare ( const BMatrix4x4f &m1, const BMatrix4x4f &m2 ) {
    return (  bFuzzyCompare ( m1.Row1, m2.Row1 ) &&
              bFuzzyCompare ( m1.Row2, m2.Row2 ) &&
              bFuzzyCompare ( m1.Row3, m2.Row3 ) &&
              bFuzzyCompare ( m1.Row4, m2.Row4 ) );
}

BOXE_NAMESPACE_END ( Math )

#endif /* BMATRIX4X4F_H */
