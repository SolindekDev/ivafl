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

#ifndef __ivafl_LOG_H
#define __ivafl_LOG_H

#include "ivafl_platform.h"

/*
 * The ivafl_logf does print log that shows in the console.
 * logs are for developer to know where's the error. ivafl_logf
 * uses c format to give additional informations
 */
void ivafl_logf(const char* fmt, ...);

#endif /* __ivafl_LOG_H */