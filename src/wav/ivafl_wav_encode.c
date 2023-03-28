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

#include <ivafl_wav.h>
#include <ivafl_alloc.h>
#include <ivafl_utils.h>

#include <string.h>

/*
 * The `ivafl_is_file_wav` function does take one argument which
 * is `FILE*` that is pointer from file structure. This function
 * does take first 4 bytes and look are they are equal to `'RIFF'`
 * (`RIFF_MAGIC` constant defined in `ivafl_wav.h`) which is always
 * the start of WAV file. If the file is WAV then this function will
 * return `0` on success and `-1` on error
 */
int 
ivafl_is_file_wav(ivafl_wav_header_t* wav_header)
{
    if (memcmp(wav_header->wav_header_info->riff_magic, RIFF_MAGIC, 4) != 0) 
    {
        // error
        return -1;
    }

    // success
    return 0;
}

/* 
 * Function `ivafl_parse_file_into_wav` does take one argument which
 * is `FILE*` that is pointer from file structure. Function does parse
 * whole file into wav_header (`ivafl_wav_header_t` structure). Structure
 * `ivafl_wav_header_t` does have every information about wav file.
 */
ivafl_wav_header_t*
ivafl_parse_file_into_wav_header(FILE* f)
{
    unsigned char* bytes = ivafl_read_bytes_from_file(f);

    ivafl_wav_header_t* wav_header_info  = (ivafl_wav_header_t*)ivafl_malloc(sizeof(ivafl_wav_header_t));
    wav_header_info->wav_header_info     = ((ivafl_wav_header_info_t*)bytes);
    wav_header_info->wav_data_section    = ((unsigned char*)(bytes + sizeof(ivafl_wav_header_info_t)));
    wav_header_info->wav_allocated_bytes = ((void*)bytes);

    return wav_header_info;
}

/*
 * The `ivafl_wav_clean` does clean up allocated memory for `ivafl_wav_header_t*`
 * structure
 */
void
ivafl_wav_clean(ivafl_wav_header_t* wav_header) 
{
    ivafl_free(wav_header->wav_allocated_bytes);
    ivafl_free(wav_header);
}

/*
 * The `ivafl_wav_get_file_length_ms` does take `ivafl_wav_header_t`
 * structure which defines all informations about wav file. Function
 * will return file length in miliseconds
 */
long ivafl_wav_get_file_length_ms(ivafl_wav_header_t* wav_header)
{
    return (ivafl_wav_get_file_length_sec(wav_header)) * 1000;
}

/*
 * The `ivafl_wav_get_file_length_sec` does take `ivafl_wav_header_t`
 * structure which defines all informations about wav file. Function
 * will return file length in seconds
 */
double ivafl_wav_get_file_length_sec(ivafl_wav_header_t* wav_header)
{
    return ((double)wav_header->wav_header_info->data_section_length / wav_header->wav_header_info->bytes_sec);
}