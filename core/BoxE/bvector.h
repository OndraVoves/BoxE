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


#ifndef BVECTOR_H
#define BVECTOR_H

#include <stdlib.h>
#include <string.h>

#include "bglobal.h"
#include "breferencecounter.h"

BOXE_NAMESPACE_BEGIN ( Core )

/*!
 * Vector ( dynamic array ).
 */
template< typename T >
class BVector {
    private:

        /*!
         * Internal data class.
         */
        class BVectorData {
            public:
                BVectorData ( int size ) : AllocSize ( 0 ), Size ( 0 ), Array ( 0 ) {
                    if ( size != 0 ) {
                        alloc ( size );
                    }
                }

                ~BVectorData() {
                    if ( AllocSize != 0 ) {
                        delete [] Array;
                    }
                }

                inline void alloc ( int size ) {
                    B_ASSERT ( size > 0 );

                    if ( Array == 0 ) {
                        free ( Array );
                    }

                    Array = ( T * ) malloc ( sizeof ( T ) * size );
                    B_CHECK_PTR ( Array );

                    AllocSize = size;
                }

                void realloc ( int new_size ) {
                    B_ASSERT ( new_size >= Size );

                    if ( new_size == 0 ) {
                        free ( Array );
                        AllocSize = 0;
                        return;
                    }

                    if ( new_size == AllocSize ) {
                        return;
                    }

                    T *new_array = ( T * ) malloc ( sizeof ( T ) * new_size );
                    B_CHECK_PTR ( new_array );

                    if ( BTypeInfo<T>::isMoveable ) {
                        memmove ( new_array, Array, sizeof ( T ) * Size );
                    } else {
                        for ( int i = 0; i < Size; i++ ) {
                            new_array[i] = T ( Array[i] );
                        }
                    }

                    free ( Array );
                    Array = new_array;

                    AllocSize = new_size;
                }

                BVectorData *makeHardCopy( ) {
                    BVectorData *new_data = 0;
                    BOXE_TRY {
                        new_data = new BVectorData ( AllocSize );

                        B_CHECK_PTR ( new_data );

                    } BOXE_CATCH ( const std::bad_alloc & ) {
                        BOXE_RETHROW;
                    }

                    new_data->Size = Size;

                    if ( Size != 0 ) {
                        T *it = Array + Size;
                        T *it2 = new_data->Array + new_data->Size;
                        while ( it != Array ) {
                            * ( --it2 ) = T ( * ( --it ) );
                        }
                    }

                    return new_data;
                };


            public:
                BReferenceCounter ReferenceCounter; //!< Reference counter.

                int AllocSize; //!< Reserved size.
                int Size;         //!< Item count.

                T *Array; //!< Item Array.
        };

    public:

        /*!
         * BVector iterator.
         */
        class Iterator {
            public:

                /*!
                 * Create iterator.
                 * \param value_ptr Pointer to value.
                 */
                Iterator ( T *value_ptr ) : ValuePtr ( value_ptr ) {}

                /*!
                 * Copy constructor.
                 * \param other Other Iterator.
                 */
                Iterator ( const Iterator &other ) : ValuePtr ( other.ValuePtr ) {}

                /*!
                 * Get value.
                 * \return Reference to value.
                 */
                inline T &operator*() const {
                    return *ValuePtr;
                }

                /*!
                 * Get value pointer.
                 * \return Pointer to value
                 */
                inline T *operator->() {
                    return ValuePtr;
                }

                /*!
                 * Get value at this + index.
                 * \param index Delta index.
                 */
                inline T &operator[] ( int index ) {
                    return * ( ValuePtr + index );
                }

                /*!
                 * Equal two iterators
                 * \param other Reference to other iterator.
                 * \return True if iterator is equal, else return false.
                 */
                inline bool operator== ( const Iterator &other ) const {
                    return ValuePtr == other.ValuePtr;
                }

                /*!
                 * Equal two iterators
                 * \param other Reference to other iterator.
                 * \return True if iterator is doferent, else return false.
                 */
                inline bool operator!= ( const Iterator &other ) const {
                    return ValuePtr != other.ValuePtr;
                }

