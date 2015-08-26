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

#ifndef BHASH_H
#define BHASH_H

#include "bglobal.h"
#include "blinkedlist.h"
#include "BPair"
#include "breferencecounter.h"

BOXE_NAMESPACE_BEGIN ( Core )

template < class Key, class Value >
class BHash {
    private:
        struct HItem {
            HItem() : pPreviousItem ( 0 ), pNextItem ( 0 ) {}

            HItem ( long hash,  const Key &key, const Value &value ) : HASH ( hash ), KEY ( key ),  VALUE ( value ) {}

            long HASH;           //!< Key.
            Key KEY;
            Value VALUE;       //!< Value.

            HItem *pPreviousItem; //!< Pointer to previous ll item.
            HItem *pNextItem;     //!< Pointer to next ll item.
        };

        struct HashData {
            inline HashData() : Count ( 0 ), pFirstItem ( 0 ), pLastItem ( 0 ) {
            }

            ~ HashData() {
                HItem *it = pFirstItem;
                while ( it != 0 ) {
                    HItem *item = it;

                    delete item;

                    it = it->pNextItem;
                }
            }

            void removeItem ( HItem *p_item ) {
                if ( Count == 1 ) {
                    Count--;
                    pFirstItem = 0;
                    pLastItem = 0;
                    return;
                }

                if ( p_item->pPreviousItem != 0 ) {
                    p_item->pPreviousItem->pNextItem = p_item->pNextItem;
                } else {
                    pFirstItem = p_item->pNextItem;
                }

                if ( p_item->pNextItem != 0 ) {
                    p_item->pNextItem->pPreviousItem = p_item->pPreviousItem;
                } else {
                    pLastItem = p_item->pPreviousItem;
                };

                Count--;
            }

            HashData *makeHardCopy( ) {
                HashData *new_data = 0;
                BOXE_TRY {
                    new_data = new HashData();

                    B_CHECK_PTR ( new_data );

                } BOXE_CATCH ( const std::bad_alloc & ) {
                    BOXE_RETHROW;
                }

                if ( Count == 0 ) {
                    return new_data;
                }

                HItem *new_item = new HItem ( pFirstItem->HASH, pFirstItem->KEY, pFirstItem->VALUE );
                new_item->pNextItem = 0;
                new_item->pPreviousItem = 0;

                new_data->pFirstItem = new_item;
                new_data->pLastItem = new_item;

                HItem *it = pFirstItem->pNextItem;
                while ( it != 0 ) {
                    HItem *new_item = new HItem ( it->HASH, it->KEY, it->VALUE );

                    new_item->pNextItem = 0;
                    new_item->pPreviousItem = new_data->pLastItem;

                    new_data->pLastItem->pNextItem = new_item;

                    new_data->pLastItem = new_item;

                    it = it->pNextItem;
                }

                new_data->Count = Count;

                return new_data;
            }

            BReferenceCounter ReferenceCounter; //!< Reference counter.

            int Count; //!< Item count.

            HItem *pFirstItem; //!< Pointer to first item.
            HItem *pLastItem;  //!< Pointer to last item.
        };


    public:
        class Iterator {
            public:

                /*!
                 * Create iterator.
                 * \param item Pointer to item.
                 */
                Iterator ( HItem *item ) : Item ( item ) {}

                /*!
                 * Copy constructor.
                 * \param other Other Iterator.
                 */
                Iterator ( const Iterator &other ) : Item ( other.Item ) {}

                /*!
                 * Get value.
                 * \return Reference to value.
                 */
                inline Value &operator*() const {
                    return Item->VALUE;
                }

                /*!
                 * Get value pointer.
                 * \return Pointer to value
                 */
                inline Value *operator->() {
                    return & ( Item->VALUE );
                }


                /*!
                 * Equal two iterators
                 * \param other Reference to other iterator.
                 * \return True if iterator is equal, else return false.
                 */
                inline bool operator== ( const Iterator &other ) const {
                    return ( Item == other.Item );
                }

                /*!
                 * Equal two iterators
                 * \param other Reference to other iterator.
                 * \return True if iterator is doferent, else return false.
                 */
                inline bool operator!= ( const Iterator &other ) const {
                    return ( Item != other.Item );
                }


