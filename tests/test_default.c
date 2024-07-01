// SPDX-License-Identifier: Apache-2.0

#include <stdio.h>

#include <glib.h>

#include "aln.h"

static void test_aln_kor(void)
{
	ALN *aln;
	unsigned int num;

	g_assert(aln_new(6, 46, 1, 0) == NULL);

	aln = aln_new(6, 1, 46, 0);
	g_assert(aln != NULL);

	g_assert(aln_get_number(aln, 0) == 0);
	g_assert(aln_get_number(aln, 1) == 0);
	g_assert(aln_get_number(aln, 2) == 0);
	g_assert(aln_get_number(aln, 3) == 0);
	g_assert(aln_get_number(aln, 4) == 0);
	g_assert(aln_get_number(aln, 5) == 0);
	g_assert(aln_get_number(aln, 6) == 0);

	/* Draw all at once */
	g_assert(aln_draw_all(aln) == 0);

	g_assert(aln_get_number(aln, 0) != 0);
	g_assert(aln_get_number(aln, 1) != 0);
	g_assert(aln_get_number(aln, 2) != 0);
	g_assert(aln_get_number(aln, 3) != 0);
	g_assert(aln_get_number(aln, 4) != 0);
	g_assert(aln_get_number(aln, 5) != 0);
	g_assert(aln_get_number(aln, 6) == 0);

	/* Numbers must not be repeated. */
	g_assert(aln_get_number(aln, 0) != aln_get_number(aln, 1));
	g_assert(aln_get_number(aln, 0) != aln_get_number(aln, 2));
	g_assert(aln_get_number(aln, 0) != aln_get_number(aln, 3));
	g_assert(aln_get_number(aln, 0) != aln_get_number(aln, 4));
	g_assert(aln_get_number(aln, 0) != aln_get_number(aln, 5));
	g_assert(aln_get_number(aln, 1) != aln_get_number(aln, 2));
	g_assert(aln_get_number(aln, 1) != aln_get_number(aln, 3));
	g_assert(aln_get_number(aln, 1) != aln_get_number(aln, 4));
	g_assert(aln_get_number(aln, 1) != aln_get_number(aln, 5));
	g_assert(aln_get_number(aln, 2) != aln_get_number(aln, 3));
	g_assert(aln_get_number(aln, 2) != aln_get_number(aln, 4));
	g_assert(aln_get_number(aln, 2) != aln_get_number(aln, 5));
	g_assert(aln_get_number(aln, 3) != aln_get_number(aln, 4));
	g_assert(aln_get_number(aln, 3) != aln_get_number(aln, 5));
	g_assert(aln_get_number(aln, 4) != aln_get_number(aln, 5));

	aln_reset(aln);

	g_assert(aln_get_number(aln, 0) == 0);
	g_assert(aln_get_number(aln, 1) == 0);
	g_assert(aln_get_number(aln, 2) == 0);
	g_assert(aln_get_number(aln, 3) == 0);
	g_assert(aln_get_number(aln, 4) == 0);
	g_assert(aln_get_number(aln, 5) == 0);
	g_assert(aln_get_number(aln, 6) == 0);

	/* Draw one by one */
	g_assert(aln_draw_number(aln, &num) == 0);
	g_assert(num == aln_get_number(aln, 0));

	g_assert(aln_draw_number(aln, &num) == 0);
	g_assert(num == aln_get_number(aln, 1));

	g_assert(aln_draw_number(aln, &num) == 0);
	g_assert(num == aln_get_number(aln, 2));

	g_assert(aln_draw_number(aln, &num) == 0);
	g_assert(num == aln_get_number(aln, 3));

	g_assert(aln_draw_number(aln, &num) == 0);
	g_assert(num == aln_get_number(aln, 4));

	g_assert(aln_draw_number(aln, &num) == 0);
	g_assert(num == aln_get_number(aln, 5));

	g_assert(aln_draw_number(aln, &num) == -1);
	g_assert(num == 0);

	aln_free(aln);
}

static void test_aln_default(void)
{
	ALN *aln;

	/* count > 0 */
	g_assert(aln_new(0, 0, 0, 0) == NULL);

	/* min < max */
	g_assert(aln_new(1, 0, 0, 0) == NULL);
	g_assert(aln_new(1, 1, 0, 0) == NULL);

	/* allow_repeat == 0 or 1 */
	g_assert(aln_new(1, 0, 1, -1) == NULL);
	g_assert(aln_new(1, 0, 1, 2) == NULL);

	/* If repetition is not allowed and the desired number range is 0 ~ 1,
	   the 'count' cannot be greater than 2 */
	g_assert(aln_new(3, 0, 1, 0) == NULL);

	/* If repetition is allowed in the above situation,
	   a number that is repeated at least once is generated */
	aln = aln_new(3, 0, 1, 1);
	g_assert(aln != NULL);
	g_assert(aln_draw_all(aln) == 0);
	g_assert(aln_get_number(aln, 0) == aln_get_number(aln, 1) ||
		 aln_get_number(aln, 1) == aln_get_number(aln, 2) ||
		 aln_get_number(aln, 2) == aln_get_number(aln, 0));
	aln_free(aln);

	/* New ALN object with 1 digit, number range 1~2, not allow repeat */
	aln = aln_new(1, 1, 2, 0);
	g_assert(aln != NULL);

	/* Not yet drawn */
	g_assert(aln_get_number(aln, 0) == 0);
	g_assert(aln_get_number(aln, 1) == 0);

	/* Draw all at once */
	g_assert(aln_draw_all(aln) == 0);

	/* The draw has already been completed */
	g_assert(aln_draw_number(aln, NULL) == -1);

	/* Only the first data is valid */
	g_assert(aln_get_number(aln, 0) != 0);
	g_assert(aln_get_number(aln, 0) >= 1);
	g_assert(aln_get_number(aln, 0) <= 2);
	g_assert(aln_get_number(aln, 1) == 0);

	aln_reset(aln);

	/* Draw one by one */
	g_assert(aln_draw_number(aln, NULL) == 0);
	g_assert(aln_draw_number(aln, NULL) == -1);

	g_assert(aln_get_number(aln, 0) != 0);
	g_assert(aln_get_number(aln, 0) >= 1);
	g_assert(aln_get_number(aln, 0) <= 2);
	g_assert(aln_get_number(aln, 1) == 0);

	aln_free(aln);
}

int main(int argc, char *argv[])
{
#if !GLIB_CHECK_VERSION(2, 36, 0)
	g_type_init();
#endif

	g_test_init(&argc, &argv, NULL);
	g_log_set_always_fatal((GLogLevelFlags)G_LOG_FATAL_MASK);

	g_test_add_func("/aln/default", test_aln_default);
	g_test_add_func("/aln/kor", test_aln_kor);

	return g_test_run();
}
