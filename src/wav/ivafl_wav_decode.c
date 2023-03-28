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
 * Function `ivafl_create_wav` does create a wav structure
 * that can be written to a file by `ivafl_write_wav_file`
 * function
 */
ivafl_wav_header_t*
ivafl_create_wav(unsigned short channels, 
                 unsigned int sample_rate,
                 unsigned int bits_per_sample,
                 unsigned char* wav_data,
                 unsigned long wav_data_len)
{
    ivafl_wav_header_t* wav_header          = (ivafl_wav_header_t*)ivafl_malloc(sizeof(ivafl_wav_header_t));
    ivafl_wav_header_info_t wav_header_info = {
        .riff_magic          = { __RIFF_MAGIC },
        .file_size           = wav_data_len + sizeof(ivafl_wav_header_info_t), // I'm not sure is this a correct way
        .file_header         = { __FILE_HEADER  },
        .format_chunk        = { __FORMAT_CHUNK_MAGIC },
        .length_format_data  = 16,
        .type_format         = 1,
        .channels_number     = channels,       
        .sample_rate         = sample_rate,
        .bytes_sec           = WAV_BYTES_SEC_CALCULATE(sample_rate, bits_per_sample, channels),
        .block_align         = WAV_BLOCK_ALIGN_CALCULATE(bits_per_sample, channels),
        .bits_per_sample     = bits_per_sample,
        .data_start          = { __DATA_START },
        .data_section_length = wav_data_len
    };

    wav_header->wav_header_info     = &wav_header_info;
    wav_header->wav_allocated_bytes = NULL;
    wav_header->wav_data_section    = wav_data;

    return wav_header;
}