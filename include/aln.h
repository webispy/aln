// SPDX-License-Identifier: Apache-2.0

/**
 * @file aln.h
 * @brief Amazing Lucky Numbers Library API
 *
 * This library provides functions to manage and generate lucky numbers.
 */

#ifndef __ALN_H__
#define __ALN_H__

#if defined(_WIN32)
#define ALN_API_EXPORT __declspec(dllexport)
#define ALN_API_IMPORT __declspec(dllimport)
#else
#define ALN_API_EXPORT __attribute__((visibility("default")))
#define ALN_API_IMPORT
#endif

#ifdef ALN_LIBRARY_BUILD
#define ALN_API ALN_API_EXPORT
#else
#define ALN_API ALN_API_IMPORT
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Opaque structure representing the Amazing Lucky Numbers generator.
 */
typedef struct _ALN ALN;

/**
 * @brief Creates a new ALN instance.
 *
 * This function allocates and initializes a new ALN instance for generating
 * lucky numbers.
 *
 * @param count The number of lucky numbers to generate.
 * @param min The minimum value a generated number can be.
 * @param max The maximum value a generated number can be.
 * @param allow_repeat If 1, allows duplicate numbers; if 0, numbers will be
 *        unique.
 * @return ALN* Pointer to the new ALN instance, or NULL on failure.
 * @see aln_free()
 */
ALN_API ALN *aln_new(unsigned int count, unsigned int min, unsigned int max,
		     int allow_repeat);

/**
 * @brief Frees an ALN instance.
 *
 * This function deallocates an ALN instance created with aln_new.
 *
 * @param aln Pointer to the ALN instance to free.
 * @see aln_new()
 */
ALN_API void aln_free(ALN *aln);

/**
 * @brief Resets an ALN instance.
 *
 * This function resets the state of the ALN instance, allowing numbers to be
 * drawn again.
 *
 * @param aln Pointer to the ALN instance to reset.
 */
ALN_API void aln_reset(ALN *aln);

/**
 * @brief Draws a single lucky number.
 *
 * This function draws a single lucky number from the ALN instance.
 *
 * @param aln Pointer to the ALN instance.
 * @param number Pointer to store the drawn number.
 * @return int Status code indicating success or failure.
 * @retval 0 Successfully drew a number.
 * @retval -1 Failed to draw a number.
 * @see aln_draw_all()
 */
ALN_API int aln_draw_number(ALN *aln, unsigned int *number);

/**
 * @brief Draws all remaining lucky numbers.
 *
 * This function draws all remaining lucky numbers from the ALN instance.
 *
 * @param aln Pointer to the ALN instance.
 * @return int Status code indicating success or failure.
 * @retval 0 Successfully drew all numbers.
 * @retval -1 Failed to draw all numbers.
 * @see aln_draw_number()
 */
ALN_API int aln_draw_all(ALN *aln);

/**
 * @brief Gets a specific lucky number by index.
 *
 * This function retrieves a specific lucky number by its index in the ALN
 * instance. Either aln_draw_number() or aln_draw_all() should be called before
 * calling this function.
 *
 * @param aln Pointer to the ALN instance.
 * @param index The index of the number to retrieve. Index starts from 0.
 * @return unsigned int The lucky number at the specified index.
 * @see aln_draw_number()
 * @see aln_draw_all()
 */
ALN_API unsigned int aln_get_number(const ALN *aln, unsigned int index);

#ifdef __cplusplus
}
#endif

#endif