                /*!
                 * Move iterator about 'index' next item.
                 * \param index Index.
                 * \return Moved iterator.
                 */
                inline Iterator operator+ ( int index ) const {
                    Iterator it ( Item );

                    int i = index;
                    while ( i != 0 ) {
                        it.Item = it.Item->pNextItem;
                        i--;
                    }

                    return it;
                }

                /*!
                 * Move iterator to next item.
                 * \return Reference to this iterator.
                 */
                inline Iterator &operator++() {
                    Item = Item->pNextItem;
                    return *this;
                }

                /*!
                 * Move iterator to next item.
                 * \return Moved iterator.
                 */
                inline Iterator operator++ ( int ) {
                    //HItem *item = Item;

                    Item = Item->pNextItem;

                    return Iterator ( Item );
                }

                /*!
                 * Move this iterator about 'index' next item.
                 * \param index Index.
                 * \return This iterator.
                 */
                inline Iterator &operator+= ( int index ) {
                    int i = index;
                    while ( i != 0 ) {
                        Item = Item->pNextItem;
                        i--;
                    }
                    return *this;
                }

                /*!
                 * Move iterator about 'index' previous item.
                 * \param index Index.
                 * \return Moved iterator.
                 */
                inline Iterator operator- ( int index ) const {
                    Iterator it ( Item );

                    int i = index;
                    while ( i != 0 ) {
                        it.Item = it.Item->pPreviousItem;
                        i--;
                    }

                    return it;
                }

                /*!
                 * Move iterator to previous item.
                 * \return Reference to this iterator.
                 */
                inline Iterator &operator--() {
                    Item = Item->pPreviousItem;
                    return *this;
                }

                /*!
                 * Move iterator to previous item.
                 * \return Moved iterator.
                 */
                inline Iterator operator-- ( int ) {
                    return Iterator ( Item->pPreviousItem );
                }

                /*!
                 * Move this iterator about 'index' previous item.
                 * \param index Index.
                 * \return This iterator.
                 */
                inline Iterator &operator-= ( int index ) {
                    int i = index;
                    while ( i != 0 ) {
                        Item = Item->pPreviousItem;
                        i--;
                    }

                }

                Value &value() {
                    return Item->VALUE;
                }

                const Key &key() {
                    return Item->KEY;
                }

            private:
                friend class BHash<Key, Value>;
                HItem *Item; //!< Pointer to item.
        };

        class ConstIterator {
            public:

                /*!
                 * Create iterator.
                 * \param item Pointer to item.
                 */
                ConstIterator ( HItem *item ) : Item ( item ) {}

                /*!
                 * Copy constructor.
                 * \param other Other ConstIterator.
                 */
                ConstIterator ( const ConstIterator &other ) : Item ( other.Item ) {}

                /*!
                 * Copy constructor.
                 * \param other Other Iterator.
                 */
                ConstIterator ( const Iterator &other ) : Item ( other.Item ) {}

                /*!
                 * Get value.
                 * \return Reference to value.
                 */
                inline Value &operator*() const {
                    return Item->VALUE;
                }

                /*!
                 * Get value pointer.
                 * \return Pointer to value
                 */
                inline Value *operator->() {
                    return & ( Item->VALUE );
                }


                /*!
                 * Equal two iterators
                 * \param other Reference to other iterator.
                 * \return True if iterator is equal, else return false.
                 */
                inline bool operator== ( const ConstIterator &other ) const {
                    return ( Item == other.Item );
                }

                /*!
                 * Equal two iterators
                 * \param other Reference to other iterator.
                 * \return True if iterator is doferent, else return false.
                 */
                inline bool operator!= ( const ConstIterator &other ) const {
                    return ( Item != other.Item );
                }


                /*!
                 * Move iterator about 'index' next item.
                 * \param index Index.
                 * \return Moved iterator.
                 */
                inline ConstIterator operator+ ( int index ) const {
                    ConstIterator it ( Item );

                    int i = index;
                    while ( i != 0 ) {
                        it.Item = it.Item->pNextItem;
                        i--;
                    }

                    return it;
                }

                /*!
                 * Move iterator to next item.
                 * \return Reference to this iterator.
                 */
                inline ConstIterator &operator++() {
                    Item = Item->pNextItem;
                    return *this;
                }

