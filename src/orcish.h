#include <stddef.h> /* size_t */
void orcish(char *, size_t);
void orcish_ptr(char *, const size_t, const void *);
void orcish_int(char *, size_t, unsigned);
void orcish_long(char *, size_t, unsigned long);
const char *orc(const void *);
const char *orc_int(unsigned);
const char *orc_long(unsigned long);
