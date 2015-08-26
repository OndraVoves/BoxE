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

#include "../include/bmatrix4x4f.h"
#include "../include/bgoniometry.h"
#include "../include/bmatrix3x3f.h"

#include <cmath>

BOXE_NAMESPACE_BEGIN ( Math )

const BMatrix4x4f BMatrix4x4f::IDENTITY ( BVector4f ( 1.0f, 0.0f, 0.0f, 0.0f ),
        BVector4f ( 0.0f, 1.0f, 0.0f, 0.0f ),
        BVector4f ( 0.0f, 0.0f, 1.0f, 0.0f ),
        BVector4f ( 0.0f, 0.0f, 0.0f, 1.0f ) );

BMatrix4x4f::BMatrix4x4f() {
}

BMatrix4x4f::BMatrix4x4f (  const BMatrix4x4f &other ) : Row1 ( other.Row1 ), Row2 ( other.Row2 ), Row3 ( other.Row3 ), Row4 ( other.Row4 ) {

}

BMatrix4x4f::BMatrix4x4f (  const float a11, const float a12, const float a13, const float a14,
                            const float a21, const float a22, const float a23, const float a24,
                            const float a31, const float a32, const float a33, const float a34,
                            const float a41, const float a42, const float a43, const float a44 ) : Row1 ( a11, a12, a13, a14 ), Row2 ( a21, a22, a23, a24 ), Row3 ( a31, a32, a33, a34 ), Row4 ( a41, a42, a43, a44 ) {
}

BMatrix4x4f::BMatrix4x4f ( const BVector4f &row1, const BVector4f &row2, const BVector4f &row3, const BVector4f &row4 ) : Row1 ( row1 ), Row2 ( row2 ), Row3 ( row3 ), Row4 ( row4 ) {
}

BMatrix4x4f &BMatrix4x4f::operator= ( const BMatrix4x4f &matrix  ) {
    Row1 = matrix.Row1;
    Row2 = matrix.Row2;
    Row3 = matrix.Row3;
    Row4 = matrix.Row4;
    return *this;
}

BMatrix4x4f &BMatrix4x4f::operator*= ( const BMatrix4x4f &matrix ) {
    const BMatrix4x4f &matrixT = matrix.transpose();
    const BMatrix4x4f thisM ( *this );

    Row1.setXYZW ( BVector4f::dotProduct ( thisM.Row1, matrixT.Row1 ),
                   BVector4f::dotProduct ( thisM.Row1, matrixT.Row2 ),
                   BVector4f::dotProduct ( thisM.Row1, matrixT.Row3 ),
                   BVector4f::dotProduct ( thisM.Row1, matrixT.Row4 ) );

    Row2.setXYZW ( BVector4f::dotProduct ( thisM.Row2, matrixT.Row1 ),
                   BVector4f::dotProduct ( thisM.Row2, matrixT.Row2 ),
                   BVector4f::dotProduct ( thisM.Row2, matrixT.Row3 ),
                   BVector4f::dotProduct ( thisM.Row2, matrixT.Row4 ) );

    Row3.setXYZW ( BVector4f::dotProduct ( thisM.Row3, matrixT.Row1 ),
                   BVector4f::dotProduct ( thisM.Row3, matrixT.Row2 ),
                   BVector4f::dotProduct ( thisM.Row3, matrixT.Row3 ),
                   BVector4f::dotProduct ( thisM.Row3, matrixT.Row4 ) );

    Row4.setXYZW ( BVector4f::dotProduct ( thisM.Row4, matrixT.Row1 ),
                   BVector4f::dotProduct ( thisM.Row4, matrixT.Row2 ),
                   BVector4f::dotProduct ( thisM.Row4, matrixT.Row3 ),
                   BVector4f::dotProduct ( thisM.Row4, matrixT.Row4 ) );

    return *this;
}

