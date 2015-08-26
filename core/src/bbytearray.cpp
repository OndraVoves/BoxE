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

#include "../include/bbytearray.h"
#include "../include/bglobal.h"

#include <cmath>

BOXE_NAMESPACE_BEGIN ( Core )

BByteArray::BByteArray() : Data ( 0 ) {
    BOXE_TRY {

        Data = new BByteArrayData ( 1 );
        B_CHECK_PTR ( Data );

        Data->ReferenceCounter.reference();

    } BOXE_CATCH ( const std::bad_alloc & ) {
        BOXE_RETHROW;
    }


    Data->Size = 0;
    Data->Array[0] = '\0';
}

BByteArray::BByteArray ( int size, char byte ) {
    BOXE_TRY {

        Data = new BByteArrayData ( size + 1 );
        B_CHECK_PTR ( Data );

        Data->ReferenceCounter.reference();

    } BOXE_CATCH ( const std::bad_alloc & ) {
        BOXE_RETHROW;
    }

    memset ( Data->Array, byte, sizeof ( char ) * size );

    Data->Size = size;
    Data->Array[size] = '\0';
}

BByteArray::BByteArray ( const char *data, int size ) {
    BOXE_TRY {

        Data = new BByteArrayData ( size + 1 );
        B_CHECK_PTR ( Data );

        Data->ReferenceCounter.reference();

    } BOXE_CATCH ( const std::bad_alloc & ) {
        BOXE_RETHROW;
    }

    memcpy ( Data->Array, data, sizeof ( char ) * size );

    Data->Size = size;
    Data->Array[size] = '\0';
}

BByteArray::BByteArray ( const char *string ) : Data ( 0 ) {
    B_ASSERT ( string != 0 );

    size_t string_leng = bstrlen ( string );


    BOXE_TRY {

        Data = new BByteArrayData ( string_leng + 1 );
        B_CHECK_PTR ( Data );

        Data->ReferenceCounter.reference();

    } BOXE_CATCH ( const std::bad_alloc & ) {
        BOXE_RETHROW;
    }

    memcpy ( Data->Array, string, sizeof ( char ) * string_leng );

    Data->Size = string_leng;

    Data->Array[string_leng] = '\0';
}

BByteArray::BByteArray ( const BByteArray &other ) : Data ( other.Data ) {
    if ( Data ) {
        Data->ReferenceCounter.reference();
    }
}

BByteArray::~BByteArray() {
    if ( !Data->ReferenceCounter.dereference() ) {
        delete Data;
    }
}

bool BByteArray::operator == ( const BByteArray &other ) const {
    if ( Data == other.Data ) {
        return true;
    }

    if ( Data->Size != other.Data->Size ) {
        return false;
    }

    return !bstrncmp ( Data->Array, other.Data->Array, other.Data->Size );
}

bool BByteArray::operator == ( const char *string ) const {
    int str_len = bstrlen ( string );

    if ( Data->Size != str_len ) {
        return false;
    }

    return !bstrncmp ( Data->Array, string, str_len );
}

BByteArray &BByteArray::append ( char ch ) {
    detach();

    if ( Data->AllocSize < Data->Size + 1 ) {
        Data->realloc ( Data->Size + 1 );
    }

    Data->Array[ Data->Size ] = ch;
    Data->Array[ Data->Size + 1 ] = '\0';

    Data->Size += 1;
    return *this;
}

BByteArray &BByteArray::append ( const char *data, int size  ) {
    detach();

    if ( Data->AllocSize < Data->Size + size + 1 ) {
        Data->realloc ( Data->Size + size + 1 );
    }

    memcpy ( Data->Array + Data->Size, data, sizeof ( char ) * size );
    Data->Array[ Data->Size + size  ] = '\0';

    Data->Size += size;

    return *this;
}

