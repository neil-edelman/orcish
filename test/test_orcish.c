/** @license 2014 Neil Edelman, distributed under the terms of the
 [MIT License](https://opensource.org/licenses/MIT).

 Test Orcish. */

#include <stdlib.h> /* malloc free */
#include <stdio.h>  /* fprintf */
#include <string.h> /* strcmp */
#include <assert.h>
#include "../src/orcish.h"

/** @return Zero. */
int main(void) {
	int i;
	char test1[1], test2[2], test5[5], test11[11], test16[16], test256[256],
		test_ver[256];

	assert(sizeof test_ver >= sizeof test256); /* _Etc_. */
	/* What tests can we run? See if they are valid strings, or else in danger
	 of crashing? */
	for(i = 0; i < 16; i++) {
		orcish(test1, sizeof test1);
		orcish(test2, sizeof test2);
		orcish(test5, sizeof test5);
		orcish(test11, sizeof test11);
		orcish(test16, sizeof test16);
		orcish(test256, sizeof test256);
		printf("<%s> <%s> <%s> <%s> <%s> <%s>\n", test1, test2, test5, test11,
			test16, test256);
	}

	{
		orcish_ptr(test1, sizeof test1, test1);
		orcish_ptr(test2, sizeof test2, test2);
		orcish_ptr(test5, sizeof test5, test5);
		orcish_ptr(test11, sizeof test11, test11);
		orcish_ptr(test16, sizeof test16, test16);
		orcish_ptr(test256, sizeof test256, test256);
		printf("ptr: <%s> <%s> <%s> <%s> <%s> <%s>\n",
			test1, test2, test5, test11, test16, test256);
		orcish_ptr(test_ver, sizeof test1, test1);
		assert(!strcmp(test1, test_ver));
		orcish_ptr(test_ver, sizeof test2, test2);
		assert(!strcmp(test2, test_ver));
		orcish_ptr(test_ver, sizeof test5, test5);
		assert(!strcmp(test5, test_ver));
		orcish_ptr(test_ver, sizeof test11, test11);
		assert(!strcmp(test11, test_ver));
		orcish_ptr(test_ver, sizeof test16, test16);
		assert(!strcmp(test16, test_ver));
		orcish_ptr(test_ver, sizeof test256, test256);
		assert(!strcmp(test256, test_ver));

		orcish_int(test256, sizeof test256, 8128);
		orcish_int(test_ver, sizeof test256, 8128);
		printf("int: <%s>\n", test256);
		assert(!strcmp(test256, test_ver));

		orcish_long(test256, sizeof test256, 8128);
		orcish_long(test_ver, sizeof test256, 8128);
		printf("long: <%s>\n", test256);
		assert(!strcmp(test256, test_ver));
	}

	{
		const char *a, *b;
		a = orc(test1), b = orc(test1);
		printf("<%s> == <%s>\n", a, b), assert(!strcmp(a, b));
		a = orc(test2), b = orc(test2);
		printf("<%s> == <%s>\n", a, b), assert(!strcmp(a, b));
		a = orc(test5), b = orc(test5);
		printf("<%s> == <%s>\n", a, b), assert(!strcmp(a, b));
		a = orc(test11), b = orc(test11);
		printf("<%s> == <%s>\n", a, b), assert(!strcmp(a, b));
		a = orc(test16), b = orc(test16);
		printf("<%s> == <%s>\n", a, b), assert(!strcmp(a, b));
		a = orc(test256), b = orc(test256);
		printf("<%s> == <%s>\n", a, b), assert(!strcmp(a, b));
		a = orc(0), b = orc(0);
		printf("<%s> == <%s>\n", a, b), assert(!strcmp(a, b));

		a = orc_int(42), b = orc_int(42);
		printf("<%s> == <%s>\n", a, b), assert(!strcmp(a, b));

		a = orc_long(42), b = orc_long(42);
		printf("<%s> == <%s>\n", a, b), assert(!strcmp(a, b));
	}

	return EXIT_SUCCESS;
}
