#include "user.h"

#include <stdlib.h>
#include <stdio.h>

void RegisterUser(List *allUsers){
    User *user = (User*)malloc(sizeof(User));

    printf("\nDigite seu name: ");
    scanf("%s", user->name);
    printf("\nDigite seu username:");
    scanf("%s", user->username);

    Create(user->colleges);
    
    Push(allUsers, user);
}

void ShowColleges(User *user){
    ShowUsers(user->colleges);
}
void suggestions(User *user){
    
}
void ShowUsers(List *l){
    Node *temp = l->start;

    while(temp != NULL){
        printf("%f", temp->info->username);
        temp = temp->next;
    }
};

User* FindUserByUsernamne(List *l, char target[USERNAME]){
    Node *temp = l->start;
    
    while(temp != NULL){
        for(int i = 0; i < USERNAME; i++){
            if(target[i] != temp->info->name[i]){
                break;
            } else {
                if(i == USERNAME - 1){
                    return temp;
                }
            }
        }
    }

    return temp;
}