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


#ifndef BSTACK_H
#define BSTACK_H

#include "./bvector.h"

BOXE_NAMESPACE_BEGIN ( Core )

/*!
 * Stack implementation.
 * \n Example:
 * \code
 * BStack<int> stack;
 * stack.push( 1 );
 * stack.push( 2 );
 * stack.push( 3 );
 * while( !stack.isEmpty() ) {
 *   std::cout << stack.pop() << ' ' ;
 * }
 * \endcode
 * This code print 3 2 1.
 */
template< typename T >
class BStack : public BVector<T> {
    public:
        /*!
         * Create empty stack.
         */
        inline BStack() {}

        /*!
         * Destructor.
         */
        inline ~BStack() {}

        /*!
         * Push value to top.
         * \param value Value.
         */
        inline void push ( const T &value ) {
            BVector<T>::append ( value );
        }

        /*!
         * Pop value from top.
         * \return Value.
         */
        inline T pop() {
            T temp = BVector<T>::data() [ BVector<T>::size() - 1 ];
            BVector<T>::resize ( BVector<T>::size() - 1 );
            return temp;
        };

        /*!
         * Get reference to top value.
         * \return Reference to value at top.
         */
        inline T &top() {
            return  BVector<T>::data() [ BVector<T>::size() - 1 ];
        }

        /*!
         * Get const reference to top value.
         * \return Const reference to value at top.
         */
        inline const T &top() const {
            return  BVector<T>::data() [ BVector<T>::size() - 1 ];
        }

};

BOXE_NAMESPACE_END ( Core )

#endif // BSTACK_H
