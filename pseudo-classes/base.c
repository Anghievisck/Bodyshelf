#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "base.h"

List* Create(List *l){
    l = (List *)malloc(sizeof(List)); 
    l->end = NULL;
    l->start = NULL;
    l->total = 0;
}

void Push(List *l, Dado *u){
    l->total++;
    Node *temp = (Node*)malloc(sizeof(Node));
    temp->info = u;
    temp->previous = NULL;
    if(l->start != NULL){
        temp->next = l->start;
        l->start->previous = temp;
        l->start = temp;
    } else {
        temp->next = NULL;
        temp->previous = NULL;
        l->start = temp;
        l->end = temp;
    }
}
//Se usar tome cuidade para ter certeza que Node esta na sua lista :p
void TurnFirst(List *l, Node *node){
    if(node!=l->start){
        node->previous->next=node->next;
        if(node->next!=NULL){
            node->next->previous=node->previous;
        }else{
            l->end=node->previous;
        }
        node->previous==NULL;
        node->next==l->start;
        l->start->previous=node;
    }
}
void Pop(List *l, int *e){
    if(l->total != 0){
        *e = 0;
        l->total--;
        Dado *u = l->start->info;
        Node *temp = l->start;
        Dado *aux = l->start->info;
        l->start = l->start->next;
        if(l->start==NULL){
            l->end=NULL;
        }
        free(temp);
        free(aux);
        return;
    } else {
        *e=1;
        return;
    }
}
Dado* Out(List *l, int *e){
    if(l->total != 0){
        *e = 0;
        l->total--;
        Dado *u = l->end->info;
        Node *temp = l->end;
        l->end = l->end->previous;
        if(l->end==NULL){
            l->start==NULL;
        }
        free(temp);
        free(u);
        return(u);
    } else {
        *e=1;
        return(NULL);
    } 
}

Dado* Top(List *l, int *e){
    if(l->total != 0){
        *e = 0;
        return l->end->info;
    } else {
        *e = 1;
    }
}

Dado* Bottom(List *l, int *e){
    if(l->total != 0){
        *e = 0;
        return l->start->info;
    }else{
        *e=1;
    }
}