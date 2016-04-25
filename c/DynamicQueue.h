#ifndef DYNAMICQUEUE_H
#define DYNAMICQUEUE_H

#include <stdlib.h>
#include <stdio.h>

/*********************************************************
    public types.
*********************************************************/
typedef struct tag_Info{
	char pcInfo[20];
	int iPriority;    
}ttag_Info;

/*********************************************************
    public operations.
*********************************************************/
void		DynamicQueue_createInstance(void);
void		DynamicQueue_deleteInstance(void);
void		DynamicQueue_addNewNode(char* pcInfo, int iPriority);
ttag_Info	DynamicQueue_getMaxNode(void);
char*		DynamicQueue_getVersion(void);
void		DynamicQueue_listQueue(void);

#endif