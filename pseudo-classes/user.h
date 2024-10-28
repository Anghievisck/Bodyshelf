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
    List *colleges, *request, *msg, *blacklist, *groups, *groupleader, *groupsrequest;
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
void Makegroup(List *a);
void AddCollegeforGroup(List *a);
void Groupsrequests(List *a);
void SendmsgGroup(List *a);
Node* FindGroupNodeByName(List *l, char target[12]);
Group* FindGroupByName(List *l, char target[12]);
void ShowLeadergroups(User *user);
void Showgroups(User *user);
void DelgroupUser(List *allusers);
void DelgropSys(Node *grupo, User *leader);
void PassTheCrown(List *allusers);
Node* FindNodeByUsernamne(List *a, char[USERNAME]);
User* FindUserByUsernamne(List *a, char[USERNAME]);

#endif