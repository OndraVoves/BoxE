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

#ifndef BPLANE3F_H
#define BPLANE3F_H

#include "../../core/include/BGlobal"

#include "./bvector3f.h"

BOXE_NAMESPACE_BEGIN ( Math )

class BPlane3f {
    public:

        /*!
         * Create null plane.
         */
        BPlane3f();

        /*!
         * Create plane from other plane.
         * \param other Other plane.
         */
        BPlane3f ( const BPlane3f &other );

        /*!
         * Create plane from normal and d.
         * \param normal Normal vector.
         * \param d D.
         */
        BPlane3f ( const BVector3f &normal, const float d );

        /*!
         * Create plane from two vector.
         * \param u U vector.
         * \param v V vector.
         */
        BPlane3f ( const BVector3f &u, const BVector3f &v );


        /*!
         * Get normal.
         * \return Plane normal.
         */
        const BVector3f &constNormal() const {
            return Normal;
        }

        /*!
         * Get normal.
         * \return Plane normal.
         */
        BVector3f normal() const {
            return Normal;
        }

        /*!
         * Get d.
         * \return D.
         */
        float d() const {
            return D;
        }

        /*!
         * Set normal.
         * \param n Normal;
         */
        void normal ( const BVector3f &n ) {
            Normal = n;
        }

        /*!
         * Set D.
         * \param _d D.
         */
        void d ( const float _d ) {
            D = _d;
        }

        void normalize();

        bool getIntersectionWithLine ( const BVector3f &line_origin,  const BVector3f &line_dir, BVector3f &out_point ) const;
        bool getIntersectionWithPlane ( const BPlane3f &plane,  BVector3f &out_line_origin,  BVector3f &out_line_dir ) const;
        bool getIntersectionWithPlanes ( const BPlane3f &plane1, const BPlane3f &plane2, BVector3f &out_point ) const;
    private:
        BVector3f Normal; //!< Normal.
        float D;          //!< D.
};

BOXE_NAMESPACE_END ( Math )

#endif // BPLANE3F_H
