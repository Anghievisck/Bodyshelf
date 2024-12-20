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
void ShowMyColleges(List *a);
void ShowCollegeRequest(List *a);
void ShowMsg(List *a);

void RemoveCollege(List *a);
void RemoveBlock(List *a);
void Block(List *a);
void DelGroup(List *a);
void DelNetwork(List *a);

#endif