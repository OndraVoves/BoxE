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

#include "../include/bintersect3.h"

#include <cmath>

BOXE_NAMESPACE_BEGIN ( Math )

EHitType Bintersect3::intersect ( const BRay3f &ray, const BPlane3f &plane, float &distance ) {
    float dot = BVector3f::dotProduct ( plane.constNormal(), ray.constDirection() );

    if ( dot == 0 ) {
        return Miss;
    }

    float d = - ( BVector3f::dotProduct ( plane.constNormal(), ray.constOrigin() ) + plane.d() ) / dot;

    if ( d > 0 ) {
        if ( d <= distance ) {
            distance = d;
            return Hit;
        } else {
            return Miss;
        }
    }

    return Miss;
}

EHitType Bintersect3::intersect ( const BRay3f &ray, const BSphere3f &sphere, float &distance ) {
    BVector3f v ( ray.constOrigin() - sphere.constOrigin() );
    float b = -BoxE::Math::BVector3f::dotProduct ( v, ray.constDirection() );
    float det = ( b * b ) - BoxE::Math::BVector3f::dotProduct ( v, v ) + sphere.radiusSquared();
    if ( det > 0 ) {
        det = sqrt ( det );

        float i1 = b - det;
        float i2 = b + det;

        if ( i2 > 0 ) {
            if ( i1 < 0 ) {
                if ( i2 < distance ) {
                    distance = i2;
                    return Inside;
                }
            } else {
                if ( i1 < distance ) {
                    distance = i1;
                    return Hit;
                }
            }
        }
    }
    return Miss;
}

BOXE_NAMESPACE_END ( Math )
