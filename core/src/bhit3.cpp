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

#include "../include/bhit3.h"

BOXE_NAMESPACE_BEGIN ( Math )

EHitType BHit3::hit ( const BSphere3f &sphere1, const BSphere3f &sphere2  ) {
    float radius_squared = sphere1.radius() + sphere2.radius();
    radius_squared *= radius_squared;

    const float lenght_squared = ( sphere2.constOrigin() - sphere1.constOrigin() ).lenghtSquared();

    if ( lenght_squared > radius_squared ) {
        return Miss;

    } else if ( lenght_squared < radius_squared ) {
        return Inside;

    } else {

        return Hit;
    }

}

BOXE_NAMESPACE_END ( Math )
