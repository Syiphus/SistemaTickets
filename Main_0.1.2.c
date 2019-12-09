#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#define MAX 200
// Diogo - 454 ----- Ângelo - 532 -------- Tiago - 608
typedef struct ticket {
	int num;
	char letra;
	int hora;	
}ticket;

void gera(int *ultimo, ticket _tickets[]){
	int erro1=0,menu;
	do{
		printf("\n___________________\nGerar Tickets\n\nTipo de Ticket\n1. Reparação.\n2. Entrega.\n3. Sair\n___________________\n");
		scanf("%d", &menu);
		switch (menu){
			case (1):
				_tickets[*ultimo].letra='A';
				_tickets[*ultimo].num=*ultimo+1;
				_tickets[*ultimo].hora=1;
				printf("O seu ticket é A%d.\n",_tickets[*ultimo].num);
				*ultimo=*ultimo+1;
				break;
			case 2:
				_tickets[*ultimo].letra='B';
				_tickets[*ultimo].num=*ultimo+1;
				_tickets[*ultimo].hora=1;
				printf("O seu ticket é A%d.\n",_tickets[*ultimo].num);
				*ultimo=*ultimo+1;
				break;
			case 3:
				break;
			default:
				printf("ERRO");
		}	
	}while(erro1==1);
}

void atender(int *ultimo,ticket _tickets[]){
	int i;
	char presenca;
	for(i=0;i<*ultimo;i++)
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

void recebe(int *ultimo,ticket _tickets[]){
	int num,i;
	char letra;
	printf("Introduza o ticket: ");
	scanf(" %c%d", &letra,&num); 
	for (i=0;i<*ultimo;i++)
	{
	if(num==_tickets[i].num)
	{
		atender(*ultimo,_tickets);
		}	
	}	
}

int main () {
	int menu,n,erro1=1, ultimo=0;
	ticket _tickets[MAX];
	setlocale(LC_ALL,"Portuguese");
	do {
		printf("\n___________________\nMenu\n\n1. Gerar Ticket\n2. Receber Ticket\n3. Gerar mapas\n4. Sair\n___________________\n");
		scanf("%d",&menu);
		switch (menu){
		case 1: 
			 gera(&ultimo,_tickets);		 
			 break;
		case 2:
			recebe(&ultimo,_tickets);
			break;
		case 3:
			break;
		case 4:
			erro1=0;
			break;
		default:
			printf("\nEscolha inválida.\n");
		}
	}while(erro1==1);
	printf("%d",_tickets[4].num);
	return 0;
}


