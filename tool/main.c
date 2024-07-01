// SPDX-License-Identifier: Apache-2.0

#include <stdio.h>

#include <glib.h>

#include "aln.h"

#define DEFAULT_COUNT 6
#define DEFAULT_MIN 1
#define DEFAULT_MAX 46
#define DEFAULT_ITERATIONS 5

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

static gint option_count = DEFAULT_COUNT;
static gint option_min = DEFAULT_MIN;
static gint option_max = DEFAULT_MAX;
static gint option_iterations = DEFAULT_ITERATIONS;
static gboolean option_allow_repeat = FALSE;

static GOptionEntry entries[] = {
	{ "count", 'c', G_OPTION_FLAG_NONE, G_OPTION_ARG_INT, &option_count,
	  "The number of lucky numbers to generate", TOSTRING(DEFAULT_COUNT) },
	{ "min", 'n', G_OPTION_FLAG_NONE, G_OPTION_ARG_INT, &option_min,
	  "The minimum value a generated number can be",
	  TOSTRING(DEFAULT_MIN) },
	{ "max", 'x', G_OPTION_FLAG_NONE, G_OPTION_ARG_INT, &option_max,
	  "The maximum value a generated number can be",
	  TOSTRING(DEFAULT_MAX) },
	{ "allow_repeat", 'r', G_OPTION_FLAG_NONE, G_OPTION_ARG_NONE,
	  &option_allow_repeat, "Allows duplicate numbers" },
	{ "iterations", 'i', G_OPTION_FLAG_NONE, G_OPTION_ARG_INT,
	  &option_iterations,
	  "The number of times to run the lucky number generation",
	  TOSTRING(DEFAULT_ITERATIONS) },
	{ NULL }
};

int main(int argc, char *argv[])
{
	GError *error = NULL;
	GOptionContext *context;
	ALN *aln;
	unsigned int i, j;

	context = g_option_context_new("");
	g_option_context_set_summary(
		context, "Amazing lucky number generator application.");
	g_option_context_set_description(
		context,
		"This application generates lucky numbers based on the "
		"provided options.\nYou can specify the count of numbers, "
		"their minimum and maximum values,\nwhether to allow "
		"duplicates, and the number of iterations to run the "
		"generator.");
	g_option_context_add_main_entries(context, entries, NULL);

	if (g_option_context_parse(context, &argc, &argv, &error) == FALSE) {
		if (error != NULL) {
			g_printerr("%s\n", error->message);
			g_error_free(error);
		}

		exit(1);
	}

	g_option_context_free(context);

	if (option_min < 0 || option_max < 0) {
		g_printerr("invalid options\n");
		return -1;
	}

	aln = aln_new(option_count, option_min, option_max,
		      (option_allow_repeat == TRUE) ? 1 : 0);
	if (!aln) {
		g_printerr("aln_new() failed\n");
		return -1;
	}

	for (i = 1; i <= option_iterations; i++) {
		aln_draw_all(aln);

		for (j = 0; j < option_count; j++) {
			printf("%02d", aln_get_number(aln, j));
			if (j < option_count - 1)
				printf(" ");
		}

		printf("\n");

		aln_reset(aln);
	}

	aln_free(aln);

	return 0;
}
