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

#ifndef STRINGLIST_H_
#define STRINGLIST_H_

#include "includes.h"

struct node {
	char *string;
	struct node *next;
};

//the actual used type
typedef struct node list;

/*inits memory for the list and assures that all the fields point to NULL
and returns the list. It Returns NULL if the list creation was unsuccefull*/
list *initList();
//returns list len
long int listLen(list *theList);
//adds a node to the end of the list, returns 0 on success
int addNode(list *myList, char *string);
//frees memory of the lists (destroys the list)
void freeList(list *theList);
//returns 0 on success, use this instead of doing it by your own
int deleteAtIdx(list *theList, int idx);
//gets the end of the list returning the node at the end of the list
list *getEnd(list *theList);
//prints the list to stdio with a bit of flavour
void printList(list *theList);
//prints the strings to stdio in each line
void printRawList(list *theList);
//USE ONLY WITH MINILOGGER, uses minLogger to print
void listOnLog(list *theList);
//replace an item in list at given idx with the given string
int replaceInList(list *theList, int idx, char *string);
//gets you to the desired index
list *getToIdx(list *theList, int idx);
//wide print of the raw list
void wPrintRawList(list *theList);

#endif