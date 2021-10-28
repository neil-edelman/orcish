/** @license 2014, 2021 Neil Edelman, distributed under the terms of the
 [MIT License](https://opensource.org/licenses/MIT). Contains some syllables
 from [SMAUG](http://www.smaug.org/), which is a derivative of
 [Merc](http://dikumud.com/Children/merc2.asp), and
 [DikuMud](http://dikumud.com/); used under fair-use. Contains
 [MurmurHash](https://github.com/aappleby/smhasher)-derived code, placed in
 public domain by Austin Appleby.

 @subtitle Name Generator

 Orcish names originate or are inspired by [JRR Tolkien's Orcish
 ](http://en.wikipedia.org/wiki/Languages_constructed_by_J._R._R._Tolkien). Use
 <fn:orc_name> to fill a memory location with an Orcish name, or <fn:orcify> to
 assign a deterministic name to a pointer.

 @std C89 */

/* This should be set to `sizeof(unsigned long) * CHAR_BIT`, or less, but it
 decreases the entropy of the random bits. */
#define ORC_LEQ_LONG_BITS 64

#include "orc.h"
#include <stdlib.h> /* rand */
#include <stdio.h>  /* strlen */
#include <ctype.h>  /* toupper */
#include <string.h> /* memcpy */
#include <assert.h> /* assert */
#include <limits.h> /* CHAR_BIT */

static const char *syllables[] = {
	"ub", "ul", "uk", "um", "uu", "oo", "ee", "uuk", "uru", "ick", "gn", "ch",
	"ar", "eth", "ith", "ath", "uth", "yth", "ur", "uk", "ug", "sna", "or",
	"ko", "uks", "ug", "lur", "sha", "grat", "mau", "eom", "lug", "uru", "mur",
	"ash", "goth", "sha", "cir", "un", "mor", "ann", "sna", "gor", "dru", "az",
	"azan", "nul", "biz", "balc", "balc", "tuo", "gon", "dol", "bol", "dor",
	"luth", "bolg", "beo", "vak", "bat", "buy", "kham", "kzam", "lg", "bo",
	"thi", "ia", "es", "en", "ion", "mok", "muk", "tuk", "gol", "fim", "ette",
	"moor", "goth", "gri", "shn", "nak", "ash", "bag", "ronk", "ask", "mal",
	"ome", "hi", "sek", "aah", "ove", "arg", "ohk", "to", "lag", "muzg", "ash",
	"mit", "rad", "sha", "saru", "ufth", "warg", "sin", "dar", "ann", "mor",
	"dab", "val", "dur", "dug", "bar", "ash", "krul", "gakh", "kraa", "rut",
	"udu", "ski", "kri", "gal", "nash", "naz", "hai", "mau", "sha", "akh",
	"dum", "olog", "lab", "lat"
};
static const unsigned syllables_max_length = 4;

static const char *suffixes[] = {
	"at", "ob", "agh", "uk", "uuk", "um", "uurz", "hai", "ishi", "ub", "ull",
	"ug", "an", "hai", "gae", "-hai", "luk", "tz", "hur", "dush", "ks", "mog",
	"grat", "gash", "th", "on", "gul", "gae", "gun", "dan", "og", "ar", "meg",
	"or", "lin", "dog", "ath", "ien", "rn", "bul", "bag", "ungol", "mog",
	"nakh", "gorg", "-dug", "duf", "ril", "bug", "snaga", "naz", "gul", "ak",
	"kil", "ku", "on", "ritz", "bad", "nya", "durbat", "durb", "kish", "olog",
	"-atul", "burz", "puga", "shar", "snar", "hai", "ishi", "uruk", "durb",
	"krimp", "krimpat", "zum", "gimb", "-gimb", "glob", "-glob", "sharku",
	"sha", "-izub", "-izish", "izg", "-izg", "ishi", "ghash", "thrakat",
	"thrak", "golug", "mokum", "ufum", "bubhosh", "gimbat", "shai", "khalok",
	"kurta", "ness", "funda"
};
static const unsigned suffixes_max_length = 7;

static const unsigned max_name_size = 256;

#define ORC_CHOOSE(array, seed) (assert((seed) <= RAND_MAX), \
	(array)[(seed) / (RAND_MAX / (sizeof (array) / sizeof *(array)) + 1)])

/** Fills `name` with a random Orcish name. Potentially up to `name_size` - 1,
 (if zero, does nothing) then puts a null terminator. Uses `r` plugged into
 `recur` to generate random values in the range of `[0, RAND_MAX]`. */
