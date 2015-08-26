#ifndef BGLOBAL_H
#define BGLOBAL_H

#include <new>

#include "boxe-config.h"

#define BOXE_NAMESPACE_BEGIN(module)\
    namespace BoxE {\
        namespace module {\
             
#define BOXE_NAMESPACE_END(module)\
    }\
    }\
     

#define BOXE_FLOAT_EPSILON 0.00001f

/*!
 * Swap two value.
 * \param value1 First value.
 * \param value2 Second value.
 */
template< typename T >
inline void bSwap ( T &value1, T &value2 ) {
    const T temp_value ( value1 );
    value1 = value2;
    value2 = temp_value;
}

/*!
 * Return absolute value.
 * \param value Value.
 * \return Absolute value.
 */
template< typename T >
inline const T bAbs ( const T &value ) {
    return value < 0 ? -value : value;
}

/*!
 * Return min value reference.
 * \param value1 First value.
 * \param value2 Second value.
 * \return Return value1 if is min, or return value2.
 */
template< typename T >
inline const T &bMin ( const T &value1, const T &value2 ) {
    return value1 < value2 ? value1 : value2;
}

/*!
 * Return max value reference.
 * \param value1 First value.
 * \param value2 Second value.
 * \return Return value1 if is max, or return value2.
 */
template< typename T >
inline const T &bMax ( const T &value1, const T &value2 ) {
    return value1 > value2 ? value1 : value2;
}


/*!
 * No operation fce.
 */
inline void boxe_noop() {}

/*
 * Exception macros. ( INSPIRATED BY Qt.... )
 */

#if !defined(BOXE_NO_EXCEPTION)
#define BOXE_TRY try
#define BOXE_CATCH(E) catch(E)
#define BOXE_THROW(E) throw E
#define BOXE_RETHROW throw
#else
#define BOXE_TRY if( true )
#define BOXE_CATCH(E) else
#define BOXE_THROW(E)
#define BOXE_RETHROW
#endif


/*
 * Debug fce and macros.
 */

/*!
 * This fce print assert message.
 * "ASSERT: 'CONDITION_STR' in file FILE on line LINE"
 * \param condition_str Condition as string.
 * \param file Filename.
 * \param line Line.
 */
extern void boxe_assert ( const char *condition_str, const char *file, int line );

/*!
 * Assert macro.
 * \param condition Asset condition.
 */
#if !defined(BOXE_NO_DEBUG)
#define B_ASSERT(condition) ( !(condition) ? boxe_assert( #condition, __FILE__, __LINE__ ) : boxe_noop() )
#else
#define B_ASSERT(condition)
#endif

/*!
 * This fce print assert message.
 * "ASSERT failure in 'WHERE': "WHAT", file FILE on line LINE
 * \param where Where did it happend.
 * \param what What happend?
 * \param file Filename.
 * \param line Line.
 */
extern void boxe_assert_msg ( const char *where, const char *what, const char *file, int line );

/*!
 * Assert macro with message.
 * \param condition Asset condition.
 * \param where Where did it happend.
 * \param what What happend?
 */
#if !defined(BOXE_NO_DEBUG)
#define B_ASSERT_MSG(condition, where, what ) ( !(condition) ? boxe_assert_msg( where, what, __FILE__, __LINE__ ) : boxe_noop() )
#else
#define B_ASSERT_MSG(condition,  where, what)
#endif

/*!
 * Print check_ptr message.
 * \param file File.
 * \param line Line.
 */
extern void boxe_check_ptr ( const char *file, int line );

/*!
 * Check ptr macro.
 * \param ptr Pointer.
 */
#if !defined(BOXE_NO_DEBUG)
#define B_CHECK_PTR(ptr) if(!ptr) boxe_check_ptr( __FILE__, __LINE__ )
#else
#define B_CHECK_PTR(ptr)
#endif

BOXE_NAMESPACE_BEGIN ( Core )

/*!
 * Template class for information about type.
 */
template< typename T >
class BTypeInfo {
    public:
        enum {
            isMoveable = false,
            isPrimtiveType = false,
            isPointer = false
        };
};

#define B_CREATE_TYPEINFO( type, moveable, primitive_type )\
    template<>\
    class BTypeInfo < type > {\
        public:\
            enum {\
                isMoveable = moveable ,\
                             isPrimtiveType = primitive_type,\
                                              isPointer = false\
            };\
    }\
     
B_CREATE_TYPEINFO ( int, true, true );
B_CREATE_TYPEINFO ( unsigned int, true, true );

B_CREATE_TYPEINFO ( short, true, true );
B_CREATE_TYPEINFO ( unsigned short, true, true );

B_CREATE_TYPEINFO ( long, true, true );
B_CREATE_TYPEINFO ( unsigned long, true, true );

B_CREATE_TYPEINFO ( float, true, true );
B_CREATE_TYPEINFO ( double, true, true );

B_CREATE_TYPEINFO ( bool, true, true );
B_CREATE_TYPEINFO ( char, true, true );
B_CREATE_TYPEINFO ( void *, true, true );

inline bool bFuzzyCompare ( const float a, const float b ) {
    return ( bAbs ( a - b ) < BOXE_FLOAT_EPSILON );
}

BOXE_NAMESPACE_END ( Core )

#ifdef __GNUC__
#define B_ALIGN_16 __attribute__((aligned (16)))
#elif defined (__MSVC__)
#define B_ALIGN_16 __declspec(align (16))
#endif

#endif // BGLOBAL_H
