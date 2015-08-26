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


#ifndef BSETTINGS_H
#define BSETTINGS_H

#include "./bglobal.h"
#include "./bvariant.h"
#include "./bhash.h"
#include "./blinkedlist.h"
#include "./basciistring.h"

BOXE_NAMESPACE_BEGIN ( Core )

class BSettings {
    public:
        BSettings();
        ~BSettings();

        BVariant value ( const BAsciiString &key, const BVariant &default_value = BVariant() ) const;
        void setValue ( const BAsciiString &key, const BVariant &value );
        void remove ( const BAsciiString &key );


        BLinkedList< BAsciiString > allKeys() const;

    private:
        BHash< BAsciiString, BVariant > VariantsHash;
};

BOXE_NAMESPACE_END ( Core )

#endif // BSETTINGS_H
