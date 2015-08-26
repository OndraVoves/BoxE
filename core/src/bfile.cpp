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

#include "../include/bfile.h"

BOXE_NAMESPACE_BEGIN ( Core )

BFile::BFile() : BIODevice(), pfFile ( 0 ), Position ( 0 ) {
}

BFile::BFile ( const BAsciiString &filename ) : BIODevice(), Filename ( filename ), pfFile ( 0 ), Position ( 0 ) {
}

BFile::~BFile() {
}

bool BFile::atEnd() const {
    return  ( Buffer.size()  == Position );
}

bool BFile::open (  BIODevice::OpenMode open_mode ) {
    if ( Filename.isEmpty() || ( open_mode & NotOpen ) ) {
        return false;
    }

    char flag[3] = { '\0', '\0', '\0' };

    switch ( open_mode ) {
        case ReadOnly:
            flag[0] = 'r';
            break;

        case WriteOnly:
            flag[0] = 'w';
            break;

        case ReadWrite:
            flag[0] = 'w';
            flag[1] = '+';
            break;

        case Append:
            flag[0] = 'a';
            break;
    }


    pfFile =  fopen ( Filename.constData(),  flag );

    if ( !pfFile ) {
        return false;
    }

    if ( open_mode & BIODevice::ReadOnly ) {
        fseek ( pfFile, 0, SEEK_END );
        size_t size = ftell ( pfFile );
        fseek ( pfFile, 0, SEEK_SET );

        char *inter_buffer = ( char * ) malloc ( size + 1 );
        fread ( inter_buffer, 1, size, pfFile );
        * ( inter_buffer + size + 1 ) = '\0';

        Buffer.setRawData ( inter_buffer, size + 1 );

        fseek ( pfFile, 0, SEEK_SET );
    }

    BIODevice::open ( open_mode );
    return true;
}

bool BFile::open ( FILE *file, BIODevice::OpenMode open_mode ) {
    BIODevice::open ( open_mode );
    pfFile = file;
    return true;
}

void BFile::close( ) {
    if ( !isOpen() ) {
        return;
    }

    Buffer.clear();
    Position = 0;
    fclose ( pfFile );

    BIODevice::close();
}

long BFile::bytesAvailable() const {
    return Buffer.size();
}

bool BFile::canReadLine() const {
    return Buffer.contains ( '\n' ) ;
}


bool BFile::copy ( const BAsciiString &new_filename ) {
    return copy ( Filename, new_filename );
}

bool BFile::exists() const {
    return exists ( Filename );
}

bool BFile::exists ( const BAsciiString &filename ) {
    if ( filename.isEmpty() ) {
        return false;
    }

    FILE *file = fopen ( filename.constData(), "r" );

    if ( !file ) {
        return false;
    }

    fclose ( file );
    return true;
}

bool BFile::copy ( const BAsciiString &filename, const BAsciiString &new_filename ) {
    if ( !exists ( filename ) || exists ( new_filename ) ) {
        return false;
    }

    BFile file_in ( filename );
    if ( !file_in.open ( BIODevice::ReadOnly ) ) {
        return false;
    }

    BFile file_out ( new_filename );
    if ( !file_out.open ( BIODevice::WriteOnly ) ) {
        return false;
    }

    file_out.write ( file_in.Buffer );

    file_in.close();
    file_out.close();

    return true;
}

bool BFile::seek ( int pos ) {
    if ( !isOpen() ) {
        return false;
    }

    if (  pos < Buffer.size() ) {
        Position = pos;
        return true;
    } else {
        return false;
    }
}

int BFile::writeData ( const char *data, int size ) {
    if ( !fwrite ( data, 1, size, pfFile ) ) {
        return -1;
    }

    if ( atEnd() ) {
        Buffer.append ( data, size );
    } else {
        Buffer.replace ( Position, size, data );
    }

    Position += size;

    return size;
}

int BFile::readData ( char *data, int size ) {
    //strncpy ( data, Buffer.constData() + Position, size );
    memcpy ( data, Buffer.constData() + Position, size );
    data[ size ] = '\0';

    Position += size;
    //fseek ( pfFile, Position, SEEK_SET );
    return size;
}

BOXE_NAMESPACE_END ( )