                /*!
                 * Move iterator to next item.
                 * \return Moved iterator.
                 */
                inline ConstIterator operator++ ( int ) {
                    HItem *item = Item;

                    Item = Item->pNextItem;

                    return ConstIterator ( Item );
                }

                /*!
                 * Move this iterator about 'index' next item.
                 * \param index Index.
                 * \return This iterator.
                 */
                inline ConstIterator &operator+= ( int index ) {
                    int i = index;
                    while ( i != 0 ) {
                        Item = Item->pNextItem;
                        i--;
                    }
                    return *this;
                }

                /*!
                 * Move iterator about 'index' previous item.
                 * \param index Index.
                 * \return Moved iterator.
                 */
                inline ConstIterator operator- ( int index ) const {
                    ConstIterator it ( Item );

                    int i = index;
                    while ( i != 0 ) {
                        it.Item = it.Item->pPreviousItem;
                        i--;
                    }

                    return it;
                }

                /*!
                 * Move iterator to previous item.
                 * \return Reference to this iterator.
                 */
                inline ConstIterator &operator--() {
                    Item = Item->pPreviousItem;
                    return *this;
                }

                /*!
                 * Move iterator to previous item.
                 * \return Moved iterator.
                 */
                inline ConstIterator operator-- ( int ) {
                    return ConstIterator ( Item->pPreviousItem );
                }

                /*!
                 * Move this iterator about 'index' previous item.
                 * \param index Index.
                 * \return This iterator.
                 */
                inline ConstIterator &operator-= ( int index ) {
                    int i = index;
                    while ( i != 0 ) {
                        Item = Item->pPreviousItem;
                        i--;
                    }

                }

                Value &value() {
                    return Item->VALUE;
                }

                const Key &key() {
                    return Item->KEY;
                }

            private:
                friend class BHash<Key, Value>;
                HItem *Item; //!< Pointer to item.
        };

    public:
        BHash();
        BHash ( const BHash<Key, Value>& other );

        /*!
         * Destructor.
         */
        ~BHash();

        inline bool isSharedWith ( const  BHash<Key, Value>& other ) const {
            return Data == other.Data;
        }

        inline bool isEmpty() const {
            return !Data->Count;
        }

        inline int count() const {
            return Data->Count;
        }

        inline void detach() {
            if ( Data->ReferenceCounter != 1 ) {
                detach_internal();
            }
        }


        /*!
         * Get begin iterator.
         * \return Begin iterator.
         */
        inline Iterator begin() {
            detach();
            return Iterator ( Data->pFirstItem );
        }

        /*!
         * Get end iterator.
         * \return End iterator.
         */
        inline Iterator end() {
            detach();
            return Iterator ( 0 );
        }

        inline ConstIterator begin() const {
            return ConstIterator ( Data->pFirstItem );
        }

        inline ConstIterator end() const {
            return ConstIterator ( 0 );
        }

        inline ConstIterator constBegin() const {
            return ConstIterator ( Data->pFirstItem );
        }

        inline ConstIterator constEnd() const {
            return ConstIterator ( 0 );
        }

        bool insert ( const Key &key, const Value &value );

        Iterator find ( const Key &key );
        ConstIterator find ( const Key &key ) const ;
        Iterator erase ( Iterator position );
        bool contains ( const Key &key ) const;

    private:
        void append ( long hash, const Key &key, const Value &value );
        void prepend ( long hash, const Key &key, const Value &value );
        Iterator insert ( Iterator before, long hash, const Key &key, const Value &value );

    private:
        HashData *Data; //!< Internal data pointer.
        Iterator Pointer;

    private:
        void detach_internal();

        bool addRight ( const long hash, const Key &key, const Value &value );
        bool addLeft ( const long hash, const Key &key, const Value &value );

        Iterator findLeft ( const long hash );
        Iterator findRight ( const long hash );

        bool findLeft ( const long hash ) const;
        bool findRight ( const long hash ) const;
};

template< class Key, class Value >
BHash<Key, Value>::BHash() : Pointer ( 0 ) {
    BOXE_TRY {
        Data = new HashData();
        B_CHECK_PTR ( Data );

        Data->ReferenceCounter.reference();

    } BOXE_CATCH ( const std::bad_alloc & ) {
        BOXE_RETHROW;
    }
}

