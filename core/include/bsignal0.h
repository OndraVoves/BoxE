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

#ifndef BSIGNAL0_H
#define BSIGNAL0_H

#include "bglobal.h"
#include "blinkedlist.h"

BOXE_NAMESPACE_BEGIN ( Core )

class BSignal0 {
    private:
        enum ESlotType {
            ST_STATIC = 0,
            ST_MEMBER
        };

        class BSlot0 {
            public:
                BSlot0 ( ESlotType slot_type ) : SlotType ( slot_type ) {
                }

                virtual bool operator== ( const BSlot0 &slot ) const = 0;

                virtual void call() = 0;

                ESlotType slotType() const {
                    return SlotType;
                }


            private:
                ESlotType SlotType;
        };

        class BSlot0StaticFce : public BSlot0 {
                typedef void ( *StaticFcePointer_t ) ();

            public:
                BSlot0StaticFce ( StaticFcePointer_t fce ) : BSlot0 ( ST_STATIC ), FunctionPtr ( fce ) {}

                virtual bool operator== ( const BSlot0 &slot ) const {
                    return ( ( slot.slotType() == ST_STATIC ) &&
                             ( FunctionPtr == static_cast< const BSlot0StaticFce & > ( slot ).FunctionPtr ) );
                }

                virtual void call() {
                    FunctionPtr();
                };


            private:
                StaticFcePointer_t FunctionPtr;
        };

        template< class Class >
        class BSlot0MemberFce : public BSlot0 {
                typedef void ( Class::*MemberFcePointer_t ) ();

            public:
                BSlot0MemberFce ( Class *cls, MemberFcePointer_t fce ) : BSlot0 ( ST_MEMBER ), ClassPtr ( cls ), FunctionPtr ( fce ) {}

                virtual bool operator== ( const BSlot0 &slot ) const {
                    return ( ( slot.slotType() == ST_MEMBER ) &&
                             ( ClassPtr == static_cast< const BSlot0MemberFce & > ( slot ).ClassPtr ) &&
                             ( FunctionPtr == static_cast< const BSlot0MemberFce & > ( slot ).FunctionPtr ) );
                }

                virtual void call() {
                    ( ClassPtr->*FunctionPtr ) ( );
                };

            private:
                Class *ClassPtr;
                MemberFcePointer_t FunctionPtr;
        };

    public:
        BSignal0() {
        }

        ~BSignal0() {
            BLinkedList< BSlot0 * >::ConstIterator it = SlotList.constBegin();
            while ( it != SlotList.constEnd() ) {
                delete ( *it++ );
            }
        }

        void connect ( void ( *fce ) () ) {
            SlotList.append ( new BSlot0StaticFce ( fce ) );
        }

        template< class Class >
        void connect ( Class *cls, void ( Class::*fce ) () )  {
            SlotList.append ( new BSlot0MemberFce<Class> ( cls, fce ) );
        }

        void disconnect ( void ( *fce ) () ) {
            BLinkedList< BSlot0 * >::Iterator it = SlotList.begin();

            BSlot0StaticFce slot ( fce );

            while ( it != SlotList.end() ) {
                if ( ( * ( *it ) ) == slot ) {
                    SlotList.erase ( it );
                    return;
                }

                ++it;
            }
        }

        template< class Class >
        void disconnect (  Class *cls, void ( Class::*fce ) () ) {
            typename BLinkedList< BSlot0 * >::Iterator it = SlotList.begin();

            BSlot0MemberFce< Class > slot ( cls, fce );

            while ( it != SlotList.end() ) {
                if ( ( * ( *it ) ) == slot ) {
                    SlotList.erase ( it );
                    return;
                }

                ++it;
            }
        }

        void emitSignal( ) {
            BLinkedList< BSlot0 * > slot_list ( SlotList );

            typename BLinkedList< BSlot0 * >::ConstIterator it = slot_list.constBegin();
            while ( it != slot_list.constEnd() ) {
                ( *it )->call();
                ++it;
            }
        }

    private:
        BLinkedList< BSlot0 * > SlotList;
};

BOXE_NAMESPACE_END ( Core )

#endif /* BSIGNAL0_H */
