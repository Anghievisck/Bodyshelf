
#include "base.h"
#include "user.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
typedef struct user User;

void RegisterUser(List *allUsers){
    //Aloco o "usuario"
    User *usera = (User*)malloc(sizeof(User));
    if (usera == NULL) {
        fprintf(stderr, "Error allocating memory for user\n");
        return;
    }
    //Aloco as listas que estao no usuario, nao sei pq precisa achei que ja vinha com o usuario mas nao vem
    usera->colleges = malloc(sizeof(List));
    usera->msg = malloc(sizeof(List));
    usera->request = malloc(sizeof(List));
    //leitura dos dados do usuario
    printf("Digite seu name: ");
    scanf("%s", usera->name);
    printf("\n");
    printf("Digite seu username:");
    scanf("%s", usera->username);
    printf("\n");
    //crio as listas do usuario
    Create(usera->colleges);
    Create(usera->request);
    Create(usera->msg);
    //bele aq fica + chato mas é o seguinte a lista guarda um *Dado nao um *usuario entao é necessario coloca esse seu usuario nesse tal de casulo do tipo *Dado
    //e esse casulo que vai para as listas esse pensamento vai acontecer em quase todas as funçoes do codigo
    Dado *casulo =(Dado*)malloc(sizeof(Dado));
    casulo->info=usera;
    Push(allUsers, casulo);
}
//essa e simples apenas imprime a lista de colegas de um usuario
void ShowColleges(User *user){
    
    ShowUsers(user->colleges);
}
//essa diferente da funçao de cima le qual o usuario
void Showmycolleges(List *allusers){
    printf("Entre com o seu apelido:");
    char username[12];
    scanf("%s", &username);
    printf("\n");
    User *user = FindUserByUsernamne(allusers, username);
    if(user == NULL){
        printf("Usuario nao encontrado");
        return;
    }
    printf("Seus colegas sao:\n");
    ShowColleges(user);
}
//essa recebe o usuario e printa todos os amigos dos amigos.obs provavelmento devo cria Mysuggestions mas isso é dbas de faze
void suggestions(User *user){
    Node *temp = user->colleges->start;
    for(int i=0; i<user->colleges->total; i++){
        ShowColleges(temp->info->info);
        temp=temp->next;
    }
}
//essa funçao vai permite um usuario a enviar para outro um convite de amizade
void Collegesrequest(List *allusers){
    //usuario que esta enviando
    printf("Entre com o seu apelido:");
    char username[12];
    scanf("%s", &username);
    printf("\n");
    User *user = FindUserByUsernamne(allusers, username);
    if(user == NULL){
        printf("Usuario nao encontrado");
        return;
    }
    //usuario alvo do convite
    char target[12];
    printf("Digite o apelido de quem quer ser parcerio:");
    scanf("%s", &target);
    printf("\n");
    User *alvo = FindUserByUsernamne(allusers, target);
    if(alvo == NULL){
        printf("Usuario nao encontrado");
        return;
    }
    //logo abaixo explico essa funçao
    addrequest(alvo, user);
    printf("Pedido encaminhado com sucesso\n");
}
void addrequest(User *aceitas, User *aguardo){
    if(aceitas != NULL && aguardo != NULL){
        //novamente aq temos um *usuario e queremos *dado para colocar na lista de request do alvo entao eu faço o casulo
        Dado *casulo =(Dado*)malloc(sizeof(Dado));
        casulo->info=aguardo;
        Push(aceitas->request, casulo);
    }
}
void Showrequests(List  *allusers){
    //essa funçao permite um usuario a ver a sua lista de convites
    printf("Entre com o seu apelido:");
    char username[12];
    scanf("%s", &username);
    printf("\n");
    User *user = FindUserByUsernamne(allusers, username);
    if(user == NULL){
        printf("Usuario nao encontrado");
        return;
    }
    //estou trabalhando essa lista como uma fila ou seja eu to pegando pelo final da lista apenas
    //se a lista de convites estiver vazia
    if(user->request->total==0){
        printf("Sem solicitacoes\n");
        return;
    }else{
        //percorrendo todos os termos da lista user->request pelo fim 
        User *temp = user->request->end->info->info;
        while(temp != NULL){
            int loop=1;
            char choice;
            //para evitar comando invalidos
            while(loop==1){
                printf("%s quer ser seu parcerio(a).Aceita (S/N)?", temp->username);
                scanf("%c", &choice);
                printf("\n");
                if(choice!='S' && choice!='N'){
                    printf("\nComando invalido\n");
                }else{
                    loop=0;
                }
            }
            //Se aceita eu adiciona cada um na lista de amigos do outro
            if(choice == 'S'){
                Dado *casulo =(Dado*)malloc(sizeof(Dado));
                casulo->info=temp;
                Push(user->colleges, casulo);
                Dado *casulo2 =(Dado*)malloc(sizeof(Dado));
                casulo2->info=user;
                Push(temp->colleges, casulo2);
            }
            //retirando o convite 
            int erro;
            Out(user->request, &erro);
            //se a lista estiver nao estiver vazia eu pego o novo ultimo convite
            if(user->request->end!=NULL){
                temp = user->request->end->info->info;
            }else{
                //se a lista estiver vazia
                return;
            }
        }
        return;
    }
}
void sendmsg(List *allusers){
    //mesmo codigo que le o usuario e acha um alvo mas dessa vez queremos enviar uma msg nao um convite
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
    //lendo a msg
    Msg *txt = (Msg*)malloc(sizeof(Msg));
    printf("Entre com a mensagem:");
    scanf("%s", &txt->name);
    //"assinando" a msg
    strcpy(txt->username, username);
    //igual com usuario é necessario o casulo para colocar a msg numa lista
    Dado *casulo =(Dado*)malloc(sizeof(Dado));
    casulo->msg=txt;
    Push(alvo->msg, casulo);
}
void showmsg(List *allusers){
    //le um usuario para poder mostrar suas mensagens
    printf("Entre com o seu apelido:");
    char username[12];
    scanf("%s", &username);
    printf("\n");
    User *user = FindUserByUsernamne(allusers, username);
    if(user == NULL){
        printf("Usuario nao encontrado");
        return;
    }
    //Se a lista msg estiver vazia tem ate msm uma super recomendação
    if(user->msg->start == NULL){
        printf("Sem mensagens, procure + amigos usando a funcao suggestions");
        return;
    }
    //aq percorro a lista msg 
    printf("Suas mensagens sao:");
    while(user->msg->start!=NULL){
        //bele a logica das é a seguinte para acessar a nossa mensgens em expecifico temos o seguinte caminho
        //todo usuario tem a lista msg essa lista encadeada tem um começo que é um bloco que tem como info um * da union essa union pode guarda tanto um usuario/
        //quanto uma msg mas aq queremos uma msg entao com user->msg-start->info->msg chegamos na primeira mensagem da lista, o seu username é a sua assinatura
        //ja name msg em si
        printf("(%s)%s\n", user->msg->start->info->msg->username, user->msg->start->info->msg->name);
        int erro;
        //retiro a primeira msg.
        Pop(user->msg, &erro);
    }
    //Aq é evidente o uso de uma pilha ja que as primeiras mensagens que aparecem sao as ultimas que foram enviadas
    printf("Mensagens exibidas");
}
void ShowUsers(List *l){
    //percorre uma lista printando o apelido dos usuarios nela 
    Node *temp = l->start;
    while(temp != NULL){
        printf("%s\n", temp->info->info->username);
        temp = temp->next;
    }
};
User* FindUserByUsernamne(List *l, char target[USERNAME]){
    //percorre uma lista verificando se ha um usuario com o mesmo nome que o dado se sim ela devolve esse usuario
    //se nao ela retorna NULL
    Node *temp = l->start;
    while(temp != NULL){
        if(strcmp(target, temp->info->info->username)==0){
            return(temp->info->info);
        }
        temp = temp->next;
    }

    return (NULL);
}