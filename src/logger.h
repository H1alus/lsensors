/*
* Copyright (c) 2020 Vittorio Folino
*
* This file is part of lsensors.
*
* lsensors is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
* 
* lsensors is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.

* You should have received a copy of the GNU General Public License
* along with lsensors.  If not, see <http://www.gnu.org/licenses/>.
*/

/*
 * Copyright (c) 2020 Vittorio Folino
 * 
 * This file is part of miniLogger.
 * 
 * miniLogger is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * miniLogger is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with miniLogger.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#define MAX_NAME_SIZE 1000

extern unsigned int debug;
extern unsigned int writeOnText;
extern char applog[MAX_NAME_SIZE];

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <stdint.h>
#include <time.h>
#include <stdarg.h>
#include <string.h>
#include <locale.h>

int log_info(const wchar_t *message, ...);
int log_error(const wchar_t *message, ...);
void log_fatal(const wchar_t *message, ...);
int log_debug(const wchar_t *message, ...);
int log_normal(const wchar_t *message, ...);
#endif
