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


#ifndef BREFERENCECOUNTER_H
#define BREFERENCECOUNTER_H

#include "bglobal.h"

BOXE_NAMESPACE_BEGIN ( Core )

/*!
 * Reference counter class.
 */
class BReferenceCounter {
    public:
        /*!
         * Create reference counter.
         * \param init_reference Initial reference count.
         */
        BReferenceCounter ( const int init_reference = 0 ) : Reference ( init_reference ) {}

        /*!
         * Copy constructor.
         * \param other Reference to other counter.
         */
        BReferenceCounter ( const BReferenceCounter &other ) : Reference ( other.Reference ) {}

        /*!
         * Increase reference.
         * \return If new reference count is non zero then return true, else return false.
         */
        inline bool reference() {
            return ( ++Reference > 0 );
        }

        /*!
         * Decrease reference.
         * \return If new reference count is non zero then return true, else return false.
         */
        inline bool dereference() {
            if ( Reference == 0 ) {
                return false;
            }

            return ( --Reference > 0 );
        }

        /*!
         * Return reference count.
         */
        inline operator int() const {
            return Reference;
        }

    private:
        int Reference; //!< Reference count.
};

BOXE_NAMESPACE_END ( Core )

#endif // BREFERENCECOUNTER_H
