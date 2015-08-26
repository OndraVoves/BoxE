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

#ifndef BFILE_H
#define BFILE_H

#include "bglobal.h"
#include "biodevice.h"
#include "basciistring.h"

#include <cstdio>


BOXE_NAMESPACE_BEGIN ( Core )

class BFile : public BIODevice {
    public:
        BFile();
        BFile ( const BAsciiString &filename );
        virtual ~BFile();

        BAsciiString filenName() const {
            return Filename;
        }

        void setFilename ( const BAsciiString &filename ) {
            Filename = filename;
        }

        virtual bool atEnd() const;

        virtual bool open ( BIODevice::OpenMode open_mode );
        bool open ( FILE *file, BIODevice::OpenMode open_mode );
        virtual void close( );

        virtual int pos() const {
            return Position;
        }

        virtual bool seek ( int pos );

        virtual long bytesAvailable() const;
        virtual bool canReadLine() const;

        BByteArray buffer() const {
            return Buffer;
        }

        bool copy ( const BAsciiString &new_filename );
        bool exists() const;

        static bool exists ( const BAsciiString &filename );
        static bool copy ( const BAsciiString &filename, const BAsciiString &new_filename );

    protected:
        virtual int writeData ( const char *data, int size );
        virtual int readData ( char *data, int size );

    private:
        BAsciiString Filename;
        FILE *pfFile;

        BByteArray Buffer;
        int Position;
};

BOXE_NAMESPACE_END ( )

#endif // BFILE_H