BByteArray &BByteArray::append ( const BByteArray &other ) {
    detach();

    const char *ch = other.Data->Array;

    size_t string_leng = other.Data->Size;

    if ( ( size_t ) Data->AllocSize < Data->Size + string_leng + 1 ) {
        Data->realloc ( Data->Size + string_leng + 1 );
    }

    memcpy ( Data->Array + Data->Size, ch, sizeof ( char ) * string_leng );
    Data->Array[ Data->Size + string_leng  ] = '\0';

    Data->Size += string_leng;

    return *this;
}

BByteArray &BByteArray::insert ( int index,  char ch ) {
//    B_ASSERT_MSG ( ( index >= 0 && index < Data->Size ), "BByteArray<T>::insert", "Index out of range" );

    int begin_distance = index;

    detach();

    if ( Data->AllocSize < Data->Size + 1 ) {
        Data->realloc ( Data->Size + 2 );
    }

    Data->Array[ ( Data->Size ) ] = ch;

    char *it = Data->Array + ( Data->Size );
    char *it2 = Data->Array + begin_distance;
    while ( it != it2 ) {
        bSwap ( *it, * ( it - 1 ) );
        --it;
    }

    Data->Size += 1;
    Data->Array[ Data->Size ] = '\0';

    return *this;
}

BByteArray &BByteArray::insert ( int index,  const char *string ) {
    if ( index >= Data->Size ) {
        return append ( string );
    }

    int begin_distance = index;
    size_t string_len = strlen ( string );

    detach();

    // TODO: realoc with move...
    if ( ( size_t ) Data->AllocSize < Data->Size + string_len + 1 ) {
        Data->realloc ( Data->Size + string_len + 1 );
    }

    char *temp_array = ( char * ) malloc ( sizeof ( char ) * ( Data->Size - index ) );
    B_CHECK_PTR ( temp_array );

    memcpy ( temp_array,  ( Data->Array + begin_distance ), sizeof ( char ) * ( Data->Size - index ) );
    memcpy ( ( Data->Array + begin_distance ), string, sizeof ( char ) * string_len );
    memcpy ( ( Data->Array + begin_distance + string_len ), temp_array, ( Data->Size - index ) );

    Data->Size += string_len;
    Data->Array[ Data->Size ] = '\0';

    free ( temp_array );

    return *this;
}

BByteArray &BByteArray::insert ( int index,  const char *string, int len ) {
    int begin_distance = index;

    detach();

    // TODO: realoc with move...
    if ( Data->AllocSize < Data->Size + len + 1 ) {
        Data->realloc ( Data->Size + len + 1 );
    }

    char *temp_array = ( char * ) malloc ( sizeof ( char ) * ( Data->Size - index ) );
    B_CHECK_PTR ( temp_array );

    memcpy ( temp_array,  ( Data->Array + begin_distance ), sizeof ( char ) * ( Data->Size - index ) );
    memcpy ( ( Data->Array + begin_distance ), string, sizeof ( char ) * len );
    memcpy ( ( Data->Array + begin_distance + len ), temp_array, ( Data->Size - index ) );

    Data->Size += len;
    Data->Array[ Data->Size ] = '\0';

    free ( temp_array );

    return *this;
}

BByteArray &BByteArray::insert ( int index,  const BByteArray &byte_array ) {
    int begin_distance = index;
    size_t string_len = byte_array.Data->Size;

    detach();

    if ( ( size_t ) Data->AllocSize < Data->Size + string_len + 1 ) {
        Data->realloc ( Data->Size + string_len + 1 );
    }

    char *temp_array = ( char * ) malloc ( sizeof ( char ) * ( Data->Size - index ) );
    B_CHECK_PTR ( temp_array );

    memcpy ( temp_array,  ( Data->Array + begin_distance ), sizeof ( char ) * ( Data->Size - index ) );
    memcpy ( ( Data->Array + begin_distance ), byte_array.Data->Array, sizeof ( char ) * string_len );
    memcpy ( ( Data->Array + begin_distance + string_len ), temp_array, ( Data->Size - index ) );

    Data->Size += string_len;
    Data->Array[ Data->Size ] = '\0';

    free ( temp_array );

    return *this;
}

char &BByteArray::operator[] ( int index ) {
    B_ASSERT_MSG ( ( index >= 0 && index < Data->Size ), "BByteArray<T>::operator[]", "Index out of range" );

    detach();
    return BByteArray::Data->Array[ index ];
}

