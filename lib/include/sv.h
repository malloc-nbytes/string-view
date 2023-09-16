#ifndef SV_H
#define SV_H

#include <aio.h>

typedef struct {
  const char *data;
  const char *end;
  size_t len;
} StringView;

StringView sv_create(const char *str);
StringView sv_appendcstr(const StringView *sv, const char *str);
StringView sv_appendsv(const StringView *sv, const StringView *sv2);
const char *sv_tocstr(const StringView *sv);
const char *sv_substr(const StringView *sv, const char* target);
const char *sv_findchar(const StringView *sv, char c);
size_t sv_len(const StringView *sv);
const char *sv_end(const StringView *sv);
const char *sv_iter(const StringView *sv);
StringView sv_cstr_tosv(const char *str);
/* StringView sv_prependsv(const StringView *sv, const StringView *sv2); */
/* StringView sv_prependcstr(const StringView *sv, const char *str); */

#endif // SV_H
