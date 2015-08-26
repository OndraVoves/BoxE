#include <cstdio>
#include <iostream>

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include <BoxECore>


using namespace BoxE::Core;
using namespace BoxE::Math;

class A {
    public:
        A() : i ( 0 ) {
        }

        A ( int number ) : i ( number ) {
            std::cout << "construkce A " << i << std::endl ;
        }

        ~A() {
            std::cout << "destrukce A " << i << std::endl ;
        }

        int i;
};

float ABCD = 0;
bool oka = false;
bool okb = false;

class TA : public BThread {
    public:
        TA() {
        }

        virtual ~TA() {
        }

    protected:
        virtual void run() {
            int i = 10;

            while ( ( i-- ) > 0 ) {
                //std::cout << "A" << std::endl;
                //fprintf( stderr, "A" );
                ABCD += 1.0f;
                ABCD *= 2.0f;
            }

            oka = true;
        }

};

class TB : public BThread {
    public:
        TB() {
        }

        virtual ~TB() {
        }

    protected:
        virtual void run() {
            int i = 10;

            while ( ( i-- ) > 0 ) {
                ABCD /= 2.0f;
                ABCD -= 2.0f;
                //fprintf( stderr, "B" );
            }
            okb = true;
        }

};

void foo() {
    std::cout << "foo()" << std::endl;
}

void foo1 ( int i, int i2 ) {
    std::cout << "foo() " << i << ":" << i2 << std::endl;
}

class CFOO {
    public:
        void FOO() {
            std::cout << "FOO()" << std::endl;
        }
};

