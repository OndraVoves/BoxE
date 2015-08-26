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

#include "../include/bplane3f.h"

BOXE_NAMESPACE_BEGIN ( Math )

BPlane3f::BPlane3f() : D ( 0.0f ) {
}

BPlane3f::BPlane3f ( const BPlane3f &other ) : Normal ( other.Normal ), D ( other.D ) {
}

BPlane3f::BPlane3f ( const BVector3f &normal, const float d ) : Normal ( normal ), D ( d ) {
}

BPlane3f::BPlane3f ( const BVector3f &u, const BVector3f &v ) {
    Normal = BVector3f::crossProduct ( u, v );
    D = - ( BVector3f::dotProduct ( Normal, u ) );
}

void BPlane3f::normalize() {
    double l = ( double ) ( Normal.length() );
    double inv = 1.0 / l ;
    D = D * inv ;
    Normal.normalize();
}

bool BPlane3f::getIntersectionWithLine ( const BVector3f &line_origin,  const BVector3f &line_dir, BVector3f &out_point ) const {
    float NdotV = BVector3f::dotProduct ( Normal, line_dir );

    if ( !NdotV ) {
        return false;
    }

    float t = - ( BVector3f::dotProduct ( Normal, line_origin ) + D ) / NdotV;
    out_point = line_origin + ( line_dir * t );

    return true;
}

bool BPlane3f::getIntersectionWithPlane ( const BPlane3f &plane,  BVector3f &out_line_origin,  BVector3f &out_line_dir ) const {
    float normal_len = Normal.length();
    float plane_normal_len = plane.Normal.length();
    float NdotN = BVector3f::dotProduct ( Normal, plane.Normal );

    double determinant = normal_len * plane_normal_len  - ( NdotN * NdotN );

    // rounding error check

    double ivert_det = 1.0 / determinant;

    double tmp1 = ( plane_normal_len * -D + NdotN * plane.D ) * ivert_det;
    double tmp2 = ( normal_len * -plane.D + NdotN * D ) * ivert_det;

    out_line_dir = BVector3f::crossProduct ( Normal, plane.Normal );
    out_line_origin = Normal * tmp1 + plane.Normal * tmp2;

    return true;
}

bool BPlane3f::getIntersectionWithPlanes ( const BPlane3f &plane1, const BPlane3f &plane2, BVector3f &out_point ) const {
    BVector3f line_origin;
    BVector3f line_dir;

    if ( getIntersectionWithPlane ( plane1, line_origin, line_dir ) ) {
        return plane2.getIntersectionWithLine ( line_origin, line_dir, out_point );
    }

    return false;
}

BOXE_NAMESPACE_END ( Math )
