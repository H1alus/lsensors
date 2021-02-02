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

#include "includes.h"
#include "stringList.h"
#include "sens.h"

int main(int argc, char *argv[]) {
    //setting output buffer:
    setlocale(LC_ALL, "en-US");
    //telling to miniLogger to write on file (applog)
    writeOnText = 1;
    //initing sensors:
    if (sensors_init(NULL) != 0) {
        log_fatal(L"can't read sensors");
    }
    //creating a list of all sensors
    sensList *sensed = getAllSensors();
    if(sensed == NULL) {
        log_fatal(L"cant create sensors objects list");
    }
    //creating a list of all sensors names
    list *sensNames = getSensorsNames(sensed);
    if(sensNames == NULL) {
        log_fatal(L"can't create sensors names list");
    }
    //no arguments == print sensors actual values
    if(argc == 1)
        printSensorsValues(sensed, sensNames);
    //list all sensors names
    else if(argc == 2 && strcmp(argv[1], "list") == 0)
        wPrintRawList(sensNames);
    //else error
    else
        log_error(L"error in arguments of sens");
    freeList(sensNames);
    freeSensList(sensed);
    sensors_cleanup();
    return 0;
}