#ifdef DEBUG
#include <assert.h>
#define common_assert(a) (assert(a))
#else
#define common_assert(a)
#endif /* DEBUG */
