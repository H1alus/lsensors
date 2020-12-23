#    Copyright (c) 2020 Vittorio Folino
#
#    This file is part of lsensors.
# 
#    lsensors is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    lsensors is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with lsensors.  If not, see <http://www.gnu.org/licenses/>.

import os
import json
import time
from datetime import datetime

PRINT_BOUND = 60

def getTime():
    now = datetime.now()
    timestamp = int(datetime.timestamp(now))
    return datetime.fromtimestamp(timestamp)

class Sensors:

    def __init__(self, wd, settings: dict):
        sensBin = os.path.join('bin', 'sens')
        self.sens = os.path.join(wd, sensBin)

        self.settings = settings
        self.samplingTime = settings["samplingTime"]
        if len(self.settings["sensorsList"]) == 0:
            self.updateSensors()
        else:
            self.sensorsList = settings["sensorsList"]
            self.sensors = settings["sensors"]

    def __updateSensorsList(self):
        outSens = os.popen(self.sens + ' list')
        self.sensorsList = outSens.readlines()
        self.sensorsList = [i.strip() for i in self.sensorsList]
        outSens.close()

    def rawOutput(self):
        outSens = os.popen(self.sens)
        sample = outSens.read()
        outSens.close()
        return sample
    
    def updateSensors(self):
        sensors = json.loads(self.rawOutput())
        self.__updateSensorsList()
        for sens in self.sensorsList:
            features = list(sensors[sens].keys())
            for feature in features:
                subfeatures = list(sensors[sens][feature])
                for subfeature in subfeatures:
                    sensors[sens][feature][subfeature] = False
        self.sensors = sensors
        self.settings["sensorsList"] = self.sensorsList
        self.settings["sensors"] = sensors
        return self.settings

    def __genValue(self, sensor, feature, subfeature):
        while True:
            out = json.loads(self.rawOutput())
            yield out[sensor][feature][subfeature]

    def getGens(self):
        gens = dict()
        for sensor in self.sensors.keys():
            for feature in self.sensors[sensor].keys():
                for subfeat in self.sensors[sensor][feature].keys():
                    if self.sensors[sensor][feature][subfeat]:
                        key = sensor + ' ' + feature + ' ' + subfeat + ':\t'
                        gens[key] = self.__genValue(sensor, feature, subfeat)
        return gens
    
    def print(self, sensor, feature, subfeature):
        while True:
            values = self.__genValue(sensor, feature, subfeature)
            print(next(values))
            time.sleep(self.samplingTime)
    
    def printAll(self):
        gens = self.getGens()
        while True:
            [print('-', end='') for i in range(0, PRINT_BOUND)]
            print()
            for sensor in gens.keys():
                print(sensor, next(gens[sensor]), ' °C')
            [print('-', end='') for i in range(0, PRINT_BOUND)]
            print()
            time.sleep(self.samplingTime)
    
    def logAll(self):
        logFolder = self.settings["logFolder"]
        filePath = os.path.join(logFolder, 'thermals.log')
        gens = self.getGens()
        while True:
            fp = open(filePath, 'a')
            [fp.write('-') for i in range(0, PRINT_BOUND)]
            fp.write('\n')
            fp.write(str(getTime()) + '\n')
            for sensor in gens.keys():
                fp.write(sensor + str(next(gens[sensor])) + '\t°C'+'\n')
            [fp.write('-') for i in range(0, PRINT_BOUND)]
            fp.write('\n')
            time.sleep(self.samplingTime)
            fp.close()