                /*!
                 * Is this iterator smaller that other?.
                 * \param other Reference to other iterator.
                 * \return True if this iterator is smaller that other, else return false.
                 */
                inline bool operator< ( const Iterator &other ) const {
                    return ValuePtr < other.ValuePtr;
                }

                /*!
                 * Is this iterator smaller that other or equal?.
                 * \param other Reference to other iterator.
                 * \return True if this iterator is smaller or equal, else return false.
                 */
                inline bool operator<= ( const Iterator &other ) const {
                    return ValuePtr <= other.ValuePtr;
                }

                /*!
                 * Is this iterator bigger that other?.
                 * \param other Reference to other iterator.
                 * \return True if this iterator is bigger that other, else return false.
                 */
                inline bool operator> ( const Iterator &other ) const {
                    return ValuePtr > other.ValuePtr;
                }

                /*!
                 * Is this iterator bigger that other or equal?.
                 * \param other Reference to other iterator.
                 * \return True if this iterator is bigger or equal, else return false.
                 */
                inline bool operator>= ( const Iterator &other ) const {
                    return ValuePtr >= other.ValuePtr;
                }

                /*!
                 * Move iterator about 'index' next item.
                 * \param index Index.
                 * \return Moved iterator.
                 */
                inline Iterator operator+ ( int index ) const {
                    return ValuePtr + index;
                }

                /*!
                 * Move iterator to next item.
                 * \return Reference to this iterator.
                 */
                inline Iterator &operator++() {
                    ValuePtr++;
                    return *this;
                }

                /*!
                 * Move iterator to next item.
                 * \return Moved iterator.
                 */
                inline Iterator operator++ ( int ) {
                    T *temp = ValuePtr;
                    ValuePtr++;
                    return temp;
                }

                /*!
                 * Move this iterator about 'index' next item.
                 * \param index Index.
                 * \return This iterator.
                 */
                inline Iterator &operator+= ( int index ) {
                    ValuePtr += index;
                    return *this;
                }

                /*!
                 * Move iterator about 'index' previous item.
                 * \param index Index.
                 * \return Moved iterator.
                 */
                inline Iterator operator- ( int index ) const {
                    return ValuePtr - index;
                }

                /*!
                 * Move iterator to previous item.
                 * \return Reference to this iterator.
                 */
                inline Iterator &operator--() {
                    ValuePtr--;
                    return *this;
                }

                /*!
                 * Move iterator to previous item.
                 * \return Moved iterator.
                 */
                inline Iterator operator-- ( int ) {
                    T *temp = ValuePtr;
                    ValuePtr--;
                    return temp;
                }

                /*!
                 * Move this iterator about 'index' previous item.
                 * \param index Index.
                 * \return This iterator.
                 */
                inline Iterator &operator-= ( int index ) {
                    ValuePtr -= index;
                    return *this;
                }

                /*!
                 * Return distance between iterators.
                 * \param other Reference to iterator.
                 * \return Distance between iterators.
                 */
                inline int operator- ( const Iterator &other ) {
                    return ValuePtr - other.ValuePtr;
                }
            private:
                T *ValuePtr; //!< Pointer to item.
        };

        /*!
         * BVector const iterator.
         */
        class ConstIterator {
            public:

                /*!
                 * Create iterator.
                 * \param value_ptr Pointer to value.
                 */
                ConstIterator ( T *value_ptr ) : ValuePtr ( value_ptr ) {}

                /*!
                 * Copy constructor.
                 * \param other Other Iterator.
                 */
                ConstIterator ( const ConstIterator &other ) : ValuePtr ( other.ValuePtr ) {}

                /*!
                 * Get value.
                 * \return Reference to value.
                 */
                inline const T &operator*() const {
                    return *ValuePtr;
                }

                /*!
                 * Get value pointer.
                 * \return Pointer to value
                 */
                inline const T *operator->() {
                    return ValuePtr;
                }

                /*!
                 * Get value at this + index.
                 * \param index Delta index.
                 */
                inline const T &operator[] ( int index ) {
                    return * ( ValuePtr + index );
                }

                /*!
                 * Equal two iterators
                 * \param other Reference to other iterator.
                 * \return True if iterator is equal, else return false.
                 */
                inline bool operator== ( const ConstIterator &other ) const {
                    return ValuePtr == other.ValuePtr;
                }

