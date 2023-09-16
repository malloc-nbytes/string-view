#ifndef SV_H
#define SV_H

#include <aio.h>
#include <stdio.h>

typedef struct {
  const char *data;
  const char *end;
  size_t len;
} StringView;

StringView sv_create(const char *str);
StringView sv_appendcstr(const StringView *sv, const char *str);
StringView sv_appendsv(const StringView *sv, const StringView *sv2);
StringView sv_erase_substr(const StringView *sv, const char *target);
StringView sv_erase_char(const StringView *sv, char c);
StringView sv_erase_range(const StringView *sv, const char *start, const char *end);
StringView sv_cstr_tosv(const char *str);
const char *sv_tocstr(const StringView *sv);
const char *sv_substr(const StringView *sv, const char *target);
const char *sv_findchar(const StringView *sv, char c);
const char *sv_end(const StringView *sv);
const char *sv_iter(const StringView *sv);
const char *sv_raw(const StringView *sv);
size_t sv_write(const StringView *sv, FILE *stream);
size_t sv_len(const StringView *sv);

#endif // SV_H