static void orcish(char *const name, size_t name_size,
	unsigned long r, unsigned (*recur)(unsigned long *)) {
	char *n = name;
	const char *part;
	size_t part_len;
	assert(name);
	if(!name_size) { return; }
	else if(name_size == 1) { *n = '\0'; return; }
	else if(name_size > max_name_size) { name_size = max_name_size; }
	/* Now `name_size \in [2, max_name_size]`. */
	if(name_size <= syllables_max_length + suffixes_max_length) {
		part = ORC_CHOOSE(syllables, recur(&r));
		part_len = strlen(part);
		if(part_len >= name_size) part_len = name_size - 1;
		memcpy(n, part, part_len), n += part_len, name_size -= part_len;
		if(name_size > suffixes_max_length) {
			part = ORC_CHOOSE(suffixes, recur(&r));
			part_len = strlen(part);
			memcpy(n, part, part_len), n += part_len, name_size -= part_len;
		}
	} else {
		unsigned no_syllables = ((unsigned)name_size - 1 - suffixes_max_length)
			/ syllables_max_length;
		while(no_syllables) {
			part = ORC_CHOOSE(syllables, recur(&r));
			part_len = strlen(part);
			memcpy(n, part, part_len), n += part_len, name_size -= part_len;
			no_syllables--;
		}
		part = ORC_CHOOSE(suffixes, recur(&r));
		part_len = strlen(part);
		memcpy(n, part, part_len), n += part_len, name_size -= part_len;
	}
	*n = '\0';
	*name = (char)toupper((unsigned char)*name);
}

#undef ORC_RAND

/* Murmur callbacks. */
#if ORC_LEQ_LONG_BITS
/** <https://github.com/aappleby/smhasher> `src/MurmurHash3.cpp fmix64`.
 @return Recurrence on `k`. */
static unsigned long fmix_long(unsigned long k) {
	k ^= k >> 33;
	k *= 0xff51afd7ed558ccd;
	k ^= k >> 33;
	k *= 0xc4ceb9fe1a85ec53;
	k ^= k >> 33;
	return k;
}
#else
#error Get more mixing functions.
#endif

/* Advances `r`.
 @return Number in `[0, RAND_MAX]`. @implements `orcish` */
static unsigned murmur_callback(unsigned long *const r)
	{ return (*r = fmix_long(*r)) % (1lu + RAND_MAX); }

/** Uses `rand`; ignores `r` and uses a global variable set by `srand`.
 @return Number in `[0, RAND_MAX]`. @implements `orcish` */
static unsigned rand_callback(unsigned long *const r)
	{ (void)r; return (unsigned)rand(); }

/** Fills `name` with a random Orcish name. Potentially up to `name_size` - 1,
 (with a maximum of 255,) then puts a null terminator. Uses `rand` from
 `stdlib.h`.
 @param[name] A valid pointer to at least `name_size` characters.
 @param[name_size] If zero, does nothing. */
void orc_name(char *const name, const size_t name_size)
	{ assert(name); orcish(name, name_size, 0, &rand_callback); }

/** Fills `name` with a deterministic Orcish name based on `p`, or if `p` is
 null, then "null". Potentially up to `name_size` - 1, (with a maximum of 255,)
 then puts a null terminator.
 @param[name] A valid pointer to at least `name_size` characters.
 @param[name_size] If zero, does nothing. */
void orc_ptr(char *const name, const size_t name_size, const void *const p) {
	assert(name || !name_size);
	if(p) {
		orcish(name, name_size, (unsigned long)p, &murmur_callback);
	} else {
		switch(name_size) {
		case 0: return;
		default: /* _Sic_; `name_size > 5` has enough. Fall-through. */
		case 5: name[3] = 'l';
		case 4: name[2] = 'l';
		case 3: name[1] = 'u';
		case 2: name[0] = 'n';
		case 1: break;
		}
		name[name_size < 5 ? name_size - 1 : 4] = '\0';
	}
}

/** Call <fn:orc_ptr> with `p` with default values and a small temporary buffer.
 @return A temporary string; can handle four names at a time. */
const char *orcify(const void *const p) {
	/* If one gets a compile error, then choose another `ORC_LEQ_LONG_BITS` at
	 the beginning of the file. */
	static char names[4
		* (sizeof(unsigned long) * CHAR_BIT >= ORC_LEQ_LONG_BITS)][10];
	static unsigned n;
	n %= sizeof names / sizeof *names;
	orc_ptr(names[n], sizeof *names, p);
	return names[n++];
}