int main (  int argc , char **argv ) {
#if 0
    BVector<A> vec_a;

    A a1 ( 1 );
    A a2 ( 2 );
    A a3 ( 3 );
    std::cout << "append() begin." << std::endl;
    vec_a.append ( a1 );
    vec_a.append ( a2 );
    vec_a.append ( a3 );
    std::cout << "append() end." << std::endl;

    BVector<A>::ConstIterator it = vec_a.constBegin();
    while ( it != vec_a.constEnd() ) {
        printf ( "vec_a[%i] == %i\n", ( int ) ( it - vec_a.constBegin() )   , ( *it ).i );
        ++it;
    }

    std::cout << "size == " << vec_a.size() << std::endl;
    std::cout << "capacity == " << vec_a.capacity() << std::endl;

    std::cout << "typeinfo = " << BTypeInfo< int >::isMoveable << std::endl;

    //vec_a.append( A() );
#endif

#if 0
    BVector<int> vector;

    vector.reserve ( 10 );

    vector.append ( 20 );
    vector.prepend ( 20 );
    vector.prepend ( 2 );

    //vector.squeeze();
    //vector.reserve(5);

    vector.remove ( vector.begin() );

    std::cout << "vector size: " << vector.size() << std::endl;
    std::cout << "vector capacity: " << vector.capacity() << std::endl;

    BVector<int>::ConstIterator it = vector.constBegin();
    while ( it != vector.constEnd() ) {
        printf ( "Vector[%i] == %i\n", ( int ) ( it - vector.constBegin() )   , *it );
        ++it;
    }

    BStack<int> stack;
    stack.push ( 1 );
    stack.push ( 2 );
    stack.push ( 3 );

    std::cout << "Count = " << stack.count ( 3 ) << std::endl;

    while ( !stack.isEmpty() ) {
        printf ( "stack.pop() = %i\n", stack.pop() );
    }

    std::cout << "stack size: " << stack.size() << std::endl;
    std::cout << "stack capacity: " << stack.capacity() << std::endl;
#endif

#if 0
    BLinkedList<int> linkedlist;

    linkedlist << 1 << 2 << 3 << 4 << 5;

    if ( linkedlist.isEmpty() ) {
        std::cout << "Je prazdnej." << std::endl;
    }


    BLinkedList<int> linkedlist2 ( linkedlist );

    if ( linkedlist2.isSharedWith ( linkedlist ) ) {
        std::cout << "sdilene." << std::endl;
    }

    std::cout << "First: " << linkedlist2.first() << std::endl;
    std::cout << "Last: " << linkedlist2.last() << std::endl;

    BLinkedList<int>::ConstIterator it = linkedlist2.constBegin();
    while ( it != linkedlist2.constEnd() ) {
        std::cout << *it << ", ";
        it++;
    }
    std::cout << std::endl;

#endif

#if 0

    BPair< int, int > p1 = bMakePair ( 1, 1 );
    BPair< int, int > p2 = bMakePair ( 2, 2 );

    if ( BLibrary::isLibrary ( "a.so" ) ) {
        std::cout << "je" << std::endl;
    }

#endif

#if 0
    BTime time1 ( 0, 0, 1 );
    BTime time2 ( 0, 0, 3 );

    std::cout << "secondTo: " << time1.secondTo ( time2 ) << std::endl;

    std::cout << "Time: " << time.elapsed() << "ms" << std::endl;
    std::cout << BTime::curentTime().hour() << ":" << BTime::curentTime().minute() << ":" << BTime::curentTime().second() << "." << BTime::curentTime().msecond() << std::endl;
#endif

#if 0
    BByteArray barray1 ( "data1/data2/data3" );
    BByteArray base64;

    std::cout << barray1.left ( 4 ).constData() << std::endl;

    for ( int i = 0; i < barray1.size(); i++ ) {
        std::cout << barray1.at ( i );
    }
    std::cout << std::endl;

    if ( barray1 == BByteArray ( "ABCD" ) ) {
        std::cout << "JJ" << std::endl;
    }

    std::cout << "bstrlen() " << bstrlen ( "1234567890" ) << std::endl;

    base64 =  barray1.toUpper().toBase64();

    std::cout << base64 << std::endl;
    std::cout << BByteArray::fromBase64 ( base64 ) << std::endl;

    BLinkedList< BByteArray > split = barray1.split ( '8' );
    BLinkedList< BByteArray >::ConstIterator it = split.constBegin();
    while ( it != split.constEnd() ) {
        std::cout << *it << std::endl;
        it++;
    }

#endif

#if 1
    /*      bool ok;
            BByteArray array( "-10" );
            int a = array.toInt( &ok);
            std::cout << "OK: " << ok << " num = " << a << std::endl;*/

    /*BByteArray array;
    array.setNum( -10 );
    std::cout << array << std::endl;

    std::cout << sizeof(int) << std::endl;
    std::cout << bAbs<int>( -20 ) << std::endl;

    std::cout << BByteArray::number( 0xffffffff, 2 ) << std::endl ;
    std::cout << BByteArray::number( 0x7fffffff, 2 ) << std::endl ;
    std::cout << BByteArray::number( 1 ) << std::endl ;*/
#endif

#if 0
    BBuffer buffer ( new BByteArray ( "data1\ndata2\ndata3" ) );
    buffer.open ( BIODevice::ReadOnly );

    std::cout << "can read line= " << buffer.canReadLine() << std::endl;

    char data[255];
    int i;
    while ( !buffer.atEnd() ) {
        i = buffer.readLine ( data, 255 );
        std::cout << "read=" << i << " \"" <<  data << "\"" << std::endl;
    }

#endif


#if 0
    BByteArray byte_array;
    BBuffer buffer ( &byte_array );
    char tmp[32];
    buffer.open ( BIODevice::ReadWrite );

    std::cout << "opened: " << buffer.isOpen() << std::endl;
    std::cout << "readable: " << buffer.isReadable() << std::endl;
    std::cout << "writeable: " << buffer.isWriteable() << std::endl;
    std::cout << "END: " << buffer.atEnd() << std::endl;

    buffer.seek ( 0 );
    std::cout << "END: " << buffer.atEnd() << std::endl;

    for ( int i = 0; i < 10; i++ ) {
        buffer.write ( "D", 1 );
    }

    buffer.seek ( 0 );


    std::cout << buffer.readAll() << std::endl;

    /*  buffer.read( tmp, 4 );

        std::cout << tmp << std::endl;*/

#endif

#if 0
    BFile file ( "./foo.bar" );

    std::cout << file.copy ( "./foo.bar.copy" )  << std::endl;

    /*  BByteArray num;
        for( int i = 0; i < 50; i++ ) {
            num.setNum( rand() ).append( '*' );
            file.write( num.constData() );
        }*/

//    BLinkedList<  BByteArray > list = file.buffer().split ( '\n' );


    /*    BLinkedList< BByteArray >::ConstIterator it = list.constBegin();
        while ( it != list.constEnd() ) {
            std::cout << *it << std::endl;
            it++;
        }*/
#endif

#if 0
    BMatrix4x4f mat1 ( BMatrix4x4f::IDENTITY );


    printf ( "| %f, %f, %f %f |\n", mat1.constRow1().x(), mat1.constRow1().y(), mat1.constRow1().z(), mat1.constRow1().w() );
    printf ( "| %f, %f, %f %f |\n", mat1.constRow2().x(), mat1.constRow2().y(), mat1.constRow2().z(), mat1.constRow2().w() );
    printf ( "| %f, %f, %f %f |\n", mat1.constRow3().x(), mat1.constRow3().y(), mat1.constRow3().z(), mat1.constRow3().w()  );
    printf ( "| %f, %f, %f %f |\n", mat1.constRow4().x(), mat1.constRow4().y(), mat1.constRow4().z(), mat1.constRow4().w()  );

    printf ( "\n" );

    BMatrix4x4f mat1T = mat1 * mat1;

    printf ( "| %f, %f, %f %f |\n", mat1T.constRow1().x(), mat1T.constRow1().y(), mat1T.constRow1().z(), mat1T.constRow1().w() );
    printf ( "| %f, %f, %f %f |\n", mat1T.constRow2().x(), mat1T.constRow2().y(), mat1T.constRow2().z(), mat1T.constRow2().w() );
    printf ( "| %f, %f, %f %f |\n", mat1T.constRow3().x(), mat1T.constRow3().y(), mat1T.constRow3().z(), mat1T.constRow3().w()  );
    printf ( "| %f, %f, %f %f |\n", mat1T.constRow4().x(), mat1T.constRow4().y(), mat1T.constRow4().z(), mat1T.constRow4().w()  );

    printf ( "%f\n", bFastSin ( bRad2Deg<float> ( 360 ) ) );
    printf ( "%f\n", bFastCos ( bRad2Deg<float> ( 360 ) ) );
#endif

#if 0

    TA ta;
    TB tb;
    ta.start();
    tb.start();

    while ( ! ( oka and okb ) ) {
    }

    std::cout << ABCD << std::endl;

#endif

#if 0
    BHash< int, int > hash;

    hash.insert ( 1, 11 );
    hash.insert ( 2, 22 );
    hash.insert ( 3, 33 );

    BHash<int, int>::ConstIterator it = hash.constBegin();
    while ( it != hash.constEnd() ) {
        std::cout << it.key() << ":" << ( *it ) << std::endl;
        ++it;
    }

    CFOO cf;
    BSignal2<int, int> signal;
    signal.connect ( &foo1 );
    signal.emitSignal ( 1, 2 );

#endif


    return 0;
}

