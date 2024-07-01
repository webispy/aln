// SPDX-License-Identifier: Apache-2.0

#include <glib.h>

#include "aln.h"

struct _ALN {
	unsigned int pos;
	unsigned int count;
	unsigned int min;
	unsigned int range;
	int allow_repeat;

	unsigned int *table;
	unsigned int *result;
};

ALN *aln_new(unsigned int count, unsigned int min, unsigned int max,
	     int allow_repeat)
{
	ALN *aln;

	g_return_val_if_fail(count > 0, NULL);
	g_return_val_if_fail(min < max, NULL);
	g_return_val_if_fail(allow_repeat == 0 || allow_repeat == 1, NULL);

	if (allow_repeat == 0 && count > max - min + 1) {
		g_return_if_fail_warning(G_LOG_DOMAIN, G_STRFUNC,
					 "count > max - min + 1");
		return NULL;
	}

	aln = g_new0(ALN, 1);
	if (!aln)
		return NULL;

	aln->allow_repeat = allow_repeat;
	aln->count = count;
	aln->min = min;
	aln->range = max - min + 1;

	aln->result = g_new0(unsigned int, count);
	if (!aln->result) {
		g_free(aln);
		return NULL;
	}

	aln->table = g_new0(unsigned int, aln->range + 1);
	if (!aln->table) {
		g_free(aln->result);
		g_free(aln);
		return NULL;
	}

	g_random_set_seed(time(NULL));
	aln_reset(aln);

	return aln;
}

void aln_free(ALN *aln)
{
	g_return_if_fail(aln != NULL);

	g_free(aln->result);
	g_free(aln->table);
	g_free(aln);
}

void aln_reset(ALN *aln)
{
	unsigned int i;

	aln->pos = 0;

	/* Reset table to (min ~ max) numbers */
	for (i = 0; i < aln->range; i++)
		aln->table[i] = aln->min + i;

	/* Reset result */
	for (i = 0; i < aln->count; i++)
		aln->result[i] = 0;
}

int aln_draw_number(ALN *aln, unsigned int *number)
{
	unsigned int num;
	unsigned int range;

	g_return_val_if_fail(aln != NULL, -1);

	/* Select the nth random number from the remaining range */
	range = aln->range;
	if (!aln->allow_repeat)
		range = aln->range - aln->pos;

	/* invalid state */
	if (aln->pos >= aln->count || range == 0) {
		if (number)
			*number = 0;

		return -1;
	}

	num = g_random_int() % range;
	aln->result[aln->pos] = aln->table[num];

	if (!aln->allow_repeat) {
		unsigned int j;

		/* Shift to left the table */
		for (j = num; j < aln->range; j++)
			aln->table[j] = aln->table[j + 1];
	}

	if (number)
		*number = aln->result[aln->pos];

	aln->pos++;

	return 0;
}

int aln_draw_all(ALN *aln)
{
	unsigned int i;

	g_return_val_if_fail(aln != NULL, -1);

	for (i = aln->pos; i < aln->count; i++) {
		if (aln_draw_number(aln, NULL) < 0)
			break;
	}

	return 0;
}

unsigned int aln_get_number(const ALN *aln, unsigned int index)
{
	g_return_val_if_fail(aln != NULL, 0);
	g_return_val_if_fail(index < aln->count, 0);

	return aln->result[index];
}
