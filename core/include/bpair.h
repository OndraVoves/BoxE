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


#ifndef BPAIR_H
#define BPAIR_H

#include "bglobal.h"

BOXE_NAMESPACE_BEGIN ( Core )

/*!
 * Template class for pair.
 */
template< class Tfirst, class Tsecond >
class BPair {
    public:

        /*!
         * Construct pair.
         */
        inline BPair() {}

        /*!
         * Create pair.
         * \param first First value.
         * \param second Second value.
         */
        inline BPair ( const Tfirst &first, const Tsecond second  )
            : First ( first ), Second ( second ) {}

        /*!
         * Copy constructor.
         * \param other Reference to other pair.
         */
        inline BPair ( const  BPair<Tfirst, Tsecond>& other ) : First ( other.First ), Second ( other.Second ) {
        }

        /*!
         * Set this pair from other pair.
         * \param other Reference to other pair.
         * \return Reference to this.
         */
        inline BPair< Tfirst, Tsecond >& operator = ( const BPair<Tfirst, Tsecond>& other ) {
            First = other.First;
            Second = other.Second;
            return *this;
        }

        /*!
         * Is two pair Equal.
         * \param other Reference to other.
         * \return True if first is equal other.first and second is equal other.second.
         */
        inline bool operator == ( const BPair<Tfirst, Tsecond>& other ) const {
            return ( ( First == other.First ) && ( Second == other.Second ) );
        }


        /*!
         * Is not two pair Equal.
         * \param other Reference to other.
         * \return True if first is not equal other.first and second is not equal other.second.
         */
        inline bool operator != (  const BPair<Tfirst, Tsecond>& other ) const {
            return ! ( *this == other  );
        }


        Tfirst First;   //!< First value.
        Tsecond Second; //!< Second value.
};


BOXE_NAMESPACE_END ( Core )

/*!
 * Make pair.
 * \param first First value.
 * \param second Second value.
 * \return Maked pair.
 */
template< class Tfirst, class Tsecond >
inline BoxE::Core::BPair< Tfirst, Tsecond > bMakePair ( const Tfirst &first, const Tsecond &second  ) {
    return BoxE::Core::BPair< Tfirst, Tsecond > ( first, second );
}

#endif // BPAIR_H
