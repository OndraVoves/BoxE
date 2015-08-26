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

#ifndef BSIGNAL2_H
#define BSIGNAL2_H

#include "bglobal.h"
#include "blinkedlist.h"
#include <stdio.h>

BOXE_NAMESPACE_BEGIN ( Core )

template< class ArgType1, class ArgType2 >
class BSignal2 {
    private:
        enum ESlotType {
            ST_STATIC = 0,
            ST_MEMBER
        };

        class BSlot2 {
            public:
                BSlot2 ( ESlotType slot_type ) : SlotType ( slot_type ) {
                }

                virtual bool operator== ( const BSlot2 &slot ) const = 0;

                virtual void call ( ArgType1 arg1, ArgType2 arg2 ) = 0;

                ESlotType slotType() const {
                    return SlotType;
                }


            private:
                ESlotType SlotType;
        };

        class BSlot2StaticFce : public BSlot2 {
                typedef void ( *StaticFcePointer_t ) ( ArgType1, ArgType2 );

            public:
                BSlot2StaticFce ( StaticFcePointer_t fce ) : BSlot2 ( ST_STATIC ), FunctionPtr ( fce ) {}

                virtual bool operator== ( const BSlot2 &slot ) const {
                    return ( ( slot.slotType() == ST_STATIC ) &&
                             ( FunctionPtr == static_cast< const BSlot2StaticFce & > ( slot ).FunctionPtr ) );
                }

                virtual void call ( ArgType1 arg1, ArgType2 arg2 ) {
                    FunctionPtr ( arg1, arg2 );
                };


            private:
                StaticFcePointer_t FunctionPtr;
        };

        template< class Class >
        class BSlot2MemberFce : public BSlot2 {
                typedef void ( Class::*MemberFcePointer_t ) ( ArgType1, ArgType2 );

            public:
                BSlot2MemberFce ( Class *cls, MemberFcePointer_t fce ) : BSlot2 ( ST_MEMBER ), ClassPtr ( cls ), FunctionPtr ( fce ) {}

                virtual bool operator== ( const BSlot2 &slot ) const {
                    return ( ( slot.slotType() == ST_MEMBER ) &&
                             ( ClassPtr == static_cast< const BSlot2MemberFce & > ( slot ).ClassPtr ) &&
                             ( FunctionPtr == static_cast< const BSlot2MemberFce & > ( slot ).FunctionPtr ) );
                }

                virtual void call ( ArgType1 arg1, ArgType2 arg2 ) {
                    ( ClassPtr->*FunctionPtr ) ( arg1, arg2 );
                };

            private:
                Class *ClassPtr;
                MemberFcePointer_t FunctionPtr;
        };

    public:
        BSignal2() {
        }

        ~BSignal2() {
            typename BLinkedList< BSlot2 * >::ConstIterator it = SlotList.constBegin();
            while ( it != SlotList.constEnd() ) {
                delete ( *it++ );
            }
        }

        void connect ( void ( *fce ) ( ArgType1, ArgType2 ) ) {
            SlotList.append ( new BSlot2StaticFce ( fce ) );
        }

        template< class Class >
        void connect ( Class *cls, void ( Class::*fce ) ( ArgType1, ArgType2 ) ) {
            SlotList.append ( new BSlot2MemberFce<Class> ( cls, fce ) );
        }

        void disconnect ( void ( *fce ) ( ArgType1, ArgType2 ) ) {
            typename BLinkedList< BSlot2 * >::Iterator it = SlotList.begin();

            BSlot2StaticFce slot ( fce );

            while ( it != SlotList.end() ) {
                if ( ( * ( *it ) ) == slot ) {
                    SlotList.erase ( it );
                    return;
                }

                ++it;
            }
        }

        template< class Class >
        void disconnect ( Class *cls, void ( Class::*fce ) ( ArgType1, ArgType2 ) ) {
            typename BLinkedList< BSlot2 * >::Iterator it = SlotList.begin();

            BSlot2MemberFce< Class > slot ( cls, fce );

            while ( it != SlotList.end() ) {
                if ( ( * ( *it ) ) == slot ) {
                    SlotList.erase ( it );
                    return;
                }

                ++it;
            }
        }

        void emitSignal ( ArgType1 arg1, ArgType2 arg2  ) {
            BLinkedList< BSlot2 * > slot_list ( SlotList );

            typename BLinkedList< BSlot2 * >::ConstIterator it = slot_list.constBegin();
            while ( it != slot_list.constEnd() ) {
                ( *it )->call ( arg1, arg2 );
                ++it;
            }
        }

    private:
        BLinkedList< BSlot2 * > SlotList;
};

BOXE_NAMESPACE_END ( Core )

#endif /* BSIGNAL2_H */
