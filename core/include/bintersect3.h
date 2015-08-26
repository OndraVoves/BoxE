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

#ifndef BINTERSECT3_H
#define BINTERSECT3_H

#include "./bglobal.h"

#include "bray3f.h"
#include "bplane3f.h"
#include "bsphere3f.h"
#include "ehittype.h"

BOXE_NAMESPACE_BEGIN ( Math )

class Bintersect3 {
    public:
        /********
         * Ray. *
         ********/
        static EHitType intersect ( const BRay3f &ray, const BPlane3f &plane, float &distance );
        static EHitType intersect ( const BRay3f &ray, const BSphere3f &sphere, float &distance );

        /**********
         * Plane. *
         **********/
        /*      static EIntersectType intersect( const BPlane3f &plane, const BRay3f& ray, float& distance ){
                    return intersect( ray, plane, distance );
                }*/

        /***********
         * Sphere. *
         ***********/
        /*      static EIntersectType intersect( const BSphere3f &sphere, const BRay3f& ray, float& distance ){
                    return intersect( ray, sphere, distance );
                }*/
};

BOXE_NAMESPACE_END ( Math )
#endif // BINTERSECT3_H
