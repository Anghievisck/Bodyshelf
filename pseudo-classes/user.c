
#include "base.h"
#include "user.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
typedef struct user User;
void dellrede(List *allusers){
    //para cada usuario
    int total=allusers->total;
    for(int i=0; i<total; i++){
        //pegando o primeiro usuario
        User *temp=allusers->start->info->user;
        //apagando lista msm
        int k=temp->msg->total;
        for(int j=0; j<k; j++){
            //apagando a info dentro do casulo
            free(temp->msg->start->info->msg);
            //apagando tanto o casulo quanto o bloco que esta o casulo com o Pop
            Pop(temp->msg, NULL);
        }
        //apagando a lista em si
        free(temp->msg);
        k=temp->colleges->total;
        for(int j=0; j<temp->colleges->total; j++){
            //apagando apenas o casulo quanto o bloco
            //note que diferente de msg a info dentro do casulo é um user que esta allusers logo deve ser apagado no decorrer do codigo
            Pop(temp->colleges, NULL);
        }
        //apagando a lista em si
        free(temp->colleges);
        k=temp->request->total;
        for(int j=0; j<temp->request->total; j++){
            //mesma logica da lista colleges
            Pop(temp->request, NULL);
        }
        free(temp->request);
        //apagando o bloco e o casulo em que o usuario esta
        Pop(allusers, NULL);
        //apagando o usuario finalmente
        free(temp);
    }
    //em tese allusers deve ficar que nem quando criado
    allusers->total=0;
}
void PrintNet(List *alluser){
    int i=1;
    if(alluser->total!=0){
        Node *temp = alluser->start;
        while(temp!=NULL){
            printf("Usuario %d\n", i);
            printf("Nome:%s\nApelido:%s\n", temp->info->user->name, temp->info->user->username);
            printf("Amigos\n:");
            ShowColleges(temp->info->user);
            temp=temp->next;
            i++;
        }
    }else{
        printf("Rede sem usuarios\n");
    }
}
void RegisterUser(List *allUsers){
    //Aloco o "usuario"
    User *usera = (User*)malloc(sizeof(User));
    if (usera == NULL) {
        fprintf(stderr, "Error allocating memory for user\n");
        return;
    }
    //leitura dos dados do usuario
    printf("Digite seu name: ");
    scanf("%s", usera->name);
    printf("\n");
    int loop=1;
    printf("Digite seu username: ");
    while(loop==1){
        scanf("%s", usera->username);
        printf("\n");
        if(FindUserByUsernamne(allUsers, usera->username)==NULL){
            loop=0;
        }else{
            printf("Seu username ja existe...\nPor favor informe outro: ");
        }
    }

    //Aloco as listas que estao no usuario, nao sei pq precisa achei que ja vinha com o usuario mas nao vem
    usera->colleges = malloc(sizeof(List));
    usera->msg = malloc(sizeof(List));
    usera->request = malloc(sizeof(List));

    //crio as listas do usuario
    Create(usera->colleges);
    Create(usera->request);
    Create(usera->msg);
    //bele aq fica + chato mas é o seguinte a lista guarda um *Dado nao um *usuario entao é necessario coloca esse seu usuario nesse tal de casulo do tipo *Dado
    //e esse casulo que vai para as listas esse pensamento vai acontecer em quase todas as funçoes do codigo
    Dado *casulo =(Dado*)malloc(sizeof(Dado));
    casulo->user=usera;
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
void Suggestions(List *alluser){
    printf("Entre com o seu apelido:");
    char username[12];
    scanf("%s", &username);
    printf("\n");
    User *user = FindUserByUsernamne(alluser, username);
    Node *temp = user->colleges->start;
    for(int i=0; i<user->colleges->total; i++){
        ShowColleges(temp->info->user);
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
        casulo->user=aguardo;
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
        User *temp = user->request->end->info->user;
        while(temp != NULL){
            int loop=1;
            char choice;
            //para evitar comando invalidos
            while(loop==1){
                printf("%s quer ser seu parcerio(a).Aceita (S/N)?", temp->username);
                scanf(" %c", &choice);
                printf("\n");
                if(choice!='S' && choice!='N'){
                    printf("\nComando invalido\n");
                }else{
                    break;
                }
            }
            //Se aceita eu adiciono cada um na lista de amigos do outro
            if(choice == 'S'){
                Dado *casulo =(Dado*)malloc(sizeof(Dado));
                casulo->user=temp;
                Push(user->colleges, casulo);
                Dado *casulo2 =(Dado*)malloc(sizeof(Dado));
                casulo2->user=user;
                Push(temp->colleges, casulo2);
            }
            //retirando o convite 
            int erro;
            Out(user->request, &erro);
            //se a lista estiver nao estiver vazia eu pego o novo ultimo convite
            if(user->request->end!=NULL){
                temp = user->request->end->info->user;
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
    User *alvo = FindUserByUsernamne(user->colleges, target);
    if(alvo == NULL){
        printf("Usuario nao encontrado");
        return;
    }
    //lendo a msg
    Msg *txt = (Msg*)malloc(sizeof(Msg));
    printf("Entre com a mensagem (sem espacos por favor :p):\n");
    char esteregg[250];
    //scanf("%250s", &txt->name);
    fgets(esteregg, sizeof(esteregg), stdin);
    strcpy(txt->name, esteregg);
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
        free(user->msg->start->info->msg);
        Pop(user->msg, &erro);
    }
    //Aq é evidente o uso de uma pilha ja que as primeiras mensagens que aparecem sao as ultimas que foram enviadas
    printf("Mensagens exibidas");
}
void ShowUsers(List *l){
    //percorre uma lista printando o apelido dos usuarios nela 
    Node *temp = l->start;
    while(temp != NULL){
        printf("%s\n", temp->info->user->username);
        temp = temp->next;
    }
};
User* FindUserByUsernamne(List *l, char target[USERNAME]){
    //percorre uma lista verificando se ha um usuario com o mesmo nome que o dado se sim ela devolve esse usuario
    //se nao ela retorna NULL
    Node *temp = l->start;
    while(temp != NULL){
        if(strcmp(target, temp->info->user->username)==0){
            return(temp->info->user);
        }
        temp = temp->next;
    }
    return (NULL);
}