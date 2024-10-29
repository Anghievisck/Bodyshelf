#ifndef BASE_H 
#define BASE_H

#include "base.h"

#define NAME 50
#define USERNAME 12

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

void RegisterUser(List *a);

void CollegesRequest(List *a);
void SendMsgToCollege(List *a);
void Block(List *a);

void GroupsRequests(List *a);
void AddCollegeToGroup(List *a);
void SendGroupMsg(List *a);

void RegisterGroup(List *a);

void PrintNetwork(List *a);

void Suggestions(List *a);

void ShowUsers(List *a);
void ShowMycolleges(List *a);
void ShowCollegeRequest(List *a);
void ShowMsg(List *a);
void ShowColleges(User *a);
void AddRequest(User *a, User *u);

void RemoveCollege(List *a);
void RemoveBlock(List *a);
void Block(List *a);
void ShowBlocks(User *a);

Node* FindGroupNodeByName(List *l, char target[12]);
Group* FindGroupByName(List *l, char target[12]);
void ShowLeaderGroups(User *user);
void ShowGroups(User *user);
void DelGroupSys(Node *grupo, User *leader);
Node* FindNodeByUsernamne(List *a, char[USERNAME]);
User* FindUserByUsernamne(List *a, char[USERNAME]);

void DelGroup(List *a);
void DelNetwork(List *a);

#endif