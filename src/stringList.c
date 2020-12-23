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

#include "stringList.h"


list *initList() {
    list *theList = (list *) malloc(sizeof(list));
    if(theList != NULL) {
        theList->string = NULL;
        theList->next = NULL;
        return theList;
    }else
        return NULL;
}

long int listLen(list *theList) {
    int len = 1;

    if (!theList->string)
        return 0;
    
    while(theList->next != NULL) {
        theList = theList->next;
        len++;
    }
    return len;
}

list *getEnd(list *theList) {
    while (theList->next != NULL) {
        theList = theList->next;
    }
    return theList;
}

int addNode(list *myList, char *string) {
    int success = 0;
    int len = strlen(string);

    if(myList->string == NULL) {
        myList->string = (char *) malloc(sizeof(char)*(len + 1));
        if (myList->string == NULL) {
                success = 1;
        } else {
            if(!strcpy(myList->string, string))
                success = 1;
        }
    } else {
        list *end = getEnd(myList);
        end->next = initList();
        end = end->next;
        end->string = (char *) malloc(sizeof(char)*(len + 1));
        if (end->string == NULL) {
            success = 1;
        } else {
            if(!strcpy(end->string, string))
                success = 1;
        }
    }
    return success;
}

int deleteAtIdx(list *theList, int idx) {

    int len = listLen(theList);
    if(idx >= len) {
        return -1;
    }

    struct node *prev;
    struct node *at = theList;
    for(int i = 0; i < idx; i++) { 
        prev = at;
        at = at->next;
    }
    prev->next = at->next;
    free(at->string);
    free(at);
    return 0;
}

void printList(list *theList) {
    printf("[ ");
    while (theList != NULL) {
        printf("\'%s\' ", theList->string);
        theList = theList->next;
    }
    printf("]\n");
}

void printRawList(list *theList) {
    while (theList != NULL) {
        printf("%s\n", theList->string);
        theList = theList->next;
    }
}

void wPrintRawList(list *theList) {
    while (theList != NULL) {
        wprintf(L"%s\n", theList->string);
        theList = theList->next;
    }
}

void ListOnLog(list *theList) {
    while (theList != NULL) {
        log_normal(L"\"%s\"\n", theList->string);
        theList = theList->next;
    }
}

void freeList(list *theList) {
    list *next;
    while(theList != NULL) {
        next = theList->next;
        free(theList->string);
        free(theList);
        theList = next;
    }
}

list *getToIdx(list *theList, int idx) {
    for(int i = 0; i < idx; i++)
        theList = theList->next;
    return theList;
}

int replaceInList(list *theList, int idx, char *string) {
    list *at = getToIdx(theList, idx);
    free(at->string);
    int len = strlen(string);
    at->string = (char *) malloc(sizeof(char)*(len + 1));

    if(at->string == NULL)
        return 1;
    
    if(!strcpy(at->string, string))
        return 1;
    
    return 0;
}