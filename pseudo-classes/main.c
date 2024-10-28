#include <stdio.h>
#include <stdlib.h>
#include "user.h"
#include "base.h"

int main(){
    int loop=1;
    List *rede = (List *)malloc(sizeof(List)); // Aloca memória para rede
    if (rede == NULL) {
        fprintf(stderr, "Erro ao alocar memória para a lista.\n");
        return 1; // Retorna um erro se a alocação falhar
    }
    int i;
    Create(rede);
    while(loop==1){
        printf("1) cadastrar um usuário\n");
        printf("2) listar usuários cadastrados e suas informações\n");
        printf("3) pedir para ser parceiro de um usuário\n");
        printf("4) avaliar lista de pedidos de parceria\n");
        printf("5) enviar mensagem para um parceiro\n");
        printf("6) ver mensagens recebidas\n");
        printf("7) sugerir novas parcerias\n");
        printf("8) reinicializar sistema\n");
        printf("O que deseja fazer? ");
        scanf(" %d", &i);
        printf("\n");
        switch (i)
        {
        case 1:
            printf("\ntest\n");
            RegisterUser(rede);
        break;
        case 2:
            PrintNet(rede);
        break;
        case 3:
            Collegesrequest(rede);
        break;
        case 4:
            Showrequests(rede);
        break;
        case 5:
            sendmsg(rede);
        break;
        case 6:
            showmsg(rede);
        break;
        case 7:
            Suggestions(rede);
        break;
        case 8:
            dellrede(rede);
        break;
        case 9:
            loop=0;
        break;
        default:
            printf("Nao seja um macaco");
        break;
        }
    }

    return 0;
}