/* 2016 Neil Edelman */

#include <stdlib.h> /* malloc free */
#include <stdio.h>  /* fprintf */
#include "../src/Orcish.h"

/** Test Orcish.

 @author	Neil
 @version	1.0; 2016-09
 @since		1.0; 2016-09 */

/* constants */
static const char *programme   = "TestOrcish";
static const char *year        = "2016";
static const int version_major = 1;
static const int version_minor = 0;

static void usage(void);

/** Entry point.
 @return		Either EXIT_SUCCESS or EXIT_FAILURE. */
int main(int argc, char **argv) {
	int i;
	char test1[1];
	char test2[2];
	char test16[16];

	do { } while(0 && argv);
	if(argc > 1) { usage(); return EXIT_SUCCESS; }

	for(i = 0; i < 128; i++) {
		Orcish(test16, sizeof test16);
		Orcish(test1, sizeof test1);
		Orcish(test2, sizeof test2);
		printf("<%s> <%s> <%s>\n", test1, test2, test16);
	}

	return EXIT_SUCCESS;
}

/** Prints command-line help. */
static void usage(void) {
	fprintf(stderr, "Usage: %s\nVersion %d.%d.\n\n"
		"%s %s Neil Edelman.\n"
		"This program comes with ABSOLUTELY NO WARRANTY.\n"
		"This is free software, and you are welcome to redistribute it.\n\n"
		"Orcish words are gathered off the Internet, SMAUG1.8, made up\n"
		"myself, etc. They originate or are inspired by JRR Tolkien's\n"
		"Orcish.\n\n",
		programme, version_major, version_minor, programme, year);
}
