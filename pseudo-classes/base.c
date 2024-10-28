#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "base.h"

void Create(List *l){
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
Dado* Pop(List *l, int *e){
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
        return(u);
    } else {
        *e=1;
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