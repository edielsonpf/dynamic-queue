#include <stdlib.h>
#include <stdio.h>

#define tam 8

typedef struct Node{
	int priority;
	int info;
	struct Node* pNext;
	struct Node* pPrev;
}no;

void buildMaxHeap(no* raiz, int i);
void maxHeapfy(no* raiz,int i);
void createEvent(no *raiz,int i);
void listEvents(no* raiz,int i);
void removeEvent(no* raiz,int i);

int main(){
	
	int op,i=0,j=0;
	no eventQueue[tam];
	
	for(j=0;j<tam;j++)
		eventQueue[j].priority = -1;
	
	do{
		
		printf("    Menu\n");
		printf("1 - New Event\n");
		printf("2 - View full Event\n");
		printf("3 - Remove Event\n");
		printf("4 - MaxHeap\n");
		printf("5 - Exit\n>");
		scanf("%d",&op);
		
		switch(op){
			case 1:
				createEvent(eventQueue,i);
				i++;
				break;
			case 2:
				listEvents(eventQueue,i);
				break;
			case 3:
				removeEvent(eventQueue,i);
				break;
			case 4:
				buildMaxHeap(eventQueue,i);
				break;
			case 5:
				break;
			default:
				printf("Invalid option\n");
				break;
		}
		
	}while(op!=5);
	
	return 0;
}

void createEvent(no *raiz,int i){
	
	printf("Priorite level: ");
	scanf("%d",&raiz[i].priority);
	
}

void listEvents(no* raiz,int i){
	
	int j=0;
	
	for(j=0;j<i;j++)
		if(raiz[j].priority != -1)
			printf("%d ",raiz[j].priority);
	printf("\n");
	
}

void removeEvent(no* raiz,int i){
	
	int priorityRemoved,j;
	
	printf("Enter the priority to be removed: ");
	scanf("%d",&priorityRemoved);
	
	for(j=0;j<i;j++)
		if(raiz[j].priority == priorityRemoved)
			raiz[j].priority = -1;
	
}

void maxHeapfy(no* raiz,int i){
	
	int esquerda = (i*2)+1;
	int direita = esquerda + 1;
	int pos;
	
	if(esquerda < tam && raiz[esquerda].priority > raiz[i].priority)
		pos = esquerda;
	else
		pos = i;
	
	if(direita < tam && raiz[direita].priority > raiz[pos].priority)
		pos = direita;
	
	if(pos != i){
		no aux = raiz[i];
		raiz[i] = raiz[pos];
		raiz[pos] = aux;
		maxHeapfy(raiz,pos);
	}
}

void buildMaxHeap(no* raiz,int i){
	int j;
	for(j=i/2;j>=0;j--)
		maxHeapfy(raiz,j);
	
}

