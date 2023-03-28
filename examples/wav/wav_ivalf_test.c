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

#include <stdlib.h>
#include <stdio.h>

int 
main(int argc, char** argv) 
{
    printf("Testing ivafl wav library.\n");
    printf("First function: ivafl_is_file_wav\n");

    FILE* f = fopen("PinkPanther30.wav", "rb");
    if (f == NULL) 
    {
        printf("File doesn't exists\n");
        return EXIT_FAILURE;
    }

    ivafl_wav_header_t* wav_header = ivafl_parse_file_into_wav_header(f);

    if (ivafl_is_file_wav(wav_header) == 0) 
        printf("`PinkPanther30.wav` is a wav file\n");
    else 
    {
        printf("`PinkPanther30.wav` isn't a wav file\n");
        return EXIT_FAILURE;
    }

    printf("riff: %.4s\n", wav_header->wav_header_info->riff_magic);
    printf("bytes_sec: %u\n", wav_header->wav_header_info->bytes_sec);
    printf("bytes_sec: %u\n", wav_header->wav_header_info->length_format_data);
    printf("length ms: %lu\n", ivafl_wav_get_file_length_ms(wav_header));
    printf("length sec: %.2f\n", ivafl_wav_get_file_length_sec(wav_header));
}