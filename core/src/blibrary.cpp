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


#include "../include/blibrary.h"

#ifdef B_OS_UNIX
#include <dlfcn.h>
#elif defined(B_OS_WIN)
#endif

#include <cstring>

BOXE_NAMESPACE_BEGIN ( Core )

#ifdef B_OS_UNIX
BLibrary::BLibrary() : Handler ( 0 ) {
}

BLibrary::BLibrary ( const BAsciiString &filename ) : Handler ( 0 ) {
    setTrueFilename ( filename );
}
#elif defined(B_OS_WIN)
BLibrary::BLibrary() : Handler ( NULL ) {
}

BLibrary::BLibrary ( const BAsciiString &filename ) : Handler ( NULL ) {
    setTrueFilename ( filename );
}
#endif

BLibrary::~BLibrary() {
    unload();
}

BAsciiString BLibrary::errorString() const {
#ifdef B_OS_UNIX
    return BAsciiString ( dlerror() );
#elif defined(B_OS_WIN)
#endif
}

bool BLibrary::load() {
#ifdef B_OS_UNIX
    Handler = dlopen ( Filename.constData(), RTLD_NOW );
    if ( Handler == 0 ) {
        return false;
    }
#elif defined(B_OS_WIN)
#endif
    return true;
}

void *BLibrary::resolv ( const BAsciiString &symbol ) {
#ifdef B_OS_UNIX
    void *sym = dlsym ( Handler, symbol.constData() );
    return sym;
#elif defined(B_OS_WIN)
    void *sym = ( void * ) GetProcAddress ( Handler, symbol.constData() );
    return sym;
#endif
}


bool BLibrary::unload() {
#ifdef B_OS_UNIX
    if ( Handler == 0 ) {
        return true;
    }

    return dlclose ( Handler );
#elif defined(B_OS_WIN)
    if ( Handler == NULL ) {
        return true;
    }

    return FreeLibrary ( Handler );
#endif
}

bool BLibrary::isLibrary ( const char *filename ) {
#ifdef B_OS_UNIX
    return !strcmp ( ".so", & ( filename[strlen ( filename ) - 3] ) );
#elif defined(B_OS_APPLE)
    return ( !strcmp ( ".so", & ( filename[strlen ( filename ) - 3] ) ) ||
             !strcmp ( ".dylib", & ( filename[strlen ( filename ) - 6] ) ) ||
             !strcmp ( ".bundle", & ( filename[strlen ( filename ) - 7] ) ) ) )
    );
#elif defined(B_OS_WIN)
    return !strcmp ( ".dll", & ( filename[strlen ( filename ) - 4] ) );
#endif
}

#define SHORT_FILE( filename ) (strrchr(filename,'/') ? strrchr(filename,'/')+1 : filename)
void BLibrary::setTrueFilename ( const BAsciiString &filename ) {
// TODO: this not nice =(.

    BAsciiString s2 ( SHORT_FILE ( filename.constData() ) );
    BAsciiString s1 ( filename );

    s1.remove ( filename.size() - s2.size(), s2.size() );

#ifdef B_OS_UNIX
    if ( filename.startsWith ( "lib" ) && filename.endsWith ( ".so" ) ) {
        Filename = filename;
        return;
    }

    if ( !s2.startsWith ( "lib" ) ) {
        s2.prepend ( "lib" );
    }

    if ( !s2.endsWith ( ".so" ) ) {
        s2.append ( ".so" );
    }

#elif defined(B_OS_WIN)
    if ( filename.endsWith ( ".dll" ) ) {
        Filename = filename;
        return;
    }


    if ( !s2.endsWith ( ".dll" ) ) {
        s2.append ( ".dll" );
    }
#endif

    Filename = s1 << s2;
}

BOXE_NAMESPACE_END ( Core )
