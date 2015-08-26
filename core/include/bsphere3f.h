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

#ifndef BSPHERE3F_H
#define BSPHERE3F_H

#include "../../core/include/BGlobal"

#include "./bvector3f.h"

BOXE_NAMESPACE_BEGIN ( Math )

/*!
 * 3-D sphere.
 */
class BSphere3f {
    public:
        /*!
         * Create null sphere.
         */
        BSphere3f();

        /*!
         * Create Sphere from other sphere.
         */
        BSphere3f ( const BSphere3f &other );

        /*!
         * Create shere.
         * \param origin Origin.
         * \param radius Radius.
         */
        BSphere3f ( const BVector3f &origin, const float radius );

        /*!
         * Get origin.
         * \return Origin.
         */
        const BVector3f &constOrigin() const {
            return Origin;
        }

        /*!
         * Get origin.
         * \return Origin.
         */
        BVector3f origin() const {
            return Origin;
        }

        /*!
         * Get radius.
         * \return Radius.
         */
        float radius() const {
            return Radius;
        }

        /*!
         * Get radius ^ 2.
         * \return Radius ^ 2.
         */
        float radiusSquared() const {
            return RadiusSquared;
        }

        /*!
         * Set origin.
         * \param origin Origin.
         */
        void origin ( const BVector3f &origin ) {
            Origin = origin;
        }

        /*!
         * Set radius.
         * \param r Radius.
         */
        void radius ( const float r ) {
            Radius = r;
            RadiusSquared = r * r;
        }

    private:
        BVector3f Origin;    //!< Origin
        float Radius;        //!< Radius
        float RadiusSquared; //!< Radius ^ 2
};

BOXE_NAMESPACE_END ( Math )

#endif // BSPHERE3F_H
