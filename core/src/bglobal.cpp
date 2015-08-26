#include "../include/bglobal.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>

#define SHORT_FILE( filename ) (strrchr(filename,'/') ? strrchr(filename,'/')+1 : filename)

void boxe_assert ( const char *condition_str, const char *file, int line ) {
    fprintf ( stderr, "ASSERT: \'%s\' in file %s on line %i.\n", condition_str, SHORT_FILE ( file ), line );
    abort();
}

void boxe_assert_msg ( const char *where, const char *what, const char *file, int line ) {
    fprintf ( stderr, "ASSERT failure in \'%s\': \"%s\", file %s on line %i.\n", where, what, SHORT_FILE ( file ), line );
    abort();
}

void boxe_check_ptr ( const char *file, int line ) {
    fprintf ( stderr, "CHECK POINTER: in file %s on line %i is invalid pointer.\n", SHORT_FILE ( file ), line );
    abort();
}

BOXE_NAMESPACE_BEGIN ( Core )

BOXE_NAMESPACE_END ( Core )
