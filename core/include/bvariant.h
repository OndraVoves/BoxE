/*
    <one line to give the library's name and an idea of what it does.>
    Copyright (C) 2011  Ondra Voves <email>

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


#ifndef BVARIANT_H
#define BVARIANT_H

#include "./bglobal.h"

BOXE_NAMESPACE_BEGIN ( Core )

class BVariant {
    public:
        typedef enum {
            VT_UNKOWN = 0,
            VT_SHORT,
            VT_USHORT,
            VT_INT,
            VT_UINT,
            VT_LONG,
            VT_ULONG,
            VT_FLOAT,
            VT_DOUBLE,
            VT_BOOL,
            VT_CHAR,
            VT_POINTER
        } EVariantType;
    public:
        BVariant();
        BVariant ( const BVariant &other );
        BVariant ( short s );
        BVariant ( unsigned short us );
        BVariant ( int i );
        BVariant ( unsigned int ui );
        BVariant ( long l );
        BVariant ( unsigned long ul );
        BVariant ( float f );
        BVariant ( double d );
        BVariant ( bool b );
        BVariant ( char c );
        BVariant ( void *p );

        template<class T>
        T value();

        template<class T>
        void setValue ( T value  );

    private:
        union data_u {
            short s;
            unsigned short us;
            int i;
            unsigned int ui;
            long l;
            unsigned long ul;
            float f;
            double d;
            bool b;
            char c;
            void *v;
        };

        data_u Data;
        EVariantType Type;
};



BOXE_NAMESPACE_END ( Core )
#endif // BVARIANT_H
