#include <stddef.h> /* size_t */
void orc_stats(void);
void orc_name(char *, size_t);
void orc_long(char *, size_t, unsigned long);
void orc_ptr(char *, size_t, const void *);
const char *orcify(const void *);
