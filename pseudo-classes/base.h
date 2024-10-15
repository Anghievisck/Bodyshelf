typedef struct User;
typedef struct Msg;
typedef union{
    User *info;
    Msg  *msg;
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
Dado* Pop(List*, int*);
Dado* Out(List*, int*);
Dado Top(List*, int*);
Dado Bottom(List*, int*);
void sortAdd(List *, Dado *);