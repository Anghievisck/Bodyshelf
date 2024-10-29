typedef union{
    struct user *user;
    struct msg *msg;
    struct group *grp;
}Dado;

typedef struct node{
    Dado *info;
    struct node *next, *previous;
}Node;

typedef struct list{
    int total;
    Node *start, *end;
}List;

List* Create(List*);
void Push(List*, Dado*);
void Pop(List*, int *);
void Out(List*, int *);

Dado* Top(List*, int *);
Dado* Bottom(List*, int *);

void TurnFirst(List *l, Node *node);