                /*!
                 * Equal two iterators
                 * \param other Reference to other iterator.
                 * \return True if iterator is doferent, else return false.
                 */
                inline bool operator!= ( const ConstIterator &other ) const {
                    return ValuePtr != other.ValuePtr;
                }

                /*!
                 * Is this iterator smaller that other?.
                 * \param other Reference to other iterator.
                 * \return True if this iterator is smaller that other, else return false.
                 */
                inline bool operator< ( const ConstIterator &other ) const {
                    return ValuePtr < other.ValuePtr;
                }

                /*!
                 * Is this iterator smaller that other or equal?.
                 * \param other Reference to other iterator.
                 * \return True if this iterator is smaller or equal, else return false.
                 */
                inline bool operator<= ( const ConstIterator &other ) const {
                    return ValuePtr <= other.ValuePtr;
                }

                /*!
                 * Is this iterator bigger that other?.
                 * \param other Reference to other iterator.
                 * \return True if this iterator is bigger that other, else return false.
                 */
                inline bool operator> ( const ConstIterator &other ) const {
                    return ValuePtr > other.ValuePtr;
                }

                /*!
                 * Is this iterator bigger that other or equal?.
                 * \param other Reference to other iterator.
                 * \return True if this iterator is bigger or equal, else return false.
                 */
                inline bool operator>= ( const ConstIterator &other ) const {
                    return ValuePtr >= other.ValuePtr;
                }

                /*!
                 * Move iterator about 'index' next item.
                 * \param index Index.
                 * \return Moved iterator.
                 */
                inline ConstIterator operator+ ( int index ) const {
                    return ValuePtr + index;
                }

                /*!
                 * Move iterator to next item.
                 * \return Reference to this iterator.
                 */
                inline ConstIterator &operator++() {
                    ValuePtr++;
                    return *this;
                }

                /*!
                 * Move iterator to next item.
                 * \return Moved iterator.
                 */
                inline ConstIterator operator++ ( int ) {
                    T *temp = ValuePtr;
                    ValuePtr++;
                    return temp;
                }

                /*!
                 * Move this iterator about 'index' next item.
                 * \param index Index.
                 * \return This iterator.
                 */
                inline ConstIterator &operator+= ( int index ) {
                    ValuePtr += index;
                    return *this;
                }

                /*!
                 * Move iterator about 'index' previous item.
                 * \param index Index.
                 * \return Moved iterator.
                 */
                inline ConstIterator operator- ( int index ) const {
                    return ValuePtr - index;
                }

                /*!
                 * Move iterator to previous item.
                 * \return Reference to this iterator.
                 */
                inline ConstIterator &operator--() {
                    ValuePtr--;
                    return *this;
                }

                /*!
                 * Move iterator to previous item.
                 * \return Moved iterator.
                 */
                inline ConstIterator operator-- ( int ) {
                    T *temp = ValuePtr;
                    ValuePtr--;
                    return temp;
                }

                /*!
                 * Move this iterator about 'index' previous item.
                 * \param index Index.
                 * \return This iterator.
                 */
                inline ConstIterator &operator-= ( int index ) {
                    ValuePtr -= index;
                    return *this;
                }

                /*!
                 * Return distance between iterators.
                 * \param other Reference to iterator.
                 * \return Distance between iterators.
                 */
                inline int operator- ( const ConstIterator &other ) {
                    return ValuePtr - other.ValuePtr;
                }
            private:
                T *ValuePtr; //!< Pointer to item.
        };

    public:
        /*!
         * Create BVector and init size item with default constructor.
         * \param size BVector init size.
         */
        explicit BVector ( int size = 0 );

        /*!
         * Create BVector and init size item with init_value.
         * \param size BVector init size.
         * \param init_value Init value.
         */
        BVector ( int size, const T &init_value );

        /*!
         * Copy constructor.
         * \param other Reference to other BVector.
         */
        BVector ( const BVector<T>& other );

        /*!
         * Destructor.
         */
        virtual ~BVector( );

        /*!
         * Get const ref. to value at index.
         * \param index Index.
         * \return Const reference to value.
         */
        const T &at ( int index ) const;

