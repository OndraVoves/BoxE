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


#include "../include/bdatastream.h"
#include "../include/bbytearray.h"
#include <unistd.h>

BOXE_NAMESPACE_BEGIN ( Core )

BDataStream::BDataStream( ) : pDevice ( 0 ) {
}

BDataStream::BDataStream ( BIODevice *device ) : pDevice ( device ) {
}

BDataStream::~BDataStream( ) {
}

BDataStream &BDataStream::writeBytes ( const char *data, unsigned int len ) {
    B_CHECK_PTR ( data );
    B_CHECK_PTR ( pDevice );

    if ( len == 0 ) {
        return *this;
    }

    if ( !pDevice->isOpen() ) {
        return *this;
    }

    if ( !pDevice->isWriteable() ) {
        return *this;
    }

    pDevice->write ( data, len );

    return *this;
}

BDataStream &BDataStream::readBytes ( char *data, unsigned int len ) {
    B_CHECK_PTR ( data );
    B_CHECK_PTR ( pDevice );

    if ( len == 0 ) {
        return *this;
    }

    if ( !pDevice->isOpen() ) {
        return *this;
    }

    if ( !pDevice->isReadable() ) {
        return *this;
    }

    pDevice->read ( data, len );

    return *this;
}

BDataStream &BDataStream::operator<< ( bool b ) {
    return writeBytes ( ( char * ) &b, sizeof ( char ) );
}

BDataStream &BDataStream::operator<< ( char c ) {
    return writeBytes ( ( char * ) &c, sizeof ( char ) );
}

BDataStream &BDataStream::operator<< ( const char *str ) {
    return writeBytes ( str, bstrlen ( str ) + 1 );
}

BDataStream &BDataStream::operator<< ( int i ) {
    return writeBytes ( ( char * ) &i, sizeof ( int ) );
}



BDataStream &BDataStream::operator>> ( bool &b ) {
    readBytes ( ( char * ) &b, 1 );
    return *this;
}

BDataStream &BDataStream::operator>> ( char &c ) {
    readBytes ( &c, 1 );
    return *this;
}

BDataStream &BDataStream::operator>> ( char*& string ) {
    char c = '\0';

    BByteArray str;

    while ( pDevice->getChar ( &c )  ) {
        str << c;
    }

    string = new char[ str.size() + 1 ];

    memcpy ( string, str.constData(), str.size() + 1 );

    return *this;
}

BDataStream &BDataStream::operator>> ( int &i ) {
    readBytes ( ( char * ) &i, sizeof ( int ) );
    return *this;
}

BOXE_NAMESPACE_END ( )
