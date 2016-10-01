/* 2016 Neil Edelman */

#include <stdlib.h> /* malloc free */
#include <stdio.h>  /* fprintf */
#include "../src/Orcish.h"

/** Test Orcish.

 @author	Neil
 @version	1.1; 2016-09
 @since		1.0; 2016-02 */

/* constants */
static const char *programme   = "TestOrcish";
static const char *year        = "2016";
static const int version_major = 1;
static const int version_minor = 1;

static void usage(void);

/** Entry point.
 @return		Either EXIT_SUCCESS or EXIT_FAILURE. */
int main(int argc, char **argv) {
	int i;
	char test1[1], test2[2], test5[5], test11[11], test16[16], test256[256];

	do { } while(0 && argv);
	if(argc > 1) { usage(); return EXIT_SUCCESS; }

	for(i = 0; i < 512; i++) {
		/* white-box: branch [1] */
		Orcish(test1, sizeof test1);
		/* white-box: branch [2-4] */
		Orcish(test2, sizeof test2);
		/* white-box: branch [5-11] */
		Orcish(test5, sizeof test5);
		/* white-box: branch [5-11] */
		Orcish(test11, sizeof test11);
		/* white-box: branch [12-] */
		Orcish(test16, sizeof test16);
		Orcish(test256, sizeof test256);
		printf("<%s> <%s> <%s> <%s> <%s> <%s>\n", test1, test2, test5, test11,
			test16, test256);
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
