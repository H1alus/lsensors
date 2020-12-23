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

#include "logger.h"

unsigned int debug = 0;
unsigned int writeOnText = 0;
char applog[MAX_NAME_SIZE] = "appLog.log\0";

static char *getTimeStamp() { 
	time_t current_time;
	char *time_string = (char *) malloc(sizeof(char)*40);


	current_time = time(NULL);

	if(current_time == (time_t) -1) {
		return NULL;
	}

	if(time_string == NULL) {
		return NULL;
	}

	struct tm *cur_time;
	cur_time = localtime(&current_time);
	strftime(time_string, 40, "%H:%M:%S", cur_time);

	return time_string;
}

int log_info(const wchar_t *message, ...) {

	FILE *fp;
	if(writeOnText == 1) {
		fp = fopen(applog, "a");
		if(fp == NULL)
			return -1;
	}
	else if (writeOnText == 0)
		fp = stdout;

    va_list args;
    va_start(args, message);
	unsigned int lenMessage = wcslen(message);
	char *timeStamp = getTimeStamp();

	if(timeStamp == NULL) {
		if(writeOnText == 1) {
			fflush(fp);
			fclose(fp);
		}
		va_end(args);
		return -1;
	}

	wchar_t fullMessage[lenMessage+100];

	if(writeOnText == 0) {
		swprintf(fullMessage, lenMessage+150, L"\x1b[34m[INFO]\x1b[0m\t%s: %ls\n", timeStamp, message);
		vfwprintf (fp, fullMessage, args);
	}

	else if(writeOnText == 1) {
		swprintf(fullMessage, lenMessage+150, L"[INFO]\t%s: %ls\n", timeStamp, message);
		vfwprintf (fp, fullMessage, args);
		fflush(fp);
		fclose(fp);
	}
	free(timeStamp);
	va_end(args);
	return 0;
}

int log_error(const wchar_t *message, ...) {

	FILE *fp;
	if(writeOnText == 1) {
		fp = fopen(applog, "a");
		if(fp == NULL)
			return -1;
	}
	else if (writeOnText == 0)
		fp = stdout;

    va_list args;
    va_start(args, message);
	unsigned int lenMessage = wcslen(message);
	char *timeStamp = getTimeStamp();

	if(timeStamp == NULL) {
		va_end(args);
		if(writeOnText == 1) {
			fflush(fp);
			fclose(fp);
		}
		return -1;
	}

	wchar_t fullMessage[lenMessage+100];

	if(writeOnText == 0) {
		swprintf(fullMessage, lenMessage+150, L"\x1b[35m[ERROR]\x1b[0m %s: %ls\n", timeStamp, message);
		vfwprintf (fp, fullMessage, args);
	}

	else if (writeOnText == 1) {
		swprintf(fullMessage, lenMessage+150, L"[ERROR]\t%s: %ls\n", timeStamp, message);
		vfwprintf (fp, fullMessage, args);
		fflush(fp);
		fclose(fp);
	}
	free(timeStamp);
	va_end(args);

	return 0;
}

void log_fatal(const wchar_t *message, ...) {

	FILE *fp;
	unsigned int setJump = 0;
	if (writeOnText == 1) {
		fp = fopen(applog, "a");
		if(fp == NULL)
			exit(EXIT_FAILURE);
	}

	else if(writeOnText == 0)
		fp = stdout;


    va_list args;
    va_start(args, message);
	unsigned int lenMessage = wcslen(message);
	char *timeStamp = getTimeStamp();

	if(timeStamp == NULL) {
		if(writeOnText == 1) {
			fflush(fp);
			fclose(fp);
			setJump = 1;
		}
		va_end(args);
	}

	if (setJump == 0) {
		wchar_t fullMessage[lenMessage+100];

		if (writeOnText == 0) {
			swprintf(fullMessage, lenMessage+150, L"\x1b[31m[FATAL]\x1b[0m %s: %ls\n", timeStamp, message);
			vfwprintf (fp, fullMessage, args);
		}

		else if (writeOnText == 1) {
			swprintf(fullMessage, lenMessage+150, L"[FATAL]\t%s: %ls\n", timeStamp, message);
			vfwprintf (fp, fullMessage, args);
			fflush(fp);
			fclose(fp);
		}

		va_end(args);
	}
	free(timeStamp);
	exit(EXIT_FAILURE);
}

int log_debug(const wchar_t *message, ...) {

	if(!debug)
		return 0;

	FILE *fp;
	if(writeOnText == 1) {
		
		fp = fopen(applog, "a");
		if(fp == NULL)
			return -1;
	}

	else if(writeOnText == 0)
		fp = stdout;


    va_list args;
    va_start(args, message);
	unsigned int lenMessage = wcslen(message);
	char *timeStamp = getTimeStamp();

	if(timeStamp == NULL) {
		if(writeOnText == 1) {
			fflush(fp);
			fclose(fp);
		}
		va_end(args);
		return -1;
	}

	wchar_t fullMessage[lenMessage+100];

	if (writeOnText == 0) {
		swprintf(fullMessage, lenMessage+150, L"\x1b[32m[DEBUG]\x1b[0m %s: %ls\n", timeStamp, message);
		vfwprintf (fp, fullMessage, args);
	}

	if(writeOnText == 1) {
		swprintf(fullMessage, lenMessage+150, L"[DEBUG]\t%s: %ls\n", timeStamp, message);
		vfwprintf (fp, fullMessage, args);
		fflush(fp);
		fclose(fp);
	}

	va_end(args);
	free(timeStamp);
	return 0;
}

int log_normal(const wchar_t *message, ...) {

	FILE *fp;
	if(writeOnText == 1) {
		fp = fopen(applog, "a");
		if(fp == NULL) 
			return -1;
	}
	else if (writeOnText == 0)
		fp = stdout;

    va_list args;
    va_start(args, message);
	vfwprintf (fp, message, args);
	va_end(args);

	return 0;
}
