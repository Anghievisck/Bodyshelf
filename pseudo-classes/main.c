#include <stdio.h>
#include <stdlib.h>
#include "user.h"

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
        printf("16) Deletar um grupo \n");
        printf("17) fecha programa \n");
        printf("O que deseja fazer? ");
        scanf(" %d", &i);
        printf("\n");
        
        switch (i){
            case 1:
                RegisterUser(rede);
            break;
            case 2:
                PrintNetwork(rede);
            break;
            case 3:
                CollegesRequest(rede);
            break;
            case 4:
                ShowCollegeRequest(rede);
            break;
            case 5:
                SendMsgToCollege(rede);
            break;
            case 6:
                ShowMsg(rede);
            break;
            case 7:
                Suggestions(rede);
            break;
            case 8:
                DelNetwork(rede);
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
                RegisterGroup(rede);
            break;
            case 13:
                AddCollegeToGroup(rede);
            break;
            case 14:
                GroupsRequests(rede);
            break;
            case 15:
                SendGroupMsg(rede);
            break;
            case 16:
                DelGroup(rede);
            break;
            case 17:
                loop=0;
            break;
            default:
                loop=1;
            break;
        }
    }

    return 0;
}