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

#ifndef BMATRIX3_H
#define BMATRIX3_H

#include "../../core/include/BGlobal"

#include "bvector3f.h"

//#include <immintrin.h>
#undef __SSE__

BOXE_NAMESPACE_BEGIN ( Math )

class BMatrix4x4f;

class BMatrix3x3f {
    public:
        const static BMatrix3x3f IDENTITY;

    public:
        BMatrix3x3f();
        BMatrix3x3f (  const BMatrix3x3f &other );
        BMatrix3x3f ( const float a11, const float a12, const float a13,
                      const float a21, const float a22, const float a23,
                      const float a31, const float a32, const float a33 );

        BMatrix3x3f (  const BVector3f &row1, const BVector3f &row2, const BVector3f &row3 );

        BMatrix3x3f &operator= ( const BMatrix3x3f &matrix  );
        BMatrix3x3f &operator*= ( const BMatrix3x3f &matrix );

        inline bool isNull() const;

        inline const BVector3f &constRow1() const;
        inline const BVector3f &constRow2() const;
        inline const BVector3f &constRow3() const;

        bool isIdentity() const;

        void setToIdentity();

        BMatrix3x3f transpose() const;

        inline friend const BMatrix3x3f operator* ( const BMatrix3x3f &m1, const BMatrix3x3f &m2 );
        inline friend const BVector3f operator* ( const BMatrix3x3f &matrix, const BVector3f &vector );
        inline friend bool bFuzzyCompare ( const BMatrix3x3f &m1, const BMatrix3x3f &m2 );

        BMatrix4x4f toMatrix4x4() const;
    private:
        BVector3f Row1;
        BVector3f Row2;
        BVector3f Row3;

    private:
        friend class BMatrix4x4f;
};

inline const BVector3f &BMatrix3x3f::constRow1() const {
    return Row1;
}

inline const BVector3f &BMatrix3x3f::constRow2() const {
    return Row2;
}

inline const BVector3f &BMatrix3x3f::constRow3() const {
    return Row3;
}

inline bool BMatrix3x3f::isNull() const {
    return ( Row1.isNull() &&
             Row2.isNull() &&
             Row3.isNull() );
}

inline const BMatrix3x3f operator* ( const BMatrix3x3f &m1, const BMatrix3x3f &m2 ) {
    const BMatrix3x3f &matrixT = m2.transpose();

    return BMatrix3x3f ( BVector3f::dotProduct ( m1.Row1, matrixT.Row1 ),
                         BVector3f::dotProduct ( m1.Row1, matrixT.Row2 ),
                         BVector3f::dotProduct ( m1.Row1, matrixT.Row3 ),

                         BVector3f::dotProduct ( m1.Row2, matrixT.Row1 ),
                         BVector3f::dotProduct ( m1.Row2, matrixT.Row2 ),
                         BVector3f::dotProduct ( m1.Row2, matrixT.Row3 ),

                         BVector3f::dotProduct ( m1.Row3, matrixT.Row1 ),
                         BVector3f::dotProduct ( m1.Row3, matrixT.Row2 ),
                         BVector3f::dotProduct ( m1.Row3, matrixT.Row3 ) );
}

inline const BVector3f operator* ( const BMatrix3x3f &matrix, const BVector3f &vector ) {
    return BVector3f ( BVector3f::dotProduct ( matrix.Row1, vector ),
                       BVector3f::dotProduct ( matrix.Row2, vector ),
                       BVector3f::dotProduct ( matrix.Row3, vector ) );
}

inline bool bFuzzyCompare ( const BMatrix3x3f &m1, const BMatrix3x3f &m2 ) {
    return ( bFuzzyCompare ( m1.Row1, m2.Row1 ) &&
             bFuzzyCompare ( m1.Row2, m2.Row2 ) &&
             bFuzzyCompare ( m1.Row3, m2.Row3 ) );
}

BOXE_NAMESPACE_END ( Math )

#endif // BMATRIX3_H
