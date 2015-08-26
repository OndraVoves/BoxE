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

#ifndef BIODEVICE_H
#define BIODEVICE_H

#include "bglobal.h"

BOXE_NAMESPACE_BEGIN ( Core )

class BByteArray;

// TODO: size and etc... need large type not int...

class BIODevice {
    public:
        typedef enum {
            NotOpen = 0x0000,
            ReadOnly = 0x0001,
            WriteOnly = 0x0002,
            ReadWrite = ReadOnly | WriteOnly,
            Append = 0x0004,
            Text =  0x0010
        } OpenMode;

    public:
        BIODevice();
        virtual ~BIODevice();

        OpenMode openMode() const {
            return ActualOpenMode;
        }

        bool isOpen() const {
            return ActualOpenMode;
        }
        bool isReadable() const {
            return ( ActualOpenMode & 0x0001 );
        }
        bool isWriteable() const {
            return ( ActualOpenMode & 0x0002 );
        }

        virtual bool atEnd() const {
            return true;
        }

        virtual bool open ( OpenMode open_mode ) {
            ActualOpenMode = open_mode;
            return false;
        }

        virtual void close( ) {
            ActualOpenMode = BIODevice::NotOpen;
        };

        int write ( const char *data, int size );
        int write ( const char *data );

        int read ( char *data, int size );
        BByteArray read ( int max_size );
        BByteArray readAll();

        long readLine ( char *data, long max_size );

        bool getChar ( char *c );
        bool putChat ( char c );

        virtual int pos() const {
            return 0;
        }
        virtual bool seek ( int pos ) {
            ( void ) pos;
            return false;
        }

        virtual long bytesAvailable() const = 0;
        virtual bool canReadLine() const = 0;

    protected:
        void setOpenMode ( OpenMode open_mode ) {
            ActualOpenMode = open_mode;
        }

        virtual int writeData ( const char *data, int size ) = 0;
        virtual int readData ( char *data, int size ) = 0;
        virtual int readLineData ( char *data, int size );
    private:
        OpenMode ActualOpenMode;

};

BOXE_NAMESPACE_END ( )

#endif // BIODEVICE_H
