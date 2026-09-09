// Dual Compatibility Header

#ifndef PLUGIN_ABI_H
#define PLUGIN_ABI_H

// #include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*Operation)(void *, const char *, char *);
typedef size_t (*OperationLen)(void *, const char *);

typedef struct Impl {
  Operation op;
  OperationLen opl;
} Impl;
typedef struct Behavior {
  void *context;
  Impl *impl;
} Behavior;

#ifdef __cplusplus
}
#endif

#endif
