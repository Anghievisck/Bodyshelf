#ifndef BASE_H 
#define BASE_H

#include "base.h"

#define NAME 50
#define USERNAME 12
typedef struct list List;
typedef struct node Node;
typedef struct user User;
typedef struct msg Msg;
typedef struct user{
    char name[NAME], username[USERNAME];
    List *colleges, *request, *msg, *blacklist, *groups, *leadergroups;
}User;
typedef struct msg{
    char name[250], username[12], chat[12];
}Msg;
typedef struct group{
    char groupname[12];
    List *members;
}Group;
void dellrede(List *a);
void PrintNet(List *a);
void RegisterUser(List *a);
void ShowUsers(List *a);
void Showmycolleges(List *a);
void ShowColleges(User *a);
void Suggestions(List *a);
void Collegesrequest(List *a);
void addrequest(User *a, User *b);
void Showrequests(List *a  );
void sendmsg(List *a );
void showmsg(List *a );
void RemoveCollege(List *a);
void RemoveBlock(List *a);
void Block(List *a);
void ShowBlocks(User *a);
Node* FindNodeByUsernamne(List *a, char[USERNAME]);
User* FindUserByUsernamne(List *a, char[USERNAME]);
#endif