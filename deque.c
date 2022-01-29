#include "defs.h"

/*
  Function:  addElementtoDeque
  Purpose:   adds the given element to the given deque
       in:   element
   return:   void
*/
void addElementtoDeque(NodeType** node){
    NodeType* temp = malloc(sizeof(*temp));
    node[0] = temp;
}
/*
  Function:  initDeque
  Purpose:   initializes a deque and add (size) number of elements with random values
       in:   random values
   return:   void
*/
void initDeque(int size, DequeType** dq){
    DequeType* deque = malloc(sizeof(*deque));
    addElementtoDeque(&(deque->head));
    initPirate(&(deque->head->data));
    deque->tail = deque->head;

    for(int i=1; i<size; i++){
        addElementtoDeque(&(deque->tail->next));
        initPirate(&(deque->tail->next->data));
        deque->tail = deque->tail->next;
    }
    deque->tail->next = NULL;

    dq[0] = deque;
}
/*
  Function:  isEmpty
  Purpose:   Points the head of the deque to null and returns value depending on deque if it is empty
   output:   0 and 1
   return:   returns 1 if deque is empty else returns 0;
*/
int isEmpty(DequeType* deque){
    if(deque->head == NULL)
        return 1;
    else
        return 0;
}
/*
  Function:  printDeque
  Purpose:   test function
   output:   prints the deque on screen
   return:   void
*/

void printDeque(DequeType* deque){
    NodeType * temp = deque->head;
    while(temp != NULL){
        printFighter(temp->data);
        temp = temp->next;
    }
}
/*
  Function:  deepCopyDeque
  Purpose:   creates a deepcopy of the deque
   output:   
   return:   void
*/
void deepCopyDeque(DequeType* p_deque, DequeType** copy){
    if(p_deque->head != NULL){
        DequeType* deque = malloc(sizeof(*deque));  // new deque
        NodeType * temp = p_deque->head;
        addElementtoDeque(&(deque->head));
        deepCopyFighter(temp->data, &(deque->head->data));
        deque->tail = deque->head;
        temp= temp->next;

        while(temp != NULL){    // iterate for every element
            addElementtoDeque(&(deque->tail->next));
            deepCopyFighter(temp->data, &(deque->tail->next->data));
            deque->tail = deque->tail->next;
            temp = temp->next;  // move next
        }
        deque->tail->next = NULL;
        copy[0] = deque;
    }
}
/*
  Function:  removeFighterFromBack
  Purpose:   removes the fighter from back i.e tail of the deque
   output:   
   return:   void
*/
void removeFighterFromBack(DequeType** deque, FighterType** fighter){
    NodeType* current = deque[0]->head;

    if(deque[0]->head == deque[0]->tail){
        removeFighterFromFront(deque, fighter);
    }
    else{
        while(current->next != deque[0]->tail){    // loop till we reach tail, stop 1 item before tail
            current = current->next;    
        }

        NodeType * temp = current->next;    // store the current tail in temp pointer
        deque[0]->tail = current;  //  Make the current item the tail i.e second last before removing
        current->next = NULL;   // make its next point to null i.e last removed no link with deque now


        fighter[0] = temp->data;    // make the return fighter pointer point to same data as removed items data pointer
        temp->next = NULL;
        
        free(temp); //clear temp node not clearing the fighters data just Nodetype
    }
}
/*
  Function:  removeFighterFromFront
  Purpose:   removes a fighter from the front i.e head of deque
   output:   
   return:   void
*/
void removeFighterFromFront(DequeType** deque, FighterType** fighter){
    NodeType* current = deque[0]->head;

    deque[0]->head = deque[0]->head->next;  //  Update the head of the deque to next node
    current->next = NULL;   // make its next point to null i.e head removed no link with deque now

    fighter[0] = current->data;    // make the return fighter pointer point to same data as removed items data pointer
    current->next = NULL;
    
    free(current); //clear temp node not clearing the fighters data just Nodetype
}
/*
  Function:  cleanUpFighterNode
  Purpose:   cleans up the memory allocated to the fighter node
   output:   
   return:   void
*/
void cleanUpFighterNode(NodeType** node){
    free(node[0]->data);
    node[0]->next = NULL;
    free(node[0]);
}
/*
  Function: cleanUpDeque
  Purpose:  cleans up the memory allocated to the deque
   output:   
   return:   void
*/
void cleanUpDeque(DequeType** deque){
    NodeType* temp = deque[0]->head;
    NodeType* temp1;

    while (temp != NULL){
        // printf("S: %d - H: %d - A: %d \n",temp->data->strength, temp->data->health, temp->data->armour);
        temp1 = temp->next;
        cleanUpFighterNode(&temp);
        temp = temp1;
    }
    // printf("\n");
    deque[0]->head = NULL;
    deque[0]->tail = NULL;
}