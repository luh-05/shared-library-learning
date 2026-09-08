// Dual Compatibility Header

#ifndef PLUGIN_ABI_H
#define PLUGIN_ABI_H

// #include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*Operation)(const char *, char *);
typedef size_t (*OperationLen)(const char *);
typedef struct Behavior {
  Operation op;
  OperationLen opl;
} Behavior;

#ifdef __cplusplus
}
#endif

#endif