char BByteArray::operator[] ( int index ) const {
    B_ASSERT_MSG ( ( index >= 0 && index < Data->Size ), "BByteArray<T>::operator[]", "Index out of range" );
    return BByteArray::Data->Array[ index ];
}

BByteArray &BByteArray::operator= ( const BByteArray &other ) {
    if ( !Data->ReferenceCounter.dereference() ) {
        delete Data;
    }

    Data = other.Data;

    if ( Data ) {
        Data->ReferenceCounter.reference();
    }

    return *this;
}

void BByteArray::resize ( int new_size ) {
    detach();

    if ( Data->AllocSize < new_size  ) {
        Data->realloc ( new_size );
    }

    if ( new_size > Data->Size ) {
        int count = bAbs ( new_size - Data->Size ) + 1;
        for ( int i = Data->Size; i < Data->Size + count; i++ ) {
            Data->Array[ i ] = '\0';
        }
    }

    if ( new_size < Data->Size ) {
        Data->Array[ new_size ] = '\0';
    }

    Data->Size = new_size;
}

BByteArray BByteArray::left ( int index ) const {
    return BByteArray ( Data->Array, index ) ;
}

bool BByteArray::startsWith ( const char *string ) const {
    if ( Data->Size == 0 ) {
        return false;
    }

    size_t string_len = bstrlen ( string );

    if ( string_len > ( size_t ) Data->Size ) {
        return false;
    }

    char *iter = Data->Array;
    size_t i_iter = 0;
    while (  * ( iter ) == string[ i_iter ] ) {
        iter++;
        i_iter++;
    }

    return i_iter == string_len;
}

bool BByteArray::startsWith ( const BByteArray &string ) const {
    if ( Data->Size == 0 ) {
        return false;
    }

    if ( string.Data->Size > Data->Size ) {
        return false;
    }

    char *iter = Data->Array;
    size_t i_iter = 0;
    while (  * ( iter ) == string.Data->Array[ i_iter ] ) {
        iter++;
        i_iter++;
    }

    return i_iter == ( size_t ) string.Data->Size;
}

bool BByteArray::endsWith ( const char *string ) const {
    if ( Data->Size == 0 ) {
        return false;
    }

    size_t string_len = bstrlen ( string );

    if ( ( string_len > ( size_t ) Data->Size ) || ( string_len == 0 )  ) {
        return false;
    }

    char *iter = Data->Array + ( Data->Size - string_len   );
    size_t i_iter = 0;
    while ( ( * ( iter ) == string[ i_iter ] ) && ( ( * ( iter ) != '\0' ) || ( string[ i_iter ] ) ) ) {
        iter++;
        i_iter++;
    }

    return i_iter == string_len;
}

bool BByteArray::endsWith ( const BByteArray &string ) const {
    if ( Data->Size == 0 ) {
        return false;
    }

    if ( ( string.Data->Size > Data->Size ) || ( string.isEmpty() )  ) {
        return false;
    }

    char *iter = Data->Array + ( Data->Size - string.Data->Size   );
    size_t i_iter = 0;
    while ( ( * ( iter ) == string.Data->Array[ i_iter ] ) && ( ( * ( iter ) != '\0' ) || ( string.Data->Array[ i_iter ] ) ) ) {
        iter++;
        i_iter++;
    }

    return i_iter == ( size_t ) string.Data->Size;
}

bool BByteArray::contains ( char ch ) const {
    if ( Data->Size == 0 ) {
        return false;
    }

    char *it = Data->Array;
    while ( *it != '\0' ) {
        if ( * ( it++ ) == ch ) {
            return true;
        }
    }

    return false;
}

bool BByteArray::contains ( const char *string ) const {
    if ( Data->Size == 0 ) {
        return false;
    }

    int string_len = bstrlen ( string );

    if ( string_len > Data->Size ) {
        return false;
    }

    char *it = Data->Array;
    char *it_end = Data->Array + bAbs ( Data->Size - string_len ) + 1;
    while ( it != it_end ) {
        if ( !bstrncmp ( ( it++ ), string, string_len ) ) {
            return true;
        }
    }

    return false;
}

