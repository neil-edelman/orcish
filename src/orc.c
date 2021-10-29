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

#include "orc.h"
#include <stdlib.h> /* rand */
#include <stdio.h>  /* strlen */
#include <ctype.h>  /* toupper */
#include <string.h> /* memcpy */
#include <assert.h> /* assert */
#include <limits.h> /* CHAR_BIT, ULONG_MAX */

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

static unsigned long exptbl[] = {
	(unsigned long)(         1.00000 * (1u + RAND_MAX)), /* 0 */
	(unsigned long)(         2.71828 * (1u + RAND_MAX)), /* 1 */
	(unsigned long)(         7.38906 * (1u + RAND_MAX)), /* 2 */
	(unsigned long)(        20.08554 * (1u + RAND_MAX)), /* 3 */
	(unsigned long)(        54.59815 * (1u + RAND_MAX)), /* 4 */
	(unsigned long)(       148.41316 * (1u + RAND_MAX)), /* 5 */
	(unsigned long)(       403.42879 * (1u + RAND_MAX)), /* 6 */
	(unsigned long)(      1096.63316 * (1u + RAND_MAX)), /* 7 */
	(unsigned long)(      2980.95799 * (1u + RAND_MAX)), /* 8 */
	(unsigned long)(      8103.08393 * (1u + RAND_MAX)), /* 9 */
	(unsigned long)(     22026.46579 * (1u + RAND_MAX)), /* 10 */
	(unsigned long)(     59874.14172 * (1u + RAND_MAX)), /* 11 */
	(unsigned long)(    162754.79142 * (1u + RAND_MAX)), /* 12 */
	(unsigned long)(    442413.39201 * (1u + RAND_MAX)), /* 13 */
	(unsigned long)(   1202604.28416 * (1u + RAND_MAX)), /* 14 */
	(unsigned long)(   3269017.37247 * (1u + RAND_MAX)), /* 15 */
	(unsigned long)(   8886110.52051 * (1u + RAND_MAX)), /* 16 */
	(unsigned long)(  24154952.75358 * (1u + RAND_MAX)), /* 17 */
	(unsigned long)(  65659969.13733 * (1u + RAND_MAX)), /* 18 */
	(unsigned long)( 178482300.96319 * (1u + RAND_MAX)), /* 19 */
	(unsigned long)( 485165195.40979 * (1u + RAND_MAX)), /* 20 */
	(unsigned long)(1318815734.48321 * (1u + RAND_MAX)), /* 21 */
	(unsigned long)(3584912846.13159 * (1u + RAND_MAX)), /* 22 */
};
static const size_t size_tbl = sizeof exptbl / sizeof *exptbl;

#include <math.h>
void orc_stats(void) {
	size_t i, s, t;

	/* Junhao, based on Knuth */
	size_t k = 0, p = RAND_MAX;
	int expected = 5, left = expected, step = 50;
	printf("p=%lu\n", p);
	do {
		k++, printf("k=%lu\n", k);
		p = p * (size_t)rand() / RAND_MAX, printf("p=%lu\n", p);
		while(p < RAND_MAX && left > 0) {
			if(left > step) {
				p *= step;
				left -= step;
			} else {
				if(left >= size_tbl) left = size_tbl - 1;
				p = p * exptbl[left] / RAND_MAX;
				left = 0;
			}
		}
	} while(p > RAND_MAX);
	printf("k - 1 = %lu\n", k - 1);

	for(i = 0; i < 23; i++) {
		printf("\t(unsigned long)(%16.5f * (1u + RAND_MAX)), /* %lu */\n", exp(i), i);
	}

	for(s = 0, i = 0; i < sizeof syllables / sizeof *syllables; i++)
		s += strlen(syllables[i]);
	printf("syl: %lu / %lu = %f\n", s, i, (double)s / i);

	for(s = 0, i = 0; i < sizeof suffixes / sizeof *suffixes; i++)
		if(s < (t = strlen(suffixes[i]))) s = t;
	printf("suf: max %lu\n", s);
}

/** Fills `name` with a random Orcish name. Potentially up to `name_size` - 1,
 (if zero, does nothing) then puts a null terminator. Uses `r` plugged into
 `recur` to generate random values in the range of `[0, RAND_MAX]`. */
