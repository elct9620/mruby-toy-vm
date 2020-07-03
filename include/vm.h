#ifndef VM_H_
#define VM_H_

#include <stdint.h>

#define check(x)

#define IREP_TYPE_SKIP 0
#define IREP_TYPE_LITERAL 1
#define IREP_TYPE_SYMBOL 2
#define IREP_TYPE_IREP 3

// TODO: Bitmask to ??
static inline int b2l2(const uint8_t* n) {
	return (n[0] << 8) | n[1];
}

#define b2l4(n) b2l2((n) + 2)

// TODO: Check header size
#define vm_load(mrb) ((mrb) + 34)
#define vm_run(mrb) vm_exec(vm_load(mrb))

int vm_exec(const uint8_t* irep);

#endif
