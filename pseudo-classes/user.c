#include "user.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Fuções internas:

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

void AddRequest(User *aceitas, User *aguardo){
    if(aceitas != NULL && aguardo != NULL){
        //novamente aq temos um *usuario e queremos *dado para colocar na lista de request do alvo entao eu faço o casulo
        Dado *casulo =(Dado*)malloc(sizeof(Dado));
        casulo->user=aguardo;
        Push(aceitas->request, casulo);
    }
}

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

void ShowGroups(User *user){
    Node *temp = user->groups->start;
    while(temp!=NULL){
            printf("%s\n", temp->info->grp->groupname);
            temp=temp->next;
    }
}

void ShowColleges(User *user){ 
    ShowUsers(user->colleges);
}

void ShowBlocks(User *user){
    ShowUsers(user->blacklist);
}

void ShowLeaderGroups(User *user){
    Node *temp = user->groupleader->start;
        while(temp!=NULL){
            printf("%s\n", temp->info->grp->groupname);
            temp=temp->next;
        }
}

void DelGroupSys(Node *grupo, User *leader){
    int erro;
    int k=grupo->info->grp->members->total;
    Group *grp=grupo->info->grp;
    User *temp=grupo->info->grp->members->start->info->user;
    if(k==1){
        Node *aux=FindGroupNodeByName(leader->groups, grupo->info->grp->groupname);
        Pop(grp->members, &erro);
        TurnFirst(leader->groups, aux);
        Pop(leader->groups, &erro);
        free(grp->members);
        free(grp);
        TurnFirst(leader->groupleader, grupo);
        Pop(leader->groupleader, &erro);
        return;
    }
    for(int i=0; i<k; i++){
        Node *aux=FindGroupNodeByName(temp->groups, grupo->info->grp->groupname);
        Pop(grupo->info->grp->members, &erro);
        TurnFirst(temp->groups, aux);
        Pop(temp->groups, &erro);
        if(grp->members->total!=0){
            temp = grupo->info->grp->members->start->info->user;
        }
    }
    free(grupo->info->grp->members);
    free(grupo->info->grp);
    TurnFirst(leader->groupleader, grupo);
    Pop(leader->groupleader, &erro);
    return;
}

// Funções do TAD

// Apaga todas as informações da rede
void DelNetwork(List *allusers){
    //para cada usuario
    int total=allusers->total;
    Node *aux=allusers->start;
    for(int i=0; i<total; i++){
        User *temp=aux->info->user;
        int k=temp->groupleader->total;
        for(int j=0; j<k; j++){
            DelGroupSys(temp->groupleader->start, temp);
        }
        aux=aux->next;
    }
    for(int i=0; i<total; i++){
        User *temp=allusers->start->info->user;
        //Ja limpos
        int erro;
        free(temp->groups);
        free(temp->groupleader);
        int k=temp->msg->total;
        for(int j=0; j<k; j++){
            //apagando a info dentro do casulo
            free(temp->msg->start->info->msg);
            //apagando tanto o casulo quanto o bloco que esta o casulo com o Pop
            Pop(temp->msg, &erro);
        }
        //apagando a lista em si
        free(temp->msg);
        k=temp->colleges->total;
        for(int j=0; j<k; j++){
            //apagando apenas o casulo quanto o bloco
            //note que diferente de msg a info dentro do casulo é um user que esta allusers logo deve ser apagado no decorrer do codigo
            Pop(temp->colleges, &erro);
        }
        //apagando a lista em si
        free(temp->colleges);
        k=temp->request->total;
        for(int j=0; j<k; j++){
            //mesma logica da lista colleges
            Pop(temp->request, &erro);
        }
        free(temp->request);
        k=temp->blacklist->total;
        for(int j=0; j<k; j++){
            Pop(temp->blacklist, &erro);
        }
        free(temp->blacklist);
        k=temp->groupsrequest->total;
        for(int j=0; j<k; j++){
            Pop(temp->groupsrequest, &erro);
        }
        free(temp->groupsrequest);
        free(temp);
        Pop(allusers, &erro);
    }
    //em tese allusers deve ficar que nem quando criado
    allusers->total=0;
}

/*
    Mostra todos os usuários com os seguintes dados:
        - Nomes
        - Apelidos
        - Amigos
        - Usuários Bloqueados
        - Grupos
*/
void PrintNetwork(List *alluser){
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
            printf("E faz parte destes grupos:\n");
            ShowGroups(temp->info->user);
            temp=temp->next;
            i++;
        }
    }else{
        printf("Rede sem usuarios\n");
    }
}

