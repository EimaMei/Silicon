/*
Copyright (C) 2022-2023 EimaMei/Sacode

This software is provided 'as-is', without any express or implied
warranty.  In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/

#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>


/* Silicon array type. */
typedef void** siArray;

/* Header for the array. */
typedef struct siArrayHeader {
	size_t capacity;
} siArrayHeader;

#define SI_ARRAY_HEADER(s) ((siArrayHeader*)s - 1)


/* Initializes a Silicon array. */
siArray si_array_init(size_t capacity);
/* Initializes a Silicon array, with its content being replaced with the provided array. */
siArray si_array_init_with_array(void** array, size_t element_count, size_t sizeof_array);
/* Initializes a Silicon array, with its content being copied into from the provided array. */
siArray si_array_copy_from_array(void* array, size_t element_count, size_t sizeof_array);
/* Gets the length of the array. */
size_t si_array_len(siArray array);
/* Frees the array from memory. */
void si_array_free(siArray array);


#ifdef SI_ARRAY_IMPLEMENTATION
#include <stdlib.h>
#include <string.h>


siArray si_array_init(size_t capacity) {
	void* ptr = malloc(sizeof(siArrayHeader) + sizeof(void*) * capacity);

	if (ptr == NULL)
		return NULL;

	siArray res = ptr + sizeof(siArrayHeader);

	siArrayHeader* header = SI_ARRAY_HEADER(res);
	header->capacity = capacity;

	return res;
}


siArray si_array_init_with_array(void** array, size_t element_count, size_t sizeof_array) {
	void* ptr = malloc(sizeof(siArrayHeader) + sizeof_array);

	siArray res = ptr + sizeof(siArrayHeader);
	res = array;

	siArrayHeader* header = SI_ARRAY_HEADER(res);
	header->capacity = element_count;

	return res;
}


siArray si_array_copy_from_array(void* array, size_t element_count, size_t sizeof_array) {
	void* ptr = malloc(sizeof(siArrayHeader) + sizeof_array);
	memcpy(ptr, array, sizeof_array);

	siArray res = ptr + sizeof(siArrayHeader);

	siArrayHeader* header = SI_ARRAY_HEADER(res);
	header->capacity = element_count;

	return res;
}


size_t si_array_len(siArray array) {
	siArrayHeader* header = SI_ARRAY_HEADER(array);
	return header->capacity;
}


void si_array_free(siArray array) {
	if (array == NULL)
		return ;

	free(SI_ARRAY_HEADER(array));
}
#endif

#ifdef __cplusplus
}
#endif