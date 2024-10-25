#include <stdio.h>
#include <stdlib.h>
#include "user.h"
#include "base.h"

int main(){
    List *rede;
    Create(rede);
    RegisterUser(rede);
    RegisterUser(rede);
    Collegesrequest(rede);
    Showrequests(rede);
    
    return 0;
}