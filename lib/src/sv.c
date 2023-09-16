#include "../include/sv.h"
#include <stdlib.h>
#include <string.h>

StringView sv_create(const char *str) {
  StringView sv;
  sv.data = str;
  sv.len = strlen(str);
  return sv;
}

StringView sv_appendcstr(const StringView *sv, const char *str) {
  size_t str_len = strlen(str);
  size_t total_len = sv->len + str_len;

  char *concat = malloc(total_len + 1);

  (void)memcpy(concat, sv->data, sv->len);
  (void)memcpy(concat, str, str_len);

  concat[total_len - 1] = '\0';
  return sv_create(concat);
}

StringView sv_appendsv(const StringView *sv, const StringView *sv2) {
  size_t total_len = sv->len + sv2->len;

  char *concat = malloc(total_len + 1);

  (void)memcpy(concat, sv->data, sv->len);
  (void)memcpy(concat, sv2->data, sv2->len);

  concat[total_len - 1] = '\0';
  return sv_create(concat);
}

size_t sv_substr(const StringView *sv, const StringView *target) {
  for (size_t i = 0; i <= sv->len - target->len; ++i) {
    if (memcmp(sv->data + i, target->data, target->len) == 0) {
      return i;
    }
  }
  return sv->len; 
}

