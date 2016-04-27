#include <string.h>
#include "DynamicQueue.h"

/*********************************************************
    private constants.
*********************************************************/

#define DYNAMICQUEUE_VERSION "DynamicQueue 0.1.0(alpha)"
#define static __PRIVATE_

/*********************************************************
    private types.
*********************************************************/

typedef struct tag_Node{
	ttag_Info tagInfo;
	int iIndex;
	struct tag_Node* ptagNext;
	struct tag_Node* ptagPrev;
	struct tag_Node* ptagParent;
}ttag_Node;

/*********************************************************
    private attributes.
*********************************************************/
ttag_Node* DynamicQueue_ptagNode;

/*********************************************************
    private operations.
*********************************************************/

int			parent(int iIndex);
int			left(int iIndex);
int			right(int iIndex);
ttag_Node*	getNode(int iIndex);
void 		changeNode(ttag_Node* node1,ttag_Node* node2);
void 		maxHeapfy(ttag_Node* ptagRaiz);

/*********************************************************
    Operations implementation
*********************************************************/

/**
	DynamicQueue constructor. This is the constructor method, its initialize Start pointer.

    @param void
    @return void
    @author jponeticarvalho
    @date   25/04/2016
*/
void DynamicQueue_createInstance(void){
	
	DynamicQueue_ptagNode = NULL;
	
}

/**
	DynamicQueue destructor. This is the destructor method, it deallocates memory
	from all nodes of the Queue.

    @param void
    @return void
    @author jponeticarvalho
    @date   25/04/2016
*/
void DynamicQueue_deleteInstance(void){
	
	if(DynamicQueue_ptagNode != NULL){
		
		ttag_Node *aux = DynamicQueue_ptagNode->ptagNext;
		
		DynamicQueue_ptagNode->ptagNext = NULL;
		
		while(aux->ptagNext != NULL){
			
			aux = aux->ptagNext;
			free(aux->ptagPrev);
			
		}
		
		free(aux);
		DynamicQueue_ptagNode = NULL;
		
		
	}
	
}

/**
	Create new node. This method allocates memory for a new node, and adds the queue. 

    @param char* pcInfo - the string referring to information from one node of the DynamicQueue.
    @param int iPriority - It is the priority of the DynamicQueue node.
    @return void
    @author jponeticarvalho
    @date   25/04/2016
*/
void DynamicQueue_addNewNode(char* pcInfo, int iPriority){
	
	ttag_Node* aux = DynamicQueue_ptagNode;

	if( DynamicQueue_ptagNode == NULL ){
		
		DynamicQueue_ptagNode = (ttag_Node*)malloc(sizeof(ttag_Node));
		
		strcpy(DynamicQueue_ptagNode->tagInfo.pcInfo,pcInfo);
		DynamicQueue_ptagNode->tagInfo.iPriority = iPriority;
		DynamicQueue_ptagNode->iIndex = 0;
		DynamicQueue_ptagNode->ptagNext = DynamicQueue_ptagNode;
		DynamicQueue_ptagNode->ptagPrev = DynamicQueue_ptagNode;
	
	}
	else{
		

		ttag_Node* ptagNewNode = (ttag_Node*)malloc(sizeof(ttag_Node));

		strcpy(ptagNewNode->tagInfo.pcInfo,pcInfo);
		ptagNewNode->tagInfo.iPriority = iPriority;
		
		aux = DynamicQueue_ptagNode->ptagPrev;
		
		DynamicQueue_ptagNode->ptagPrev = ptagNewNode;
		
		aux->ptagNext = ptagNewNode;
		
		ptagNewNode->ptagNext = DynamicQueue_ptagNode;
		ptagNewNode->ptagPrev = aux;
		ptagNewNode->iIndex = (aux->iIndex) + 1;
		
	}
	
	aux = DynamicQueue_ptagNode->ptagPrev;
	
	while(aux->iIndex >= 0 && ( aux->tagInfo.iPriority > getNode(parent(aux->iIndex))->tagInfo.iPriority ) ){
		changeNode(aux,getNode(parent(aux->iIndex)));
	}
	
}

/**
	Get a pointer to the highest priority value among the nodes,
	and places the next higher in first position in the Queue.

    @param void
    @return ttag_Info - a struct variable to the highest priority value among the nodes,
			or return pcInfo = "\0", for the not exist nodes in the queue.
    @author jponeticarvalho
    @date   25/04/2016
*/
ttag_Info DynamicQueue_getMaxNode(void){
	
	ttag_Info tagInfo;
	tagInfo.pcInfo[0] = '\0';
	tagInfo.iPriority = -1;
	
	if(DynamicQueue_ptagNode == NULL) return tagInfo;
	
	tagInfo = DynamicQueue_ptagNode->tagInfo;
	ttag_Node* aux = DynamicQueue_ptagNode;
	
	if(DynamicQueue_ptagNode->ptagNext != DynamicQueue_ptagNode){
		DynamicQueue_ptagNode->ptagNext->ptagPrev = DynamicQueue_ptagNode->ptagPrev;
		DynamicQueue_ptagNode->ptagPrev->ptagNext = DynamicQueue_ptagNode->ptagNext;
		DynamicQueue_ptagNode->ptagPrev->iIndex = 0;
		DynamicQueue_ptagNode = DynamicQueue_ptagNode->ptagPrev;
	}
	else{
		DynamicQueue_ptagNode = NULL;
	}
	
	free(aux);
	
	if(DynamicQueue_ptagNode != NULL)
		maxHeapfy(DynamicQueue_ptagNode);
	
	return tagInfo;
	
}

