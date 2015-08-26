/*
   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License version 2 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#ifndef BGONIOMETRY_H
#define BGONIOMETRY_H

#include "./bglobal.h"
#include <cmath>

BOXE_NAMESPACE_BEGIN ( Math )

static const float PI      = 3.1415926535898; //!< PI
static const float TWO_PI  = 6.2831853071796; //!< PI * 2
static const float HALF_PI = 1.5707963267949; //!< PI / 2

template< class T >
static inline T bDeg2Rad ( T angle_deg ) {
    return ( ( PI * angle_deg ) / 180.0 );
}

template< class T >
static inline T bRad2Deg ( T angle_rad ) {
    return ( ( angle_rad * 180.0 ) / PI );
}

inline float bFastSin ( const float angle ) {
    return sin ( angle );

    float x = angle;

    if ( x > PI ) {
        x = PI - x;
    }

    const float B = 4.0f / PI;
    const float C = -4.0f / ( PI * PI );

    return ( B * x ) + ( C * x * bAbs ( x ) );
}

inline float bFastCos ( const float angle ) {
    return cos ( angle );
    float x = angle;

    x += PI / 2;

    if ( x > PI ) {
        x -= 2 * PI;
    }

    return bFastSin ( x );
}

BOXE_NAMESPACE_END ( Math )

#endif /* BGONIOMETRY_h */
