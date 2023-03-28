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
#include <stdio.h>

#define ivafl_DEFAULT_BYTES_FOPEN_MODE ("rb")

/*
 * This function does read given file and return
 * `unsigned char*` (array of bytes) that then can 
 * be used to for example parse wav file or other 
 * format
 */
unsigned char*
ivafl_read_bytes(const char* filename)
{
    FILE* f = fopen(filename, ivafl_DEFAULT_BYTES_FOPEN_MODE);
    if (f == ivafl_NULL)
    {
        ivafl_logf("(ivafl_read_bytes) Failed while opening `%s` file", filename);
        exit(EXIT_FAILURE);
    }

    unsigned char* bytes = ivafl_read_bytes_from_file(f);
    fclose(f);

    return bytes;
}

/*
 * This function does read given `FILE*` structure
 * that need to be opened with `"rb"` mode. Function
 * does return unsigned char* (array of bytes) that 
 * then can be used to for example parse wav file 
 * or other format
 */
unsigned char*
ivafl_read_bytes_from_file(FILE* f)
{
    if (f == ivafl_NULL)
    {
        ivafl_logf("(ivafl_read_bytes_from_file) Failed given file is `NULL`");
        exit(EXIT_FAILURE);
    }

    size_t file_len      = ivafl_get_size_file(f);
    unsigned char* bytes = ivafl_malloc((sizeof(unsigned char) * file_len) + 1);
    char curr_char       = 'A';

    for (size_t i = 0; i < file_len; i++) 
    {
        curr_char = fgetc(f);
        bytes[i]  = curr_char;
    }

    return bytes;
}

/*
 * The `ivafl_get_size_file` function does return `size_t`
 * that indicates the given `FILE*` structure content length
 */
size_t
ivafl_get_size_file(FILE* f)
{
    if (f == ivafl_NULL)
    {
        ivafl_logf("(ivafl_get_size_file) Failed given file is `NULL`");
        exit(EXIT_FAILURE);
    }

    fseek(f, 0, SEEK_END);
    size_t len = ftell(f);
    fseek(f, 0, SEEK_SET);

    return len;
}