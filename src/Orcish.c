/** 2014 Neil Edelman.
 neil dot edelman each mail dot mcgill dot ca
 <p>
 Orcish words are gathered off the Internet, SMAUG1.8, made up myself,
 etc. They originate or are inspired by JRR Tolkien's Orcish; this
 file has had many incarnations and was ported from Java. Random
 words are super-useful in testing and character generation.  {@link
 http://en.wikipedia.org/wiki/Languages_constructed_by_J._R._R._Tolkien}.
 <p>
 ANSI C89; provides one function, @code{void Orcish(char *const name,
 const size_t name_size)}, which takes @code{name}, a string, and
 replaces it, to a maximum of @code{name_size} characters, with a
 @code{rand()} Orcish name.

 @author	Neil
 @version	1.1, 2016-09
 @since		2014 */

#include <stdlib.h> /* rand */
#include <stdio.h>	/* snprintf strlen */
#include <ctype.h>	/* toupper */
#include <string.h>	/* strcat, strncat */

static const char *syllable[] = {
	"ub", "ul", "uk", "um", "uu", "oo", "ee", "uuk", "uru",
	"ick", "gn", "ch", "ar", "eth", "ith", "ath", "uth", "yth",
	"ur", "uk", "ug", "sna", "or", "ko", "uks", "ug", "lur", "sha", "grat",
	"mau", "eom", "lug", "uru", "mur", "ash", "goth", "sha", "cir", "un",
	"mor", "ann", "sna", "gor", "dru", "az", "azan", "nul", "biz", "balc",
	"balc", "tuo", "gon", "dol", "bol", "dor", "luth", "bolg", "beo",
	"vak", "bat", "buy", "kham", "kzam", "lg", "bo", "thi", "ia", "es", "en",
	"ion", "mok", "muk", "tuk", "gol", "fim", "ette", "moor", "goth", "gri",
	"shn", "nak", "ash", "bag", "ronk", "ask", "mal", "ome", "hi",
	"sek", "aah", "ove", "arg", "ohk", "to", "lag", "muzg", "ash", "mit",
	"rad", "sha", "saru", "ufth", "warg", "sin", "dar", "ann", "mor", "dab",
	"val", "dur", "dug", "bar", "ash", "krul", "gakh", "kraa", "rut", "udu",
	"ski", "kri", "gal", "nash", "naz", "hai", "mau", "sha", "akh", "dum",
	"olog", "lab", "lat"
};
static const unsigned max_syllable_length = 4;

static const char *suffix[] = {
	"at", "ob", "agh", "uk", "uuk", "um", "uurz", "hai", "ishi", "ub",
	"ull", "ug", "an", "hai", "gae", "-hai", "luk", "tz", "hur", "dush",
	"ks", "mog", "grat", "gash", "th", "on", "gul", "gae", "gun",
	"dan", "og", "ar", "meg", "or", "lin", "dog", "ath", "ien", "rn", "bul",
	"bag", "ungol", "mog", "nakh", "gorg", "-dug", "duf", "ril", "bug",
	"snaga", "naz", "gul", "ak", "kil", "ku", "on", "ritz", "bad", "nya",
	"durbat", "durb", "kish", "olog", "-atul", "burz", "puga", "shar",
	"snar", "hai", "ishi", "uruk", "durb", "krimp", "krimpat", "zum",
	"gimb", "-gimb", "glob", "-glob", "sharku", "sha", "-izub", "-izish",
	"izg", "-izg", "ishi", "ghash", "thrakat", "thrak", "golug", "mokum",
	"ufum", "bubhosh", "gimbat", "shai", "khalok", "kurta", "ness", "funda"
};
static const unsigned max_suffix_length = 7;

/** You must have space for (at least) name_size (byte) characters.
 @param name		Filled with a random word in psudo-Orcish.
 @param name_size	sizeof(name); suggest 16, which would be enough for
 					2 syllables and a suffix. */
void Orcish(char *const name, const size_t name_size) {
	char *str;
	int a;

	if(name_size == 0) return;

	name[0] = '\0';

	if(name_size == 1) {
		return;
	} else if(name_size < max_syllable_length + 1) {
		a = rand() / (RAND_MAX + 1.0) * (sizeof syllable / sizeof *syllable);
		strncat(name, syllable[a], name_size - 1);
	} else if(name_size < max_syllable_length + max_suffix_length + 1) {
		a = rand() / (RAND_MAX + 1.0) * (sizeof syllable / sizeof *syllable);
		str = strcat(name, syllable[a]);
		a = rand() / (RAND_MAX + 1.0) * (sizeof syllable / sizeof *syllable);
		strncat(str, syllable[a], name_size - strlen(name) - 1);
	} else {
		unsigned i, syllables;

		syllables = (name_size - 1 - max_suffix_length) / max_syllable_length;
		str = name;
		name[0] = '\0';
		for(i = 0; i < syllables; i++) {
			a = rand() / (RAND_MAX + 1.0) * (sizeof syllable/sizeof *syllable);
			str = strcat(str, syllable[a]);
		}
		a = rand() / (RAND_MAX + 1.0) * (sizeof suffix / sizeof *suffix);
		strcat(str, suffix[a]);
	}

	name[0] = toupper(name[0]);

}
