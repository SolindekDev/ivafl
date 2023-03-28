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

#ifndef __ivafl_UTILS_H
#define __ivafl_UTILS_H

typedef long unsigned int size_t;

#define ivafl_NULL ((void*)0)

#include <stdio.h>

/*
 * This function does read given file and return
 * unsigned char* (array of bytes) that then can 
 * be used to for example parse wav file or other 
 * format
 */
unsigned char* ivafl_read_bytes(const char* filename);

/*
 * This function does read given FILE* structure
 * that need to be opened with "rb" mode. Function
 * does return unsigned char* (array of bytes) that 
 * then can  be used to for example parse wav file 
 * or other format
 */
unsigned char* ivafl_read_bytes_from_file(FILE* f);

/*
 * The `ivafl_get_size_file` function does return `size_t`
 * that indicates the given `FILE*` structure content length
 */
size_t ivafl_get_size_file(FILE* f);

#endif /* __ivafl_UTILS_H */