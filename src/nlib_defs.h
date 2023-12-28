
#ifndef INC_NLIB_DEFS_H
#define INC_NLIB_DEFS_H

#include "stdint.h"
#include "stdbool.h"

typedef enum NL_RESULT {
    NL_OK = 0,
    NL_ERR_FULL,
    NL_ERR_EMPTY,
    NL_ERR_NOT_INITIALIZED,
} NL_RESULT;

#endif // INC_NLIB_DEFS_H