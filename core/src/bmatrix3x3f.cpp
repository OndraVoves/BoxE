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

#include "../include/bmatrix3x3f.h"

#include "../include/bmatrix4x4f.h"

BOXE_NAMESPACE_BEGIN ( Math )

const BMatrix3x3f BMatrix3x3f::IDENTITY ( BVector4f::RIGHT, BVector4f::UP, BVector4f::BACKWARD );

BMatrix3x3f::BMatrix3x3f() {
}

BMatrix3x3f::BMatrix3x3f (  const BMatrix3x3f &other ) : Row1 ( other.Row1 ), Row2 ( other.Row2 ), Row3 ( other.Row3 ) {

}

BMatrix3x3f::BMatrix3x3f ( const float a11, const float a12, const float a13,
                           const float a21, const float a22, const float a23,
                           const float a31, const float a32, const float a33 ) : Row1 ( a11, a12, a13 ), Row2 ( a21, a22, a23 ), Row3 ( a31, a32, a33 ) {
}

BMatrix3x3f::BMatrix3x3f (  const BVector3f &row1, const BVector3f &row2, const BVector3f &row3 ) : Row1 ( row1 ), Row2 ( row2 ), Row3 ( row3 ) {
}

BMatrix3x3f &BMatrix3x3f::operator= ( const BMatrix3x3f &matrix  ) {
    Row1 = matrix.Row1;
    Row2 = matrix.Row2;
    Row3 = matrix.Row3;
    return *this;
}

BMatrix3x3f &BMatrix3x3f::operator*= ( const BMatrix3x3f &matrix ) {
    const BMatrix3x3f &matrixT = matrix.transpose();
    const BMatrix3x3f thisM ( *this );

    Row1.setXYZ ( BVector3f::dotProduct ( thisM.Row1, matrixT.Row1 ),
                  BVector3f::dotProduct ( thisM.Row1, matrixT.Row2 ),
                  BVector3f::dotProduct ( thisM.Row1, matrixT.Row3 ) );

    Row2.setXYZ ( BVector3f::dotProduct ( thisM.Row2, matrixT.Row1 ),
                  BVector3f::dotProduct ( thisM.Row2, matrixT.Row2 ),
                  BVector3f::dotProduct ( thisM.Row2, matrixT.Row3 ) );

    Row3.setXYZ ( BVector3f::dotProduct ( thisM.Row3, matrixT.Row1 ),
                  BVector3f::dotProduct ( thisM.Row3, matrixT.Row2 ),
                  BVector3f::dotProduct ( thisM.Row3, matrixT.Row3 ) );

    return *this;
}

bool BMatrix3x3f::isIdentity() const {
    if ( ( Row1.x() != 1.0f ) && ( Row2.y() != 1.0f ) && ( Row3.z() != 1.0f ) ) {
        return false;
    }

    if ( ( Row1.y() != 0.0f ) && ( Row1.z() != 0.0f ) ) {
        return false;
    }

    if ( ( Row1.x() != 0.0f ) && ( Row1.z() != 0.0f ) ) {
        return false;
    }

    if ( ( Row1.x() != 0.0f ) && ( Row1.y() != 0.0f ) ) {
        return false;
    }

    return true;
}

void BMatrix3x3f::setToIdentity() {
    Row1.setXYZ ( 1.0f, 0.0f, 0.0f );
    Row2.setXYZ ( 0.0f, 1.0f, 0.0f );
    Row3.setXYZ ( 0.0f, 0.0f, 1.0f );
}

BMatrix3x3f BMatrix3x3f::transpose() const {
    return BMatrix3x3f ( Row1.x(), Row2.x(), Row3.x(),
                         Row1.y(), Row2.y(), Row3.y(),
                         Row1.z(), Row2.z(), Row3.z() );
}

BMatrix4x4f BMatrix3x3f::toMatrix4x4() const {
    return BMatrix4x4f ( BVector4f ( Row1, 0.0f ),
                         BVector4f ( Row2, 0.0f ),
                         BVector4f ( Row3, 0.0f ),
                         BVector4f ( 0.0f, 0.0f, 0.0f, 1.0f ) );
}

BOXE_NAMESPACE_END ( Math )
