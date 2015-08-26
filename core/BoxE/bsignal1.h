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

#ifndef BSIGNAL1_H
#define BSIGNAL1_H

#include "bglobal.h"
#include "blinkedlist.h"

BOXE_NAMESPACE_BEGIN ( Core )

template< class ArgType1 >
class BSignal1 {
    private:
        enum ESlotType {
            ST_STATIC = 0,
            ST_MEMBER
        };

        class BSlot1 {
            public:
                BSlot1 ( ESlotType slot_type ) : SlotType ( slot_type ) {
                }

                virtual bool operator== ( const BSlot1 &slot ) const = 0;

                virtual void call ( ArgType1 arg ) = 0;

                ESlotType slotType() const {
                    return SlotType;
                }


            private:
                ESlotType SlotType;
        };

        class BSlot1StaticFce : public BSlot1 {
                typedef void ( *StaticFcePointer_t ) ( ArgType1 );

            public:
                BSlot1StaticFce ( StaticFcePointer_t fce ) : BSlot1 ( ST_STATIC ), FunctionPtr ( fce ) {}

                virtual bool operator== ( const BSlot1 &slot ) const {
                    return ( ( slot.slotType() == ST_STATIC ) &&
                             ( FunctionPtr == static_cast< const BSlot1StaticFce & > ( slot ).FunctionPtr ) );
                }

                virtual void call ( ArgType1 arg ) {
                    FunctionPtr ( arg );
                };


            private:
                StaticFcePointer_t FunctionPtr;
        };

        template< class Class >
        class BSlot1MemberFce : public BSlot1 {
                typedef void ( Class::*MemberFcePointer_t ) ( ArgType1 );

            public:
                BSlot1MemberFce ( Class *cls, MemberFcePointer_t fce ) : BSlot1 ( ST_MEMBER ), ClassPtr ( cls ), FunctionPtr ( fce ) {}

                virtual bool operator== ( const BSlot1 &slot ) const {
                    return ( ( slot.slotType() == ST_MEMBER ) &&
                             ( ClassPtr == static_cast< const BSlot1MemberFce & > ( slot ).ClassPtr ) &&
                             ( FunctionPtr == static_cast< const BSlot1MemberFce & > ( slot ).FunctionPtr ) );
                }

                virtual void call ( ArgType1 arg ) {
                    ( ClassPtr->*FunctionPtr ) ( arg );
                };

            private:
                Class *ClassPtr;
                MemberFcePointer_t FunctionPtr;
        };

    public:
        BSignal1() {
        }

        ~BSignal1() {
            typename BLinkedList< BSlot1 * >::ConstIterator it = SlotList.constBegin();
            while ( it != SlotList.constEnd() ) {
                delete ( *it++ );
            }
        }

        void connect ( void ( *fce ) ( ArgType1 ) ) {
            SlotList.append ( new BSlot1StaticFce ( fce ) );
        }

        template< class Class >
        void connect ( Class *cls, void ( Class::*fce ) ( ArgType1 ) ) {
            SlotList.append ( new BSlot1MemberFce<Class> ( cls, fce ) );
        }

        void disconnect ( void ( *fce ) ( ArgType1 ) ) {
            typename BLinkedList< BSlot1 * >::Iterator it = SlotList.begin();

            BSlot1StaticFce slot ( fce );

            while ( it != SlotList.end() ) {
                if ( ( * ( *it ) ) == slot ) {
                    SlotList.erase ( it );
                    return;
                }

                ++it;
            }
        }

        template< class Class >
        void disconnect ( Class *cls, void ( Class::*fce ) ( ArgType1 ) ) const {
            typename BLinkedList< BSlot1 * >::Iterator it = SlotList.begin();

            BSlot1MemberFce< Class > slot ( cls, fce );

            while ( it != SlotList.end() ) {
                if ( ( * ( *it ) ) == slot ) {
                    SlotList.erase ( it );
                    return;
                }

                ++it;
            }
        }

        void emitSignal ( ArgType1 arg  ) {
            BLinkedList< BSlot1 * > slot_list ( SlotList );

            typename BLinkedList< BSlot1 * >::ConstIterator it = slot_list.constBegin();
            while ( it != slot_list.constEnd() ) {
                ( *it )->call ( arg );
                ++it;
            }
        }

    private:
        BLinkedList< BSlot1 * > SlotList;
};

BOXE_NAMESPACE_END ( Core )

#endif /* BSIGNAL1_H */
