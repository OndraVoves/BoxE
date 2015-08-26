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

#include "../include/bbuffer.h"

BOXE_NAMESPACE_BEGIN ( Core )

BBuffer::BBuffer()
    : BIODevice(), pcByteArray ( 0 ), Position ( 0 ) {
}

BBuffer::BBuffer ( BByteArray *pc_byte_array )
    : BIODevice(), pcByteArray ( pc_byte_array ), Position ( 0 ) {
}

BBuffer::~BBuffer() {
}

bool BBuffer::atEnd() const {
    return !pcByteArray ? true : (  pcByteArray->size() == Position );
}

bool BBuffer::seek ( int pos ) {
    if ( !isOpen() ) {
        return false;
    }

    if (  ( pcByteArray ) &&  ( pos < pcByteArray->size() ) ) {
        Position = pos;
        return true;
    } else {
        return false;
    }
}

long BBuffer::bytesAvailable() const {
    return !pcByteArray ? 0 : pcByteArray->size();
}

bool BBuffer::canReadLine() const {
    return !pcByteArray ? 0 : pcByteArray->contains ( '\n' ) ;
}

int BBuffer::writeData ( const char *data, int size ) {
    if ( !pcByteArray ) {
        return -1;
    }

    if ( atEnd() ) {
        pcByteArray->append ( data, size );
    }
    pcByteArray->replace ( Position, size, data );

    Position += size;

    return size;
}

int BBuffer::readData ( char *data, int size ) {
    if ( !pcByteArray ) {
        return -1;
    }

    strncpy ( data, pcByteArray->constData() + Position, size );
    data[ size ] = '\0';

    Position += size;
    return size;
}

BOXE_NAMESPACE_END ( )
