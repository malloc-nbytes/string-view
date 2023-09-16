#include "../include/sv.h"
#define CUT_IMPL
#define CUT_ABORT_ON_FAIL
#include "./cut.h"

#include <string.h>

void test_sv_len()
{
  const char *str = "Hello World";
  StringView sv = sv_create(str);
  cut_assert_true(sv.len == 11);
}

void test_sv_raw()
{
  const char *str = "Hello World";
  StringView sv = sv_create(str);
  cut_assert_true(sv.len == 11);
  cut_assert_true(strcmp(sv_raw(&sv), str) == 0);
}

void test_sv_iter()
{
  const char *str = "Hello World";
  size_t i = 0;
  StringView sv = sv_create(str);
  for (const char *c = sv_iter(&sv); c != sv_end(&sv); c = sv_iter(&sv)) {
    cut_assert_eq(*c, str[i]);
    i++;
  }

  cut_assert_eq(sv_iter(&sv), sv_end(&sv));
}

void test_sv_end()
{
  const char *str = "Hello World";
  StringView sv = sv_create(str);
  const char *end = sv_end(&sv);
  cut_assert_true(end == &str[11]);
}

void test_sv_findchar()
{
  const char *str = "Hello World";
  StringView sv = sv_create(str);
  const char *found = sv_findchar(&sv, 'W');
  cut_assert_true(found != sv_end(&sv));

  const char *should_fail = sv_findchar(&sv, '!');
  cut_assert_true(should_fail == sv_end(&sv));
}

void test_sv_substr()
{
  const char *str = "Hello World";
  StringView sv = sv_create(str);
  const char *substr = sv_substr(&sv, "World");
  cut_assert_true(substr != sv_end(&sv));

  const char *should_fail = sv_substr(&sv, "World!");
  cut_assert_true(should_fail == sv_end(&sv));
}

void test_sv_tocstr()
{
  const char *str = "Hello World";
  StringView sv = sv_create(str);
  const char *cstr = sv_tocstr(&sv);
  cut_assert_true(sv.len == 11);
  cut_assert_true(strcmp(cstr, str) == 0);
}

void test_sv_cstr_tosv()
{
  const char *str = "Hello World";
  StringView sv = sv_cstr_tosv(str);
  cut_assert_true(sv.len == 11);
  cut_assert_true(strcmp(sv_raw(&sv), str) == 0);
}

void test_sv_erase_range()
{
  const char *str = "Hello World";
  StringView sv = sv_create(str);
  StringView sv2 = sv_erase_range(&sv, sv_substr(&sv, "World"), sv_end(&sv));
  cut_assert_true(sv.len == 11);
  cut_assert_true(sv2.len == 6);
  cut_assert_true(strcmp(sv_raw(&sv), str) == 0);
  cut_assert_true(strcmp(sv_raw(&sv2), "Hello ") == 0);
}

void test_sv_erase_char()
{
  const char *str = "Hello World";
  StringView sv = sv_create(str);
  StringView sv2 = sv_erase_char(&sv, 'l');
  cut_assert_true(sv.len == 11);
  cut_assert_true(sv2.len == 8);
  cut_assert_true(strcmp(sv_raw(&sv), str) == 0);
  cut_assert_true(strcmp(sv_raw(&sv2), "Heo Word") == 0);
}

void test_sv_erase_substr_mult()
{
  const char *str = "hello hello hello world!";
  StringView sv = sv_create(str);
  StringView sv2 = sv_erase_substr(&sv, "hello ");
  cut_assert_true(strcmp(sv_raw(&sv), str) == 0);
  cut_assert_true(strcmp(sv_raw(&sv2), "world!") == 0);
}

void test_sv_erase_substr_once()
{
  const char *str = "Hello World";
  StringView sv = sv_create(str);
  StringView sv2 = sv_erase_substr(&sv, " World");
  cut_assert_true(sv.len == 11);
  cut_assert_true(sv2.len == 5);
  cut_assert_true(strcmp(sv_raw(&sv), str) == 0);
  cut_assert_true(strcmp(sv_raw(&sv2), "Hello") == 0);
}

void test_append_sv()
{
  const char *str = "Hello World";
  StringView sv = sv_create(str);
  StringView sv2 = sv_appendsv(&sv, &sv);
  cut_assert_true(sv.len == 11);
  cut_assert_true(sv2.len == 22);
  cut_assert_true(strcmp(sv_raw(&sv), str) == 0);
  cut_assert_true(strcmp(sv_raw(&sv2), "Hello WorldHello World") == 0);
}

void test_append_cstr()
{
  const char *str = "Hello World";
  StringView sv = sv_create(str);
  StringView sv2 = sv_appendcstr(&sv, "!");
  cut_assert_true(sv.len == 11);
  cut_assert_true(sv2.len == 12);
  cut_assert_true(strcmp(sv_raw(&sv), str) == 0);
  cut_assert_true(strcmp(sv_raw(&sv2), "Hello World!") == 0);
}

void test_basic_sv_create()
{
  const char *str = "Hello World";
  StringView sv = sv_create(str);
  cut_assert_true(sv.len == 11);
  cut_assert_true(strcmp(sv_raw(&sv), str) == 0);
}

int main(void) {
  CUT_BEGIN;

  test_basic_sv_create();
  test_append_cstr();
  test_append_sv();
  test_sv_erase_substr_once();
  test_sv_erase_substr_mult();
  test_sv_erase_char();
  test_sv_erase_range();
  test_sv_cstr_tosv();
  test_sv_tocstr();
  test_sv_substr();
  test_sv_findchar();
  test_sv_end();
  test_sv_iter();
  test_sv_raw();
  test_sv_len();

  CUT_END;
  return 0;
}