#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DynamicQueue.h"

int main(){
	
	printf("%s\n",DynamicQueue_getVersion());
	
	int op,i=0;
	
	DynamicQueue_createInstance();
	
	do{
		
		printf("    Menu\n");
		printf("1 - New Event\n");
		printf("2 - View full Event\n");
		printf("3 - Remove Event\n");
		printf("4 - Edit Event\n");
		printf("5 - Search Event\n");
		printf("6 - Exit\n>");
		scanf("%d",&op);
		
		switch(op){
			 case 1:
			 	char sInfo[20];
			 	int iPriority;
			 	printf("Enter the name of the event\n>");
				scanf("%s",sInfo);
				printf("Enter the priority\n>");
				scanf("%d",&iPriority);
				DynamicQueue_addNewNode(sInfo,iPriority);
				i++;
				break;
			case 2:
				DynamicQueue_listQueue();
				break;
			case 3:
				ttag_Info tagInfo;
				tagInfo = DynamicQueue_getMaxNode();
				if(strcmp(tagInfo.pcInfo,"\0") != 0)
					printf("Name: %s\nPriority: %d\n",(tagInfo.pcInfo),(tagInfo.iPriority));
				else
					printf("No more event!\n");
				i--;
				break;
			case 4:
				//editEvent(&eventQueue);
				break;
			case 5:
				//searchEvent(eventQueue);
				break;
			case 6:
				DynamicQueue_deleteInstance();
				break;
			default:
				printf("Invalid option\n");
				break;
		}
		
	}while(op!=6);
	
	return 0;
}