template< class Key, class Value >
BHash<Key, Value>::BHash ( const BHash<Key, Value>& other ) {
    Data = other.Data;
    Data->ReferenceCounter.reference();
}

template< class Key, class Value >
BHash<Key, Value>::~BHash() {
    if ( !Data->ReferenceCounter.dereference() ) {
        delete Data;
    }
}


template< class Key, class Value >
bool BHash<Key, Value>::insert ( const Key &key, const Value &value ) {
    if ( isEmpty() ) {
        append ( bCalcHash ( key ), key, value );
        Pointer.Item = Data->pLastItem;
        return true;
    } else {
        const long hash = bCalcHash ( key );
        if ( hash > Pointer.Item->HASH ) {
            return addRight ( hash, key, value );

        } else {
            return addLeft ( hash, key,  value );
        }
    }
}

template< class Key, class Value >
typename BHash<Key, Value>::Iterator BHash<Key, Value>::find ( const Key &key ) {
    if ( isEmpty() ) {
        return Iterator ( 0 );
    }

    const long hash = bCalcHash ( key );

    BHash<Key, Value>::Iterator it = begin();
    while ( it != end() ) {
        if ( bCalcHash ( it.key() ) == hash ) {
            return it;
        }
        it++;
    }

    return Iterator ( 0 );

    /*    if ( hash == Pointer.Item->HASH ) {
            return Iterator ( Pointer );

        } else if ( hash > Pointer.Item->HASH ) {
            return Iterator ( findRight ( hash ) );

        } else if ( hash < Pointer.Item->HASH ) {
            return Iterator ( findLeft ( hash ) );
        }*/
}

template< class Key, class Value >
typename BHash<Key, Value>::ConstIterator BHash<Key, Value>::find ( const Key &key ) const {
    if ( isEmpty() ) {
        return ConstIterator ( 0 );
    }

    const long hash = bCalcHash ( key );

    BHash<Key, Value>::ConstIterator it = constBegin();
    while ( it != constEnd() ) {
        if ( bCalcHash ( it.key() ) == hash ) {
            return it;
        }
        it++;
    }

    return Iterator ( 0 );

    /*    if ( hash == Pointer.Item->HASH ) {
            return Iterator ( Pointer );

        } else if ( hash > Pointer.Item->HASH ) {
            return Iterator ( findRight ( hash ) );

        } else if ( hash < Pointer.Item->HASH ) {
            return Iterator ( findLeft ( hash ) );
        }*/
}

template< class Key, class Value >
bool BHash<Key, Value>::contains ( const Key &key ) const {
    if ( isEmpty() ) {
        return false;
    }

    const long hash = bCalcHash ( key );
    if ( hash == Pointer.Item->HASH ) {
        return true;

    } else if ( hash > Pointer.Item->HASH ) {
        return findRight ( hash );

    } else {
        return findLeft ( hash );
    }
}


template< class Key, class Value >
void BHash<Key, Value>::detach_internal() {
    if ( !Data->ReferenceCounter.dereference() ) {
        delete Data;
        return;
    }

    Data = Data->makeHardCopy();
    Data->ReferenceCounter.reference();
}

template< class Key, class Value >
void BHash<Key, Value>::append ( long hash, const Key &key, const Value &value  ) {
    detach();

    HItem *new_item = 0;

    BOXE_TRY {
        new_item = new HItem;
        B_CHECK_PTR ( new_item );

    } BOXE_CATCH ( const std::bad_alloc & ) {
        BOXE_RETHROW;
    }

    new_item->VALUE = value;
    new_item->HASH = hash;
    new_item->KEY = key;

    if ( Data->pLastItem == 0 ) {
        new_item->pNextItem = 0;
        new_item->pPreviousItem = 0;

        Data->pLastItem = new_item;
        Data->pFirstItem = new_item;
        Data->Count = 1;
        return;

    } else {
        new_item->pNextItem = 0;
        new_item->pPreviousItem = Data->pLastItem;

        Data->pLastItem->pNextItem = new_item;

        Data->pLastItem = new_item;

        Data->Count += 1;
    }

}

