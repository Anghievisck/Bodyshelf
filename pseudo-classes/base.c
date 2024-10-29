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

    l->total++;
}

//Se usar tome cuidade para ter certeza que Node esta na sua lista :p
void RemoveNode(List *l, Node *node){
    if(l->total == 0){
        return;
    } else if(l->total == 1){
        free(l->start->info);
        free(l->start);

        l->start = NULL;
        l->end = NULL;

        l->total = 0;

        return;
    }

    Node *temp = l->start;

    if(node == l->start){
        l->start->next->previous = NULL;
        l->start = l->start->next;

        free(node->info);
        free(node);

        l->total--;
    } else if(node == l->end){
        l->end->previous->next = NULL;
        l->end = l->end->previous;

        free(node->info);
        free(node);

        l->total--;
    } else {
        while (temp->next != NULL){
            if(temp == node){
                temp->previous->next = temp->next;
                temp->next->previous = temp->previous;

                free(node->info);
                free(node);

                l->total--;

                break;
            }

            temp = temp->next;
        }
    }
}

void Pop(List *l, int *e){
    if(l->total != 0){
        Node *temp = l->start;
        Dado *aux = l->start->info;

        l->start = l->start->next;

        if(l->start == NULL){
            l->end = NULL;
        }

        free(temp);
        free(aux);

        *e = 0;
        l->total--;

        return;
    } else {
        *e = 1;

        return;
    }
}

void Out(List *l, int *e){
    if(l->total != 0){
        Dado *u = l->end->info;
        Node *temp = l->end;

        l->end = l->end->previous;

        if(l->end == NULL){
            l->start = NULL;
        }

        free(temp);
        free(u);

        *e = 0;
        l->total--;

        return;
    } else {
        *e = 1;

        return;
    } 
}