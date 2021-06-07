/** 2016 Neil Edelman.

 Test Orcish.

 @title		TestOrcish
 @author	Neil
 @version	1.1; 2016-09
 @since		1.0; 2016-02 */

#include <stdlib.h> /* malloc free */
#include <stdio.h>  /* fprintf */
#include "../src/orcish.h"

/** @return Zero. */
int main(void) {
	int i;
	char test1[1], test2[2], test5[5], test11[11], test16[16], test256[256];

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
