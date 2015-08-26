/*
    <one line to give the library's name and an idea of what it does.>
    Copyright (C) 2011  Ondra Voves <email>

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


#include "../include/bvariant.h"

BOXE_NAMESPACE_BEGIN ( Core )

template<>
void BVariant::setValue<short> ( short value ) {
    Data.s = value;
    Type = VT_SHORT;
}

template<>
void BVariant::setValue ( unsigned short value ) {
    Data.us = value;
    Type = VT_USHORT;
}

template<>
void BVariant::setValue ( int value ) {
    Data.i = value;
    Type = VT_INT;
}

template<>
void BVariant::setValue ( unsigned int value ) {
    Data.ui = value;
    Type = VT_UINT;
}

template<>
void BVariant::setValue ( long value ) {
    Data.l = value;
    Type = VT_LONG;
}

template<>
void BVariant::setValue ( unsigned long value ) {
    Data.ul = value;
    Type = VT_ULONG;
}

template<>
void BVariant::setValue ( float value ) {
    Data.f = value;
    Type = VT_FLOAT;
}

template<>
void BVariant::setValue ( double value ) {
    Data.d = value;
    Type = VT_DOUBLE;
}

template<>
void BVariant::setValue ( bool value ) {
    Data.b = value;
    Type = VT_BOOL;
}

template<>
void BVariant::setValue ( char value ) {
    Data.c = value;
    Type = VT_CHAR;
}

template<>
void BVariant::setValue ( void *value ) {
    Data.v = value;
    Type = VT_POINTER;
}

BVariant::BVariant() : Type ( VT_UNKOWN ) {
}

BVariant::BVariant ( const BVariant &other ) : Data ( other.Data ), Type ( other.Type ) {
}

BVariant::BVariant ( short s ) {
    setValue ( s );
}

BVariant::BVariant ( unsigned short us ) {
    setValue ( us );
}

BVariant::BVariant ( int i ) {
    setValue ( i );
}

BVariant::BVariant ( unsigned int ui ) {
    setValue ( ui );
}

BVariant::BVariant ( long l ) {
    setValue ( l );
}

BVariant::BVariant ( unsigned long ul ) {
    setValue ( ul );
}

BVariant::BVariant ( float f ) {
    setValue ( f );
}

BVariant::BVariant ( double d ) {
    setValue ( d );
}

BVariant::BVariant ( bool b ) {
    setValue ( b );
}

BVariant::BVariant ( char c ) {
    setValue ( c );
}

BVariant::BVariant ( void *p ) {
    setValue ( p );
}

template<>
short BVariant::value() {
    return Data.s;
}

template<>
unsigned short BVariant::value() {
    return Data.us;
}

template<>
int BVariant::value() {
    return Data.i;
}

template<>
unsigned int  BVariant::value() {
    return Data.ui;
}

template<>
long BVariant::value() {
    return Data.l;
}

template<>
unsigned long BVariant::value() {
    return Data.ul;
}

template<>
float BVariant::value() {
    return Data.f;
}

template<>
double BVariant::value() {
    return Data.d;
}

template<>
bool BVariant::value() {
    return Data.b;
}

template<>
char BVariant::value() {
    return Data.c;
}

template<>
void *BVariant::value() {
    return Data.v;
}



BOXE_NAMESPACE_END ( Core )
