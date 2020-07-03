#include <stdio.h>
#include "op_code.h"
#include "vm.h"

extern const uint8_t app[];

int main(int argc, char** argv) {
  vm_run(app);

  return 0;
}
