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

#include "sens.h"

list *getSensorsNames(sensList *sensors) {
    list *sensorsList = initList();
    if (sensorsList  == NULL)
        return NULL;
    char chipName[MAX_LEN];
    while (sensors != NULL) {
        if (sensors_snprintf_chip_name(chipName, MAX_LEN, sensors->name) < 0) {
            return NULL;
        } else if (addNode(sensorsList, chipName)) {
            return NULL;
        }
        sensors = sensors->next;
    }
    return sensorsList;
}

subfeaturesList 
*getAllSubfeatures(const sensors_chip_name *name, 
                const sensors_feature *feature) {

    int nr = 0;
    subfeaturesList *outList;
    subfeaturesList *start = NULL;
    const sensors_subfeature *subfeature = sensors_get_all_subfeatures(name, feature, &nr);
    if(subfeature != NULL) {
        outList = (subfeaturesList *) malloc(sizeof(subfeaturesList));
            if(outList == NULL)
                return NULL;
        start = outList;
    }
    while(subfeature != NULL) {
        outList->subfeature = subfeature;
        subfeature = sensors_get_all_subfeatures(name, feature, &nr);
        if(subfeature != NULL) {
            outList->next = (subfeaturesList *) malloc(sizeof(subfeaturesList));
            outList = outList->next;
            if(outList == NULL)
                return NULL;
        }
    }
    outList->next = NULL;
    return start;
}

featuresList *getAllFeatures(const sensors_chip_name *name) { 
    int nr = 0;
    featuresList *outList;
    featuresList *start = NULL;
    const sensors_feature *feature = sensors_get_features(name, &nr);
    if(feature != NULL) {
        outList = (featuresList *) malloc(sizeof(featuresList));
        if(outList == NULL)
            return NULL;
        start = outList;
    }
    while(feature != NULL) {
        outList->feature = feature;
        outList->subfeatures = getAllSubfeatures(name, feature);
        feature = sensors_get_features(name, &nr);
        if (feature != NULL) {
            outList->next = (featuresList *) malloc(sizeof(featuresList));
            outList = outList->next;
            if(outList == NULL)
                return NULL;
        }
    }
    outList->next = NULL;
    return start;
}

sensList *getAllSensors() {
    int nr = 0;
    sensList *sensorsList;
    sensList *start = NULL;
    const sensors_chip_name *name = sensors_get_detected_chips(NULL, &nr);
    if(name != NULL) {
        sensorsList = (sensList *) malloc(sizeof(sensList));
        if(sensorsList == NULL)
            return NULL;
        start = sensorsList;
    }
    while(name != NULL) {
        sensorsList->name = name;
        sensorsList->features = getAllFeatures(name);
        name = sensors_get_detected_chips(NULL, &nr);
        if(name != NULL) {
            sensorsList->next = (sensList *) malloc(sizeof(sensList));
            sensorsList = sensorsList->next;
            if(sensorsList == NULL) {
                return NULL;
            }
        }
    }
    sensorsList->next = NULL;
    return start;
}

int hasFeatureTemp(featuresList *features) {
    while(features != NULL) {
        if(features->feature->type == SENSORS_FEATURE_TEMP) {
            return 1;
        }
        features = features->next;
    }
    return 0;
}

void printSensorsValues(sensList *sensors, list *sensNames) {
    featuresList *features;
    subfeaturesList *subfeatures;
    int subfeat_nr;
    double value;
    wprintf(L"{");
	while(sensors != NULL) {
		wprintf(L"\n\t\"%s\": {", sensNames->string);
        sensNames = sensNames->next;
        features = sensors->features;
        
        while(features != NULL) {
            char *featureName = sensors_get_label(sensors->name, features->feature);
            wprintf(L"\n\t\t\"%s\": {", featureName);
            subfeatures = features->subfeatures;
            
            while(subfeatures != NULL) {
                subfeat_nr = subfeatures->subfeature->number;
                sensors_get_value(sensors->name, subfeat_nr, &value);
                wprintf(L"\n\t\t\t\"%s\": %lf", subfeatures->subfeature->name, value);
                if (subfeatures->next != NULL) {
                    wprintf(L",");
                }
                subfeatures = subfeatures->next;
            }
            wprintf(L"\n\t\t}");
            if (features->next != NULL) {
                wprintf(L",");
            }
            features = features->next;
            free(featureName);
        }
        wprintf(L"\n\t}");
        if(sensors->next != NULL) {
            wprintf(L",");
        }
        sensors = sensors->next;
	}
    wprintf(L"\n}\n");
}

void freeSubfeaturesList(subfeaturesList *list) {
    subfeaturesList *next;
    while(list != NULL) {
        next = list->next;
        free(list);
        list = next;
    }
}

void freeFeaturesList(featuresList *list) {
    featuresList *next;
    while(list != NULL) {
        next = list->next;
        freeSubfeaturesList(list ->subfeatures);
        free(list);
        list = next;
    }
}

void freeSensList(sensList *list) {
    sensList *next;
    while(list != NULL) {
        next = list->next;
        freeFeaturesList(list->features);
        free(list);
        list = next;
    }
}