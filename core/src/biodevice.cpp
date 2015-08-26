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

#include "../include/biodevice.h"
#include "../include/bbytearray.h"


BOXE_NAMESPACE_BEGIN ( Core )

BIODevice::BIODevice() : ActualOpenMode ( NotOpen ) {
}

BIODevice::~BIODevice() {
    if ( isOpen() ) {
        close();
    }
}

int BIODevice::write ( const char *data, int size ) {
    if ( !isWriteable() && !isOpen() ) {
        return -1;
    }

    return writeData ( data, size );
}

int BIODevice::write ( const char *data ) {
    if ( !isWriteable() && !isOpen() ) {
        return -1;
    }

    return writeData ( data, bstrlen ( data ) );
}

int BIODevice::read ( char *data, int size ) {
    if ( !isReadable() && !isOpen() ) {
        return -1;
    }

    return readData ( data, size );
}

BByteArray BIODevice::read ( int max_size ) {
    if ( !isReadable() && !isOpen() ) {
        return BByteArray();
    }

    long size = bMin ( bytesAvailable(), ( long ) max_size );

    char *temp_array = ( char * ) malloc ( sizeof ( char ) * ( size ) );
    read ( temp_array, size );

    B_CHECK_PTR ( temp_array );

    BByteArray ret ( temp_array, size );

    return ret;
}

BByteArray BIODevice::readAll( ) {
    if ( !isReadable() && !isOpen() ) {
        return BByteArray();
    }

    size_t size = bytesAvailable();

    char *temp_array = ( char * ) malloc ( sizeof ( char ) * ( size ) );

    //char *temp_array = new char[ size ];

    B_CHECK_PTR ( temp_array );
    read ( temp_array, size );

    BByteArray ret;
    return ret.setRawData ( temp_array, size ) ;
}

long BIODevice::readLine ( char *data, long max_size ) {
    if ( ( !isReadable() && !isOpen() ) || !data ) {
        return -1;
    }

    return readLineData ( data, max_size );
}

int BIODevice::readLineData ( char *data, int size ) {
    long read_size = 1;
    while ( getChar ( data ) or ( size ) ) {
        if ( *data == '\n' ) {
            *data = '\0';
            return read_size;
        }

        data++;
        read_size++;
        size--;
    }

    * ( data ) = '\0';
    return read_size;
}

bool BIODevice::getChar ( char *c ) {
    if ( ( !isReadable() && !isOpen() ) || !c || atEnd() ) {
        return false;
    }

    return readData ( c, 1 );
}

bool BIODevice::putChat ( char c ) {
    if ( ( !isWriteable() && !isOpen() ) ||  atEnd() ) {
        return false;
    }

    return write ( &c, 1 );
}

BOXE_NAMESPACE_END ()