float BMatrix4x4f::getDeterminant() const {
    return ( Row1.w() * Row2.z() * Row3.y() * Row4.x() ) - ( Row1.z() * Row2.w() * Row3.y() * Row4.x() ) -
           ( Row1.w() * Row2.y() * Row3.z() * Row4.x() ) + ( Row1.y() * Row2.w() * Row3.z() * Row4.x() ) +
           ( Row1.z() * Row2.y() * Row3.w() * Row4.x() ) - ( Row1.y() * Row2.z() * Row3.w() * Row4.x() ) -
           ( Row1.w() * Row2.z() * Row3.x() * Row4.y() ) + ( Row1.z() * Row2.w() * Row3.x() * Row4.y() ) +
           ( Row1.w() * Row2.x() * Row3.z() * Row4.y() ) - ( Row1.x() * Row2.w() * Row3.z() * Row4.y() ) -
           ( Row1.z() * Row2.x() * Row3.w() * Row4.y() ) + ( Row1.x() * Row2.z() * Row3.w() * Row4.y() ) +
           ( Row1.w() * Row2.y() * Row3.x() * Row4.z() ) - ( Row1.y() * Row2.w() * Row3.x() * Row4.z() ) -
           ( Row1.w() * Row2.x() * Row3.y() * Row4.z() ) + ( Row1.x() * Row2.w() * Row3.y() * Row4.z() ) +
           ( Row1.y() * Row2.x() * Row3.w() * Row4.z() ) - ( Row1.x() * Row2.y() * Row3.w() * Row4.z() ) -
           ( Row1.z() * Row2.y() * Row3.x() * Row4.w() ) + ( Row1.y() * Row2.z() * Row3.x() * Row4.w() ) +
           ( Row1.z() * Row2.x() * Row3.y() * Row4.w() ) - ( Row1.x() * Row2.z() * Row3.y() * Row4.w() ) -
           ( Row1.y() * Row2.x() * Row3.z() * Row4.w() ) + ( Row1.x() * Row2.y() * Row3.z() * Row4.w() );
}

BMatrix4x4f BMatrix4x4f::getInverse() const {
    float determinant  = getDeterminant();

    if ( Core::bFuzzyCompare ( determinant, 0.0f ) ) {
        return BMatrix4x4f();
    }

    determinant = 1.0f / determinant;

    BMatrix4x4f out;

    out.Row1.x ( determinant * ( Row2.y() * ( Row3.z() * Row4.w() - Row3.w() * Row4.z() ) +
                                 Row2.z() * ( Row3.w() * Row4.y() - Row3.y() * Row4.w() ) +
                                 Row2.w() * ( Row3.y() * Row4.z() - Row3.z() * Row4.y() ) ) );

    out.Row1.y ( determinant * ( Row3.y() * ( Row1.z() * Row4.w() - Row1.w() * Row4.z() ) +
                                 Row3.z() * ( Row1.w() * Row4.y() - Row1.y() * Row4.w() ) +
                                 Row3.w() * ( Row1.y() * Row4.z() - Row1.z() * Row4.y() ) ) );

    out.Row1.z ( determinant * ( Row4.y() * ( Row1.z() * Row2.w() - Row1.w() * Row2.z() ) +
                                 Row4.z() * ( Row1.w() * Row2.y() - Row1.y() * Row2.w() ) +
                                 Row4.w() * ( Row1.y() * Row2.z() - Row1.z() * Row2.y() ) ) );

    out.Row1.w ( determinant * ( Row1.y() * ( Row2.w() * Row3.z() - Row2.z() * Row3.w() ) +
                                 Row1.z() * ( Row2.y() * Row3.w() - Row2.w() * Row3.y() ) +
                                 Row1.w() * ( Row2.z() * Row3.y() - Row2.y() * Row3.z() ) ) );

    out.Row2.x ( determinant * ( Row2.z() * ( Row3.x() * Row4.w() - Row3.w() * Row4.x() ) +
                                 Row2.w() * ( Row3.z() * Row4.x() - Row3.x() * Row4.z() ) +
                                 Row2.x() * ( Row3.w() * Row4.z() - Row3.z() * Row4.w() ) ) );

    out.Row2.y ( determinant * ( Row3.z() * ( Row1.x() * Row4.w() - Row1.w() * Row4.x() ) +
                                 Row3.w() * ( Row1.z() * Row4.x() - Row1.x() * Row4.z() ) +
                                 Row3.x() * ( Row1.w() * Row4.z() - Row1.z() * Row4.w() ) ) );

    out.Row2.z ( determinant * ( Row4.z() * ( Row1.x() * Row2.w() - Row1.w() * Row2.x() ) +
                                 Row4.w() * ( Row1.z() * Row2.x() - Row1.x() * Row2.z() ) +
                                 Row4.x() * ( Row1.w() * Row2.z() - Row1.z() * Row2.w() ) ) );

    out.Row2.w ( determinant * ( Row1.z() * ( Row2.w() * Row3.x() - Row2.x() * Row3.w() ) +
                                 Row1.w() * ( Row2.x() * Row3.z() - Row2.z() * Row3.x() ) +
                                 Row1.x() * ( Row2.z() * Row3.w() - Row2.w() * Row3.z() ) ) );

    out.Row3.x ( determinant * ( Row2.w() * ( Row3.x() * Row4.y() - Row3.y() * Row4.x() ) +
                                 Row2.x() * ( Row3.y() * Row4.w() - Row3.w() * Row4.y() ) +
                                 Row2.y() * ( Row3.w() * Row4.x() - Row3.x() * Row4.w() ) ) );

    out.Row3.y ( determinant * ( Row3.w() * ( Row1.x() * Row4.y() - Row1.y() * Row4.x() ) +
                                 Row3.x() * ( Row1.y() * Row4.w() - Row1.w() * Row4.y() ) +
                                 Row3.y() * ( Row1.w() * Row4.x() - Row1.x() * Row4.w() ) ) );

    out.Row3.z ( determinant * ( Row4.w() * ( Row1.x() * Row2.y() - Row1.y() * Row2.x() ) +
                                 Row4.x() * ( Row1.y() * Row2.w() - Row1.w() * Row2.y() ) +
                                 Row4.y() * ( Row1.w() * Row2.x() - Row1.x() * Row2.w() ) ) );

    out.Row3.w ( determinant * ( Row1.w() * ( Row2.y() * Row3.x() - Row2.x() * Row3.y() ) +
                                 Row1.x() * ( Row2.w() * Row3.y() - Row2.y() * Row3.w() ) +
                                 Row1.y() * ( Row2.x() * Row3.w() - Row2.w() * Row3.x() ) ) );

    out.Row4.x ( determinant * ( Row2.x() * ( Row3.z() * Row4.y() - Row3.y() * Row4.z() ) +
                                 Row2.y() * ( Row3.x() * Row4.z() - Row3.z() * Row4.x() ) +
                                 Row2.z() * ( Row3.y() * Row4.x() - Row3.x() * Row4.y() ) ) );

    out.Row4.y ( determinant * ( Row3.x() * ( Row1.z() * Row4.y() - Row1.y() * Row4.z() ) +
                                 Row3.y() * ( Row1.x() * Row4.z() - Row1.z() * Row4.x() ) +
                                 Row3.z() * ( Row1.y() * Row4.x() - Row1.x() * Row4.y() ) ) );

    out.Row4.z ( determinant * ( Row4.x() * ( Row1.z() * Row2.y() - Row1.y() * Row2.z() ) +
                                 Row4.y() * ( Row1.x() * Row2.z() - Row1.z() * Row2.x() ) +
                                 Row4.z() * ( Row1.y() * Row2.x() - Row1.x() * Row2.y() ) ) );

    out.Row4.w ( determinant * ( Row1.x() * ( Row2.y() * Row3.z() - Row2.z() * Row3.y() ) +
                                 Row1.y() * ( Row2.z() * Row3.x() - Row2.x() * Row3.z() ) +
                                 Row1.z() * ( Row2.x() * Row3.y() - Row2.y() * Row3.x() ) ) );

    return out;
}

