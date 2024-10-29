#include <stdio.h>
#include <stdlib.h>

#include "pseudo-classes/user.h"

typedef enum {
    REGISTER_USER,
    PRINT_NET,
    REQUEST_COLLEGE,
    VIEW_COLLEGE_REQUESTS,
    SEND_COLLEGES_MSG,
    VIEW_MSG,
    POSSIBLE_COLLEGES,
    RESTART_SYSTEM,
    REMOVE_COLLEGE,
    BLOCK_USER,
    REMOVE_BLOCK,
    REGISTER_GROUP,
    ADD_TO_GROUP,
    VIEW_GROUP_REQUESTS,
    SEND_GROUP_MSG,
    DELETE_GROUP,
    CLOSE_PROGRAMM
} OPTIONS;

int main(){
    int loop = 1, i;

    List *rede = (List *)malloc(sizeof(List)); // Aloca memória para rede

    if (rede == NULL) {
        fprintf(stderr, "Erro ao alocar memória para a lista.\n");
        return 1; // Retorna um erro se a alocacão falhar
    }

    Create(rede);

    while(loop == 1){
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
        i--;

        printf("\n");

        switch (i){
            case REGISTER_USER:
                RegisterUser(rede);
            break;
            case PRINT_NET:
                PrintNetwork(rede);
            break;
            case REQUEST_COLLEGE:
                CollegesRequest(rede);
            break;
            case VIEW_COLLEGE_REQUESTS:
                ShowCollegeRequest(rede);
            break;
            case SEND_COLLEGES_MSG:
                SendMsgToCollege(rede);
            break;
            case VIEW_MSG:
                ShowMsg(rede);
            break;
            case POSSIBLE_COLLEGES:
                Suggestions(rede);
            break;
            case RESTART_SYSTEM:
                DelNetwork(rede);
            break;
            case REMOVE_COLLEGE:
                RemoveCollege(rede);
            break;
            case BLOCK_USER:
                Block(rede);
            break;
            case REMOVE_BLOCK:
                RemoveBlock(rede);
            break;
            case REGISTER_GROUP:
                RegisterGroup(rede);
            break;
            case ADD_TO_GROUP:
                AddCollegeToGroup(rede);
            break;
            case VIEW_GROUP_REQUESTS:
                GroupsRequests(rede);
            break;
            case SEND_GROUP_MSG:
                SendGroupMsg(rede);
            break;
            case DELETE_GROUP:
                DelGroup(rede);
            break;
            case CLOSE_PROGRAMM:
                loop=0;
            break;
            default:
                printf("\nOpcao invalida\n");
            break;
        }
    }

    return 0;
}