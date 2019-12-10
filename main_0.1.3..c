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

void gera(int *ultimoA, int *ultimoB, int *ultimoS, ticket _tickets[]){
	int erro1=0,menu;
	do{
		printf("\n___________________\nGerar Tickets\n\nTipo de Ticket\n1. Reparação.\n2. Entrega.\n3. Sair\n___________________\n");
		scanf("%d", &menu);
		switch (menu){
			case 1:
				_tickets[*ultimoS].letra='A';
				_tickets[*ultimoS].num=*ultimoA+1;
				_tickets[*ultimoS].hora=1;
				printf("O seu ticket é A%d.\n",_tickets[*ultimoS].num);
				*ultimoA=*ultimoA+1;
				break;
			case 2:
				_tickets[*ultimoS].letra='B';
				_tickets[*ultimoS].num=*ultimoB+1;
				_tickets[*ultimoS].hora=1;
				printf("O seu ticket é B%d.\n",_tickets[*ultimoS].num);
				*ultimoB=*ultimoB+1;
				break;
			case 3:
				break;
			default:
				printf("ERRO");
		}	
	}while(erro1==1);
}

void atender(int *ultimoA, int *ultimoB, int *ultimoS,ticket _tickets[]){
	int i;
	char presenca;
	for(i=0;i<*ultimoS;i++)
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

void recebe(int *ultimoA, int *ultimoB, int *ultimoS, ticket _tickets[], int *ultimoATA,int *ultimoATB){
	int num, i;
	char letra;
	printf("Introduza o ticket: \n");
	scanf(" %c%d", &letra,&num); 
	if (toupper(letra)=='A'){
		if (num<*ultimoA+1 && num>=*ultimoA-3){
			
		} 
	}
	for (i=0;i<*ultimoS;i++)
	{
		if(num==_tickets[i].num)
	{
		atender(&ultimoA, &ultimoB, &ultimoS, _tickets);
		}	
	}	
}

int main () {
	int menu,n,erro1=1, ultimoA=0, ultimoB=0, ultimoS=0, ultimoATB=0, ultimoATA=0;
	ticket _tickets[MAX];
	setlocale(LC_ALL,"Portuguese");
	do {
		printf("\n___________________\nMenu\n\n1. Gerar Ticket\n2. Receber Ticket\n3. Gerar mapas\n4. Sair\n___________________\n");
		scanf("%d",&menu);
		switch (menu){
		case 1: 
			 gera(&ultimoA,&ultimoB,&ultimoS,_tickets);		 
			 break;
		case 2:
			recebe(&ultimoA,&ultimoB,&ultimoS,_tickets, &ultimoATA, &ultimoATB);
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
