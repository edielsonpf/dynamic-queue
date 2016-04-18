#include <stdlib.h>
#include <stdio.h>

typedef struct tag_EventNode{
	char info[20];
	int priority;
	int index;
	struct tag_EventNode* ptagNext;
	struct tag_EventNode* ptagPrev;
}ttag_EventNode;

void buildMaxHeap(ttag_EventNode* raiz, int i,ttag_EventNode** eventQueue);
void maxHeapfy(ttag_EventNode* raiz,int i,ttag_EventNode** eventQueue);

void createEvent(ttag_EventNode** eventQueue,int i);
void listEvents(ttag_EventNode* raiz);
void removeEvent(ttag_EventNode* raiz,int i,ttag_EventNode **eventQueue);
void searchEvent(ttag_EventNode* raiz);
void editEvent(ttag_EventNode** eventQueue);

void updateIndex(ttag_EventNode *eventQueue);
void freeMemory(ttag_EventNode* raiz);

ttag_EventNode* getNode(ttag_EventNode* raiz,int searched);
ttag_EventNode* getEvent(ttag_EventNode* raiz,char* searched);
void changeNode(ttag_EventNode* node1, ttag_EventNode* node2,ttag_EventNode** eventQueue);

int strcomp(char * str1, char * str2);

int parent(int index){
	return (index-1)/2;
}

int left(int index){
	return (2*index)+1;
}

int right(int index){
	return (2*index)+2;
}

int main(){
	
	int op,i=0;
	ttag_EventNode* eventQueue = NULL;
	
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
				createEvent(&eventQueue,i);
				i++;
				break;
			case 2:
				listEvents(eventQueue);
				break;
			case 3:
				removeEvent(eventQueue,i,&eventQueue);
				i--;
				break;
			case 4:
				editEvent(&eventQueue);
				break;
			case 5:
				searchEvent(eventQueue);
				break;
			case 6:
				freeMemory(eventQueue);
				break;
			default:
				printf("Invalid option\n");
				break;
		}
		
	}while(op!=6);
	
	return 0;
}

void createEvent(ttag_EventNode **eventQueue,int i){

	ttag_EventNode *aux = (*eventQueue);
	/* the 'newEvent' pointer will be released in removeEvent() or freeMemory() */
	ttag_EventNode *newEvent = (ttag_EventNode*) malloc(sizeof(ttag_EventNode));
	
	printf("Enter the name of the event\n>");
	scanf("%s",newEvent->info);
	printf("Enter the priority\n>");
	scanf("%d",&newEvent->priority);
	
	newEvent->ptagNext = NULL;
	
	if(*eventQueue!= NULL){
		while(aux->ptagNext != NULL){
			aux = aux->ptagNext;
		}
		
		aux->ptagNext = newEvent;
		newEvent->ptagPrev = aux;
		aux->ptagNext->index = i;
	}
	else{
		(*eventQueue) = newEvent;
		(*eventQueue)->index = 0;
		(*eventQueue)->ptagPrev =NULL;
	}
	
	int newIndex = i;
	int pai = parent(newIndex);
	
	while(newIndex >= 0 && ( getNode(*eventQueue,newIndex)->priority > getNode(*eventQueue,pai)->priority ) ){
		changeNode(getNode(*eventQueue,newIndex), getNode(*eventQueue,pai),&(*eventQueue));
		newIndex = pai;
		pai = parent(newIndex);
	}
	
	/*
	buildMaxHeap(*eventQueue,i+1,&(*eventQueue));
	*/
}

void listEvents(ttag_EventNode* raiz){
	
	ttag_EventNode *aux = raiz;
	int cont =0;
	
	while(aux != NULL){
		printf("%s -> ",aux->info);
		aux = aux->ptagNext;
		cont++;
		if(cont == 4){
			printf("\n");
			cont=0;
		}
	}
	printf("NULL\n");
}

void removeEvent(ttag_EventNode* raiz,int i,ttag_EventNode **eventQueue){
	
	ttag_EventNode* aux;
	if(*eventQueue != NULL){

		aux = getNode(*eventQueue,i-1);
		printf("%d\n",aux->priority);		
		if(aux != *eventQueue){
			
			ttag_EventNode *max = (*eventQueue);
			
			if((*eventQueue)->ptagNext != aux){
				aux->ptagNext =(*eventQueue)->ptagNext;
				aux->ptagPrev->ptagNext = NULL;
				aux->ptagPrev = NULL;
				aux->index = 0;
				
				(*eventQueue)->ptagNext->ptagPrev = aux;
				(*eventQueue) = aux;
			}
			else{
				aux->ptagPrev = NULL;
				aux->index = 0;
				(*eventQueue) = aux;
			}
			
			free(max);
			
			maxHeapfy(*eventQueue,0,&(*eventQueue));
			
		}
		
		else{
			free(*eventQueue);
			*eventQueue = NULL;
		}
		
	}
	else{
		printf("Dont exist events to be removed!\n");
	}
	
	
}

void searchEvent(ttag_EventNode* raiz){
	
	
	
}

