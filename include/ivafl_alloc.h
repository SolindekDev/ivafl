/*
 *   ivafl - Image, Video, Aufio formats library
 *   Copyright (C) 2023 SolindekDev
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef __ivafl_ALLOC_H
#define __ivafl_ALLOC_H

#include "ivafl_platform.h"
#include "ivafl_utils.h"

/* 
 * Function for reallocating memory at given pointer.
 * Basically it can grow size of our allocation. If 
 * return equals NULL ((void*)0) then allocating 
 * failed
*/
void* __ivafl_realloc(const void* ptr, size_t nsize);

/*
 * Easier allocating that does simple math (n * size)
 * that does call malloc to allocate memory. If return 
 * equals NULL ((void*)0) then allocating failed
 */
void* __ivafl_calloc(int n, size_t size);

/*
 * Allocating given amount of bytes. If return equals
 * NULL ((void*)0) then allocating failed
 */
void* __ivafl_malloc(size_t size);

/*
 * Free allocated memory at given pointer.
 */
void __ivafl_free(const void* ptr);

/*
 * Binding for memory allocation functions
 */
#define ivafl_realloc(ptr, ns)  __ivafl_calloc((const void*)ptr, (size_t)ns)
#define ivafl_malloc(size)      __ivafl_malloc((size_t)size)
#define ivafl_calloc(n, size)   __ivafl_calloc((int)n, (size_t)size)
#define ivafl_free(ptr)         __ivafl_free((const void*)ptr)

#endif /* __ivafl_ALLOC_H */