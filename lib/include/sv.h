#ifndef SV_H
#define SV_H

#include <aio.h>

typedef struct {
  const char *data;
  size_t len;
} StringView;

StringView sv_create(const char *str);
StringView sv_appendcstr(const StringView *sv, const char *str);
StringView sv_appendsv(const StringView *sv, const StringView *sv2);
size_t sv_substr(const StringView *sv, const StringView *target);

#endif // SV_H
