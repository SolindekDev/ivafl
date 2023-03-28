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

#include <ivafl_utils.h>
#include <ivafl_alloc.h>
#include <ivafl_log.h>

#include <stdlib.h>

/* 
 * Function for reallocating memory at given pointer.
 * Basically it can grow size of our allocation. If 
 * return equals NULL ((void*)0) then allocating 
 * failed
*/
void* 
__ivafl_realloc(const void* ptr, size_t nsize)
{ 
    void* allocated_ptr = realloc((void*)ptr, nsize);
    if (allocated_ptr == ivafl_NULL)
        ivafl_logf("(__ivafl_realloc) Couldn't reallocate %lu bytes", nsize);

    return allocated_ptr;
}

/*
 * Easier allocating that does simple math (n * size)
 * that does call malloc to allocate memory. If return 
 * equals NULL ((void*)0) then allocating failed
 */
void* 
__ivafl_calloc(int n, size_t size)
{ 
    void* allocated_ptr = calloc(n, size);
    if (allocated_ptr == ivafl_NULL)
        ivafl_logf("(__ivafl_calloc) Couldn't allocate %lu bytes", size);

    return allocated_ptr;
}

/*
 * Allocating given amount of bytes. If return equals
 * NULL ((void*)0) then allocating failed
 */
void* 
__ivafl_malloc(size_t size)
{ 
    void* allocated_ptr = malloc(size);
    if (allocated_ptr == ivafl_NULL)
        ivafl_logf("(__ivafl_malloc) Couldn't allocate %lu bytes", size);

    return allocated_ptr;
}

/*
 * Free allocated memory at given pointer.
 */
void 
__ivafl_free(const void* ptr)
{
    free((void*)ptr);
}