bool BByteArray::contains ( const BByteArray &string ) const {
    if ( Data->Size == 0 ) {
        return false;
    }

    if ( Data == string.Data ) {
        return true;
    }


    if ( string.Data->Size > Data->Size ) {
        return false;
    }

    char *it = Data->Array;
    char *it_end = Data->Array + bAbs ( Data->Size - string.Data->Size ) + 1;
    while ( it != it_end ) {
        if ( !bstrncmp ( ( it++ ), string.Data->Array, string.Data->Size ) ) {
            return true;
        }
    }

    return false;
}

int BByteArray::count ( char ch ) const {
    if ( Data->Size == 0 ) {
        return 0;
    }

    int ret = 0;

    char *it = Data->Array;
    char *it_end = Data->Array + Data->Size;
    while ( it != it_end ) {
        if ( *it++ == ch ) {
            ret++;
        }
    }

    return ret;
}

int BByteArray::count ( const char *string ) const {
    if ( Data->Size == 0 ) {
        return 0;
    }

    int string_len = bstrlen ( string );

    if ( string_len > Data->Size ) {
        return 0;
    }

    int ret = 0;

    char *it = Data->Array;
    char *it_end = Data->Array + bAbs ( Data->Size - string_len ) + 1;
    while ( it != it_end ) {
        if ( !bstrncmp ( ( it++ ), string, string_len ) ) {
            ret++;
        }
    }

    return ret;
}

int BByteArray::count ( const BByteArray &string ) const {
    if ( Data->Size == 0 ) {
        return 0;
    }

    if ( string.Data == Data ) {
        return 1;
    }

    if ( string.Data->Size > Data->Size ) {
        return 0;
    }

    int ret = 0;

    char *it = Data->Array;
    char *it_end = Data->Array + bAbs ( Data->Size - string.Data->Size ) + 1;
    while ( it != it_end ) {
        if ( !bstrncmp ( ( it++ ), string.Data->Array, string.Data->Size ) ) {
            ret++;
        }
    }

    return ret;
}

BByteArray BByteArray::repeated ( int num ) const {
    if ( num < 1 ) {
        return BByteArray();
    }

    BByteArray ret_ba;
    ret_ba.reserve ( Data->Size * num );

    char *it1 = Data->Array;
    char *it2 = ret_ba.Data->Array;
    char *it2_end = ret_ba.Data->Array + ( num * Data->Size );

    while ( it2 != it2_end ) {

        memcpy ( it2, it1, sizeof ( char ) * Data->Size );

        it2 += Data->Size;
    }

    * ( it2_end ) = '\0';

    return ret_ba;
}

BByteArray &BByteArray::remove ( int position, int len ) {
    // Negative index?
    if ( position < 0 ) {
        return *this;
    }

    // Clear all array.
    if ( position == 0 && ( len >= Data->Size )  ) {
        clear();
        return *this;
    }

    // end clearing....
    if ( ( position + len ) > Data->Size - 1 ) {
        resize ( Data->Size - len );
        return *this;
    }

    detach();

    memmove ( Data->Array + position, Data->Array + position + len, Data->Size - ( position + len ) );
    resize ( Data->Size - len );

    return *this;
}

BByteArray &BByteArray::replace ( int position, int len, const char *after ) {
    return ( remove ( position, len ).insert ( position, after ) );
}

BByteArray &BByteArray::replace ( int position, int len, const char *after, int after_len ) {
    return ( remove ( position, len ).insert ( position, after, after_len ) );
}

BByteArray &BByteArray::replace ( int position, int len, const BByteArray &after ) {
    return ( remove ( position, len ).insert ( position, after ) );
}

BByteArray &BByteArray::replace ( char before, char after ) {
    detach();

    char *it = Data->Array;
    char *it_end = it + Data->Size;

    while ( it != it_end ) {
        if ( *it == before ) {
            *it = after;
        }
        it++;
    }

    return *this;
}

