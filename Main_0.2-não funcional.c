#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
#define MAX 100

/*typedef struct Reparacao {
	int numero[100];
	int total;
	char tipobilhete[3];
}Reparacao;*/
typedef struct Entrega {
	int numero[100];
	char tipobilhete[3];
}Entrega;

int gera(int *totalgerados,int totalrep[]){
	int erro1=1,menu,numeroticket,totalcri=0;
	do{
		printf("\n\n\nTipo de Ticket\n1. Reparação.\n2. Entrega.\n3. Voltar atrás.\n");
		scanf("%d", &menu);
		switch (menu){
			case 1:
				totalcri=totalrep[totalcri];
				*totalgerados++;
				printf("o numero do seu ticket é A%d\n",totalrep[totalcri]);
				break;
			case 2:
				// falta criar estrutura
				break;
			case 3: 
				main(); // Caso seja escolhido o valor 3 este volta à função main
			default:
				printf("ERRO");
				erro1=0;
		}	
	}while(erro1==0);
	return *totalgerados;
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
	int menu,n,erro1=1, ultimo,totalgerados=0,i;
	setlocale(LC_ALL,"Portuguese");
	int totalrep[100];
	for(i=0;i<MAX;i++)
	{
		totalrep[i]=i+1;
	}
	printf("MENU\n");
	do {
		printf("1. Gerar Ticket\n2. Receber Ticket\n");
		scanf("%d",&menu);
		switch (menu){
		case 1: 
			 totalgerados=gera(&totalgerados,totalrep);		 
			 break;
		case 2:
			recebe(&ultimo);
			break;
		default:
			printf("\nEscolha inválida.\n");
			erro1=0;
		}
	}while(erro1==0 || totalgerados!=0);
	return 0;
}


