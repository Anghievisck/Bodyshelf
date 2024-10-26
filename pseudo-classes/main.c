#include <stdio.h>
#include <stdlib.h>
#include "user.h"
#include "base.h"

int main(){
    List *rede = (List *)malloc(sizeof(List)); // Aloca memória para rede
    if (rede == NULL) {
        fprintf(stderr, "Erro ao alocar memória para a lista.\n");
        return 1; // Retorna um erro se a alocação falhar
    }
    Create(rede);
    RegisterUser(rede);
    RegisterUser(rede);
    Collegesrequest(rede);
    Showrequests(rede);
    Showmycolleges(rede);
    Showmycolleges(rede);
    sendmsg(rede);
    showmsg(rede);
    
    return 0;
}