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

### 			SENS MAKEFILE 

#SENS SRC AND OBJ FILES
SENS_SRC_DIR := src
SENS_OBJ_DIR := sens_obj

#WHERE TO PUT THE BINARIES
BINARIES := ./bin


SENS := $(BINARIES)/sens

#WILDCARDS FOR SENS SRC AND OBJ FILES
SENS_SRC := $(wildcard $(SENS_SRC_DIR)/*.c)
SENS_OBJ := $(SENS_SRC:$(SENS_SRC_DIR)/%.c=$(SENS_OBJ_DIR)/%.o)

#FLAGS FOR THE PROGRAM
SENS_FLAGS :=  -fmessage-length=0
SENS_LFLAGS := -lsensors


.PHONY: all clean rem

all: $(SENS) rem

	
# SENS
$(SENS): $(SENS_OBJ) 
	gcc  $^ $(SENS_LFLAGS) -o $@

$(SENS_OBJ_DIR)/%.o: $(SENS_SRC_DIR)/%.c | $(SENS_OBJ_DIR)
	gcc $(SENS_FLAGS) -c $< -o $@

# DIRECTORY CREATION
$(BINARIES) $(SENS_OBJ_DIR):
	mkdir -p $(BINARIES) $(SENS_OBJ_DIR)

clean:
	@$(RM) -rv $(SENS_OBJ_DIR) $(BINARIES)
	
rem:
	@$(RM) -r $(SENS_OBJ_DIR)

-include $(SENS_OBJ:.o=.d)
