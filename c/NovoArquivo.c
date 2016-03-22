#include <stdlib.h>
#include <stdio.h>

typedef struct Node{
	char info[20];
	int priority;
	int index;
	struct Node* pNext;
	struct Node* pPrev;
}no;

void buildMaxHeap(no* raiz, int i);
void maxHeapfy(no* raiz,int i);
void createEvent(int i);
void listEvents(no* raiz);
void removeEvent(no* raiz);
void searchEvent(no* raiz);
void freeMemory(no* raiz);
no* getNode(no* raiz,int searched);
no* getEvent(no* raiz,char* searched);
void changeNode(no* node1, no* node2);
int strcomp(char * str1, char * str2);

no* eventQueue = NULL;

int main(){
	
	int op,i=0;
	// no *eventQueue = NULL;
	
	do{
		
		printf("    Menu\n");
		printf("1 - New Event\n");
		printf("2 - View full Event\n");
		printf("3 - Remove Event\n");
		printf("4 - Search Event\n");
		printf("5 - Exit\n>");
		scanf("%d",&op);
		
		switch(op){
			 case 1:
				createEvent(i);
				i++;
				break;
			case 2:
				listEvents(eventQueue);
				break;
			case 3:
				removeEvent(eventQueue,i);
				break;
			case 4:
				searchEvent(eventQueue);
				break;
			case 5:
				freeMemory(eventQueue);
				break;
			default:
				printf("Invalid option\n");
				break;
		}
		
	}while(op!=5);
	
	return 0;
}

void createEvent(int i){

	no *aux = eventQueue;
	/* the 'newEvent' pointer will be released in removeEvetn() or freeMemory() */
	no *newEvent = (no*) malloc(sizeof(no));
	
	printf("Enter the name of the event\n>");
	scanf("%s",newEvent->info);
	printf("Enter the priority\n>");
	scanf("%d",&newEvent->priority);
	
	newEvent->pNext = NULL;
	
	if(eventQueue!= NULL){
		while(aux->pNext != NULL){
			aux = aux->pNext;
		}
		
		aux->pNext = newEvent;
		newEvent->pPrev = aux;
		aux->pNext->index = i;
	}
	else{
		eventQueue = newEvent;
		eventQueue->index = 0;
		eventQueue->pPrev =NULL;
	}
	
	buildMaxHeap(eventQueue,i+1);
	
}

void listEvents(no* raiz){
	
	no *aux = raiz;
	int cont =0;
	
	while(aux != NULL){
		printf("%s -> ",aux->info);
		aux = aux->pNext;
		cont++;
		if(cont == 4){
			printf("\n");
			cont=0;
		}
	}
	printf("NULL\n");
}

void removeEvent(no* raiz,int i){
	
	no* aux = eventQueue;
	if(eventQueue != NULL){
		eventQueue = eventQueue->pNext;
		free(aux);
		buildMaxHeap(eventQueue,i);
	}
	else{
		printf("Dont exist events to be removed!\n");
	}
	
	
}

void searchEvent(no* raiz){
	
	
	
}

void maxHeapfy(no* raiz,int i){
	
	no* esquerda = getNode(raiz,(i*2)+1);
	no* direita;
	if(esquerda != NULL)
		direita = esquerda->pNext;
	else
		direita = NULL;
	no* buffer;
	
	if(esquerda != NULL && esquerda->priority > raiz->priority)
		buffer = esquerda;
	else
		buffer = raiz;
	
	if(direita != NULL && direita->priority > buffer->priority)
		buffer = direita;
	
	if(buffer != raiz){
		changeNode(buffer,raiz);
		maxHeapfy(buffer,buffer->index);
	}
}

void buildMaxHeap(no* raiz,int i){
	int j;
	for(j=i/2;j>=0;j--)
		maxHeapfy(getNode(raiz,j),j);
	
}

void freeMemory(no* raiz){
	
	if(raiz != NULL){
		
		while(raiz->pNext != NULL){
			raiz = raiz->pNext;
			free(raiz->pPrev);
		}
		free(raiz);
		
	}
		
}

no* getNode(no* raiz,int searched){
	
	no* aux = raiz;
	
	if(aux != NULL){
		
		while(aux != NULL){
			
			if(aux->index == searched) return aux;
			aux = aux->pNext;
		}
		
	}
	
	return NULL;
	
}

no* getEvent(no* raiz,char* searched){
	
	no* aux = raiz;
	
	if(aux != NULL){
		
		while(aux != NULL){
			
			if(strcomp(aux->info,searched) == 0) return aux;
			aux = aux->pNext;
		}
		
	}
	
	return NULL;	
	
}

void changeNode(no* node1, no* node2){
	
	no* aux;
	if(node2->pNext != node1){
		
		if(node1->pNext != NULL && node2->pNext != NULL){
			
			aux = node1->pNext->pPrev;
			node1->pNext->pPrev = node2;
			node2->pNext->pPrev = aux;
			
		}
		else if(node1->pNext != NULL)
			node1->pNext->pPrev = node2;
		else
			node2->pNext->pPrev = node1;
		
		if(node1->pPrev != NULL && node2->pPrev != NULL){
			
			aux = node1->pPrev->pNext;
			node1->pPrev->pNext = node2;
			node2->pPrev->pNext = aux;
			
		}
		else if(node1->pPrev != NULL)
			node1->pPrev->pNext = node2;
		else
			node2->pPrev->pNext = node1;
	
		aux = node1->pNext;
		node1->pNext = node2->pNext;
		node2->pNext = aux;
		
		aux = node1->pPrev;
		node1->pPrev = node2->pPrev;
		node2->pPrev = aux;
		
	}
	else{
		
		if(node1->pNext != NULL)
			node1->pNext->pPrev = node1->pPrev;
		
		node1->pPrev = node2->pPrev;
		
		if(node2->pPrev != NULL)
			node2->pPrev->pNext = node2->pNext;
			
		node2->pNext = node1->pNext;
		
		node1->pNext = node2;
		node2->pPrev = node1;
		
	}
	
	if(node1 == eventQueue)
		eventQueue = node2;
	else if(node2 == eventQueue)
		eventQueue = node1;
	
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