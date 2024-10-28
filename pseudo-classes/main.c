#include <stdio.h>
#include <stdlib.h>
#include "user.h"
#include "base.h"

int main(){
    int loop=1, i;
    List *rede;
    rede=Create(rede);
    while(loop==1){
        printf("1) cadastrar um usuario \n");
        printf("2) listar usuarios cadastrados e suas informacoes \n");
        printf("3) pedir para ser parceiro de um usuario \n");
        printf("4) avaliar lista de pedidos de parceria \n");
        printf("5) enviar mensagem para um parceiro \n");
        printf("6) ver mensagens recebidas \n");
        printf("7) sugerir novas parcerias \n");
        printf("8) reinicializar sistema \n");
        printf("9) remover colega \n");
        printf("10) bloquear usuario \n");
        printf("11) remover bloqueio \n");
        printf("12) criar grupo \n");
        printf("13) adicionar colega ao grupo \n");
        printf("14) avaliar lista de pedidos de grupos \n");
        printf("15) enviar mensagem para grupo \n");
        printf("17) Deletar um grupo \n");
        printf("18) fecha programa \n");
        printf("O que deseja fazer? ");
        scanf(" %d", &i);
        printf("\n");
        
        switch (i){
            case 1:
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
                RemoveCollege(rede);
            break;
            case 10:
                Block(rede);
            break;
            case 11:
                RemoveBlock(rede);
            break;
            case 12:
                Makegroup(rede);
            break;
            case 13:
                AddCollegeforGroup(rede);
            break;
            case 14:
                Groupsrequests(rede);
            break;
            case 15:
                SendmsgGroup(rede);
            break;
            case 16:
                DelgroupUser(rede);
            break;
            case 18:
                loop=0;
            break;
            default:
                loop=1;
            break;
        }
    }

    return 0;
}