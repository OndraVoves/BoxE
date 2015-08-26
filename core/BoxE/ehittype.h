#ifndef EHITTYE_H
#define EHITTYE_H

#include "../../core/include/BGlobal"

BOXE_NAMESPACE_BEGIN ( Math )

typedef enum {
    Miss = 0,   //!< Miss
    Hit = 1,    //!< Hit from outside.
    Inside = -1 //!< Hit from inside.
} EHitType;

BOXE_NAMESPACE_END ( Math )

#endif  /* EHITTYE_H */