BByteArray &BByteArray::replace ( char before, const char *after ) {
    int after_len = bstrlen ( after );

    for ( int i = 0; i < Data->Size; i++ ) {
        if ( Data->Array[ i ] == before ) {
            insert ( i, after );
            remove ( i + after_len, 1 );
            i += after_len;
        }
    }

    return *this;
}

BByteArray &BByteArray::replace ( char before, const BByteArray &after ) {
    for ( int i = 0; i < Data->Size; i++ ) {
        if ( Data->Array[ i ] == before ) {
            insert ( i, after );
            remove ( i + after.Data->Size, 1 );
            i += after.Data->Size;
        }
    }

    return *this;
}

BByteArray &BByteArray::replace ( const char *before, const BByteArray &after ) {
    int before_len = bstrlen ( before );

    if ( before_len > Data->Size ) {
        return *this;
    }

    for ( int i = 0; i < Data->Size; i++ ) {
        if ( bstrncmp ( ( Data->Array + i ), before, before_len ) == 0  ) {
            insert ( i, after );
            remove ( i + after.Data->Size, before_len );
            i += after.Data->Size;
        }
    }

    return *this;
}

BByteArray &BByteArray::replace ( const char *before, int before_len, const char *after, int after_len ) {
    if ( before_len > Data->Size ) {
        return *this;
    }

    for ( int i = 0; i < Data->Size; i++ ) {
        if ( bstrncmp ( ( Data->Array + i ), before, before_len ) == 0  ) {
            insert ( i, after, after_len );
            remove ( i + after_len, before_len );
            i += after_len;
        }
    }

    return *this;
}

BByteArray &BByteArray::replace ( const BByteArray &before, const char *after ) {
    if ( before.Data->Size > Data->Size ) {
        return *this;
    }

    int after_len = bstrlen ( after );

    for ( int i = 0; i < Data->Size; i++ ) {
        if ( bstrncmp ( ( Data->Array + i ), before.Data->Array, before.Data->Size ) == 0  ) {
            insert ( i, after, after_len );
            remove ( i + after_len, before.Data->Size );
            i += after_len;
        }
    }

    return *this;
}

BByteArray &BByteArray::replace ( const BByteArray &before, const BByteArray &after ) {
    if ( before.Data->Size > Data->Size ) {
        return *this;
    }

    for ( int i = 0; i < Data->Size; i++ ) {
        if ( bstrncmp ( ( Data->Array + i ), before.Data->Array, before.Data->Size ) == 0  ) {
            insert ( i, after );
            remove ( i + after.Data->Size, before.Data->Size );
            i += after.Data->Size;
        }
    }

    return *this;
}

int BByteArray::indexOf ( char ch, int from ) const {
    char *it = Data->Array + from;
    const char *it_end = Data->Array + Data->Size;

    while ( it <= it_end ) {
        if ( *it == ch ) {
            return it - Data->Array;
        }
        it++;
    }

    return -1;
}

int BByteArray::indexOf ( const char *string, int from ) const {
    if ( Data->Size == 0 ) {
        return -1;
    }

    int string_len = bstrlen ( string );

    if ( string_len > Data->Size ) {
        return -1;
    }

    char *it = Data->Array + from;
    char *it_end = Data->Array + bAbs ( Data->Size - string_len ) + 1;
    while ( it != it_end ) {
        if ( !bstrncmp ( ( it++ ), string, string_len ) ) {
            return ( it -  Data->Array ) - 1;
        }
    }

    return -1;
}

int BByteArray::indexOf ( const BByteArray &string, int from ) const {
    if ( Data->Size == 0 ) {
        return -1;
    }

    if ( string.Data->Size > Data->Size ) {
        return -1;
    }

    char *it = Data->Array + from;
    char *it_end = Data->Array + bAbs ( Data->Size - string.Data->Size ) + 1;
    while ( it != it_end ) {
        if ( !bstrncmp ( ( it++ ), string.Data->Array, string.Data->Size ) ) {
            return ( it -  Data->Array ) - 1;
        }
    }

    return -1;
}


