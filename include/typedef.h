/*
 *** Data type definition
*/

#ifndef TYPEDEF_H
#define TYPEDEF_H

#include <stdint.h>

/* INT */
typedef int8_t              B;      // 8 bit
typedef int16_t             H;      // 16 bit
typedef int32_t             W;      // 32 bit
typedef int64_t             D;      // 64 bit

/* UINT */
typedef uint8_t             UB;      // 8 bit
typedef uint16_t            UH;      // 16 bit
typedef uint32_t            UW;      // 32 bit
typedef uint64_t            UD;      // 64 bit

/* volatile INT */
typedef volatile int8_t     _B;      // 8 bit
typedef volatile int16_t    _H;      // 16 bit
typedef volatile int32_t    _W;      // 32 bit
typedef volatile int64_t    _D;      // 64 bit

/* volatile UINT */
typedef volatile uint8_t    _UB;      // 8 bit
typedef volatile uint16_t   _UH;      // 16 bit
typedef volatile uint32_t   _UW;      // 32 bit
typedef volatile uint64_t   _UD;      // 64 bit

/* No size */
typedef int                 INT;
typedef unsigned int        UINT;

/* Others */
typedef INT                 ID;     // ID
typedef UW                  ATR;    // Attribute
typedef INT                 ER;     // Error code
typedef INT                 PRI;    // Priority
typedef W                   TMO;    // Duration for Timeout
typedef UW                  RELTIM; // Relative time
typedef W                   SZ;     // Size

typedef void                (*FP)();    // Function pointer

#define NULL                (0)

typedef UINT                BOOL;
#define TRUE                (1)
#define FALSE               (0)

#endif  /* TYPEDEF_H */
