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

#include "../include/bsphere3f.h"

BOXE_NAMESPACE_BEGIN ( Math )

BSphere3f::BSphere3f() : Radius ( 0.0f ), RadiusSquared ( 0.0f ) {
}

BSphere3f::BSphere3f ( const BSphere3f &other ) : Origin ( other.Origin ), Radius ( other.Radius ), RadiusSquared ( other.RadiusSquared ) {
}

BSphere3f::BSphere3f ( const BVector3f &origin, const float radius ) : Origin ( origin ), Radius ( radius ), RadiusSquared ( radius *radius ) {
}

BOXE_NAMESPACE_END ( Math )