BLinkedList< BByteArray > BByteArray::split ( char sep_char ) const {

    BLinkedList< BByteArray > ret_list;
    char *from = Data->Array;
    char *to = from + Data->Size;

    char *it = Data->Array;
    char *it_end = it + Data->Size;


    while ( it != it_end ) {
        if ( *it == sep_char ) {
            to = it;
            ret_list.append ( BByteArray ( from, ( to - from ) ) );
            from = it + 1;
        }

        it++;
    }

    ret_list.append ( BByteArray ( from, ( it_end - from ) ) );

    return ret_list;
}

BByteArray &BByteArray::setRawData ( char *data, int size ) {
    detach();

    if ( data ) {
        delete Data;
    }

    BOXE_TRY {

        Data = new BByteArrayData ( 0 );
        B_CHECK_PTR ( Data );

        Data->ReferenceCounter.reference();
    } BOXE_CATCH ( const std::bad_alloc & ) {
        BOXE_RETHROW;
    }

    Data->AllocSize = size;
    Data->Size = size;
    Data->Array = data;

    return *this;
}

int base64decode ( char ch ) {
    static const char *table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    const char *it = table;
    int ret = 0;
    while ( *it != ch ) {
        it++;
    }

    ret = it - table;
    return ret;
}

BByteArray BByteArray::toBase64( ) const {
    static const char *table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    char *it = Data->Array;
    char *it_end = it + Data->Size;

    char buf_int[3];
    char buf_out[5] = { '\0', '\0', '\0', '\0', '\0',};
    int val = 0;
    int num = 0;

    BByteArray ret;
    while ( it < it_end ) {
        buf_int[ 0 ] = *it;

        if ( it + 2 == it_end ) {
            num = 2;
        } else if ( it + 1 == it_end ) {
            num = 1;
        } else {
            num = 3;
        }

        if ( num == 3 ) {
            buf_int[ 1 ] = * ( it + 1 );
            buf_int[ 2 ] = * ( it + 2 );

            val = ( buf_int[0] << 16 ) | ( buf_int[1] << 8 ) | ( buf_int[2] );

            buf_out[0] = table[ ( val >> 18 ) & 0x3F ];
            buf_out[1] = table[ ( val >> 12 ) & 0x3F ];
            buf_out[2] = table[ ( val >> 6 ) & 0x3F ];
            buf_out[3] = table[ ( val ) & 0x3F ];

        } else if ( num == 2 ) {
            buf_int[ 1 ] = * ( it + 1 );

            val = ( buf_int[0] << 16 ) | ( buf_int[1] << 8 );

            buf_out[0] = table[ ( val >> 18 ) & 0x3F ];
            buf_out[1] = table[ ( val >> 12 ) & 0x3F ];
            buf_out[2] = table[ ( val >> 6 ) & 0x3F ];
            buf_out[3] = '=';
        } else if ( num == 1 ) {
            val = ( buf_int[0] << 16 );

            buf_out[0] = table[ ( val >> 18 ) & 0x3F ];
            buf_out[1] = table[ ( val >> 12 ) & 0x3F ];
            buf_out[2] = '=';
            buf_out[3] = '=';

        }


        ret << buf_out;
        it += 3;
    }

    return ret;
}

