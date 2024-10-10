#include <stdlib.h>
#include "user.h"


void Create(List *l){
    l->end = NULL;
    l->start = NULL;
    l->total = 0;
}

void Push(List *l, User *u){
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
        l->start = temp;
        l->end = temp;
    }
}

User* Pop(List *l, int *e){
    if(l->total != 0){
        *e = 0;
        l->total--;

        User *u = l->start->info;
        Node *temp = l->start;
        l->start = l->start->next;

        free(temp);

        return(u);
    } else {
        *e=1;
    }
}

User* Out(List *l, int *e){
    if(l->total != 0){
        *e = 0;
        l->total--;

        User *u = l->end->info;
        Node *temp = l->end;
        l->end = l->end->previous;
        free(temp);

        return(u);
    } else {
        *e=1;
    } 
}

User* Top(List *l, int *e){
    if(l->total != 0){
        *e = 0;

        return l->end->info;
    } else {
        *e = 1;
    }
}

User* Bottom(List *l, int *e){
    if(l->total != 0){
        *e = 0;

        return l->start->info;
    }else{
        *e=1;
    }
}