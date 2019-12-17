#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <conio.h>
#define MAX 50

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
	if(*ultimoS<MAX){
		do{
			printf("\n___________________\nGerar Tickets\n\nTipo de Ticket\n1. Reparação.\n2. Entrega.\n3. Retroceder\n___________________\n");
			scanf("%d", &menu);
			switch (menu){
				case 1:
					_tickets[*ultimoS].letra='A';
					*ultimoA=*ultimoA+1;
					_tickets[*ultimoS].num=*ultimoA;
					_tickets[*ultimoS].atendido=0;
					time(&segundos);
					_tickets[*ultimoS].hora_=localtime(&segundos);
					printf("O seu ticket é A%d.\n",_tickets[*ultimoS].num);
					*ultimoS=*ultimoS+1;
					break;
				case 2:
					_tickets[*ultimoS].letra='B';
					*ultimoB=*ultimoB+1;
					_tickets[*ultimoS].num=*ultimoB;
					_tickets[*ultimoS].atendido=0;
					time(&segundos);
					_tickets[*ultimoS].hora_=localtime(&segundos);
					printf("O seu ticket é B%d.\n",_tickets[*ultimoS].num);
					*ultimoS=*ultimoS+1;
					break;
				case 3:
					break;
				default:
					printf("ERRO");
			}
		}while(erro1==1);
	}
	else{
		printf("Sala de espera cheia");
	}
}

void remover(int i,ticket _tickets[],int *ultimoS){//remove clientes do vetor
	for(i;i<*ultimoS;i++){
		_tickets[i]=_tickets[i+1];
	}
	(*ultimoS)--;
}

void recebe(int *ultimoS, ticket _tickets[]){ //falta acabar esta funcao
	int i, _presenca, flag;
	if(*ultimoS>0){
		do{
			for(i=0; i<*ultimoS; i++){
				flag=0;
				if(_tickets[i].atendido<3){
					printf("\nO próximo ticket a ser atendido é o: %c%d\n", _tickets[i].letra, _tickets[i].num);
					_presenca=presenca();
					if(_presenca==1){
						remover(i,_tickets,&*ultimoS);//falta mexer com tempos aqui e guardar info dos que foram atendidos
						break;
					}
					else{
						if(_presenca==0){
							(_tickets[i].atendido)++;// e aqui o tempo dos que estao à espera
						}
					}
				}
				else{
					printf("\nTicket %c%d fora da validade.\n",_tickets[i].letra, _tickets[i].num);
					flag=1;
					remover(i,_tickets,&*ultimoS);//falta info pros mapas dos que perderam a vez
					i--;
				}
			}
		}while(_presenca==0);
	}
	else{
		printf("\nNenhum ticket para atender.\n");
	}
}

int presenca(){ // Testa a presença de um ticket e retorna 1 para presente e 0 para ausente
	int i;
	char presenca;
		do{
			printf("\nO cliente está presente? [S/N]\n");
			scanf(" %c", &presenca);
			if(toupper(presenca)=='S'){
				return 1;
			}
			else{
				if(toupper(presenca)=='N'){
					return 0;
				}
			}	
		}while(toupper(presenca)!='S'||toupper(presenca)!='N');
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
}*///esta funcao nao vai provavelmente ser mais precisa

int main () {
	int menu,n,erro1=1, ultimoA=0, ultimoB=0, ultimoS=0, ultimoAT=0;
	ticket _tickets[MAX];
	setlocale(LC_ALL,"Portuguese");
	do {
		printf("\n___________________\n       Menu\n\n1. Gerar Ticket\n2. Receber Ticket\n3. Gerar mapas\n4. Sair\n___________________\n");
		scanf("%d",&menu);
		switch (menu){
		case 1: 
			 gera(&ultimoA,&ultimoB, &ultimoS,_tickets);		 
			 break;
		case 2:
			recebe(/*&ultimoA,&ultimoB,*/&ultimoS,_tickets);
			break;
		case 3:
			break;
		case 4:
			erro1=0;
			break;
		default:
			//textcolor(4);
			printf("\nEscolha inválida.\n");
		}
	}while(erro1==1);
	return 0;
}
