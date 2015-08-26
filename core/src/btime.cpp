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


#include "../include/btime.h"

#include <ctime>

#ifdef B_OS_UNIX
#include <sys/time.h>
#include <sys/timeb.h>
#endif


BOXE_NAMESPACE_BEGIN ( Core )

BTime::BTime() : Time ( 0 ) {
}

BTime::BTime ( int hour, int minute, int second, int msecond )
    :  Time ( 0 ) {
    setHMS ( hour, minute, second, msecond );
}

BTime::BTime (  const BTime &other ) : Time ( other.Time ) {
}

bool BTime::operator== ( const BTime &other ) const {
    return ( Time == other.Time );
}

bool BTime::operator!= ( const BTime &other ) const {
    return ( Time != other.Time );
}

bool BTime::operator< ( const BTime &other ) const {
    return ( Time < other.Time );
}

bool BTime::operator<= ( const BTime &other ) const {
    return ( Time <= other.Time );
}

bool BTime::operator> ( const BTime &other ) const {
    return ( Time > other.Time );
}

bool BTime::operator>= ( const BTime &other ) const {
    return ( Time >= other.Time );
}

BTime &BTime::operator= ( const BTime &other ) {
    Time = other.Time;
    return *this;
}

bool BTime::isValid() const {
    return ( ( ( hour() >= 0 ) && ( hour() <= 23 ) ) &&
             ( ( minute() >= 0 ) && ( minute() <= 59 ) ) &&
             ( ( second() >= 0 ) && ( second() <= 59 ) ) &&
             ( ( second() >= 0 ) && ( second() <= 999 ) ) );
}

int BTime::hour() const {
    return ( Time - ( ( Time / ( 1000 * 60 * 60 * 24 ) ) * ( 1000 * 60 * 60 * 24 ) ) ) / ( 1000 * 60 * 60 );
}

int BTime::minute() const {
    return ( Time - ( ( Time / ( 1000 * 60 * 60 ) ) * ( 1000 * 60 * 60 ) ) ) / ( 1000 * 60 );
}

int BTime::second() const {
    return ( Time - ( ( Time / ( 1000 * 60 ) ) * ( 1000 * 60 ) ) ) / ( 1000 );
}

int BTime::msecond() const {
    return ( Time - ( ( Time / ( 1000 ) ) * ( 1000  ) ) ) ;
}

BTime BTime::addSecond ( int second ) {
    BTime time;
    time.Time = Time + ( second * 60 );
    return time;
}

BTime BTime::addMSecond ( int msecond ) {
    BTime time;
    time.Time = Time + msecond;
    return time;
}

bool BTime::setHMS ( int hour, int minute, int second , int msecond ) {
    Time = ( hour * 60 * 60 * 1000 ) + ( minute * 60 * 1000 ) + ( second * 1000 ) + msecond;
    return isValid();
}


void BTime::start() {
    Time = curentTime().Time;
}

long int BTime::elapsed() const {
    return (  curentTime().Time - Time );
}

long int BTime::restart() {
    long int tmp = elapsed();

    Time = curentTime().Time;

    return tmp;
}

long int BTime::secondTo ( const BTime &time ) const {
    return ( time.Time / 1000 ) - ( Time / 1000 );
}

long int BTime::msecondTo ( const BTime &time ) const {
    return ( time.Time - Time );
}

BTime BTime::curentTime() {
#ifdef B_OS_UNIX
    timeval time1;
    struct tm *local_time;

    gettimeofday ( &time1, 0 );
    local_time = localtime (  &time1.tv_sec );

    BTime time;

    time.Time = ( ( time1.tv_sec + local_time->tm_gmtoff ) * 1000 ) + ( time1.tv_usec / 1000 );

    return time;
#else
    time_t actual_time;
    struct tm *local_time;

    time ( &actual_time );
    local_time = localtime ( &actual_time );

    BTime time;
    //time.Time = ( actual_time + local_time->tm_gmtoff )  * 1000;
    // !TODO tm_gmtoff is not in win!!!????
    return time;
#endif


}

BOXE_NAMESPACE_END ( Core )
