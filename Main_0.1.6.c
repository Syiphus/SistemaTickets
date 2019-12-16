#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#define MAX 200

// Diogo - 454 ----- Ângelo - 532 -------- Tiago - 608

typedef struct ticket {
	int num;
	char letra;
	struct tm* hora_;	
	int atendido;
}ticket;

void gera(int *ultimoA, int *ultimoB, int *ultimoS, ticket _tickets[]){
	int erro1=0,menu;
	time_t segundos;
	do{
		printf("\n___________________\nGerar Tickets\n\nTipo de Ticket\n1. Reparação.\n2. Entrega.\n3. Sair\n___________________\n");
		scanf("%d", &menu);
		switch (menu){
			case 1:
				_tickets[*ultimoS].letra='A';
				_tickets[*ultimoS].num=*ultimoA+1;
				time(&segundos);
				_tickets[*ultimoS].hora_=localtime(&segundos);
				printf("O seu ticket é A%d.\n",_tickets[*ultimoS].num);
				*ultimoA=*ultimoA+1;
				*ultimoS=*ultimoS+1;
				break;
			case 2:
				_tickets[*ultimoS].letra='B';
				_tickets[*ultimoS].num=*ultimoB+1;
				time(&segundos);
				_tickets[*ultimoS].hora_=localtime(&segundos);
				printf("O seu ticket é B%d.\n",_tickets[*ultimoS].num);
				*ultimoB=*ultimoB+1;
				*ultimoS=*ultimoS+1;
				break;
			case 3:
				break;
			default:
				printf("ERRO");
		}
			
	}while(erro1==1);
}

char presenca(){
	int i;
	char presenca;
		do{
			printf("O cliente esta presente? [S/N]");
			scanf(" %c", &presenca);
			if(presenca=='s'||presenca=='S'){
				return 1;
				break;
			}	
		}while(presenca!='s'||presenca!='S'||presenca!='N'||presenca!='n');
}

void removew(int i,ticket _tickets[],int *ultimoS) //remover clientes ja atendidos e nao so
{

	for(i;i<*ultimoS;i++)
	{
		_tickets[i]=_tickets[i+1];
	}
	*ultimoS=*ultimoS-1; //O Tiago acaba esta funcao
}

void recebe(int *ultimoS,ticket _tickets[],int *ultimoAT) //falta acabar esta funcao
{
	int i;
	do
	{
		for(i=0;i<*ultimoS;i++)
		{
			if(_tickets[i].atendido<=3)
			{
				if(presenca()==1)
				{
					removew(i,_tickets,&ultimoS);
				}
			}
		}
	}while(i=0);
}

/*void recebe(int *ultimoA, int *ultimoB, int *ultimoS, ticket _tickets[], int *ultimoAT){
	int num;
	char letra;
	_tickets[*ultimoAT].atendido=0;
	letra=_tickets[*ultimoAT].letra; 
	num = _tickets[*ultimoAT].num;
	if(toupper(letra)=='A'){
		if (num<*ultimoS+1 && num>=*ultimoAT-3 && _tickets[*ultimoAT].atendido==0){
			printf("O próximo ticket a ser atendido é o: A%d\n\n", _tickets[*ultimoAT].num);
			if(presenca()==1) {
				_tickets[*ultimoAT].atendido=1;			
				*ultimoAT=*ultimoAT+1;
			}
			else{
			
				
			}
		} 
		else{
			printf("Ticket não válido.1");
		}
	}
	else{
		if (toupper(letra)=='B'){
			if(num<*ultimoAT+1 && num>=*ultimoAT-3){
				printf("O próximo ticket a ser atendido é o: B%d\n\n", _tickets[*ultimoAT].num);
				if(presenca()==1) {
					*ultimoAT=*ultimoAT+1;
				}	
			}
			else{
				printf("Ticket não válido.2");
			}
		}
		else{
			printf("Ticket não válido.3");
		}
	}	
}*/

int main () {
	int menu,n,erro1=1, ultimoA=0, ultimoB=0, ultimoS=0, ultimoAT=0;
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
			recebe(/*&ultimoA,&ultimoB,*/&ultimoS,_tickets, &ultimoAT);
			printf("%d", ultimoAT);
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
	return 0;
}
