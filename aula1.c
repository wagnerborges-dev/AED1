#include <stdio.h>
#include <stdlib.h>

int main (void){
    
int numero;
int*ponteiro;

printf(" digite um valor: ");
scanf("%d", &numero);

ponteiro = &numero;

printf(" Numero = %d \n Ponteiro = %p \n", numero, ponteiro);

*ponteiro = 4; 

printf(" Numero = %d \n Ponteiro = %p \n", numero, ponteiro);    

return (0);

}
