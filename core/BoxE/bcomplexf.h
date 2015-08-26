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


#ifndef BCOMPLEXF_H
#define BCOMPLEXF_H

#include "./bglobal.h"
#include "bgoniometry.h"
#include <cmath>

BOXE_NAMESPACE_BEGIN ( Math )

class BComplexf {
    public:
        BComplexf();
        BComplexf ( float re, float im );
        BComplexf ( const BComplexf &other );

        BComplexf &operator = ( const BComplexf &other );
        bool operator == ( const BComplexf &other ) const;
        bool operator != ( const BComplexf &other ) const;

        BComplexf operator+ ( const BComplexf &other ) const;
        BComplexf &operator+= ( const BComplexf &other  );

        BComplexf operator- ( const BComplexf &other ) const;
        BComplexf &operator-= ( const BComplexf &other  );

        BComplexf operator* ( const BComplexf &other ) const;
        BComplexf &operator*= ( const BComplexf &other ) ;

        float real() const {
            return Re;
        }

        float imaginar() const {
            return Im;
        }

        void real ( float r ) {
            Re = r;
        }

        void imaginar ( float i ) {
            Im = i;
        }

        BComplexf conjugated() const;

        float modul() const;
        float modulSquared() const;

        float argument() const;

        BComplexf powerOf2( ) const;

    private:
        float Re;
        float Im;
};

inline BComplexf::BComplexf() : Re ( 0.0f ), Im ( 0.0f ) {
}

inline BComplexf::BComplexf ( float re, float im ) : Re ( re ), Im ( im ) {
}

inline BComplexf::BComplexf ( const BComplexf &other ) : Re ( other.Re ), Im ( other.Im ) {
}

inline BComplexf &BComplexf::operator = ( const BComplexf &other ) {
    Re = other.Re;
    Im = other.Im;

    return *this;
}

inline bool BComplexf::operator == ( const BComplexf &other ) const {
    return ( Core::bFuzzyCompare ( Re, other.Re ) &&  Core::bFuzzyCompare ( Re, other.Re ) );
}

inline bool BComplexf::operator != ( const BComplexf &other ) const {
    return ! ( Core::bFuzzyCompare ( Re, other.Re ) &&  Core::bFuzzyCompare ( Re, other.Re ) );
}

inline BComplexf BComplexf::operator+ ( const BComplexf &other ) const {
    return BComplexf ( Re + other.Re, Im + other.Im );
}

inline BComplexf &BComplexf::operator+= ( const BComplexf &other ) {
    Re += other.Re;
    Im += other.Im;

    return *this;
}

inline BComplexf BComplexf::operator- ( const BComplexf &other ) const {
    return BComplexf ( Re - other.Re, Im - other.Im );
}

inline BComplexf &BComplexf::operator-= ( const BComplexf &other ) {
    Re -= other.Re;
    Im -= other.Im;

    return *this;
}

inline BComplexf BComplexf::operator* ( const BoxE::Math::BComplexf &other ) const {
    return BComplexf ( ( Re * other.Re ) - ( Im * other.Im ), ( Re * other.Im ) + ( Im * other.Re ) );
}

inline BComplexf &BComplexf::operator*= ( const BoxE::Math::BComplexf &other ) {
    float r = ( Re * other.Re ) - ( Im * other.Im );
    float i =  ( Re * other.Im ) + ( Im * other.Re );

    Re = r;
    Im = i;

    return *this;
}

inline BComplexf BComplexf::conjugated() const {
    return BComplexf ( Re, -Im );
}

inline float BComplexf::modul() const {
    return sqrt ( ( Re * Re ) + ( Im * Im ) );
}

inline float BComplexf::modulSquared() const {
    return ( Re * Re ) + ( Im * Im );
}

inline float BComplexf::argument() const {
    return bRad2Deg ( acos ( Re / modul() ) );
}

inline BComplexf BComplexf::powerOf2( ) const {
    return BComplexf ( ( Re * Re ) - ( Im * Im ), 2 * Re * Im  );
}

BOXE_NAMESPACE_END ( Math )

#endif // BCOMPLEXF_H
