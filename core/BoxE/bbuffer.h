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

#ifndef BBUFFER_H
#define BBUFFER_H

#include "bglobal.h"
#include "biodevice.h"
#include "bbytearray.h"

BOXE_NAMESPACE_BEGIN ( Core )

class BBuffer : public BIODevice {
    public:
        BBuffer();
        BBuffer ( BByteArray *pc_byte_array );
        virtual ~BBuffer();


        virtual bool atEnd() const;

        virtual int pos() const {
            return Position;
        }

        virtual bool seek ( int pos );

        virtual long bytesAvailable() const;
        virtual bool canReadLine() const;

    protected:
        virtual int writeData ( const char *data, int size );
        virtual int readData ( char *data, int size );
    private:
        BByteArray *pcByteArray;
        int Position;
};

BOXE_NAMESPACE_END ( )

#endif // BBUFFER_H
