#include <stdio.h>
#include <string.h>
#include "vm.h"
#include "op_code.h"

const uint8_t* irep_get(const uint8_t* p, int type, int n) {
  int lenirep = b2l4(p);

  p += 8;
  int nirep = b2l2(p);

  p += 2;
  {
    int codelen = b2l4(p);
    p += 4;
    int align = (int)p & 3;
    if (align) {
      p += 4 - align;
    }
    p += codelen;
  }
  {
    int plen = b2l4(p);
    if (type == IREP_TYPE_LITERAL) {
      check(n >= 0 && n < plen);
      plen = n;
    }
    p += 4;
    for (int i = 0; i < plen; i++) {
      uint8_t type = *p;
      uint16_t len = b2l2(p + 1);
      p += len + 3;
    }
    if (type == IREP_TYPE_LITERAL) {
      return p;
    }
  }
  {
		int symlen = b2l4(p);
		if (type == IREP_TYPE_SYMBOL) {
			check(n >= 0 && n < symlen);
			symlen = n;
		}
		p += 4;
		for (int i = 0; i < symlen; i++) {
			uint16_t len = b2l2(p);
			p += len + 3; // len + '¥0'
		}
		if (type == IREP_TYPE_SYMBOL) {
			return p;
		}
	}

  return p;
}

int vm_exec(const uint8_t* irep) {
  // Cursor
  const uint8_t* p = irep;

  // TODO: Check usage
  p += 4;

  // Get locals
  int nlocals = b2l2(p);
  // Get args
  p += 2;
  int nregs = b2l2(p);
  intptr_t reg[nregs - 1];
  // Get ireps
  p += 2;
  int nireps = b2l2(p);

  printf("locals: %d, rergs: %d, ireps: %d\n", nlocals, nregs, nireps);

  {
    int codelen = b2l4(p);
    p += 4;
    int align = (int)p & 3;
    if (align) {
      p += 4 - align;
    }
  }

  int err = 0;

  // Temp
  int32_t a = 0;
  int32_t b = 0;
  int32_t c = 0;

  // Init
  reg[0] = 0;

  for(;;) {
    uint8_t op = *p++;

    switch(op) {
      case OP_LOADSELF:
        a = *p++;
        reg[a] = reg[0];
        printf("r[%d] = self %ld\n", a, reg[a]);
        break;
      case OP_STRING:
        a = *p++; b = *p++;
        reg[a] = (intptr_t)irep_get(irep, IREP_TYPE_LITERAL, b) + 2;
        printf("r[%d] = str_dup(lit[%d] %s)\n", a, b, (const char*)reg[a]);
        break;
      case OP_SEND:
        a = *p++; b = *p++; c = *p++;
        const char* func = (const char*)(irep_get(irep, IREP_TYPE_SYMBOL, b) + 2);
        if (c) {
					printf("r[%d] = r[%d].sym[%d:%s](r[%d]:%ld-r[%d])\n", a, a, b, func, a + 1, reg[a + 1], a + c);
        } else {
					printf("r[%d] = r[%d].sym[%d:%s]()\n", a, a, b, func);
        }

        if(strcmp(func, "puts") == 0) {
          printf("Ruby> %s\n", (const char*)(++reg[a + 1]));
        } else {
          printf("Unsupport func %s\n", func);
        }
        break;
      case OP_RETURN:
			case OP_RETURN_BLK:
			case OP_BREAK:
        a = *p++;
        printf("%s r[%d]\n", op == OP_RETURN ? "return" : "break", a);
        return reg[a];
        break;
      default:
        printf("Unsupport OP Code: %d\n", op);
        err = 1;
    }

    if (err == 1) {
      break;
    }
  }

  return 0;
}
