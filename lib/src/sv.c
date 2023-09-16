#include "../include/sv.h"
#include <stdlib.h>
#include <string.h>

StringView sv_create(const char *str)
{
  StringView sv;
  size_t str_len = strlen(str);
  sv.data = str;
  sv.end = &str[str_len];
  sv.len = str_len;
  return sv;
}

const char *sv_iter(const StringView *sv)
{
  static size_t pos = 0;
  if (pos < sv->len) {
    const char *next = sv->data + pos;
    pos++;
    return next;
  }
  return sv->end;
}

size_t sv_len(const StringView *sv)
{
  return sv->len;
}

const char *sv_end(const StringView *sv)
{
  return sv->end;
}

const char *sv_findchar(const StringView *sv, char c)
{
  for (size_t i = 0; i < sv->len; i++) {
    if (sv->data[i] == c) {
      return &sv->data[i];
    }
  }
  return sv->end;
}

const char *sv_tocstr(const StringView *sv)
{
  char *cstr = malloc(sv->len + 1);
  (void)memcpy(cstr, sv->data, sv->len);
  cstr[sv->len] = '\0';
  return cstr;
}

StringView sv_appendcstr(const StringView *sv, const char *str)
{
  size_t str_len = strlen(str);
  size_t total_len = sv->len + str_len;

  char *concat = malloc(total_len + 1);

  (void)memcpy(concat, sv->data, sv->len);
  (void)memcpy(concat, str, str_len);

  concat[total_len] = '\0';
  return sv_create(concat);
}

StringView sv_appendsv(const StringView *sv, const StringView *sv2)
{
  size_t total_len = sv->len + sv2->len;

  char *concat = malloc(total_len + 1);

  (void)memcpy(concat, sv->data, sv->len);
  (void)memcpy(concat, sv2->data, sv2->len);

  concat[total_len] = '\0';
  return sv_create(concat);
}

const char *sv_substr(const StringView *sv, const char* target) {
  size_t target_len = strlen(target);
    
  if (target_len == 0) {
    return sv->data;
  }

  for (size_t i = 0; i < sv->len; ++i) {
    if (strncmp(sv->data + i, target, target_len) == 0) {
      return &sv->data[i];
    }
  }

  return sv->end;
}