        /*!
         * Get const ref. to value at index.
         * \param index Index.
         * \return Const reference to value.
         * \see at
         */
        const T &operator[] ( int index ) const;

        /*!
         * Get ref. to value at index.
         * \param index Index.
         * \return Reference to value.
         */
        T &operator[] ( int index );

        /*!
         * Set this vector as copy of other vector.
         * \param other Const reference to other BVector.
         * \return Reference to this BVector.
         */
        BVector<T>& operator= ( const BVector<T>& other );


        /*!
         * Append value to vector.
         * \param value Const reference to value.
         * \return Reference to this.
         */
        BVector<T>& operator<< ( const T &value ) {
            append ( value );
            return *this;
        }

        /*!
         * Is BVector empty?
         * \return True if BVector is empty, else return false.
         */
        inline bool isEmpty() const {
            return ( Data->Size == 0 );
        }

        /*!
         * Have this BVector shared data with other?
         * \param other Const reference to other vector.
         * \return True if this BVector have shared data with other BVector.
         */
        inline bool isSharedWith ( const BVector<T>& other ) {
            return Data == other.Data;
        }

        /*!
        * Is value in BVector?
         * \return True if value is in BVector, else return false.
         */
        bool contains ( const T &value ) const;

        /*!
         * Return count of item with 'value'.
         * \param  value Value to find.
         * \return Count of item with value equal 'value'.
         */
        int count ( const T &value ) const;

        /*!
         * Get pointer to internal array.
         * \return Pointer to internal array.
         */
        inline T *data() {
            detach();
            return Data->Array;
        }

        /*!
         * Get const pointer to internal array.
         * \return Const pointer to internal array.
         * \see constData
         */
        inline const T *data() const {
            return Data->Array;
        }

        /*!
         * Get const pointer to internal array.
         * \return Const pointer to internal array.
         * \see data
         */
        inline const T *constData() const {
            return Data->Array;
        }

        // iter
        /*!
        * Get begin iterator.
         * \return Begin iterator.
         */
        inline Iterator begin() {
            detach();
            return Iterator ( Data->Array );
        }

        /*!
        * Get end iterator.
         * \return End iterator.
         */
        inline Iterator end() {
            detach();
            return Iterator ( Data->Array + Data->Size );
        }

        /*!
        * Get begin const iterator.
         * \return Begin const iterator.
         */
        inline ConstIterator begin() const {
            return ConstIterator ( Data->Array );
        }

        /*!
        * Get end const iterator.
         * \return end const iterator.
         */
        inline ConstIterator end() const {
            return ConstIterator ( Data->Array + Data->Size );
        }

        /*!
        * Get begin const iterator.
         * \return Begin const iterator.
         */
        inline ConstIterator constBegin() const {
            return ConstIterator ( Data->Array );
        }


        /*!
        * Get end const iterator.
         * \return end const iterator.
         */
        inline ConstIterator constEnd() const {
            return ConstIterator ( Data->Array + Data->Size );
        }

        /*!
         * Replace value at index.
         * \param index Index.
         * \param value Const reference to value.
         */
        inline void replace ( int index, const T &value ) {
            if ( isEmpty() ) {
                return;
            }

            B_ASSERT_MSG ( ( index >= 0 && index < Data->Size ), "BVector<T>::at", "Index out of range" );
            data() [ index ] = value;
        }

        /*!
         * Reserve memory for size. New size must be >= Count.
         * \param size Reserve size.
         */
        inline void reserve ( int size ) {
            detach();
            Data->realloc ( size );
        }

        /*!
         * Remove all unused memory.
         */
        inline void squeeze() {
            reserve ( size() );
        }

        /*!
         * Insert value before iterator.
         * \param before Iterator.
         * \param value Value.
         */
        void insert ( Iterator before, const T &value );

        /*!
         * Insert value before index.
         * \param before_index Index.
         * \param value Value.
         */
        inline void insert ( int before_index, const T &value ) {
            insert ( begin() + before_index, value );
        }

        /*!
         * Append value to end.
         * \param value Value.
         */
        void append ( const T &value );

        /*!
         * Prepend value to begin.
         * \param value Value.
         */
        inline void prepend ( const T &value ) {
            insert ( begin(), value );
        }