// Deleta um grupo onde o usuário é o dono do respectivo grupo
void DelGroup(List *allusers){
    printf("Entre com o seu username:");
    char username[12];
    scanf("%s", &username);
    printf("\n");
    User *user = FindUserByUsernamne(allusers, username);
    if(user == NULL){
        printf("Usuario nao encontrado");
        return;
    }
    if(user->groupleader->total==0){
        printf("Voce nao e lider de nenhum grupo :p.\n");
        return;
    }
    printf("Voce e lider destes grupos:\n");
    ShowLeaderGroups(user);
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
        DelGroupSys(grupo, user);
    }
}

// Cria um grupo, o usuário que criou é chamado de Líder do Grupo
void RegisterGroup(List *allusers){
    printf("Entre com o seu username:");
    char username[12];
    scanf("%s", &username);
    printf("\n");
    User *user = FindUserByUsernamne(allusers, username);
    if(user == NULL){
        printf("Usuario nao encontrado");
        return;
    }

    Group *grp = (Group*)malloc(sizeof(Group));
    grp->members=Create(grp->members);

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

// Envia uma solicitação para outro usuário para o mesmo entrar em um certo grupo
void AddCollegeToGroup(List *allusers){
    char username[12], temp[12], target[12];
    
    printf("Entre com o seu username:");
    scanf("%s", &username);
    printf("\n");
    
    User *user = FindUserByUsernamne(allusers, username);

    if(user == NULL){
        printf("Usuario nao encontrado");
        return;
    }

    printf("Voce e lider destes grupos:");
    ShowLeaderGroups(user);

    printf("Escolha um Grupo: ");
    scanf("%s", &temp);

    Group *grupo;
    grupo = FindGroupByName(user->groupleader, temp);

    if(grupo == NULL){
        printf("Nenhum grupo selecionado.\n");
        return;
    }

    printf("Digite o username de quem voce quer adicionar ao grupo:");
    scanf("%s", &target);
    printf("\n");

    if(FindUserByUsernamne(grupo->members, target) != NULL){
        printf("Ele ja esta no grupo...\n");
        return;
    }

    User *alvo = FindUserByUsernamne(user->colleges, target);

    if(alvo == NULL){
        printf("Esse usuário não é seu colega...\n");
        return;
    }

    Dado *casulo =(Dado*)malloc(sizeof(Dado));
    Dado *casulo2 =(Dado*)malloc(sizeof(Dado));

    casulo->grp=grupo;
    casulo2->user=alvo;

    Push(alvo->groupsrequest, casulo);
    Push(grupo->members, casulo2);
}

// Mostra para algum usuário todas as solicitações de grupo enviadas para ele
void GroupsRequests(List *allusers){
    //essa funçao permite um usuario a ver a sua lista de convites para grupos
    printf("Entre com o seu username:");
    char username[12];
    scanf("%s", &username);
    printf("\n");
    User *user = FindUserByUsernamne(allusers, username);
    if(user == NULL){
        printf("Usuario nao encontrado");
        return;
    }
    /*
        Estamos trabalhando essa lista como uma fila, ou seja, pegamos pelo final da lista apenas
        se a lista de convites estiver vazia
    */
    if(user->groupsrequest->total==0){
        printf("Sem solicitacoes\n");
        return;
    }else{
        //percorrendo todos os termos da lista user->request pelo fim 
        Group *temp = user->groupsrequest->end->info->grp;
        while(temp != NULL){
            int loop = 1;
            char choice;
            //para evitar comando invalidos
            while(loop == 1){
                printf("O grupo %s quer voce com eles.Aceita (S/N)?", temp->groupname);
                scanf(" %c", &choice);
                printf("\n");

                // Remove o "case-sensitive" da variável choice
                choice = toupper(choice);

                if(choice != 'S' && choice != 'N'){
                    printf("\nComando invalido\n");
                }else{
                    break;
                }
            }
            // Se aceita, adicionamos cada um na lista de amigos do outro
            if(choice == 'S'){
                Dado *casulo =(Dado*)malloc(sizeof(Dado));
                casulo->grp = temp;
                Push(user->groups, casulo);
                Dado *casulo2 =(Dado*)malloc(sizeof(Dado));
                casulo2->user=user;
                Push(temp->members, casulo2);
            }
            //retirando o convite 
            int erro;
            Out(user->groupsrequest, &erro);
            //se a lista estiver nao estiver vazia, pegamos o novo ultimo convite
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

// Envia uma mensaem para um grupo onde o usuário faz parte
void SendGroupMsg(List *allusers){
    char username[12], temp[12], tempo[250];

    printf("Entre com o seu username:");
    scanf("%s", &username);
    printf("\n");

    User *user = FindUserByUsernamne(allusers, username);

    if(user == NULL){
        printf("Usuario nao encontrado");
        return;
    }

    printf("Voce faz parte destes grupos:\n");
    ShowGroups(user);

    printf("Escolha um Grupo: ");
    scanf("%s", &temp);
    printf("\n");

    Group *grupo;
    grupo = FindGroupByName(user->groups, temp);
    
    if(grupo == NULL){
        printf("Nenhum grupo selecionado");
        return;
    }

    printf("Entre com a mensagem: ");
    getchar(); 
    fgets(tempo, sizeof(tempo), stdin);
    printf("\n");

    Node *aux = grupo->members->start;

    while(aux != NULL){
        if(strcmp(aux->info->user->username, username) != 0){
            Msg *txt = (Msg*)malloc(sizeof(Msg));

            strcpy(txt->name, tempo);
            strcpy(txt->username, username);
            strcpy(txt->chat, grupo->groupname);

            Dado *casulo = (Dado*)malloc(sizeof(Dado));

            casulo->msg = txt;

            Push(aux->info->user->msg, casulo);
        }
        aux = aux->next;
    }
}

// Cria um novo usuário na rede, não permite duplicidade de usernames
void RegisterUser(List *allUsers){
    int loop = 1, i = 1;

    //Aloca um "usuario"
    User *user = (User*)malloc(sizeof(User));

    if (user == NULL) {
        printf("Erro\n");
        return;
    }

    //leitura dos dados do usuario
    printf("Digite seu nome: ");
    getchar(); 
    fgets(user->name, sizeof(user->name), stdin);
    user->name[strcspn(user->name, "\n")] = 0;
    printf("\n");

    printf("Digite seu username: ");

    while(loop == 1){
        fgets(user->username, sizeof(user->username), stdin);
        user->username[strcspn(user->username, "\n")] = 0;
        printf("\n");

        if(strchr(user->username, ' ')) {
            printf("Por favor retire o espaco do username.\nPor favor informe outro: ");
        } else {
            if(FindUserByUsernamne(allUsers, user->username) == NULL){
                loop = 0;
            } else {
                printf("Seu username ja existe...\nPor favor informe outro: ");
            }
        }
    }

    // Incializa as listas do usuario
    user->colleges = Create(user->colleges);
    user->request = Create(user->request);
    user->msg = Create(user->msg);
    user->blacklist = Create(user->blacklist);
    user->groups = Create(user->groups);
    user->groupleader = Create(user->groupleader);
    user->groupsrequest = Create(user->groupsrequest);

    /*
        Aqui, note que criamos um ponteiro do tipo dado chamado de "casulo", pois a nossa lista
        usa um sistema de union para o bloco, então não salvamos um poteiro para um usuário
        e sim, um ponteiro para a union. É possível notar que essa lógica é aplicada em diversas
        áreas do código
    */
    Dado *casulo = (Dado*)malloc(sizeof(Dado));
    casulo->user = user;
    Push(allUsers, casulo);
}

/*
    Uma de nossas funções extras, aqui permitimos a um usuário "bloquear" outro, impedindo ele de
    receber solicitações do usuário bloqueado, também automáticamente remove o usuário bloquado
    da lista de amigos, se necessário.
*/
void Block(List *allusers){
    char username[12], target[12];
    int erro;

    printf("Entre com o seu username: ");
    scanf("%s", &username);
    printf("\n");

    User *user = FindUserByUsernamne(allusers, username);
    if(user == NULL){
        printf("Usuario nao encontrado");
        return;
    }

    // Usuário alvo do block
    printf("Digite o username de quem voce quer bloquear:");
    scanf("%s", &target);
    printf("\n");

    if(FindUserByUsernamne(user->blacklist, target)!=NULL){
        printf("Ele ja esta bloqueado :p\n");
        return;
    }

    // Caso eles sejam amigos
    Node *temp = FindNodeByUsernamne(user->colleges, target);

    if(temp != NULL){
        Node *aux = FindNodeByUsernamne(temp->info->user->colleges, username);

        TurnFirst(temp->info->user->colleges, aux);
        Pop(temp->info->user->colleges, &erro);
        
        temp = FindNodeByUsernamne(user->colleges, target);
        TurnFirst(user->colleges, temp);
        Pop(user->colleges, &erro);

        printf("Amizade removida automaticamente\n");

        User *alvo = FindUserByUsernamne(allusers, target);

        Dado *casulo = (Dado*)malloc(sizeof(Dado));
        casulo->user = alvo;

        Push(user->blacklist, casulo);
        printf("Usuario bloqueado\n");
        return;
    }

    temp = FindNodeByUsernamne(user->request, target);

    if(temp != NULL){
        TurnFirst(user->request,temp);
        Pop(user->request, &erro);
        printf("O convite enviado a voce por este usuario foi automaticamente removido\n");
    }

    User *alvo = FindUserByUsernamne(allusers, target);

    if(alvo == NULL){
        printf("Usuario nao encontrado.\n");
        return;
    }

    temp = FindNodeByUsernamne(alvo->request, username);
    if(temp != NULL){
        TurnFirst(alvo->request,temp);
        Pop(alvo->request, &erro);
        printf("O convite enviado por voce a este usuario foi automaticamente removido\n");
    } else {
        printf("certo");
    }

    Dado *casulo =(Dado*)malloc(sizeof(Dado));
    casulo->user=alvo;
    Push(user->blacklist, casulo);
    printf("Usuario bloqueado\n");
}

// Mostra todos os colegas de um usuário
void ShowMycolleges(List *allusers){
    printf("Entre com o seu username:");
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

/*
    Esta função mostra todos os amigos dos amigos de um usuário, com intuito de sugerir
    uma nova amizade
*/
void Suggestions(List *alluser){
    char username[12];

    printf("Entre com o seu username:");
    scanf("%s", &username);
    printf("\n");
    User *user = FindUserByUsernamne(alluser, username);

    Node *temp = user->colleges->start;
    for(int i=0; i<user->colleges->total; i++){
        Node *aux = temp->info->user->colleges->start;
        while(aux != NULL){
            if(strcmp(aux->info->user->username, username) != 0){
                printf("%s\n", aux->info->user->username);
            }
            aux = aux->next;
        }
        temp = temp->next;
    }
}

//essa funçao vai permite um usuario a enviar para outro um convite de amizade
void CollegesRequest(List *allusers){
    //usuario que esta enviando
    printf("Entre com o seu username:");
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
    printf("Digite o username de quem quer ser parcerio:");
    scanf("%s", &target);
    printf("\n");
    if(FindUserByUsernamne(user->colleges, target)!=NULL){
        printf("Ele ja é seu amigo :p\n");
        return;
    }
    User *alvo = FindUserByUsernamne(allusers, target);
    if(alvo == NULL){
        printf("Usuario nao encontrado");
        return;
    }
    if(FindUserByUsernamne(alvo->request, username)!=NULL){
        printf("Ja tem um pedido encaminhado.\n");
        return;
    }
    if(FindUserByUsernamne(alvo->blacklist, user->username)!=NULL){
        printf("voce esta bloqueado :p\n");
        return;
    }
    if(FindUserByUsernamne(user->blacklist, alvo->username)!=NULL){
        printf("Tu primeiro da Block no mano e quer senta na janelinha, desbloqueia antes primeiro.\n");
        return;
    }
    //logo abaixo explico essa funçao
    AddRequest(alvo, user);
    printf("Pedido encaminhado com sucesso\n");
}
void RemoveCollege(List *allusers){
    //usuario que esta enviando
    printf("Entre com o seu username: ");
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
    printf("Digite o username de quem voce quer remover: ");
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
    printf("Entre com o seu username:");
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
    printf("Digite o username de quem voce quer remover:");
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
void ShowCollegeRequest(List  *allusers){
    //essa funçao permite um usuario a ver a sua lista de convites
    printf("Entre com o seu username:");
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
void SendMsgToCollege(List *allusers){
    //mesmo codigo que le o usuario e acha um alvo mas dessa vez queremos enviar uma msg nao um convite
    printf("Entre com o seu username:");
    char username[12];
    scanf("%s", &username);
    printf("\n");
    User *user = FindUserByUsernamne(allusers, username);
    if(user == NULL){
        printf("Usuario nao encontrado");
        return;
    }
    char target[12];
    printf("Digite o username de seu amigo:");
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
void ShowMsg(List *allusers){
    //le um usuario para poder mostrar suas mensagens
    printf("Entre com o seu username:");
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
        printf("Sem mensagens, procure + amigos usando a funcao suggestions\n");
        return;
    }
    //aq percorro a lista msg 
    printf("Suas mensagens sao:\n");
    while(user->msg->start!=NULL){
        //bele a logica das é a seguinte para acessar a nossa mensgens em expecifico temos o seguinte caminho
        //todo usuario tem a lista msg essa lista encadeada tem um começo que é um bloco que tem como info um * da union essa union pode guarda tanto um usuario/
        //quanto uma msg mas aq queremos uma msg entao com user->msg-start->info->msg chegamos na primeira mensagem da lista, o seu username é a sua assinatura
        //ja name msg em si
        printf("enviado por(%s) na %s: %s\n", user->msg->start->info->msg->username, user->msg->start->info->msg->chat ,user->msg->start->info->msg->name);
        int erro;
        //retiro a primeira msg.
        free(user->msg->start->info->msg);
        Pop(user->msg, &erro);
    }
    //Aq é evidente o uso de uma pilha ja que as primeiras mensagens que aparecem sao as ultimas que foram enviadas
    printf("Mensagens exibidas\n");
}
void ShowUsers(List *l){
    //percorre uma lista printando o username dos usuarios nela 
    Node *temp = l->start;
    while(temp != NULL){
        printf("%s\n", temp->info->user->username);
        temp = temp->next;
    }
};