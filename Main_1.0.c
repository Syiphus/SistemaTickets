#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#define MAX 100

/*typedef reparacao {
	int numero[100];
	char 
};
*/
void gera(int atend[]){
	int erro1=1,menu;
	do{
		printf("\n\n\nTipo de Ticket\n1. Reparação.\n2. Entrega.\n");
		scanf("%d", &menu);
		switch (menu){
			case 1:
				// falta criar estrutura (struct)
				
				break;
			case 2:
				// falta criar estrutura
				break;
			default:
				printf("ERRO");
				erro1=0;
		}	
	}while(erro1==0);
}

void atender_A(char a[], int n, int *ref_ultimo){
	int i;
	char presenca;
	for(i=*ref_ultimo;i<n;i++)
	{
		do{
			printf("O cliente esta presente? [S/N]");
			scanf(" %c", &presenca);
			if(presenca=='s'||presenca=='S'){
				break;
			}	
		}while(presenca!='s'||presenca!='S'||presenca!='N'||presenca!='n');
	}
}

void recebe(int ref_ultimo){
	int numero,num=5, ultimo;
	char letra,ticket[5];
	printf("Introduza o ticket: ");
	scanf(" %c%d", &letra, &num); 
	if(letra=='a' || letra=='A'){
	atender_A(ticket, num, ref_ultimo);	
	}	
}

int main () {
	int menu,n,erro1=1, n_atendimento[MAX], ultimo;
	setlocale(LC_ALL,"Portuguese");
	printf("MENU\n");
	do {
		printf("1. Gerar Ticket\n2. Receber Ticket\n");
		scanf("%d",&menu);
		switch (menu){
		case 1: 
			 gera(n_atendimento);		 
			 break;
		case 2:
			recebe(&ultimo);
			break;
		default:
			printf("\nEscolha inválida.\n");
			erro1=0;
		}
	}while(erro1==0);
	return 0;
}


