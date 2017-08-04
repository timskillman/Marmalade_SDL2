#pragma once

#include "SRGXTypes.h"
#include "IwDebug.h"

// Math
#ifndef ABS
#define ABS(a)          (((a) > 0) ? (a) : -(a))
#endif

#ifndef MAX
#define MAX(a, b)       (((a) > (b)) ? (a) : (b))
#endif

#ifndef MIN
#define MIN(a, b)       (((a) < (b)) ? (a) : (b))
#endif

#ifndef MAX3
#define MAX3(a, b, c)   (((a) > (b)) ? MAX(a,c) : MAX(b,c))
#endif

#ifndef MIN3
#define MIN3(a, b, c)   (((a) < (b)) ? MIN(a,c) : MIN(b,c))
#endif

#ifndef SQR
#define SQR(a)          ((a) * (a))
#endif

// Copy
#ifndef COPY32
#define COPY32(a, b)    (*(uint32*)&(a) = *(uint32*)&(b))
#endif

#ifndef COPY16
#define COPY16(a, b)    (*(uint16*)&(a) = *(uint16*)&(b))
#endif

#ifndef COPY8
#define COPY8(a, b) (*(uint8*)&(a) = *(uint8*)&(b))
#endif