bool BMatrix4x4f::isIdentity() const {
    if ( ( Row1.x() != 1.0f ) && ( Row2.y() != 1.0f ) && ( Row3.z() != 1.0f ) && ( Row4.w() != 1.0f ) ) {
        return false;
    }

    if ( ( Row1.y() != 0.0f ) && ( Row1.z() != 0.0f ) && ( Row1.w() != 0.0f ) ) {
        return false;
    }

    if ( ( Row1.x() != 0.0f ) && ( Row1.z() != 0.0f ) && ( Row1.w() != 0.0f ) ) {
        return false;
    }

    if ( ( Row1.x() != 0.0f ) && ( Row1.y() != 0.0f ) && ( Row1.w() != 0.0f ) ) {
        return false;
    }

    if ( ( Row1.x() != 0.0f ) && ( Row1.y() != 0.0f ) && ( Row1.z() != 0.0f ) ) {
        return false;
    }

    return true;
}

void BMatrix4x4f::setToIdentity() {
    Row1.setXYZW ( 1.0f, 0.0f, 0.0f, 0.0f );
    Row2.setXYZW ( 0.0f, 1.0f, 0.0f, 0.0f );
    Row3.setXYZW ( 0.0f, 0.0f, 1.0f, 0.0f );
    Row4.setXYZW ( 0.0f, 0.0f, 0.0f, 1.0f );
}

BMatrix4x4f BMatrix4x4f::transpose() const {
    return BMatrix4x4f ( Row1.x(), Row2.x(), Row3.x(), Row4.x(),
                         Row1.y(), Row2.y(), Row3.y(), Row4.y(),
                         Row1.z(), Row2.z(), Row3.z(), Row4.z(),
                         Row1.w(), Row2.w(), Row3.w(), Row4.w() );
}