BByteArray BByteArray::fromBase64 ( const BByteArray &code ) {
    char *it = code.Data->Array;
    char *it_end = it + code.Data->Size;

    char buf_int[4];
    char buf_out[4] = { '\0', '\0', '\0', '\0' };
    int val = 0;

    BByteArray ret;

    while ( it < it_end ) {
        buf_int[ 0 ] = *it;
        buf_int[ 1 ] = * ( it + 1 );
        buf_int[ 2 ] = * ( it + 2 );
        buf_int[ 3 ] = * ( it + 3 );

        if ( ( buf_int[2] != '=' ) && ( buf_int[3] != '=' ) ) {
            val = ( base64decode ( buf_int[0] ) << 18 ) | ( base64decode ( buf_int[1] ) << 12 ) | ( base64decode ( buf_int[2] ) << 6 ) | base64decode ( buf_int[3] );

            buf_out[ 0 ] = val >> 16 & 0xFF;
            buf_out[ 1 ] = val >> 8 & 0xFF;
            buf_out[ 2 ] = val & 0xFF;

        } else if ( ( buf_int[2] == '=' ) ) {
            val = ( base64decode ( buf_int[0] ) << 18 ) | ( base64decode ( buf_int[1] ) << 12 );

            buf_out[ 0 ] = val >> 16 & 0xFF;
            buf_out[ 1 ] = '\0';
            buf_out[ 2 ] = '\0';

            ret << buf_out;
            return ret;
        } else {
            val = ( base64decode ( buf_int[0] ) << 18 ) | ( base64decode ( buf_int[1] ) << 12 ) | ( base64decode ( buf_int[2] ) << 6 );

            buf_out[ 0 ] = val >> 16 & 0xFF;
            buf_out[ 1 ] = val >> 8 & 0xFF;
            buf_out[ 2 ] = '\0';

            ret << buf_out;
            return ret;
        }

        ret << buf_out;
        it += 4;
    }

    return ret;
}

BByteArray BByteArray::toLower() const {
    if ( Data->Size == 0 ) {
        return *this;
    }

    BByteArray ret ( Data->Array );
    char *it = ret.Data->Array;
    const char *it_end = it + ret.Data->Size;

    while ( it != it_end ) {
        if ( isUpper ( *it ) ) {
            *it += 32;
        }

        it++;
    }

    return ret;
}

BByteArray BByteArray::toUpper() const {
    if ( Data->Size == 0 ) {
        return *this;
    }

    BByteArray ret ( Data->Array );
    char *it = ret.Data->Array;
    const char *it_end = it + ret.Data->Size;

    while ( it != it_end ) {
        if ( isLower ( *it ) ) {
            *it -= 32;
        }

        it++;
    }

    return ret;
}

int BByteArray::toInt ( bool *ok, int base ) const {
    B_CHECK_PTR ( ok );

    int offset = 0;

    if ( !base ) {
        if ( startsWith ( "0x" ) ) {
            base = 16;
            offset = 2;

        } else  if ( startsWith ( '0' ) ) {
            base = 8;
            offset = 1;

        } else {
            base = 10;
        }
    }

    if ( startsWith ( '-' ) ) {
        offset = 1;
    }

    const char *it = Data->Array + offset;
    const char *it_end = Data->Array + ( Data->Size );
    int ret = 0;

    int on = ( Data->Size - offset ) - 1;

    if ( base <= 10 ) {
        while ( it != it_end ) {
            if ( isAlphabetic ( *it ) ) {
                *ok = false;
                return 0;
            }

            ret +=  ( *it - '0' ) * pow ( base, on-- );
            it++;
        }
    } else {
        int num = 0;
        while ( it != it_end ) {
            if ( isNumeric ( *it ) ) {
                ret +=  ( *it - '0' ) * pow ( base, on-- );

            } else {
                if ( isUpper ( *it ) && ( ( *it >= 'A' ) && ( *it <= 'A' + ( base - 11 ) ) ) ) {
                    num = ( 10 + ( *it - 'A' ) );
                } else if ( ( *it >= 'a' ) && ( *it <= 'a' + ( base - 11 ) ) ) {
                    num = ( 10 + ( *it - 'a' ) );
                } else {
                    *ok = false;
                    return 0;
                }

                ret +=  num * pow ( base, on-- );
            }
            it++;
        }
    }

    *ok = true;

    if ( startsWith ( '-' ) ) {
        ret *= -1;
    }

    return ret;
}

int number_of_order ( int num ) {
    int i = 1;
    while ( ( num /= 10 ) > 0 ) {
        i++;
    }

    return i;
}

