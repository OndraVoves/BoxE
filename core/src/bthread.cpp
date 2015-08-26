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

#include "../include/bthread.h"

#include <unistd.h>

BOXE_NAMESPACE_BEGIN ( Core )

BThread::BThread() {
}

BThread::~BThread() {
}

void BThread::start() {
#ifdef B_OS_UNIX
    pthread_create ( &Thread, NULL, &entryPoint, this );
#endif
}

void *BThread::entryPoint ( void *arg ) {
    static_cast< BThread * > ( arg )->run();
    return 0;
}

void BThread::sleep ( unsigned long secs ) {
}

void BThread::msleep ( unsigned long msecs ) {
}

void BThread::usleep ( unsigned long usecs ) {
}

BOXE_NAMESPACE_END ( Core )