template< class Key, class Value >
void BHash<Key, Value>::prepend ( long hash, const Key &key, const Value &value ) {
    detach();

    HItem *new_item = 0;

    BOXE_TRY {
        new_item = new HItem;
        B_CHECK_PTR ( new_item );

    } BOXE_CATCH ( const std::bad_alloc & ) {
        BOXE_RETHROW;
    }

    new_item->VALUE = value;
    new_item->HASH = hash;
    new_item->KEY = key;

    if ( Data->pFirstItem == 0 ) {
        new_item->pNextItem = 0;
        new_item->pPreviousItem = 0;

        Data->pLastItem = new_item;
        Data->pFirstItem = new_item;
        Data->Count = 1;
        return;

    } else {
        new_item->pNextItem = Data->pFirstItem;
        new_item->pPreviousItem = 0;

        Data->pFirstItem->pPreviousItem = new_item;

        Data->pFirstItem = new_item;

        Data->Count += 1;
    }

}

template< class Key, class Value >
typename BHash<Key, Value>::Iterator BHash<Key, Value>::insert ( typename BHash<Key, Value>::Iterator before, long hash, const Key &key,  const Value &value ) {
    if ( before == begin() ) {
        prepend ( hash, key, value );
        return begin();

    } else if ( before == end() ) {
        append ( hash, key, value );
        return end();
    }

    detach();

    HItem *new_item = 0;
    BOXE_TRY {
        new_item = new HItem ( hash, key,  value );
    } BOXE_CATCH ( const std::bad_alloc & ) {
        BOXE_RETHROW;
    }

    new_item->pNextItem = before.Item;
    new_item->pPreviousItem = before.Item->pPreviousItem;

    before.Item->pPreviousItem->pNextItem = new_item;
    before.Item->pPreviousItem = new_item;

    return Iterator ( new_item );
}

template< class Key, class Value >
typename BHash<Key, Value>::Iterator BHash<Key, Value>::erase ( BHash<Key, Value>::Iterator position ) {
    detach();

    Data->removeItem ( position.Item );
    delete position.Item;

    Pointer = begin();
    return position++;
}

template< class Key, class Value >
bool BHash<Key, Value>::addRight ( const long int hash, const Key &key, const Value &value ) {
    while ( Pointer !=  end() ) { // TODO: constEnd;
        if ( hash < Pointer.Item->HASH ) {
            insert ( Pointer, hash, key,  value );
            return true;
        }
        ++Pointer;
    }

    append ( hash, key, value );
    Pointer.Item = Data->pLastItem;
    return true;
}

template< class Key, class Value >
bool BHash<Key, Value>::addLeft ( const long int hash, const Key &key, const Value &value ) {
    while ( Pointer != begin()  ) { // TODO: constEnd;
        if ( hash > Pointer.Item->HASH ) {
            insert ( Pointer + 1, hash, key, value );
            return true;
        }
        --Pointer;
    }

    prepend ( hash, key, value );
    Pointer = begin();
    return true;
}


template< class Key, class Value >
typename BHash<Key, Value>::Iterator BHash<Key, Value>::findRight ( const long hash ) {
    while ( Pointer !=  end() ) { // TODO: constEnd;
        if ( hash == Pointer.Item->HASH ) {
            return Pointer;
        }
        ++Pointer;
    }

    Pointer = Data->pLastItem;

    return Iterator ( 0 );
}

template< class Key, class Value >
typename BHash<Key, Value>::Iterator BHash<Key, Value>::findLeft ( const long hash ) {
    while ( Pointer != end()  ) { // TODO: constEnd;
        if ( hash == Pointer.Item->HASH ) {
            return Pointer;
        }

        --Pointer;
    }
    Pointer = Data->pFirstItem;
    return Iterator ( 0 );
}

template< class Key, class Value >
bool BHash<Key, Value>::findRight ( const long hash ) const {
    ConstIterator p ( Pointer );

    while ( p != constEnd() ) { // TODO: constEnd;
        if ( hash == p.Item->HASH ) {
            return true;
        }
        ++p;
    }

    return false;
}

template< class Key, class Value >
bool BHash<Key, Value>::findLeft ( const long hash ) const {
    ConstIterator p ( Pointer );

    while ( p != constEnd()  ) { // TODO: constEnd;
        if ( hash == p.Item->HASH ) {
            return true;
        }

        --p;
    }

    return false;
}



extern long bCalcHash ( int value );


BOXE_NAMESPACE_END ( Core )

#endif // BHASH_H