        /*!
         * Resize vector. New element are init a default constructor.
         * \param new_size New size.
         */
        void resize ( int new_size );

        /*!
         * Return BVector alloc size.
         * \return BVector alloc size.
         */
        inline int capacity() {
            return Data->AllocSize;
        }

        /*!
         * Remove item at position and return iterator to next position.
         * \param position Position.
         * \return Iterator to next position.
         */
        Iterator remove ( Iterator position );

        /*!
         * Remove item at position.
         * \param position Item position ( index ).
         */
        void remove ( int position );

        /*!
         * Remove all items.
         */
        void clear();

        /*!
        * Item count.
         * \return Item count.
         */
        inline int size() {
            return Data->Size;
        }

        /*!
         * Deatach this BVector data.
         */
        inline void detach() {
            if ( Data->ReferenceCounter != 1 ) {
                detach_internal();
            }
        }

        /*!
         * Return value at index.
         * \param index Index.
         * \return Return value. If index is out of range then return default constructor value.
         * \see value
         */
        T value ( int index ) const;

        /*!
         * Return value at index.
         * \param index Index.
         * \param default_value Default value.
         * \return Return value. If index is out of range then return default_value.
         * \see value
         */
        T value ( int index, const T &default_value ) const;

    private:
        BVectorData *Data; //!< Internal BVector data.


    private:
        void detach_internal();
        //friend class Iterator;
};

template< typename T >
inline BVector<T>::BVector ( int size ) {
    B_ASSERT ( size >= 0 );

    BOXE_TRY {

        Data = new BVectorData ( size );
        B_CHECK_PTR ( Data );

        Data->ReferenceCounter.reference();

    } BOXE_CATCH ( const std::bad_alloc & ) {
        BOXE_RETHROW;
    }

    T *it = Data->Array;
    T *it_end   = Data->Array + Data->AllocSize;
    while ( it != it_end ) {
        * ( it++ ) = T();
    }

    Data->Size = size;
}

template< typename T >
inline BVector<T>::BVector ( int size, const T &init_value ) {
    B_ASSERT ( size > 0 );

    BOXE_TRY {

        Data = new BVectorData ( size );
        B_CHECK_PTR ( Data );

        Data->ReferenceCounter.reference();

    } BOXE_CATCH ( const std::bad_alloc & ) {
        BOXE_RETHROW;
    }

    T *it = Data->Array;
    T *it_end   = Data->Array + Data->AllocSize;
    while ( it != it_end ) {
        * ( it++ ) = T ( init_value );
    }

    Data->Size = size;
}

template< typename T >
inline BVector<T>::BVector ( const BVector<T>& other ) {
    Data = other.Data;
    if ( Data ) {
        Data->ReferenceCounter.reference();
    }
}

template< typename T >
BVector<T>::~BVector() {
    if ( !Data->ReferenceCounter.dereference() ) {
        delete Data;
    }
}


template< typename T >
inline const T &BVector<T>::at ( int index ) const  {
    B_ASSERT_MSG ( ( index >= 0 && index < Data->Size ), "BVector<T>::at", "Index out of range" );
    return Data->Array[ index ];
}

template< typename T >
inline const T &BVector<T>::operator[] ( int index ) const {
    B_ASSERT_MSG ( ( index >= 0 && index < Data->Size ), "BVector<T>::at", "Index out of range" );
    return Data->Array[ index ];
}

template< typename T >
inline T &BVector<T>::operator[] ( int index ) {
    B_ASSERT_MSG ( ( index >= 0 && index < Data->Size ), "BVector<T>::at", "Index out of range" );
    detach();
    return Data->Array[ index ];
}

template< typename T >
inline BVector<T> &BVector<T>::operator= ( const BVector<T>& other ) {
    if ( !Data->ReferenceCounter.dereference() ) {
        delete Data;
    }

    Data = other.Data;

    if ( Data ) {
        Data->ReferenceCounter.reference();
    }

    return *this;
}

template< typename T >
inline bool BVector<T>::contains ( const T &value ) const {
    T *it = Data->Array + Data->Size;
    while ( it != Data->Array ) {
        if ( *--it == value ) {
            return true;
        }
    }

    return false;
}

