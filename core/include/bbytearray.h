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

#ifndef BBYTEARRAY_H
#define BBYTEARRAY_H

#include <stdlib.h>
#include <string.h>

#include "bglobal.h"
#include "breferencecounter.h"
#include "blinkedlist.h"
#include "bdatastream.h"

BOXE_NAMESPACE_BEGIN ( Core )

/*!
 * Return lenght of string.
 * \param string String.
 * \return String lenght.
 */
extern unsigned int bstrlen ( const char *string );

extern int bstrcmp ( const char *string1, const char *string2 );
extern int bstrncmp ( const char *string1, const char *string2, unsigned int len );
extern int bstricmp ( const char *string1, const char *string2 );
extern int bstrincmp ( const char *string1, const char *string2, unsigned int len );

inline bool isAlphabetic ( char ch ) {
    return ( ( ch >= 'a' ) && ( ch <= 'z' ) ) || ( ( ch >= 'A' ) && ( ch <= 'Z' ) );
}

inline bool isUpper ( char ch ) {
    return ( ( ch >= 'A' ) && ( ch <= 'Z' ) );
}

inline bool isLower ( char ch ) {
    return ( ( ch >= 'a' ) && ( ch <= 'z' ) );
}

inline bool isNumeric ( char ch ) {
    return ( ( ch >= '0' ) && ( ch <= '9' ) );
}

inline bool isAlphanumeric ( char ch ) {
    return ( ( ch >= 'a' ) && ( ch <= 'z' ) ) || ( ( ch >= 'A' ) && ( ch <= 'Z' ) ) || ( ( ch >= '0' ) && ( ch <= '9' ) );
}


class BByteArray {
    private:
        /*!
         * Internal data class.
         */
        class BByteArrayData {
            public:
                BByteArrayData ( int size ) : AllocSize ( 0 ), Size ( 0 ), Array ( 0 ) {
                    if ( size != 0 ) {
                        alloc ( size );
                    }
                }

                ~BByteArrayData() {
                    if ( Array ) {
                        free ( Array );
                    }
                }

                inline void alloc ( int size ) {
                    B_ASSERT ( size > 0 );

                    if ( Array != 0 ) {
                        free ( Array );
                        Array = 0;
                    }

                    Array = ( char * ) malloc ( sizeof ( char ) * size );
                    B_CHECK_PTR ( Array );

                    AllocSize = size;
                }

                void realloc ( int new_size ) {
                    B_ASSERT ( new_size >= Size );

                    if ( new_size == 0 ) {
                        free ( Array );
                        Array = 0;
                        AllocSize = 0;
                        return;
                    }

                    if ( new_size == AllocSize ) {
                        return;
                    }

                    char *new_array = ( char * ) malloc ( sizeof ( char ) * new_size );
                    B_CHECK_PTR ( new_array );

                    //memmove ( new_array, Array, sizeof ( char ) * Size );
                    memcpy ( new_array, Array, sizeof ( char ) * Size );
                    // BUG: free raise double-free !!!
                    //free ( Array );

                    Array = new_array;
                    AllocSize = new_size;
                }

                BByteArrayData *makeHardCopy( ) {
                    BByteArrayData *new_data = 0;
                    BOXE_TRY {
                        new_data = new BByteArrayData ( AllocSize );

                        B_CHECK_PTR ( new_data );

                    } BOXE_CATCH ( const std::bad_alloc & ) {
                        BOXE_RETHROW;
                    }

                    new_data->Size = Size;

                    //TODO: memcopy.
                    if ( Size != 0 ) {
                        char *it = Array + Size;
                        char *it2 = new_data->Array + new_data->Size;
                        while ( it != Array ) {
                            * ( --it2 ) = char ( * ( --it ) );
                        }
                    }

                    return new_data;
                };


            public:
                BReferenceCounter ReferenceCounter; //!< Reference counter.

                int AllocSize; //!< Reserved size.
                int Size;         //!< Item count.

                char *Array; //!< Item Array.
        };

    public:
        BByteArray();
        BByteArray ( const char *string );
        BByteArray ( const char *data, int size );
        BByteArray ( int size, char byte );
        BByteArray ( const BByteArray &other );
        ~BByteArray();

        BByteArray &operator= ( const BByteArray &other );

        BByteArray &operator= ( const char *string ) {
            *this = BByteArray ( string );
            return *this;
        }

        bool operator == ( const BByteArray &other ) const;
        bool operator == ( const char *string ) const;

        inline BByteArray &operator<< ( char ch ) {
            return append ( ch );
        }

        inline BByteArray &operator<< ( const char *ch ) {
            return append ( ch );
        }

        inline BByteArray &operator<< ( const BByteArray &other ) {
            return append ( other );
        }