/**
	This method list all nodes of the Queue. 

    @param void
    @return void
    @author jponeticarvalho
    @date   25/04/2016
*/
void DynamicQueue_listQueue(void){
	
	ttag_Node *aux;
	
	if(DynamicQueue_ptagNode != NULL){
	
		aux = DynamicQueue_ptagNode->ptagNext;
		
		printf("%s/%d -> ",DynamicQueue_ptagNode->tagInfo.pcInfo,DynamicQueue_ptagNode->tagInfo.iPriority);
		
		while(aux != DynamicQueue_ptagNode){
			printf("%s/%d -> ",aux->tagInfo.pcInfo,aux->tagInfo.iPriority);
			aux = aux->ptagNext;
		}
		
	}
	
	printf("NULL\n");
	
	if(DynamicQueue_ptagNode != NULL){
		aux = DynamicQueue_ptagNode->ptagPrev;
		
		printf("%s/%d -> ",DynamicQueue_ptagNode->tagInfo.pcInfo,DynamicQueue_ptagNode->tagInfo.iPriority);
		
		while(aux != DynamicQueue_ptagNode){
			printf("%s/%d -> ",aux->tagInfo.pcInfo,aux->tagInfo.iPriority);
			aux = aux->ptagPrev;
		}
	
	}
	
	printf("NULL\n");
	
}

/**
	Get parent of the node.(heap view)

    @param int iIndex - index that references a node.
    @return int - parent index node.
    @author jponeticarvalho
    @date   20/04/2016
*/
int parent(int index){
	return (int)(index-1.0)/2.0;
}

/**
	Get left son of the node.(heap view)

    @param int iIndex - index that references a node.
    @return int - left son index node.
    @author jponeticarvalho
    @date   20/04/2016
*/
int left(int index){
	return (2*index)+1;
}

/**
	Get right son of the node.(heap view)

    @param int iIndex - index that references a node.
    @return int - right son index node.
    @author jponeticarvalho
    @date   20/04/2016
*/
int right(int index){
	return (2*index)+2;
}

/**
	This method changes nodes of position in the queue.

    @param ttag_Node* node1 - It is the first node
    @param ttag_Node* node2 - It is the second node
    @return void
    @author jponeticarvalho
    @date   25/04/2016
*/
void changeNode(ttag_Node* node1, ttag_Node* node2){
	
	ttag_Node* aux;
	
	int temp = node1->iIndex;
	node1->iIndex = node2->iIndex;
	node2->iIndex = temp;
	
	if(node1->ptagNext == node2){
		
		if(node1->ptagPrev != node2){
			
			node1->ptagNext = node2->ptagNext;
			node2->ptagPrev = node1->ptagPrev;
			
			node1->ptagPrev->ptagNext = node2;
			node2->ptagNext->ptagPrev = node1;
			node1->ptagPrev = node2;
			node2->ptagNext = node1;
			
			
			
		}
		
	}
	else{
		
		if(node1->ptagPrev == node2){
			
			node2->ptagNext = node1->ptagNext;
			node2->ptagNext->ptagPrev = node2;
			
			node1->ptagPrev = node2->ptagPrev;
			node1->ptagPrev->ptagNext = node1;
			
			node1->ptagNext = node2;
			node2->ptagPrev = node1;
			
		}
		else{
			
			node1->ptagPrev->ptagNext = node2;
			node1->ptagNext->ptagPrev = node2;
			
			node2->ptagPrev->ptagNext = node1;
			node2->ptagNext->ptagPrev = node1;
			
			aux = node1->ptagNext;
			node1->ptagNext = node2->ptagNext;
			node2->ptagNext = aux;
			
			aux = node1->ptagPrev;
			node1->ptagPrev = node2->ptagPrev;
			node2->ptagPrev = aux;
			
		}
		
	}

	if(DynamicQueue_ptagNode == node2) DynamicQueue_ptagNode = node1;
	
}

/**
	This method looks for a node in the queue

    @param int iIndex - Index sought node.
    @return pointer to the node of the Index.
    @author jponeticarvalho
    @date   25/04/2016
*/
ttag_Node* getNode(int iIndex){
	
	ttag_Node *aux = DynamicQueue_ptagNode;
	
	if(aux != NULL){
		
		if(aux->iIndex == iIndex) return aux;
		aux = aux->ptagNext;
		
		while(aux != DynamicQueue_ptagNode){
			
			if(aux->iIndex == iIndex) return aux;
			aux = aux->ptagNext;
		}
		
	}
	
	return NULL;
	
}

/**
	This method sort the queue with maximum priority node.

    @param ttag_Node* ptagRaiz - references the start of the sub-tree heap view
    @return void
    @author jponeticarvalho
    @date   25/04/2016
*/
void maxHeapfy(ttag_Node* ptagRaiz){
	
	ttag_Node* esquerda = getNode(left(ptagRaiz->iIndex));
	ttag_Node* direita = getNode(right(ptagRaiz->iIndex));
	
	ttag_Node* buffer;
	
	if(esquerda != NULL && esquerda->tagInfo.iPriority > ptagRaiz->tagInfo.iPriority)
		buffer = esquerda;
	else
		buffer = ptagRaiz;
	
	if(direita != NULL && direita->tagInfo.iPriority > buffer->tagInfo.iPriority)
		buffer = direita;
	
	if(buffer != ptagRaiz){
		changeNode(buffer,ptagRaiz);
		maxHeapfy(ptagRaiz);
	}
}

/**
	Get DynamicQueue version

    @param void
    @return pointer to the version string
    @author jponeticarvalho
    @date   20/04/2016
*/
char* DynamicQueue_getVersion(){
	return (char*)DYNAMICQUEUE_VERSION;
}

/***********************************************************************
	To readjust.
***********************************************************************/

/*
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
*/