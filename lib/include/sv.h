#ifndef SV_H
#define SV_H

#include <aio.h>   // For size_t.
#include <stdio.h> // For FILE.

typedef struct {
  const char *data; // Always points to str[0].
  const char *end;  // Always points to str[strlen(str)] aka '\0'.
  size_t len;       // Always equal to strlen(str) - 1.
} StringView;

/*
 * Create a `StringView` from a C string.
 * @param `str` The C string to create a `StringView` from.
 * @return A new `StringView` with the same data as `str`.
*/
StringView sv_create(const char *str);

/* Append a C string to a `StringView`.
 * @param `sv` The `StringView` to append to.
 * @param `str` The C string to append.
 * @return A new `StringView` with the C string appended.
 */
StringView sv_appendcstr(const StringView *sv, const char *str);

/* Append a `StringView` to a `StringView`.
 * @param `sv` The `StringView` to append to.
 * @param `sv2` The `StringView` to append.
 * @return A new `StringView` with the `StringView` appended.
 */
StringView sv_appendsv(const StringView *sv, const StringView *sv2);

/* Erase a substring from a `StringView`.
 * @param `sv` The `StringView` to erase from.
 * @param `target` The substring to erase. 
 * @return A new `StringView` with the substring erased.
 */
StringView sv_erase_substr(const StringView *sv, const char *target);

/* Erase all characters that match `c` from a `StringView`.
 * @param `sv` The `StringView` to erase from.
 * @param `c` The character to erase.
 * @return A new `StringView` with the characters erased.
 */
StringView sv_erase_char(const StringView *sv, char c);

/* Erase a range of characters from a `StringView`.
 * @param `sv` The `StringView` to erase from.
 * @param `start` The start of the range to erase.
 * @param `end` The end of the range to erase.
 * @return A new `StringView` with the range erased.
 */
StringView sv_erase_range(const StringView *sv, const char *start, const char *end);

/* Create a `StringView` from a C string.
 * @param `str` The C string to create a `StringView` from.
 * @return A new `StringView` with the same data as `str`.
 */
StringView sv_cstr_tosv(const char *str);

/* Convert a `StringView` to a C string.
 * @param `sv` The `StringView` to convert.
 * @return A C string with the same data as `sv`.
 */
const char *sv_tocstr(const StringView *sv);

/* Find the first occurrence of a substring in a `StringView`.
 * @param `sv` The `StringView` to search.
 * @param `target` The substring to search for.
 * @return A pointer to the first occurrence of `target` in `sv`. Returns `sv->end` if `target` is not found.
 */
const char *sv_substr(const StringView *sv, const char *target);

/* Find the first occurrence of a character in a `StringView`.
 * @param `sv` The `StringView` to search.
 * @param `c` The character to search for.
 * @return A pointer to the first occurrence of `c` in `sv`. Returns `sv->end` if `c` is not found.
 */
const char *sv_findchar(const StringView *sv, char c);

/* Get the end of a `StringView`. This does not return the last character, rather it retuns a pointer to the character after the last character.
 * @param `sv` The `StringView` to get the end of.
 * @return A pointer to the end of `sv`.
 */
const char *sv_end(const StringView *sv);

/* Iterate through the characters of a `StringView`.
 * @param `sv` The `StringView` to iterate through.
 * @return A pointer to the next character in `sv`. Returns `sv->end` if there are no more characters.
 */
const char *sv_iter(const StringView *sv);

/* Get the raw data of a `StringView`.
 * @param `sv` The `StringView` to get the raw data of.
 * @return A pointer to the raw data of `sv`.
 */
const char *sv_raw(const StringView *sv);

/* Write a `StringView` to a file.
 * @param `sv` The `StringView` to write.
 * @param `stream` The file to write to.
 * @return The number of bytes written.
 */
size_t sv_write(const StringView *sv, FILE *stream);

/* Get the length of a `StringView`.
 * @param `sv` The `StringView` to get the length of.
 * @return The length of `sv`.
 */
size_t sv_len(const StringView *sv);

#endif // SV_H
