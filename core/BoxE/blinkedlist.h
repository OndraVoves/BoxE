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


#ifndef BLINKEDLIST_H
#define BLINKEDLIST_H

#include "bglobal.h"
#include "breferencecounter.h"

BOXE_NAMESPACE_BEGIN ( Core )

/*!
 * Template linked list implementation.
 */
template< typename T >
class BLinkedList {
    private:
        struct LLItem {
            LLItem() : pPreviousItem ( 0 ), pNextItem ( 0 ) {}

            LLItem ( const T &value ) : Value ( value ) {}

            T Value;           //!< Value.
            LLItem *pPreviousItem; //!< Pointer to previous ll item.
            LLItem *pNextItem;     //!< Pointer to next ll item.
        };

        struct BLinkedListData {
            inline BLinkedListData() : Count ( 0 ), pFirstItem ( 0 ), pLastItem ( 0 ) {
            }

            ~ BLinkedListData() {
                LLItem *it = pFirstItem;
                while ( it != 0 ) {
                    LLItem *item = it;

                    delete item;

                    it = it->pNextItem;
                }
            }

            void removeItem ( LLItem *p_item ) {
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

            BLinkedListData *makeHardCopy( ) {
                BLinkedListData *new_data = 0;
                BOXE_TRY {
                    new_data = new BLinkedListData();

                    B_CHECK_PTR ( new_data );

                } BOXE_CATCH ( const std::bad_alloc & ) {
                    BOXE_RETHROW;
                }

                if ( Count == 0 ) {
                    return new_data;
                }

                LLItem *new_item = new LLItem ( pFirstItem->Value );
                new_item->pNextItem = 0;
                new_item->pPreviousItem = 0;

                new_data->pFirstItem = new_item;
                new_data->pLastItem = new_item;

                LLItem *it = pFirstItem->pNextItem;
                while ( it != 0 ) {
                    LLItem *new_item = new LLItem ( it->Value );

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

            LLItem *pFirstItem; //!< Pointer to first item.
            LLItem *pLastItem;  //!< Pointer to last item.
        };

    public:
        /*!
         * Linked list iterator.
         */
        class Iterator {
            public:

                /*!
                 * Create iterator.
                 * \param item Pointer to item.
                 */
                Iterator ( LLItem *item ) : Item ( item ) {}

                /*!
                 * Copy constructor.
                 * \param other Other Iterator.
                 */
                Iterator ( const Iterator &other ) : Item ( other.Item ) {}

                /*!
                 * Get value.
                 * \return Reference to value.
                 */
                inline T &operator*() const {
                    return Item->Value;
                }

                /*!
                 * Get value pointer.
                 * \return Pointer to value
                 */
                inline T *operator->() {
                    return & ( Item->Value );
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
                    LLItem *item = Item;

                    Item = Item->pNextItem;

                    return Iterator ( item );
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

            private:
                friend class BLinkedList<T>;
                LLItem *Item; //!< Pointer to item.
        };

        /*!
         * Linked list const iterator.
         */
        class ConstIterator {
            public:

                /*!
                 * Create iterator.
                 * \param item Pointer to item.
                 */
                ConstIterator ( LLItem *item ) : Item ( item ) {}

                /*!
                 * Copy constructor.
                 * \param other Other Iterator.
                 */
                ConstIterator ( const ConstIterator &other ) : Item ( other.Item ) {}

                /*!
                 * Get value.
                 * \return Reference to value.
                 */
                inline T &operator*() const {
                    return Item->Value;
                }

                /*!
                 * Get value pointer.
                 * \return Pointer to value
                 */
                inline T *operator->() {
                    return & ( Item->Value );
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
                    LLItem *item = Item;

                    Item = Item->pNextItem;

                    return ConstIterator ( item );
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
                    return Iterator ( Item->pPreviousItem );
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

            private:
                LLItem *Item; //!< Pointer to item.
        };

    public:
        /*!
         * Construct empty linked list.
         */
        BLinkedList();

        /*!
         * Construct linkedlist from other.
         * \param other Reference to other linkedlist.
         */
        BLinkedList ( const BLinkedList<T>& other );

        /*!
         * Destructor.
         */
        ~BLinkedList();

        /*!
         * Append value to linked list.
         * \param value Reference to value.
         * \return Reference to this linkedlist.
         */
        inline BLinkedList<T>& operator<< ( const T &value ) {
            append ( value );
            return *this;
        }

        /*!
         * Is this ll shared with other?
         * \param other Reference to other ll.
         * \return True if this is shared with other, else return false.
         */
        inline bool isSharedWith ( const BLinkedList<T> & other ) const {
            return Data == other.Data;
        }

        /*!
         * If linkedlist emtpy return true, else return false.
         * \return True if empty, else return false.
         */
        inline bool isEmpty() const {
            return !Data->Count;
        }

        /*!
        * Return item count.
         * \return Item count.
         */
        inline int count() const {
            return Data->Count;
        }

        /*!
         * Return count of value in linkedlist.
         * \param value Reference to Value.
         * \return Count of value.
         */
        int count ( const T &value ) const;

        /*!
         * Return true if linkedlist contains value.
         * \param value Reference to value.
         * \return True if linkedlist contains value.
         */
        bool contains ( const T &value ) const;

        /*!
         * Return true if linkedlist starts with value.
         * \param value Reference to value.
         * \return True if linkedlist starts witch value, else return false.
         */
        inline bool startsWith ( const T &value ) const {
            return Data->pFirstItem->Value == value;
        }

        /*!
         * Return true if linkedlist ends with value.
         * \param value Reference to value.
         * \return True if linkedlist ends witch value, else return false.
         */
        inline bool endsWith ( const T &value ) const {
            return Data->pLastItem->Value == value;
        }

        /*!
         * Get reference to first value.
         * \return Reference to first value.
         */
        T &first();

        /*!
         * Get const reference to first value.
         * \return Const reference to first value.
         */
        const T &first( ) const;

        /*!
         * Get reference to last value.
         * \return Reference to last value.
         */
        T &last();

        /*!
         * Get const reference to last value.
         * \return Const reference to last value.
         */
        const T &last( ) const;

        /*!
         * Get first value and remove first item.
         * \return Value.
         */
        T takeFirst( );

        /*!
         * Get last value and remove last item.
         * \return Value.
         */
        T takeLast( );

        /*!
         * Remove first item.
         */
        void removeFirst();

        /*!
         * Remove last item.
         */
        void removeLast();

        /*!
         * Remove one value from ll.
         * \param value Reference to value.
         */
        void removeOne ( const T &value );

        /*!
         * Remove all value from ll.
         * \param value Reference to value.
         */
        int removeAll ( const T &value );

        /*!
         * Append value to end.
         * \param value Value.
         */
        void append ( const T &value );

        /*!
         * Append value to start.
         * \param value Value.
         */
        void prepend ( const T &value );

        /*!
         * Insert value before iterator.
         * \param before insert before this iterator.
         * \param value Reference to value.
         * \return Iterator to inserted item.
         */
        Iterator insert ( Iterator before, const T &value );

        /*!
         * Erase item at position.
         * \param position Position to erase.
         * \return Iterator to next item.
         */
        Iterator erase ( Iterator position );

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

        /*!
         * Get last item as iterator.
         * \return "Last" iterator.
         */
        inline Iterator lastItem() {
            detach();
            return Iterator ( Data->pLastItem );
        }

        /*!
         * Get const begin iterator.
         * \return Const begin iterator.
         */
        inline ConstIterator begin() const {
            return ConstIterator ( Data->pFirstItem );
        }

        /*!
         * Get const end iterator.
         * \return Const end iterator.
         */
        inline ConstIterator end() const {
            return ConstIterator ( 0 );
        }

        /*!
         * Get const begin iterator.
         * \return Const begin iterator.
         */
        inline ConstIterator constBegin() const {
            return ConstIterator ( Data->pFirstItem );
        }

        /*!
         * Get const end iterator.
         * \return Const end iterator.
         */
        inline ConstIterator constEnd() const {
            return ConstIterator ( 0 );
        }



        /*!
         * Detach linked list.
         */
        inline void detach() {
            if ( Data->ReferenceCounter != 1 ) {
                detach_internal();
            }
        }

    private:
        BLinkedListData *Data; //!< Internal data pointer.

        void detach_internal();
};

template< typename T >
inline BLinkedList<T>::BLinkedList() {
    BOXE_TRY {
        Data = new BLinkedListData();
        B_CHECK_PTR ( Data );

        Data->ReferenceCounter.reference();

    } BOXE_CATCH ( const std::bad_alloc & ) {
        BOXE_RETHROW;
    }
}

template< typename T >
inline BLinkedList<T>::BLinkedList ( const BLinkedList<T>& other ) {
    Data = other.Data;
    Data->ReferenceCounter.reference();
}

template< typename T >
inline BLinkedList<T>::~BLinkedList() {
    if ( !Data->ReferenceCounter.dereference() ) {
        delete Data;
    }
}

template< typename T >
int BLinkedList<T>::count ( const T &value ) const {
    LLItem *it = Data->pFirstItem;
    int i = 0;
    while ( it != 0 ) {

        if ( it->Value == value ) {
            i++;
        }

        it = it->pNextItem;
    }

    return i;
}

template< typename T >
bool BLinkedList<T>::contains ( const T &value ) const {
    LLItem *it = Data->pFirstItem;
    while ( it != 0 ) {

        if ( it->Value == value ) {
            return true;
        }

        it = it->pNextItem;
    }

    return false;
}

template< typename T >
inline T &BLinkedList<T>::first() {
    B_ASSERT_MSG ( Data->Count != 0, "BLinkedList<T>::first()", "List is empty." );

    detach();

    return ( Data->pFirstItem->Value );
}

template< typename T >
inline const T &BLinkedList<T>::first() const {
    B_ASSERT_MSG ( Data->Count != 0, "BLinkedList<T>::first()", "List is empty." );

    return ( Data->pFirstItem->Value );
}

template< typename T >
inline T &BLinkedList<T>::last() {
    B_ASSERT_MSG ( Data->Count != 0, "BLinkedList<T>::last()", "List is empty." );
    detach();
    return ( Data->pLastItem->Value );
}

template< typename T >
inline const T &BLinkedList<T>::last() const {
    B_ASSERT_MSG ( Data->Count != 0, "BLinkedList<T>::last()", "List is empty." );

    return ( Data->pLastItem->Value );
}

template< typename T >
T BLinkedList<T>::takeFirst( ) {
    B_ASSERT_MSG ( Data->Count != 0, "BLinkedList<T>::takeFirst()", "List is empty." );

    detach();

    T return_value ( Data->pFirstItem->Value );

    LLItem *first = Data->pFirstItem;

    Data->removeItem ( first );

    delete first;

    return return_value;
}

template< typename T >
T BLinkedList<T>::takeLast( ) {
    B_ASSERT_MSG ( Data->Count != 0, "BLinkedList<T>::takeLast()", "List is empty." );

    detach();

    T return_value ( Data->pLastItem->Value );

    LLItem *last = Data->pLastItem;

    Data->removeItem ( last );

    delete last;

    return return_value;
}

template< typename T >
void BLinkedList<T>::removeFirst() {
    detach();

    if ( isEmpty() ) {
        return;
    }

    LLItem *first = Data->pFirstItem;
    Data->removeItem ( first );
    delete first;
}

template< typename T >
void BLinkedList<T>::removeLast() {
    detach();

    if ( isEmpty() ) {
        return;
    }

    LLItem *last = Data->pLastItem;
    Data->removeItem ( last );
    delete last;
}

template< typename T >
void BLinkedList<T>::removeOne ( const T &value ) {
    detach();

    LLItem *it = Data->pFirstItem;
    while ( it != 0 ) {

        if ( it->Value == value ) {
            Data->removeItem ( it );
            delete it;

            return;
        }

        it = it->pNextItem;
    }
}

template< typename T >
int BLinkedList<T>::removeAll ( const T &value ) {
    detach();

    int i = 0;
    LLItem *it = Data->pFirstItem;
    while ( it != 0 ) {

        if ( it->Value == value ) {
            Data->removeItem ( it );
            delete it;
            i++;
        }

        it = it->pNextItem;
    }

    return i;
}

template< typename T >
void BLinkedList<T>::append ( const T &value ) {
    detach();

    LLItem *new_item = 0;

    BOXE_TRY {
        new_item = new LLItem;
        B_CHECK_PTR ( new_item );

    } BOXE_CATCH ( const std::bad_alloc & ) {
        BOXE_RETHROW;
    }

    new_item->Value = value;

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

template< typename T >
void BLinkedList<T>::prepend ( const T &value ) {
    detach();

    LLItem *new_item = 0;

    BOXE_TRY {
        new_item = new LLItem;
        B_CHECK_PTR ( new_item );

    } BOXE_CATCH ( const std::bad_alloc & ) {
        BOXE_RETHROW;
    }

    new_item->Value = value;

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

template< typename T >
typename BLinkedList<T>::Iterator BLinkedList<T>::insert ( typename BLinkedList<T>::Iterator before, const T &value ) {
    if ( before == begin() ) {
        prepend ( value );
        return begin();

    } else if ( before == end() ) {
        append ( value );
        return end();
    }

    detach();

    LLItem *new_item = 0;
    BOXE_TRY {
        new_item = new LLItem ( value );
    } BOXE_CATCH ( const std::bad_alloc & ) {
        BOXE_RETHROW;
    }

    new_item->pNextItem = before.Item;
    new_item->pPreviousItem = before.Item->pPreviousItem;

    before.Item->pPreviousItem->pNextItem = new_item;
    before.Item->pPreviousItem = new_item;

    return Iterator ( new_item );
}

template< typename T >
typename BLinkedList<T>::Iterator BLinkedList<T>::erase ( BLinkedList<T>::Iterator position ) {
    detach();

    Data->removeItem ( position.Item );
    delete position.Item;

    return position++;
}

template< typename T >
void BLinkedList<T>::detach_internal() {
    if ( !Data->ReferenceCounter.dereference() ) {
        delete Data;
        return;
    }

    Data = Data->makeHardCopy();
    Data->ReferenceCounter.reference();
}

BOXE_NAMESPACE_END ( Core )

#endif // BLINKEDLIST_H
