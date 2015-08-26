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

#ifndef BRAY3F_H
#define BRAY3F_H

#include "../../core/include/BGlobal"

#include "./bvector3f.h"


BOXE_NAMESPACE_BEGIN ( Math )

class BRay3f {
    public:
        /*!
         * Create null ray.
         */
        BRay3f();

        /*!
         * Create ray from other ray.
         * \param other Other ray.
         */
        BRay3f ( const BRay3f &other );

        /*!
         * Create ray.
         * \param origin Origin.
         * \param direction Direction.
         */
        BRay3f ( const BVector3f &origin, const BVector3f &direction );


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
         * Get direction.
         * \return Direction.
         */
        const BVector3f &constDirection() const {
            return Direction;
        }

        /*!
         * Get direction.
         * \return Direction.
         */
        BVector3f direction() const {
            return Direction;
        }

        /*!
         * Set origin.
         * \param origin Origin.
         */
        void origin ( const BVector3f &origin ) {
            Origin =  origin;
        }

        /*!
         * Set direction.
         * \param direction Direction.
         */
        void direction ( const BVector3f &direction ) {
            Direction =  direction;
        }
    private:
        BVector3f Origin;    //!< Ray origin.
        BVector3f Direction; //!< Ray direction.
};

BOXE_NAMESPACE_END ( Math )

#endif // BRAY3F_H
