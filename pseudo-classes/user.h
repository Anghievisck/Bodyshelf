#include "base.h"

#define NAME 50
#define USERNAME 12

typedef struct user{
    char name[NAME], username[USERNAME];
    List *colleges;
}User;

void RegisterUser(List*);
void ShowUsers(List*);
void ShowColleges(User*);

User FindUserByUsernamne(List*, char[USERNAME]);