BByteArray &BByteArray::setNum ( int num, int base ) {
    clear();

    if ( num == 0 ) {
        ( *this ) = "0";
        return *this;
    }

    if ( ( base < 2 ) || ( base > 32 ) ) {
        return *this;
    }

    bool minus = false;
    if ( ( num < 0 ) ) {
        num = -num;
        minus = true;
    }

    if ( base <= 10 ) {

        while ( num != 0 ) {
            prepend ( '0' + ( num % base ) );
            num /= base;
        }

    } else {
        int number = 0;

        while ( num != 0 ) {
            number =  ( num % base );

            if ( number < 10 ) {
                prepend ( '0' + number );
            } else {
                prepend ( 'a' + ( number - 10 ) );
            }

            num /= base;
        }
    }

    if ( minus and ( base != 2 ) ) {
        prepend ( '-' );
    }

    return *this;
}

BByteArray &BByteArray::setNum ( unsigned int num, int base ) {
    clear();

    if ( ( base < 2 ) || ( base > 32 ) ) {
        return *this;
    }

    if ( base <= 10 ) {

        while ( num != 0 ) {
            prepend ( '0' + ( num % base ) );
            num /= base;
        }

    } else {
        int number = 0;

        while ( num != 0 ) {
            number =  ( num % base );

            if ( number < 10 ) {
                prepend ( '0' + number );
            } else {
                prepend ( 'a' + ( number - 10 ) );
            }

            num /= base;
        }
    }

    return *this;
}

void BByteArray::detach_internal() {
    if ( !Data->ReferenceCounter.dereference() ) {
        delete Data;
        return;
    }

    Data = Data->makeHardCopy();
    Data->ReferenceCounter.reference();
}

unsigned int bstrlen ( const char *string ) {
    const char *it = string;
    while ( * ( it++ ) != '\0' ) {
    }
    return ( it - string ) - 1;
}

int bstrcmp ( const char *string1, const char *string2 ) {
    int ret = 0;
    while ( ( *string1 != '\0' ) || ( *string2  != '\0' ) ) {
        ret = * ( string1++ ) - * ( string2++ );

        if ( ret == 0 ) {
            continue;
        } else {
            return ( ret > 0 ? 1 : -1 );
        }
    }

    return 0;
}

int bstricmp ( const char *string1, const char *string2 ) {
    int ret = 0;
    while ( ( *string1 != '\0' ) || ( *string2  != '\0' ) ) {
        ret = * ( string1++ ) - * ( string2++ );

        if ( ( ret == 0 ) || ( ( isAlphabetic ( *string1 ) ) && ( isAlphabetic ( *string2 ) ) && (  bAbs ( ret ) == 32  ) ) ) {
            continue;
        } else {
            return ( ret > 0 ? 1 : -1 );
        }
    }

    return 0;
}

int bstrncmp ( const char *string1, const char *string2, unsigned int len ) {
    int ret = 0;
    while ( ( len-- != 0 ) && ( ( *string1 != '\0' ) || ( *string2  != '\0' ) ) ) {
        ret = * ( string1++ ) - * ( string2++ );

        if ( ret == 0 ) {
            continue;
        } else {
            return ( ret > 0 ? 1 : -1 );
        }
    }

    return 0;
}

int bstrincmp ( const char *string1, const char *string2, unsigned int len ) {
    int ret = 0;
    while ( ( len-- != 0 ) && ( ( *string1 != '\0' ) || ( *string2  != '\0' ) ) ) {
        ret = * ( string1 ) - * ( string2 );

        if ( ret == 0 || ( ( isAlphabetic ( *string1 ) ) && ( isAlphabetic ( *string2 ) ) && (  bAbs ( ret ) == 32  ) ) ) {
            continue;
        } else {
            return ( ret > 0 ? 1 : -1 );
        }
    }

    return 0;
}

long bCalcHash ( const BByteArray &value ) {
    long hash_value = 0;

    for ( int i = 0; i < value.size(); i++ ) {
        hash_value += value[ i ];
        hash_value += ( hash_value << 10 );
        hash_value ^= ( hash_value >> 6 );
    }

    hash_value += ( hash_value << 3 );
    hash_value ^= ( hash_value >> 11 );
    hash_value += ( hash_value << 15 );

    return hash_value;
}

BOXE_NAMESPACE_END ( Core )
