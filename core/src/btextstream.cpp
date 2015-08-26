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


#include "../include/btextstream.h"

BOXE_NAMESPACE_BEGIN ( Core )

BTextStream::BTextStream(  ) : pDevice ( 0 ) {
}

BTextStream::BTextStream ( BIODevice *device ) : pDevice ( device ) {
}

BTextStream::~BTextStream( ) {
}

BAsciiString BTextStream::read ( unsigned long maxsize ) {
    B_CHECK_PTR ( pDevice );

    if ( maxsize == 0 ) {
        return BAsciiString();
    }

    return pDevice->read ( maxsize );
}

BAsciiString BTextStream::readLine ( unsigned long maxsize ) {
    B_CHECK_PTR ( pDevice );

    if ( !pDevice->canReadLine() ) {
        return BAsciiString();
    }

    if ( maxsize == 0 ) {
        return BAsciiString();
    }

    char *str = ( char * ) malloc ( maxsize + 1 );
    long size = pDevice->readLine ( str, maxsize );

    return  BAsciiString ( str, size );
}

BAsciiString BTextStream::readAll() {
    B_CHECK_PTR ( pDevice );

    return pDevice->readAll();
}

BTextStream &BTextStream::operator<< ( char c ) {
    B_CHECK_PTR ( pDevice );
    pDevice->write ( &c, 1 );

    return *this;
}

BTextStream &BTextStream::operator<< ( const char *str ) {
    B_CHECK_PTR ( pDevice );
    pDevice->write ( str, bstrlen ( str ) );
    return *this;
}

BTextStream &BTextStream::operator<< ( int i ) {
    B_CHECK_PTR ( pDevice );
    BByteArray num = BByteArray::number ( i );
    pDevice->write ( num.constData(), num.size() );
    return *this;
}

BTextStream &BTextStream::operator>> ( char &c ) {
    B_CHECK_PTR ( pDevice );
    pDevice->read ( &c, 1 );
    return *this;
}

BTextStream &BTextStream::operator>> ( char *&string ) {
    char c = '\0';

    BByteArray str;

    while ( pDevice->getChar ( &c )  ) {
        str << c;
    }

    string = new char[ str.size() + 1 ];

    memcpy ( string, str.constData(), str.size() + 1 );

    return *this;
}

BOXE_NAMESPACE_END ()
