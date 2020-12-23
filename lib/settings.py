#    Copyright (c) 2020 lsensors 
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

import json
import os
import copy
import sys
import shutil
 
CONFIG_DIR = 'etc'
jsonSettings = 'settings.json'
jsonDefaults = '.defaults.json'

class Settings:

    def __init__(self, absRoot): 
        self.__configDir = os.path.join(absRoot, CONFIG_DIR)
        self.__absDefaults = os.path.join(self.__configDir, jsonDefaults)
        self.__absSettings = os.path.join(self.__configDir, jsonSettings)
        self.__values = self.__loadSettings()
        self.__clean()
    
    def __loadDefaults(self) -> dict:
        try:
            with open(self.__absDefaults, 'r') as j:
                read = json.load(j)
        except: 
            read = None
        return read

    def __loadSettings(self) -> dict:   
        files = os.listdir(self.__configDir)
        if jsonSettings in files: 
            try: 
                with open(self.__absSettings, 'r') as j:
                    settings = json.load(j)
            except:
                #log the ERROR 
                settings = None
        else:
           settings =  self.__loadDefaults()
        return settings

    def __clean(self):
        logFolder = self.__values["logFolder"]
        logDirList = os.listdir(logFolder)
        absLog = os.path.join(logFolder, 'thermals.log')
        oldLog = os.path.join(logFolder, 'thermals.log.old')
        if self.__values["startUpReset"]:
            if 'thermals.log.old' in logDirList:
                    os.remove(oldLog)
            if 'thermals.log' in logDirList:
                shutil.move(absLog, oldLog)

    def save(self):
        encoded = json.dumps(self.__values, indent=4)

        try:
            with open(self.__absSettings, 'w') as j:
                j.write(encoded)
        
        except:
            #log the ERROR
            pass
    
    def getSettings(self) -> dict:
        return copy.deepcopy(self.__values)

    def update(self, vals : dict):
        self.__values = copy.deepcopy(vals)