void BMatrix4x4f::translate ( const BVector3f &translate ) {
    BMatrix4x4f translate_matrix;
    translate_matrix.setToIdentity();
    translate_matrix.Row1.w ( translate.x() );
    translate_matrix.Row2.w ( translate.y() );
    translate_matrix.Row3.w ( translate.z() );

    operator*= ( translate_matrix );
}

void BMatrix4x4f::rotateX ( const float angle ) {
    BMatrix4x4f rotate_matrix;;
    rotate_matrix.setToIdentity();

    const float rad_angle = Math::bDeg2Rad<float> ( angle );

    const float a_sin = bFastSin ( rad_angle );
    const float a_cos = bFastCos ( rad_angle );

    rotate_matrix.Row2.setXYZW ( 0.0f, a_cos, -a_sin, 0.0f );
    rotate_matrix.Row3.setXYZW ( 0.0f, a_sin, a_cos, 0.0f );

    operator*= ( rotate_matrix );
}

void BMatrix4x4f::rotateY ( const float angle ) {
    BMatrix4x4f rotate_matrix;
    rotate_matrix.setToIdentity();

    const float rad_angle = Math::bDeg2Rad<float> ( angle );

    const float a_sin = bFastSin ( rad_angle );
    const float a_cos = bFastCos ( rad_angle );

    rotate_matrix.Row1.setXYZW (  a_cos, 0.0f, a_sin, 0.0f );
    rotate_matrix.Row3.setXYZW ( -a_sin, 0.0f, a_cos, 0.0f );

    operator*= ( rotate_matrix );
}

void BMatrix4x4f::rotateZ ( const float angle ) {
    BMatrix4x4f rotate_matrix;
    rotate_matrix.setToIdentity();

    const float rad_angle = Math::bDeg2Rad<float> ( angle );

    const float a_sin = bFastSin ( rad_angle );
    const float a_cos = bFastCos ( rad_angle );

    rotate_matrix.Row1.setXYZW ( a_cos, -a_sin, 0.0f, 0.0f );
    rotate_matrix.Row2.setXYZW ( a_sin,  a_cos, 0.0f, 0.0f );

    operator*= ( rotate_matrix );
}

void BMatrix4x4f::scale ( const BVector3f &scale ) {
    BMatrix4x4f scale_matrix;
    scale_matrix.setToIdentity();

    scale_matrix.Row1.x ( scale.x() );
    scale_matrix.Row2.y ( scale.y() );
    scale_matrix.Row3.z ( scale.z() );

    operator*= ( scale_matrix );
}

void BMatrix4x4f::setOrthographic ( float left, float right, float bottom, float top, float nearr, float farr ) {
    setToIdentity();

    Row1.x ( 2.0 / ( right - left ) );
    Row2.y ( 2.0 / ( top - bottom ) );
    Row3.z ( -2.0 / ( farr - nearr ) );

    Row1.w ( - ( ( right + left ) / ( right - left ) ) );
    Row2.w ( - ( ( top + bottom ) / ( top - bottom ) ) );
    Row3.w (  - ( ( farr + nearr ) / ( farr - nearr ) ) );
}

void BMatrix4x4f::setPerspective ( float fovy, float aspect, float nearr, float farr ) {
    setToIdentity();

    const double h = 1.0 / tan ( Math::bDeg2Rad< float > ( fovy * 0.5 ) );
    double neg_depth = nearr - farr;

    Row1.x ( h / aspect );

    Row2.y ( h );

    Row3.z ( ( nearr + farr ) / neg_depth );
    Row3.w ( 2.0f * ( nearr * farr ) / neg_depth );

    Row4.z ( -1.0f );
    Row4.w ( 0.0f );
}

void BMatrix4x4f::setLookAt ( const BVector3f &eye, const BVector3f &center, const BVector3f &up ) {
    BVector3f forward = center - eye;
    forward.normalize();

    BVector3f right = BVector3f::crossProduct ( forward, up );
    right.normalize();

    BVector3f up2 = BVector3f::crossProduct ( right, forward );
    up2.normalize();

    Row1 = right.toVector4f();
    Row2 = up2.toVector4f();
    Row3 = -forward.toVector4f();
    Row4.setXYZW ( 0.0f, 0.0f, 0.0f, 1.0f );

    translate ( -eye );
}


BMatrix3x3f BMatrix4x4f::toMatrix3x3() const {
    return BMatrix3x3f ( BVector3f ( Row1 ),
                         BVector3f ( Row2 ),
                         BVector3f ( Row3 ) );
}

BOXE_NAMESPACE_END ( Math )
