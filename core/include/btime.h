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


#ifndef BTIME_H
#define BTIME_H

#include "bglobal.h"

BOXE_NAMESPACE_BEGIN ( Core )

/*!
 * Class for time.
 */
class BTime {
    public:

        /*!
         * Create time 00:00:00.0.
         */
        BTime();

        /*!
         * Construct timer from other time.
         * \param other Reference to other.
         */
        BTime ( const BTime &other );

        /*!
         * Construct BTime.
         * \param hour Hour.
         * \param minute Minute.
         * \param second Second.
         * \param msecond Milisecond.
         */
        BTime ( int hour, int minute, int second = 0, int msecond = 0 );

        /*!
         * Compare time.
         * \param other Reference to other.
         * \return True if time is equal, else return false.
         */
        bool operator== ( const BTime &other ) const;

        /*!
         * Compare time.
         * \param other Reference to other.
         * \return False if time is equal, else return true.
         */
        bool operator!= ( const BTime &other ) const;

        /*!
         * this < other.
         * \param other Reference to other.
         * \return True if this < other, else return false.
         */
        bool operator< ( const BTime &other ) const;

        /*!
         * this <= other.
         * \param other Reference to other.
         * \return True if this <= other, else return false.
         */
        bool operator<= ( const BTime &other ) const;

        /*!
         * this > other.
         * \param other Reference to other.
         * \return True if this > other, else return false.
         */
        bool operator> ( const BTime &other ) const;

        /*!
         * this >= other.
         * \param other Reference to other.
         * \return True if this >= other, else return false.
         */
        bool operator>= ( const BTime &other ) const;

        /*!
         * Set time from other time.
         * \param other Pointer to other time.
         * \return Reference to this.
         */
        BTime &operator= ( const BTime &other );

        bool isValid() const;

        /*!
         * Hour.
         * \return Hour.
         */
        int hour() const;

        /*!
         * Minute.
         * \return Minute.
         */
        int minute() const;

        /*!
         * Second.
         * \return Second.
         */
        int second() const;

        /*!
         * Millisecond.
         * \return Millisecond.
         */
        int msecond() const;

        /*!
         * Return this time + second.
         * \param second Second.
         * \return Final time.
         */
        BTime addSecond ( int second );

        /*!
         * Return this time + msecond.
         * \param msecond Millisecond.
         * \return Final time.
         */
        BTime addMSecond ( int msecond );

        /*!
         * Set time.
         * \param hour Hour.
         * \param minute Minute.
         * \param second Second.
         * \param msecond Millisecond.
         * \return True if time is valid, else return false.
         */
        bool setHMS ( int hour, int minute, int second = 0, int msecond = 0 );

        /*!
         * Start elapsed counter.
         */
        void start();

        /*!
         * Get elapsed time.
         * \return elapsed time.
         */
        long int elapsed() const ;

        /*!
         * Restart elapsed counter and return actual elapsed time.
         * \return Elapsed time.
         */
        long int restart();

        /*!
         * Return number of second to time.
         * \param time Reference to time.
         * \return Number of second to time.
         */
        long int secondTo ( const BTime &time ) const;

        /*!
         * Return number of millisecond to time.
         * \param time Reference to time.
         * \return Number of millisecond to time.
         */
        long int msecondTo ( const BTime &time ) const;

        /*!
         * Get curent time.
         * \return curent time.
         */
        static BTime curentTime();

    private:
        long int Time; //!< Time.
};

BOXE_NAMESPACE_END ( Core )

#endif // BTIME_H
