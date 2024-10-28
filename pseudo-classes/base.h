#ifndef USER_H
#define USER_H

#include "user.h"

typedef struct user User;
typedef struct msg Msg;
typedef struct group Group;
typedef struct node Node;

typedef union{
    User *user;
    Msg  *msg;
    Group *grp;
}Dado;
typedef struct node{
    Dado *info;
    Node *next, *previous;
}Node;
typedef struct list{
    int total;
    Node *start, *end;
}List;

void Create(List*);
void Push(List*, Dado*);
Dado* Pop(List*, int *);
Dado* Out(List*, int *);
Dado* Top(List*, int *);
Dado* Bottom(List*, int *);
void TurnFirst(List *l, Node *node);
#endif 