template< typename T >
inline int BVector<T>::count ( const T &value ) const {
    T *it = Data->Array + Data->Size;
    int count = 0;
    while ( it != Data->Array ) {
        if ( *--it == value ) {
            count++;
        }
    }

    return count;
}

template< typename T >
T BVector<T>::value ( int index ) const {
    if ( index < 0 || index >= Data->Size ) {
        return T();
    }

    return Data->Array[ index ];
}

template< typename T >
T BVector<T>::value ( int index, const T &default_value ) const {
    if ( index < 0 || index >= Data->Size ) {
        return default_value;
    }

    return Data->Array[ index ];
}

template< typename T >
void BVector<T>::insert ( Iterator before, const T &value ) {
    int begin_distance = bAbs ( begin() - before );

    detach();

    if ( Data->AllocSize < Data->Size + 1 ) {
        Data->realloc ( Data->Size + 1 );
    }

    Data->Array[ ( Data->Size ) ] = T ( value );

    T *it = Data->Array + ( Data->Size );
    Iterator it2 = begin() + begin_distance;
    while ( it != it2.operator->() ) {
        bSwap ( *it, * ( it - 1 ) );
        --it;
    }


    Data->Size += 1;
}

template< typename T >
void BVector<T>::append ( const T &value ) {
    detach();

    if ( Data->AllocSize < Data->Size + 1 ) {
        Data->realloc ( Data->Size + 1 );
    }

    Data->Array[ Data->Size ] = T ( value );

    Data->Size += 1;
}


template< typename T >
void BVector<T>::resize ( int new_size ) {
    detach();

    if ( Data->AllocSize < new_size ) {
        Data->realloc ( new_size );
    }

    if ( new_size > Data->Size ) {
        int count = bAbs ( new_size - Data->Size );
        for ( int i = Data->Size; i < Data->Size + count; i++ ) {
            Data->Array[ i ] = T();
        }
    }


    Data->Size = new_size;
}

template< typename T >
typename  BVector<T>::Iterator BVector<T>::remove ( typename BVector<T>::Iterator position ) {
    if ( isEmpty() ) {
        return  BVector<T>::Iterator ( 0 );
    }

    detach();

    int begin_distance = bAbs ( position - begin() );

    T *new_array = ( T * ) malloc ( sizeof ( T ) * Data->AllocSize );
    B_CHECK_PTR ( new_array );

    if ( !BTypeInfo<T>::isPrimtiveType ) {
        ( *position ).~T();
    }

    if ( begin_distance != 0 ) {
        for ( int i = 0; i < begin_distance; i++ ) {
            new_array[i] = T ( Data->Array[ i ] );
        }
    }

    for ( int i = begin_distance; i < Data->Size - 1; i++ ) {
        new_array[ i ] = T ( Data->Array[ i + 1  ] );
    }


    free ( Data->Array );
    Data->Array = new_array;

    Data->Size -= 1;
    return BVector<T>::Iterator ( Data->Array + begin_distance );
}

template< typename T >
void BVector<T>::clear() {
    *this = BVector<T>();
}

template< typename T >
void BVector<T>::remove ( int position ) {
    B_ASSERT_MSG ( ( position >= 0 ) && ( position < Data->Size ), "BVector<T>::remove" , "Index out of range" );
    remove ( begin() + position );
}

template< typename T >
void BVector<T>::detach_internal() {
    if ( !Data->ReferenceCounter.dereference() ) {
        delete Data;
        return;
    }

    Data = Data->makeHardCopy();
    Data->ReferenceCounter.reference();

    /*    BVectorData *new_data = 0;

        BOXE_TRY {
            new_data = new BVectorData ( Data->AllocSize );
            B_CHECK_PTR ( new_data );

            new_data->ReferenceCounter.reference();

        } BOXE_CATCH ( const std::bad_alloc & ) {
            BOXE_RETHROW;
        }

        new_data->Size = Data->Size;

        T *it = Data->Array + Data->Size;
        T *it2 = new_data->Array + new_data->Size;
        while ( it != Data->Array ) {
            * ( --it2 ) = T ( * ( --it ) );
        }

        Data = new_data;*/
}

BOXE_NAMESPACE_END ( Core )

#endif // BVECTOR_H
