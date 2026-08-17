#include <stdio.h>
#include <stdlib.h>

int main (void){
    
int numero;
int*ponteiro = NULL;

printf(" digite um valor: ");
scanf("%d", &numero);

ponteiro = &numero;

printf(" Numero = %d \n Ponteiro = %p");

return (0);

}