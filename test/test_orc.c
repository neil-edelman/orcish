/** @license 2014 Neil Edelman, distributed under the terms of the
 [MIT License](https://opensource.org/licenses/MIT). */

#include <stdlib.h> /* malloc free */
#include <stdio.h>  /* fprintf */
#include <string.h> /* strcmp */
#include <assert.h>
#include "../src/orc.h"

/** @return Zero. */
int main(void) {
	int i;
	char test1[1], test2[2], test5[5], test11[11], test16[16], test256[256],
		test_ver[256];

	assert(sizeof test_ver >= sizeof test256); /* _Etc_. */

	orc_name(0, 0);
	orc_name(test1, 0);

	for(i = 0; i < 8; i++) {
		orc_name(test1, sizeof test1);
		orc_name(test2, sizeof test2);
		orc_name(test5, sizeof test5);
		orc_name(test11, sizeof test11);
		orc_name(test16, sizeof test16);
		orc_name(test256, sizeof test256);
		printf("<%s> <%s> <%s> <%s> <%s> <%s>\n", test1, test2, test5, test11,
			test16, test256);
	}

	{
		orc_ptr(test1, sizeof test1, test1);
		orc_ptr(test2, sizeof test2, test2);
		orc_ptr(test5, sizeof test5, test5);
		orc_ptr(test11, sizeof test11, test11);
		orc_ptr(test16, sizeof test16, test16);
		orc_ptr(test256, sizeof test256, test256);
		printf("ptr: <%s> <%s> <%s> <%s> <%s> <%s>\n",
			test1, test2, test5, test11, test16, test256);
		orc_ptr(test_ver, sizeof test1, test1);
		assert(!strcmp(test1, test_ver));
		orc_ptr(test_ver, sizeof test2, test2);
		assert(!strcmp(test2, test_ver));
		orc_ptr(test_ver, sizeof test5, test5);
		assert(!strcmp(test5, test_ver));
		orc_ptr(test_ver, sizeof test11, test11);
		assert(!strcmp(test11, test_ver));
		orc_ptr(test_ver, sizeof test16, test16);
		assert(!strcmp(test16, test_ver));
		orc_ptr(test_ver, sizeof test256, test256);
		assert(!strcmp(test256, test_ver));
	}

	{
		const char *a, *b;
		a = orcify(test1), b = orcify(test1);
		printf("<%s> == <%s>\n", a, b), assert(!strcmp(a, b));
		a = orcify(test2), b = orcify(test2);
		printf("<%s> == <%s>\n", a, b), assert(!strcmp(a, b));
		a = orcify(test5), b = orcify(test5);
		printf("<%s> == <%s>\n", a, b), assert(!strcmp(a, b));
		a = orcify(test11), b = orcify(test11);
		printf("<%s> == <%s>\n", a, b), assert(!strcmp(a, b));
		a = orcify(test16), b = orcify(test16);
		printf("<%s> == <%s>\n", a, b), assert(!strcmp(a, b));
		a = orcify(test256), b = orcify(test256);
		printf("<%s> == <%s>\n", a, b), assert(!strcmp(a, b));
		a = orcify(0), b = orcify(0);
		printf("<%s> == <%s>\n", a, b), assert(!strcmp(a, b));
	}
	orc_stats();

	return EXIT_SUCCESS;
}
