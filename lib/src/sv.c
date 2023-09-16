#include "../include/sv.h"
#include <stdio.h>
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

size_t sv_write(const StringView *sv, FILE *stream)
{
  return fwrite(sv->data, sizeof(char), sv->len, stream);
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

const char *sv_raw(const StringView *sv)
{
  return sv->data;
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

StringView sv_cstr_tosv(const char *str)
{
  return sv_create(str);
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

const char *sv_substr(const StringView *sv, const char* target)
{
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

StringView sv_erase_substr(const StringView *sv, const char *target)
{
  const char *substr = sv_substr(sv, target);
  if (substr == sv->end) {
    return *sv;
  }

  size_t target_len = strlen(target);
  size_t new_len = sv->len - target_len;

  char *new_str = malloc(new_len + 1);
  (void)memcpy(new_str, sv->data, substr - sv->data);
  (void)memcpy(new_str + (substr - sv->data), substr + target_len, sv->len - (substr - sv->data) - target_len);
  new_str[new_len] = '\0';

  StringView new_sv = sv_create(new_str);
  return sv_erase_substr(&new_sv, target);
}

StringView sv_erase_char(const StringView *sv, char c)
{
  size_t new_len = sv->len;
  char *new_str = malloc(new_len + 1);

  size_t j = 0;
  for (size_t i = 0; i < sv->len; ++i) {
    if (sv->data[i] != c) {
      new_str[j] = sv->data[i];
      ++j;
    }
  }

  new_str[new_len] = '\0';
  return sv_create(new_str);
}

StringView sv_erase_range(const StringView *sv, const char *start, const char *end)
{
  size_t new_len = sv->len - (end - start);
  char *new_str = malloc(new_len + 1);

  (void)memcpy(new_str, sv->data, start - sv->data);
  (void)memcpy(new_str + (start - sv->data), end, sv->len - (end - sv->data));
  new_str[new_len] = '\0';

  return sv_create(new_str);
}
