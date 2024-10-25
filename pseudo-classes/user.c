
#include "base.h"
#include "user.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
typedef struct user User;

void RegisterUser(List *allUsers){
    User *usera = (User*)malloc(sizeof(User));
    printf("\nDigite seu name: ");
    scanf("%s", usera->name);
    printf("\nDigite seu username:");
    scanf("%s", usera->username);
    Create(usera->colleges);
    Create(usera->request);
    Create(usera->msg);
    Dado casulo;
    casulo.info=usera;
    Push(allUsers, &casulo);
}
void ShowColleges(User *user){
    ShowUsers(user->colleges);
}
void suggestions(User *user){
    Node *temp = user->colleges->start;
    for(int i=0; i<user->colleges->total; i++){
        ShowColleges(temp->info->info);
        temp=temp->next;
    }
}
void Collegesrequest(List *allusers){
    printf("Entre com o seu apelido:");
    char username[12];
    scanf("%s", &username);
    printf("\n");
    User *user = FindUserByUsernamne(allusers, username);
    if(user == NULL){
        printf("Usuario nao encontrado");
        return;
    }
    char target[12];
    printf("Digite o apelido de quem quer ser parcerio:");
    scanf("%s", &target);
    printf("\n");
    User *alvo = FindUserByUsernamne(allusers, target);
    if(alvo == NULL){
        printf("Usuario nao encontrado");
        return;
    }
    addrequest(alvo, user);
    printf("Pedido encaminhado com sucesso");
}
void addrequest(User *aceitas, User *aguardo){
    if(aceitas != NULL && aguardo != NULL){
        Dado casulo;
        casulo.info=aguardo;
        Push(aceitas->request, &casulo);
    }
}
void Showrequests(List  *allusers){
    printf("Entre com o seu apelido:");
    char username[12];
    scanf("%s", &username);
    printf("\n");
    User *user = FindUserByUsernamne(allusers, username);
    if(user == NULL){
        printf("Usuario nao encontrado");
        return;
    }
    User *temp = user->request->end->info->info;
    if(temp == NULL){
        printf("Sem solicitacoes");
    }else{
        while(temp != NULL){
            temp = user->request->end->info->info;
            int loop=1;
            char choice;
            while(loop==1){
                printf("%s quer ser seu parcerio(a).Aceita (S/N)?", temp->name);
                scanf("%c", &choice);
                if(choice!='S' || choice!='N'){
                    printf("\nComando invalido\n");
                }else{
                    loop=0;
                }
            }
            if(choice == 'S'){
                Dado casulo;
                casulo.info=temp;
                Push(user->colleges, &casulo);
                casulo.info=user;
                Push(temp->colleges, &casulo);
            }
            int erro;
            Out(user->request, &erro);
        }
    }
}
void sendmsg(List *allusers){
    printf("Entre com o seu apelido:");
    char username[12];
    scanf("%s", &username);
    printf("\n");
    User *user = FindUserByUsernamne(allusers, username);
    if(user == NULL){
        printf("Usuario nao encontrado");
        return;
    }
    char target[12];
    printf("Digite o apelido de seu amigo:");
    scanf("%s", &target);
    printf("\n");
    User *alvo = FindUserByUsernamne(allusers, target);
    if(alvo == NULL){
        printf("Usuario nao encontrado");
        return;
    }
    Msg *txt = (Msg*)malloc(sizeof(Msg));
    printf("Entre com a mensagem:");
    scanf("%s", &txt->name);
    strcpy(txt->username, username);
    Dado casulo;
    casulo.msg=txt;
    Push(alvo->msg, &casulo);
}
void showmsg(List *allusers){
    printf("Entre com o seu apelido:");
    char username[12];
    scanf("%s", &username);
    printf("\n");
    User *user = FindUserByUsernamne(allusers, username);
    if(user == NULL){
        printf("Usuario nao encontrado");
        return;
    }
    if(user->msg->start == NULL){
        printf("Sem mensagens, procure + amigos usando a funcao suggestions");
        return;
    }
    printf("Suas mensagens sao:");
    while(user->msg->start!=NULL){

        printf("(%s)%s", user->msg->start->info->msg->username, user->msg->start->info->msg->name);
        int erro;
        Pop(user->msg, &erro);
    }
    printf("Mensagens exibidas");
}
void ShowUsers(List *l){
    Node *temp = l->start;

    while(temp != NULL){
        printf("%f", temp->info->info->username);
        temp = temp->next;
    }
};


User* FindUserByUsernamne(List *l, char target[USERNAME]){
    Node *temp = l->start;
    while(temp != NULL){
        for(int i = 0; i < USERNAME; i++){
            if(target[i] != temp->info->info->name[i]){
                break;
            } else {
                if(i == USERNAME - 1){
                    return (temp->info->info);
                }
            }
        }
        temp = temp->next;
    }

    return (temp->info->info);
}