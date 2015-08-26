/*
    <one line to give the library's name and an idea of what it does.>
    Copyright (C) 2011  <copyright holder> <email>

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


#ifndef BCOMPLEXD_H
#define BCOMPLEXD_H

#include "./bglobal.h"
#include "bgoniometry.h"
#include <cmath>

BOXE_NAMESPACE_BEGIN ( Math )

class BComplexd {
    public:
        BComplexd();
        BComplexd ( double re, double im );
        BComplexd ( const BComplexd &other );

        BComplexd &operator = ( const BComplexd &other );
        bool operator == ( const BComplexd &other ) const;
        bool operator != ( const BComplexd &other ) const;

        BComplexd operator+ ( const BComplexd &other ) const;
        BComplexd &operator+= ( const BComplexd &other  );

        BComplexd operator- ( const BComplexd &other ) const;
        BComplexd &operator-= ( const BComplexd &other  );

        BComplexd operator* ( const BComplexd &other ) const;
        BComplexd &operator*= ( const BComplexd &other ) ;

        double real() const {
            return Re;
        }

        double imaginar() const {
            return Im;
        }

        void real ( double r ) {
            Re = r;
        }

        void imaginar ( double i ) {
            Im = i;
        }

        BComplexd conjugated() const;

        double modul() const;
        double modulSquared() const;

        double argument() const;

        BComplexd powerOf2( ) const;

    private:
        double Re;
        double Im;
};

inline BComplexd::BComplexd() : Re ( 0.0f ), Im ( 0.0f ) {
}

inline BComplexd::BComplexd ( double re, double im ) : Re ( re ), Im ( im ) {
}

inline BComplexd::BComplexd ( const BComplexd &other ) : Re ( other.Re ), Im ( other.Im ) {
}

inline BComplexd &BComplexd::operator = ( const BComplexd &other ) {
    Re = other.Re;
    Im = other.Im;

    return *this;
}

inline bool BComplexd::operator == ( const BComplexd &other ) const {
    return ( Core::bFuzzyCompare ( Re, other.Re ) &&  Core::bFuzzyCompare ( Re, other.Re ) );
}

inline bool BComplexd::operator != ( const BComplexd &other ) const {
    return ! ( Core::bFuzzyCompare ( Re, other.Re ) &&  Core::bFuzzyCompare ( Re, other.Re ) );
}

inline BComplexd BComplexd::operator+ ( const BComplexd &other ) const {
    return BComplexd ( Re + other.Re, Im + other.Im );
}

inline BComplexd &BComplexd::operator+= ( const BComplexd &other ) {
    Re += other.Re;
    Im += other.Im;

    return *this;
}

inline BComplexd BComplexd::operator- ( const BComplexd &other ) const {
    return BComplexd ( Re - other.Re, Im - other.Im );
}

inline BComplexd &BComplexd::operator-= ( const BComplexd &other ) {
    Re -= other.Re;
    Im -= other.Im;

    return *this;
}

inline BComplexd BComplexd::operator* ( const BoxE::Math::BComplexd &other ) const {
    return BComplexd ( ( Re * other.Re ) - ( Im * other.Im ), ( Re * other.Im ) + ( Im * other.Re ) );
}

inline BComplexd &BComplexd::operator*= ( const BoxE::Math::BComplexd &other ) {
    double r = ( Re * other.Re ) - ( Im * other.Im );
    double i =  ( Re * other.Im ) + ( Im * other.Re );

    Re = r;
    Im = i;

    return *this;
}

inline BComplexd BComplexd::conjugated() const {
    return BComplexd ( Re, -Im );
}

inline double BComplexd::modul() const {
    return sqrt ( ( Re * Re ) + ( Im * Im ) );
}

inline double BComplexd::modulSquared() const {
    return ( Re * Re ) + ( Im * Im );
}

inline double BComplexd::argument() const {
    return bRad2Deg ( acos ( Re / modul() ) );
}

inline BComplexd BComplexd::powerOf2( ) const {
    return BComplexd ( ( Re * Re ) - ( Im * Im ), 2 * Re * Im  );
}

BOXE_NAMESPACE_END ( Math )

#endif // BCOMPLEXD_H
