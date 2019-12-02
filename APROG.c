#include <stdio.h>
#include <locale.h>
#include <stdlib.h>



int main () {
	int menu,n,erro1=1;
	setlocale(LC_ALL,"Portuguese");
	printf("MENU\n");
	do {
		printf("1. Gerar Ticket\n2. Receber Ticket\n");
		scanf("%d",&menu);
		switch (menu){
		case 1: 
			 printf("\n\n\nTipo de Ticket\n1. Reparação.\n2. Entrega.\n");
			 break;
		case 2:
			break;
		default:
			printf("\nEscolha inválida.\n");
			erro1=0;
		}
	}
	while(erro1==0);
}
