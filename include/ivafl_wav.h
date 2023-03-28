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

/*
 * These pages helped me a lot while writing wav decoder and encoder
 *  - https://docs.fileformat.com/audio/wav/
 *  - http://www.topherlee.com/software/pcm-tut-wavformat.html
*/

#ifndef __ivafl_WAV_H
#define __ivafl_WAV_H

#include <ivafl_utils.h>

#include <stdio.h>

/*
 * ----------------------
 *     Wav structure
 * ----------------------
 */

/*
 * Wav Calculate macros
 */

#define WAV_BYTES_SEC_CALCULATE(sample_rate, bits_per_sample, channels)       \
                          (sample_rate * bits_per_sample * channels) / 8      \

#define WAV_BLOCK_ALIGN_CALCULATE(bits_per_sample, channels)     \
                          (bits_per_sample * channels) / 8       \

/*
 * WAV Channels
 */
#define WAV_MONO_CHANNLES   (unsigned short)0x01
#define WAV_STEREO_CHANNELS (unsigned short)0x02

/* 
 * RIFF Magic is a field with which we can be 100% certain
 * that file that we are reading is a wav
 */

#define __RIFF_MAGIC         'R', 'I', 'F', 'F'
#define __FORMAT_CHUNK_MAGIC 'f', 'm', 't', ' '
#define __FILE_HEADER        'W', 'A', 'V', 'E'
#define __DATA_START         'd', 'a', 't', 'a'

static const unsigned char RIFF_MAGIC[4] = { __RIFF_MAGIC };

/* 
 * This header does take the most important informations about
 * the wav file
 */
typedef struct ivafl_wav_header_info_t {
    unsigned char  riff_magic[4];
    unsigned int   file_size;
    unsigned char  file_header[4];
    unsigned char  format_chunk[4];
    unsigned int   length_format_data;
    unsigned short type_format;
    unsigned short channels_number;
    unsigned int   sample_rate;
    unsigned int   bytes_sec;
    unsigned short block_align;
    unsigned short bits_per_sample;
    unsigned char  data_start[4];
    unsigned int   data_section_length;
} ivafl_wav_header_info_t;

/*
 * Look of a wav file
 *   0  - 44  : wav header
 *   44 - ... : wav data
 */
typedef struct ivafl_wav_header_t {
    ivafl_wav_header_info_t* wav_header_info;
    unsigned char*           wav_data_section;
    void*                    wav_allocated_bytes;
} ivafl_wav_header_t;

/*
 * ----------------------
 *        Decode
 * ----------------------
 */

/*
 * Function `ivafl_create_wav` does create a wav structure
 * that can be written to a file by `ivafl_write_wav_file`
 * function
 */
ivafl_wav_header_t* ivafl_create_wav(unsigned short channels, 
                                     unsigned int sample_rate,
                                     unsigned int bits_per_sample,
                                     unsigned char* wav_data,
                                     unsigned long wav_data_len);

/*
 * ----------------------
 *        Encode
 * ----------------------
 */

/*
 * The `ivafl_is_file_wav` function does take one argument which
 * is `FILE*` that is pointer from file structure. This function
 * does take first 4 bytes and look are they are equal to `'RIFF'`
 * (`RIFF_MAGIC` constant defined in `ivafl_wav.h`) which is always
 * the start of WAV file. If the file is WAV then this function will
 * return `0` on success and `-1` on error
 */
int ivafl_is_file_wav(ivafl_wav_header_t* wav_header);

/* 
 * Function `ivafl_parse_file_into_wav` does take one argument which
 * is `FILE*` that is pointer from file structure. Function does parse
 * whole file into wav_header (`ivafl_wav_header_t` structure). Structure
 * `ivafl_wav_header_t` does have every information about wav file.
 */
ivafl_wav_header_t* ivafl_parse_file_into_wav_header(FILE* f);

/*
 * The `ivafl_wav_clean` does clean up allocated memory for `ivafl_wav_header_t*`
 * structure
 */
void ivafl_wav_clean(ivafl_wav_header_t* wav_header);

/*
 * The `ivafl_wav_get_file_length_ms` does take `ivafl_wav_header_t`
 * structure which defines all informations about wav file. Function
 * will return file length in miliseconds
 */
long ivafl_wav_get_file_length_ms(ivafl_wav_header_t* wav_header);

/*
 * The `ivafl_wav_get_file_length_sec` does take `ivafl_wav_header_t`
 * structure which defines all informations about wav file. Function
 * will return file length in seconds
 */
double ivafl_wav_get_file_length_sec(ivafl_wav_header_t* wav_header);

 #endif /* __ivafl_WAV_H */