void maxHeapfy(ttag_EventNode* raiz,int i,ttag_EventNode** eventQueue){
	
	ttag_EventNode* esquerda = getNode(raiz,left(i));
	ttag_EventNode* direita = getNode(raiz,right(i));
	
	ttag_EventNode* buffer;
	
	if(esquerda != NULL && esquerda->priority > raiz->priority)
		buffer = esquerda;
	else
		buffer = raiz;
	
	if(direita != NULL && direita->priority > buffer->priority)
		buffer = direita;
	
	if(buffer != raiz){
		changeNode(buffer,raiz,&(*eventQueue));
		maxHeapfy(raiz,raiz->index,&(*eventQueue));
	}
}

void freeMemory(ttag_EventNode* raiz){
	
	if(raiz != NULL){
		
		while(raiz->ptagNext != NULL){
			raiz = raiz->ptagNext;
			free(raiz->ptagPrev);
		}
		free(raiz);
		
	}
		
}

ttag_EventNode* getNode(ttag_EventNode* raiz,int searched){
	
	ttag_EventNode* aux = raiz;
	
	if(aux != NULL){
		
		while(aux != NULL){
			
			if(aux->index == searched) return aux;
			aux = aux->ptagNext;
		}
		
	}
	
	return NULL;
	
}

ttag_EventNode* getEvent(ttag_EventNode* raiz,char* searched){
	
	ttag_EventNode* aux = raiz;
	
	if(aux != NULL){
		
		while(aux != NULL){
			
			if(strcomp(aux->info,searched) == 0) return aux;
			aux = aux->ptagNext;
		}
		
	}
	
	return NULL;	
	
}

void changeNode(ttag_EventNode* node1, ttag_EventNode* node2,ttag_EventNode** eventQueue){
	
	ttag_EventNode* aux;
	
	int temp = node1->index;
	node1->index = node2->index;
	node2->index = temp;
	
	if(node2->ptagNext != node1){
		
		if(node1->ptagNext != NULL && node2->ptagNext != NULL){
			
			aux = node1->ptagNext->ptagPrev;
			node1->ptagNext->ptagPrev = node2;
			node2->ptagNext->ptagPrev = aux;
			
		}
		else if(node1->ptagNext != NULL)
			node1->ptagNext->ptagPrev = node2;
		else
			node2->ptagNext->ptagPrev = node1;
		
		if(node1->ptagPrev != NULL && node2->ptagPrev != NULL){
			
			aux = node1->ptagPrev->ptagNext;
			node1->ptagPrev->ptagNext = node2;
			node2->ptagPrev->ptagNext = aux;
			
		}
		else if(node1->ptagPrev != NULL)
			node1->ptagPrev->ptagNext = node2;
		else
			node2->ptagPrev->ptagNext = node1;
	
		aux = node1->ptagNext;
		node1->ptagNext = node2->ptagNext;
		node2->ptagNext = aux;
		
		aux = node1->ptagPrev;
		node1->ptagPrev = node2->ptagPrev;
		node2->ptagPrev = aux;
		
	}
	else{
		
		if(node1->ptagNext != NULL)
			node1->ptagNext->ptagPrev = node1->ptagPrev;
		
		node1->ptagPrev = node2->ptagPrev;
		
		if(node2->ptagPrev != NULL)
			node2->ptagPrev->ptagNext = node2->ptagNext;
			
		node2->ptagNext = node1->ptagNext;
		
		node1->ptagNext = node2;
		node2->ptagPrev = node1;
		
	}
	
	if(node1 == *eventQueue)
		*eventQueue = node2;
	else if(node2 == *eventQueue)
		*eventQueue = node1;
	
}

void editEvent(ttag_EventNode** eventQueue){
	
	ttag_EventNode *aux = *eventQueue;
	int cont =0;
	
	while(aux != NULL){
		printf("%s -> ",aux->info);
		aux = aux->ptagNext;
		cont++;
		if(cont == 4){
			printf("\n");
			cont=0;
		}
	}
	printf("NULL\n");
	
	char searched[20];
	
	printf("Enter when Event you want change(name)\n>");
	scanf("%s",searched);
	
	aux = NULL;
	aux = getEvent(*eventQueue,searched);
	
	if(aux == NULL){
		printf("Don't found this Event!\n");
		return;
	}
		
	printf("When new name for this Event?\n>");
	scanf("%s",aux->info);
	printf("And a new priority?\n>");
	scanf("%d",&aux->priority);
	
	maxHeapfy(aux,aux->index,&(*eventQueue));
	
	int newIndex = aux->index;
	int pai = parent(newIndex);
	
	while(newIndex >= 0 && ( getNode(*eventQueue,newIndex)->priority > getNode(*eventQueue,pai)->priority ) ){
		changeNode(getNode(*eventQueue,newIndex), getNode(*eventQueue,pai),&(*eventQueue));
		newIndex = pai;
		pai = parent(newIndex);
	}
	
}

void updateIndex(ttag_EventNode *eventQueue){
	
	ttag_EventNode *aux = eventQueue;
	
	while(aux != NULL){

		aux->index = aux->index - 1;
		aux = aux->ptagNext;
	}
	
}

int strcomp(char * str1, char * str2){
	int i=0;
	while(str1[i] != '\0' && str2[i] != '\0'){
		if(str1[i] < str2[i]) return -1;
		else if(str1[i] > str2[i]) return 1;
		i++;
	}
	if(str1[i] != '\0' && str2[i] == '\0') return 1;
	else if(str1[i] == '\0' && str2[i] != '\0') return -1;
	else return 0;
}