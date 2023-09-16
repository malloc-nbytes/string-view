#include "../include/sv.h"
#include <stdlib.h>
#include <stdio.h>

int main(void) {

  const char *str = "hello world";

  StringView sv = sv_create(str);

  return 0;
}
