#include "base.h"

#define NAME 50
#define USERNAME 12

typedef struct user{
    char name[NAME], username[USERNAME];
    List *colleges, *request;
}User;

void RegisterUser(List*);
void ShowUsers(List*);
void ShowColleges(User*);
void suggestions(User *);
void Collegesrequest(List *);
void addrequest(User *, User *);
void Showrequests(List  *);

User* FindUserByUsernamne(List*, char[USERNAME]);