static void orc_rand(char *const name, const size_t name_size,
	unsigned long r, unsigned (*recur)(unsigned long *)) {
#define ORC_SAMPLE(array, seed) (assert((seed) <= RAND_MAX), \
	(array)[(seed) / (RAND_MAX / (sizeof (array) / sizeof *(array)) + 1)])
	unsigned len, part_len, descend = 1u + RAND_MAX, limit, x = 0;
	const char *part;
	char *n = name;
	assert((name || !name_size) && recur);
	if(!name_size) { return; }
	else if(name_size == 1) { *n = '\0'; return; }
	/* The length of space we have to fill syllables. */
	len = (name_size < max_name_size ? (unsigned)name_size : max_name_size) - 1;
	len = len > suffixes_max_length ? len - suffixes_max_length : 0;
	printf("starting len = %u\n", len);
	/* Knuth's Poisson distribution with fixed point, RAND_MAX ~ 1. */
	limit = /* e^{-rate} */RAND_MAX / 222;
	do {
		x++;
		part_len = (unsigned)strlen(part = ORC_SAMPLE(syllables, recur(&r)));
		if(part_len > len) part_len = len; /* Clip. */
		memcpy(n, part, (size_t)part_len), n += part_len, len -= part_len;
	} while(len > syllables_max_length + suffixes_max_length
		&& (descend = (unsigned)((unsigned long)recur(&r) * descend / RAND_MAX))
		> limit);
	part_len = (unsigned)strlen(part = ORC_SAMPLE(suffixes, recur(&r)));
	if(part_len > len) part_len = len; /* Clip. */
	memcpy(n, part, (size_t)part_len), n += part_len, len -= part_len;
	*n = '\0';
	*name = (char)toupper((unsigned char)*name);
	printf("Size %lu: rand %u.\n", name_size, x);
#undef ORC_SAMPLE
}

#if ULONG_MAX <= 0xffffffff || ULONG_MAX < 0xffffffffffffffff /* <!-- !long */
/** <https://github.com/aappleby/smhasher> `src/MurmurHash3.cpp fmix32`.
 @return Recurrence on `h`. */
static unsigned long fmix(unsigned long h) {
	h ^= h >> 16;
	h *= 0x85ebca6b;
	h ^= h >> 13;
	h *= 0xc2b2ae35;
	h ^= h >> 16;
	return h;
}
#else /* !long --><!-- long */
/** <https://github.com/aappleby/smhasher> `src/MurmurHash3.cpp fmix64`.
 @return Recurrence on `k`. */
static unsigned long fmix(unsigned long k) {
	k ^= k >> 33;
	k *= 0xff51afd7ed558ccd;
	k ^= k >> 33;
	k *= 0xc4ceb9fe1a85ec53;
	k ^= k >> 33;
	return k;
}
#endif /* long --> */

/* Advances `r`.
 @return Number in `[0, RAND_MAX]`. @implements `orcish` */
static unsigned murmur_callback(unsigned long *const r)
	{ return (*r = fmix(*r)) % (1lu + RAND_MAX); }

/** Uses `rand`; ignores `r` and uses a global variable set by `srand`.
 @return Number in `[0, RAND_MAX]`. @implements `orcish` */
static unsigned rand_callback(unsigned long *const r)
	{ (void)r; return (unsigned)rand(); }

/** Fills `name` with a random Orcish name. Potentially up to `name_size` - 1,
 (with a maximum of 255,) then puts a null terminator. Uses `rand` from
 `stdlib.h`.
 @param[name] A valid pointer to at least `name_size` characters.
 @param[name_size] If zero, does nothing. */
void orc_name(char *const name, const size_t name_size) {
	assert(name || !name_size);
	orc_rand(name, name_size, 0, &rand_callback);
}

/** Fills `name` with a deterministic Orcish name based on `l`, potentially
 up to `name_size` - 1, (with a maximum of 255,) then puts a null terminator.
 @param[name] A valid pointer to at least `name_size` characters.
 @param[name_size] If zero, does nothing. */
void orc_long(char *const name, const size_t name_size, const unsigned long l) {
	assert(name || !name_size);
	orc_rand(name, name_size, l, &murmur_callback);
}

/** Fills `name` with a deterministic Orcish name based on `p`, or if `p` is
 null, then "null". Potentially up to `name_size` - 1, (with a maximum of 255,)
 then puts a null terminator.
 @param[name] A valid pointer to at least `name_size` characters.
 @param[name_size] If zero, does nothing. */
void orc_ptr(char *const name, const size_t name_size, const void *const p) {
	assert(name || !name_size);
	if(p) {
		/* There will be data lost in the upper bits if
		 `sizeof(unsigned long) < sizeof(void *)`, but it's probably okay? */
		orc_long(name, name_size, (unsigned long)p);
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
	static char names[4][10];
	static unsigned n;
	n %= sizeof names / sizeof *names;
	orc_ptr(names[n], sizeof *names, p);
	return names[n++];
}
