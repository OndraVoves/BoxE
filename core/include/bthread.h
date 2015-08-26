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

#ifndef BTHREAD_H
#define BTHREAD_H

#include "bglobal.h"

#ifdef B_OS_UNIX
#include <pthread.h>
#endif

BOXE_NAMESPACE_BEGIN ( Core )

class BThread {
    public:
        BThread();
        virtual ~BThread();

        void start();
    protected:
        virtual void run() = 0;

        static void sleep ( unsigned long secs );
        static void msleep ( unsigned long msecs );
        static void usleep ( unsigned long usecs );
    private:
        static void *entryPoint ( void *arg );

    private:
#ifdef B_OS_UNIX
        pthread_t Thread;
#endif
};

BOXE_NAMESPACE_END ( Core )

#endif // BTHREAD_H
