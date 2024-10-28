
#include "base.h"
#include "user.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
typedef struct user User;
void dellrede(List *allusers){
    //para cada usuario
    int total=allusers->total;
    Node *aux=allusers->start;
    for(int i=0; i<total; i++){
        User *temp=aux->info->user;
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
        for(int j=0; j<k; j++){
            //apagando apenas o casulo quanto o bloco
            //note que diferente de msg a info dentro do casulo é um user que esta allusers logo deve ser apagado no decorrer do codigo
            Pop(temp->colleges, NULL);
        }
        //apagando a lista em si
        free(temp->colleges);
        k=temp->request->total;
        for(int j=0; j<k; j++){
            //mesma logica da lista colleges
            Pop(temp->request, NULL);
        }
        free(temp->request);
        k=temp->blacklist->total;
        for(int j=0; j<k; j++){
            Pop(temp->blacklist, NULL);
        }
        k=temp->groupsrequest->total;
        for(int j=0; j<k; j++){
            Pop(temp->groupsrequest, NULL);
        }
        free(temp->blacklist);
        printf("to aq");
        k=temp->groupleader->total;
        for(int j=0; j<k; j++){
            DelgropSys(temp->groupleader->start, temp);
        }
        printf("aq tambem");
        aux=aux->next;
    }
    printf("\nto aq\n");
    //pela forma que eu escolhi faze os grupos prefiri separar aq pois fica +seguro e simples;
    for(int i=0; i<total; i++){
        User *temp=allusers->start->info->user;
        free(temp->groups);
        free(temp->groupleader);
        free(temp);
        int erro;
        Pop(allusers, &erro);
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
            printf("Amigos:\n");
            ShowColleges(temp->info->user);
            printf("\n");
            printf("Bloqueados:\n");
            ShowBlocks(temp->info->user);
            printf("\n");
            printf("E faz parte destes grupos:\n ");
            Showgroups(temp->info->user);
            temp=temp->next;
            i++;
        }
    }else{
        printf("Rede sem usuarios\n");
    }
}
void PassTheCrown(List *allusers){
    printf("Entre com o seu apelido:");
    char username[12];
    scanf("%s", &username);
    printf("\n");
    User *user = FindUserByUsernamne(allusers, username);
    if(user == NULL){
        printf("Usuario nao encontrado");
        return;
    }
    if(user->groupleader->total==0){
        printf("Voce nao é lider de nenhum grupo :p.\n");
        return;
    }
    printf("Voce é lider destes grupos:");
    ShowLeadergroups(user);
    char temp[12];
    printf("Escolha um Grupo: ");
    scanf("%s", &temp);
    Node *grupo;
    grupo=FindGroupNodeByName(user->groupleader, temp);
    if(grupo==NULL){
        printf("Nenhum grupo selecionado.\n");
        return;
    }
    printf("Esses são os membros deste grupo:\n");
    ShowUsers(grupo->info->grp->members);
    printf("Qual sera o proximo lider: ");
    char target[12];
    scanf("%s ", &target);
    User *alvo=FindUserByUsernamne(grupo->info->grp->members, target);
    if(alvo==NULL){
        printf("Usuario nao encontrado.\n");
        return;
    }
    Dado *casulo =(Dado*)malloc(sizeof(Dado));
    casulo->grp=grupo->info->grp;
    Push(alvo->groupleader, casulo);
    TurnFirst(user->groupleader, grupo);
    int erro;
    Pop(user->groupleader, &erro);
}
void DelgroupUser(List *allusers){
    printf("Entre com o seu apelido:");
    char username[12];
    scanf("%s", &username);
    printf("\n");
    User *user = FindUserByUsernamne(allusers, username);
    if(user == NULL){
        printf("Usuario nao encontrado");
        return;
    }
    if(user->groupleader->total==0){
        printf("Voce nao é lider de nenhum grupo :p.\n");
        return;
    }
    printf("Voce é lider destes grupos:\n");
    ShowLeadergroups(user);
    char temp[12];
    printf("Escolha um Grupo: ");
    scanf("%s", &temp);
    printf("\n");
    Node *grupo;
    grupo=FindGroupNodeByName(user->groupleader, temp);
    if(grupo==NULL){
        printf("Nenhum grupo selecionado.\n");
        return;
    }
    char choice;
    printf("Voce tem certeza disso? Se sim digite S: ");
    scanf(" %c", &choice);
    printf("\n");
    int erro;
    if(choice=='S'){
        DelgropSys(grupo, user);
    }
}
void DelgropSys(Node *grupo, User *leader){
    int erro;
    User *temp=grupo->info->grp->members->start->info->user;
    while(temp!=NULL){
        Node *aux=FindGroupNodeByName(temp->groups, grupo->info->grp->groupname);
        TurnFirst(temp->groups, aux);
        Pop(temp->groups, &erro);
        Pop(grupo->info->grp->members, &erro);
        temp = grupo->info->grp->members->start->info->user;
    }
    printf("aq tambem\n");
    free(grupo->info->grp);
    free(grupo->info->grp->members);
    TurnFirst(leader->groupleader, grupo);
    Pop(leader->groupleader, &erro);
}
void Makegroup(List *allusers){
    printf("Entre com o seu apelido:");
    char username[12];
    scanf("%s", &username);
    printf("\n");
    User *user = FindUserByUsernamne(allusers, username);
    if(user == NULL){
        printf("Usuario nao encontrado");
        return;
    }
    Group *grp =(Group*)malloc(sizeof(Group));
    grp->members=malloc(sizeof(List));
    Create(grp->members);
    printf("Entre com o nome do grupo: ");
    scanf("%s", grp->groupname);
    Dado *casulo =(Dado*)malloc(sizeof(Dado));
    Dado *casulo2 =(Dado*)malloc(sizeof(Dado));
    casulo2->user = user;
    casulo->grp=grp;
    Push(user->groupleader, casulo);
    Push(user->groups, casulo);
    Push(grp->members, casulo2);
}
void AddCollegeforGroup(List *allusers){
    printf("Entre com o seu apelido:");
    char username[12];
    scanf("%s", &username);
    printf("\n");
    User *user = FindUserByUsernamne(allusers, username);
    if(user == NULL){
        printf("Usuario nao encontrado");
        return;
    }
    printf("Voce é lider destes grupos:");
    ShowLeadergroups(user);
    char temp[12];
    printf("Escolha um Grupo: ");
    scanf("%s", &temp);
    Group *grupo;
    grupo=FindGroupByName(user->groupleader, temp);
    if(grupo==NULL){
        printf("Nenhum grupo selecionado.\n");
        return;
    }
    char target[12];
    printf("Digite o apelido de quem voce quer adicionar ao grupo:");
    scanf("%s", &target);
    printf("\n");
    if(FindUserByUsernamne(grupo->members, target)!=NULL){
        printf("Ele ja esta no grupo :p\n");
        return;
    }
    User *alvo = FindUserByUsernamne(allusers, target);
    if(FindUserByUsernamne(alvo->blacklist, user->username)!=NULL){
        printf("voce esta bloqueado :p\n");
        return;
    }
    if(FindUserByUsernamne(user->blacklist, alvo->username)!=NULL){
        printf("Tu primeiro da Block no mano e quer senta na janelinha, desbloqueia antes primeiro.\n");
        return;
    }
    Dado *casulo =(Dado*)malloc(sizeof(Dado));
    Dado *casulo2 =(Dado*)malloc(sizeof(Dado));
    casulo->grp=grupo;
    casulo2->user=alvo;
    Push(alvo->groupsrequest, casulo);
    Push(grupo->members, casulo2);
}
void Groupsrequests(List *allusers){
    //essa funçao permite um usuario a ver a sua lista de convites para grupos
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
    if(user->groupsrequest->total==0){
        printf("Sem solicitacoes\n");
        return;
    }else{
        //percorrendo todos os termos da lista user->request pelo fim 
        Group *temp = user->groupsrequest->end->info->grp;
        while(temp != NULL){
            int loop=1;
            char choice;
            //para evitar comando invalidos
            while(loop==1){
                printf("O grupo %s quer voce com eles.Aceita (S/N)?", temp->groupname);
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
                casulo->grp=temp;
                Push(user->groups, casulo);
                Dado *casulo2 =(Dado*)malloc(sizeof(Dado));
                casulo2->user=user;
                Push(temp->members, casulo2);
            }
            //retirando o convite 
            int erro;
            Out(user->groupsrequest, &erro);
            //se a lista estiver nao estiver vazia eu pego o novo ultimo convite
            if(user->groupsrequest->end!=NULL){
                temp = user->groupsrequest->end->info->grp;
            }else{
                //se a lista estiver vazia
                return;
            }
        }
        return;
    }
}
void SendmsgGroup(List *allusers){
    printf("Entre com o seu apelido:");
    char username[12];
    scanf("%s", &username);
    printf("\n");
    User *user = FindUserByUsernamne(allusers, username);
    if(user == NULL){
        printf("Usuario nao encontrado");
        return;
    }
    printf("Voce é faz parte destes grupos:\n");
    Showgroups(user);
    char temp[12];
    printf("Escolha um Grupo: ");
    scanf("%s", &temp);
    printf("\n");
    Group *grupo;
    grupo=FindGroupByName(user->groups, temp);
    if(grupo==NULL){
        printf("Nenhum grupo selecionado");
        return;
    }
    char tempo[250];
    printf("Entre com a mensagem :");
    getchar(); 
    fgets(tempo, sizeof(tempo), stdin);
    printf("\n");
    Node *aux=grupo->members->start;
    while(aux!=NULL){
        Msg *txt = (Msg*)malloc(sizeof(Msg));
        strcpy(txt->name, temp);
        strcpy(txt->username, username);
        strcpy(txt->chat, grupo->groupname);
        Dado *casulo =(Dado*)malloc(sizeof(Dado));
        casulo->msg=txt;
        if(aux->info->user->username!=username){
            Push(aux->info->user->msg, casulo);
        }
        aux=aux->next;
    }
}
Node* FindGroupNodeByName(List *l, char target[12]){
    Node *temp = l->start;
    while(temp != NULL){
        if(strcmp(target, temp->info->grp->groupname)==0){
            return(temp);
        }
        temp = temp->next;
    }
    return (NULL);
}
Group* FindGroupByName(List *l, char target[12]){
    Node *temp = l->start;
    while(temp != NULL){
        if(strcmp(target, temp->info->grp->groupname)==0){
            return(temp->info->grp);
        }
        temp = temp->next;
    }
    return (NULL);
}
void ShowLeadergroups(User *user){
    Node *temp = user->groupleader->start;
        while(temp!=NULL){
            printf("%s\n", temp->info->grp->groupname);
            temp=temp->next;
        }
}
void Showgroups(User *user){
    Node *temp = user->groups->start;
    while(temp!=NULL){
            printf("%s\n", temp->info->grp->groupname);
            temp=temp->next;
    }
}
void RegisterUser(List *allUsers){
    //Aloco o "usuario"
    User *user = (User*)malloc(sizeof(User));
    if (user == NULL) {
        printf("Erro\n");
        return;
    }
    //leitura dos dados do usuario
    printf("Digite seu name: ");
    getchar(); 
    fgets(user->name, sizeof(user->name), stdin);
    user->name[strcspn(user->name, "\n")] = 0;
    printf("\n");
    int loop=1;
    printf("Digite seu username: ");
    while(loop==1){
        fgets(user->username, sizeof(user->username), stdin);
        user->username[strcspn(user->username, "\n")] = 0;
        printf("\n");
        if (strchr(user->username,' ')) {
            printf("Por favor retire o espaco do apelido.\nPor favor informe outro: ");
        }else{
            if(FindUserByUsernamne(allUsers, user->username)==NULL){
                loop=0;
            }else{
                printf("Seu username ja existe...\nPor favor informe outro: ");
            }
        }
    }

    //Aloco as listas que estao no usuario, nao sei pq precisa achei que ja vinha com o usuario mas nao vem
    user->colleges = malloc(sizeof(List));
    user->msg = malloc(sizeof(List));
    user->request = malloc(sizeof(List));
    user->blacklist = malloc(sizeof(List));
    user->groups = malloc(sizeof(List));
    user->groupleader = malloc(sizeof(List));
    user->groupsrequest = malloc(sizeof(List));
    //crio as listas do usuario
    Create(user->colleges);
    Create(user->request);
    Create(user->msg);
    Create(user->blacklist);
    Create(user->groups);
    Create(user->groupleader);
    Create(user->groupsrequest);
    //bele aq fica + chato mas é o seguinte a lista guarda um *Dado nao um *usuario entao é necessario coloca esse seu usuario nesse tal de casulo do tipo *Dado
    //e esse casulo que vai para as listas esse pensamento vai acontecer em quase todas as funçoes do codigo
    Dado *casulo =(Dado*)malloc(sizeof(Dado));
    casulo->user=user;
    Push(allUsers, casulo);
}
//essa e simples apenas imprime a lista de colegas de um usuario
void ShowColleges(User *user){ 
    ShowUsers(user->colleges);
}
//Da o famigerado block
void Block(List *allusers){
    printf("Entre com o seu apelido:");
    char username[12];
    scanf("%s", &username);
    printf("\n");
    User *user = FindUserByUsernamne(allusers, username);
    if(user == NULL){
        printf("Usuario nao encontrado");
        return;
    }
    //usuario alvo do block
    char target[12];
    printf("Digite o apelido de quem voce quer bloquear:");
    scanf("%s", &target);
    printf("\n");
    if(FindUserByUsernamne(user->blacklist, target)!=NULL){
        printf("Ele ja esta bloqueado :p\n");
        return;
    }
    //caso eles sejam amigos
    Node *temp=FindNodeByUsernamne(user->colleges, target);
    if(temp!=NULL){
        Node *aux=FindNodeByUsernamne(temp->info->user->colleges, username);
        int erro;
        TurnFirst(temp->info->user->colleges, aux);
        Pop(temp->info->user->colleges, &erro);
        TurnFirst(user->colleges, temp);
        Pop(user->colleges, &erro);
        printf("Amizade removida automaticamente\n");
    }
    temp=FindNodeByUsernamne(user->request, target);
    if(temp!=NULL){
        TurnFirst(user->request,temp);
        int erro;
        Pop(user->request, &erro);
        printf("O convite enviado a voce por este usuario foi automaticamente removido\n");
    }
    User *alvo = FindUserByUsernamne(allusers, target);
    if(alvo == NULL){
        printf("Usuario nao encontrado.\n");
        return;
    }
    temp=FindNodeByUsernamne(alvo->request, username);
    if(temp!=NULL){
        TurnFirst(alvo->request,temp);
        int erro;
        Pop(alvo->request, &erro);
        printf("O convite enviado por voce a este usuario foi automaticamente removido\n");
    }
    Dado *casulo =(Dado*)malloc(sizeof(Dado));
    casulo->user=alvo;
    Push(user->blacklist, casulo);
    printf("Usuario bloqueado\n");
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
    if(FindUserByUsernamne(user->colleges, target)!=NULL){
        printf("Ele ja é seu amigo :p\n");
        return;
    }
    User *alvo = FindUserByUsernamne(allusers, target);
    if(FindUserByUsernamne(alvo->blacklist, user->username)!=NULL){
        printf("voce esta bloqueado :p\n");
        return;
    }
    if(FindUserByUsernamne(user->blacklist, alvo->username)!=NULL){
        printf("Tu primeiro da Block no mano e quer senta na janelinha, desbloqueia antes primeiro.\n");
        return;
    }
    if(alvo == NULL){
        printf("Usuario nao encontrado");
        return;
    }
    //logo abaixo explico essa funçao
    addrequest(alvo, user);
    printf("Pedido encaminhado com sucesso\n");
}
void RemoveCollege(List *allusers){
    //usuario que esta enviando
    printf("Entre com o seu apelido: ");
    char username[12];
    scanf("%s", &username);
    printf("\n");
    User *user = FindUserByUsernamne(allusers, username);
    if(user == NULL){
        printf("Usuario nao encontrado");
        return;
    }
    //usuario alvo do convite
    printf("Seus amigos sao:\n");
    ShowColleges(user);
    char target[12];
    printf("Digite o apelido de quem voce quer remover: ");
    scanf("%s", &target);
    printf("\n");
    Node *alvo = FindNodeByUsernamne(user->colleges, target);
    if(alvo == NULL){
        printf("Amigo nao encontrado");
        return;
    }
    Node *aux=FindNodeByUsernamne(alvo->info->user->colleges, username);
    int erro;
    TurnFirst(alvo->info->user->colleges, aux);
    Pop(alvo->info->user->colleges, &erro);
    TurnFirst(user->colleges, alvo);
    Pop(user->colleges, &erro);
}
void RemoveBlock(List *allusers){
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
    printf("As pessoas bloqueadas por voce são:\n");
    ShowBlocks(user);
    char target[12];
    printf("Digite o apelido de quem voce quer remover:");
    scanf("%s", &target);
    printf("\n");
    Node *alvo = FindNodeByUsernamne(user->blacklist, target);
    if(alvo == NULL){
        printf("Usuario nao encontrado");
        return;
    }
    TurnFirst(user->blacklist, alvo);
    int erro;
    Pop(user->blacklist, &erro);
}
void ShowBlocks(User *user){
    ShowUsers(user->blacklist);
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
    printf("Entre com a mensagem :");
    getchar(); 
    fgets(txt->name, sizeof(txt->name), stdin);
    printf("\n");
    //"assinando" a msg
    strcpy(txt->username, username);
    strcpy(txt->chat, "DM");
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
        printf("enviado por(%s) no chat%s, %s\n", user->msg->start->info->msg->username, user->msg->start->info->msg->chat ,user->msg->start->info->msg->name);
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
Node* FindNodeByUsernamne(List *l, char target[USERNAME]){
    //percorre uma lista verificando se ha um usuario com o mesmo nome que o dado se sim ela devolve esse usuario
    //se nao ela retorna NULL
    Node *temp = l->start;
    while(temp != NULL){
        if(strcmp(target, temp->info->user->username)==0){
            return(temp);
        }
        temp = temp->next;
    }
    return (NULL);
}
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