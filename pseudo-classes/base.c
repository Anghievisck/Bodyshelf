#include <stdlib.h>
#include <string.h>
#include "user.h"


void Create(List *l){
    l->end = NULL;
    l->start = NULL;
    l->total = 0;
}

void Push(List *l, Dado *u){
    l->total++;

    Node *temp = (Node*)malloc(sizeof(Node));

    temp->info->info = u;
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
void sortAdd(List *l, Dado *u){
    if(l->total == 0){
        Push(l, u);
    }else{
        l -> total++;
        Node *temp = (Node*)malloc(sizeof(Node));
        temp->info->info = u;
        Node *aux = l->start;
        while(aux != NULL){
            if(strcmp(u->info->username, aux->info->info->username) < 0){
                temp->next = aux;
                temp->previous = aux->previous;
                aux->previous->next = temp;
                aux->previous = temp;
                return;
            }
            aux=aux->next;
        }
        temp->next = NULL;
        temp->previous = l->end;
        l->end->next = temp;
        l->end = temp;
    }
}

Dado* Pop(List *l, int *e){
    if(l->total != 0){
        *e = 0;
        l->total--;

        User *u = l->start->info->info;
        Node *temp = l->start;
        l->start = l->start->next;

        free(temp);

        return(u);
    } else {
        *e=1;
    }
}

Dado* Out(List *l, int *e){
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

Dado Top(List *l, int *e){
    if(l->total != 0){
        *e = 0;

        return l->end->info->info;
    } else {
        *e = 1;
    }
}

Dado Bottom(List *l, int *e){
    if(l->total != 0){
        *e = 0;

        return l->start->info->info;
    }else{
        *e=1;
    }
}