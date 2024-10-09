typedef struct user;

typedef struct node{
    user *info;
    node *next, *previous;
}Node;

typedef struct list{
    int total;
    Node *start, *end;
}List;

void Create(List*);
void Push(List*, user*, int*);
user Pop(List*, int*);
user Out(List*, int*);
user Top(List*, int*);
user Bottom(List*, int*);