#include <errno.h>
#include <stdbool.h>
#include <stdint.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;

typedef int refcount_t;

#define __iomem

#define ARRAY_SIZE(x) sizeof(x) / sizeof(*x)

#define BIT(x) (1 << (x))

#define round_down(x, y) ((x) - (x) % (y))
