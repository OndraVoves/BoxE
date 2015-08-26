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


#include "../include/bsettings.h"

BOXE_NAMESPACE_BEGIN ( Core )

BSettings::BSettings() {

}

BSettings::~BSettings() {

}

BVariant BSettings::value ( const BAsciiString &key, const BVariant &default_value ) const {
    BHash< BAsciiString, BVariant >::ConstIterator it =  VariantsHash.find ( key );
    if ( it == VariantsHash.constEnd() ) {
        return default_value;
    } else {
        return ( *it );
    }
}

void BSettings::setValue ( const BAsciiString &key, const BVariant &value ) {
    BHash< BAsciiString, BVariant >::Iterator it =  VariantsHash.find ( key );
    if ( it == VariantsHash.end() ) {
        VariantsHash.insert ( key, value );
    } else {
        ( *it ) = value;
    }
}

void BSettings::remove ( const BAsciiString &key ) {
    BHash< BAsciiString, BVariant >::Iterator it =  VariantsHash.find ( key );

    if ( ! ( it == VariantsHash.end() ) ) {
        VariantsHash.erase ( it );
    }
}

BLinkedList< BAsciiString > BSettings::allKeys() const {
    BLinkedList< BAsciiString > keys;
    BHash< BAsciiString, BVariant >::ConstIterator it = VariantsHash.constBegin();

    while ( it != VariantsHash.constEnd() ) {
        keys << it.key();
        ++it;
    }

    return keys;

}

BOXE_NAMESPACE_END ( Core )
