typedef struct user;

typedef struct node{
    User *info;
    Node *next, *previous;
}Node;

typedef struct list{
    int total;
    Node *start, *end;
}List;

void Create(List*);
void Push(List*, User*);
User* Pop(List*, int*);
User* Out(List*, int*);
User* Top(List*, int*);
User* Bottom(List*, int*);