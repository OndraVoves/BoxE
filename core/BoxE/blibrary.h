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


#ifndef BLIBRARY_H
#define BLIBRARY_H

#include "bglobal.h"
#include "basciistring.h"

BOXE_NAMESPACE_BEGIN ( Core )

class BLibrary {
    public:
        BLibrary();
        BLibrary ( const BAsciiString &filename );
        ~BLibrary();

        BAsciiString filename() const {
            return Filename;
        }

        bool isLoaded() const {
#ifdef B_OS_UNIX
            return ( Handler != 0 );
#elif defined(B_OS_WIN)
            return ( Handler != NULL );
#endif
        }

        bool load();
        bool unload();
        BAsciiString errorString() const;

        void *resolv ( const BAsciiString &symbol );

    private:
        BAsciiString Filename;

#ifdef B_OS_UNIX
        void *Handler;
#elif defined(B_OS_WIN)
        HINSTANCE Handler;
#endif

    private:
        void setTrueFilename ( const BAsciiString &filename );

    public:
        static bool isLibrary ( const char *filename );
};

BOXE_NAMESPACE_END ( Core )

#endif // BLIBRARY_H
