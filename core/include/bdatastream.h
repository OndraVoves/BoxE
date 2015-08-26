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


#ifndef BDATASTREAM_H
#define BDATASTREAM_H

#include "bglobal.h"
#include "biodevice.h"

BOXE_NAMESPACE_BEGIN ( Core )


class BDataStream {
    public:
        BDataStream(  );
        BDataStream ( BIODevice *device );
        ~BDataStream( );

        BIODevice *device() const {
            return pDevice;
        }

        void setDevice ( BIODevice *device ) {
            pDevice = device;
        }

        bool atEnd( ) const {
            B_CHECK_PTR ( pDevice );
            return pDevice->atEnd();
        }

        BDataStream &writeBytes ( const char *data, unsigned int len );
        BDataStream &readBytes ( char *data, unsigned int len );

        BDataStream &operator<< ( bool b );
        BDataStream &operator<< ( char c );
        BDataStream &operator<< ( const char *str );
        BDataStream &operator<< ( int i );

        BDataStream &operator>> ( bool &b );
        BDataStream &operator>> ( char &c );
        BDataStream &operator>> ( char*& string );
        BDataStream &operator>> ( int &i );

    private:
        BIODevice *pDevice;
};

BOXE_NAMESPACE_END ( )

#endif // BDATASTREAM_H
