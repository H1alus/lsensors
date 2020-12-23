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

#ifndef SENS_H_
#define SENS_H_

#include "includes.h"
#include "stringList.h"

#define MAX_SENS_SIZE 100

//nested linked list types for sensors
struct subfeaturesList {
    const sensors_subfeature *subfeature;
    struct subfeaturesList *next;
};

typedef struct subfeaturesList subfeaturesList; 

struct featuresList {
    const sensors_feature *feature;
    subfeaturesList *subfeatures;
    struct featuresList *next;
};

typedef struct featuresList featuresList;

struct sensList{
    const sensors_chip_name *name;
    featuresList *features;
    struct sensList *next;
};

typedef struct sensList sensList;

//get a string list of sensors names
list *getSensorsNames();

//get all sensors
sensList *getAllSensors();

// print sensors values
void printSensorsValues(sensList *sensors, list *sensNames);
/*
free allocated memory for a sensList.
You still need to call sensors_cleanup() to free all sensors objects
*/
void freeSensList(sensList *list);


#endif