        char &operator[] ( int index );
        char operator[] ( int index ) const;


        inline bool isEmpty() const {
            return ( Data->Size == 0 );
        }

        inline bool isNull() const {
            return ( Data == 0 ) ;
        }

        inline bool isSharedWith ( const BByteArray &other ) {
            return Data == other.Data;
        }

        inline char *data() {
            detach();
            return Data->Array;
        }

        inline const char *data() const {
            return Data->Array;
        }

        inline const char *constData() const {
            return Data->Array;
        }

        inline char at ( int index ) const {
            B_ASSERT_MSG ( ( index >= 0 && index < Data->Size ), "BByteArray<T>::at", "Index out of range" );
            return Data->Array[ index ];
        }

        BByteArray &append ( char ch );
        inline BByteArray &append ( const char *data ) {
            return append ( data, bstrlen ( data ) );
        }

        BByteArray &append ( const char *data, int size );
        BByteArray &append ( const BByteArray &other );

        BByteArray &insert ( int index,  char ch );
        BByteArray &insert ( int index,  const char *string );
        BByteArray &insert ( int index,  const char *string, int len );
        BByteArray &insert ( int index,  const BByteArray &byte_array );

        inline BByteArray &prepend ( char ch ) {
            return insert ( 0, ch );
        }

        inline BByteArray &prepend ( const char *string ) {
            return insert ( 0, string );
        }

        inline BByteArray &prepend ( const BByteArray &byte_array ) {
            return insert ( 0, byte_array );
        }

        inline void detach() {
            if ( Data->ReferenceCounter != 1 ) {
                detach_internal();
            }
        }

        inline int capacity() {
            return Data->AllocSize;
        }

        inline int size() const {
            return Data->Size;
        }

        inline void clear() {
            resize ( 0 );
        }

        void resize ( int new_size );

        inline void reserve ( int size ) {
            detach();
            Data->realloc ( size );
        }

        BByteArray left ( int index ) const;

        inline bool startsWith ( char ch ) const {
            return Data->Size == 0 ? false : ( Data->Array[0] == ch );
        }
        bool startsWith ( const char *string ) const;
        bool startsWith ( const BByteArray &string ) const;

        inline bool endsWith ( char ch ) const {
            return Data->Size == 0 ? false : ( Data->Array[Data->Size - 1 ] == ch );
        }
        bool endsWith ( const char *string ) const;
        bool endsWith ( const BByteArray &string ) const;

        bool contains ( char ch ) const;
        bool contains ( const char *string ) const;
        bool contains ( const BByteArray &string ) const;

        int count ( char ch ) const;
        int count ( const char *string ) const;
        int count ( const BByteArray &string ) const;

        BByteArray repeated ( int num ) const;

        BByteArray &remove ( int position, int len );

        BByteArray &replace ( int position, int len, const char *after );
        BByteArray &replace ( int position, int len, const char *after, int after_len );
        BByteArray &replace ( int position, int len, const BByteArray &after );

        BByteArray &replace ( char before, char after );
        BByteArray &replace ( char before, const char *after );
        BByteArray &replace ( char before, const BByteArray &after );

        BByteArray &replace ( const char *before, const BByteArray &after );
        BByteArray &replace ( const char *before, int before_len, const char *after, int after_len );
        BByteArray &replace ( const BByteArray &before, const char *after );
        BByteArray &replace ( const BByteArray &before, const BByteArray &after );

        int indexOf ( char ch, int from = 0 ) const;
        int indexOf ( const char *string, int from = 0 ) const;
        int indexOf ( const BByteArray &string, int from = 0 ) const;

        BLinkedList< BByteArray > split ( char sep_char ) const;

        BByteArray toBase64( ) const;

        BByteArray toLower() const;
        BByteArray toUpper() const;

        /*!
         * Remove all unused memory.
         */
        inline void squeeze() {
            reserve ( size() );
        }

        BByteArray &setRawData ( char *data, int size );

        operator char *() {
            return data();
        }

        operator const char *() const {
            return constData();
        }


        int toInt ( bool *ok, int base = 10 ) const;

        BByteArray &setNum ( int num, int base = 10 );
        BByteArray &setNum ( unsigned int num, int base = 10 );

    public:
        static BByteArray fromBase64 ( const BByteArray &code );
        inline static BByteArray number ( int num, int base = 10 ) {
            return BByteArray().setNum ( num, base );
        }
    private:
        BByteArrayData *Data;

    private:
        void detach_internal();
};

inline BDataStream &operator<< ( BDataStream &stream, const BByteArray &bytearray ) {
    return stream.writeBytes ( bytearray.constData(), bytearray.size() );
}

extern long bCalcHash ( const BByteArray &value );

BOXE_NAMESPACE_END ( Core )
#endif // BBYTEARRAY_H
