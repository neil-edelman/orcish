/** @license 2014 Neil Edelman, distributed under the terms of the
 [MIT License](https://opensource.org/licenses/MIT).

 Test Orcish.

 @title TestOrcish
 @author Neil
 @version 2016-09
 @since 2016-02 */

#include <stdlib.h> /* malloc free */
#include <stdio.h>  /* fprintf */
#include "../src/orcish.h"

/** @return Zero. */
int main(void) {
	int i;
	char test1[1], test2[2], test5[5], test11[11], test16[16], test256[256];

	for(i = 0; i < 512; i++) {
		/* white-box: branch [1] */
		orcish(test1, sizeof test1);
		/* white-box: branch [2-4] */
		orcish(test2, sizeof test2);
		/* white-box: branch [5-11] */
		orcish(test5, sizeof test5);
		/* white-box: branch [5-11] */
		orcish(test11, sizeof test11);
		/* white-box: branch [12-] */
		orcish(test16, sizeof test16);
		orcish(test256, sizeof test256);
		printf("<%s> <%s> <%s> <%s> <%s> <%s>\n", test1, test2, test5, test11,
			test16, test256);
	}

	return EXIT_SUCCESS;
}
