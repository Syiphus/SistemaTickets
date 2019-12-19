#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <conio.h>
#include <string.h> 

#define MAX 5
#define USERNAME "aprog"
#define PASS "aproglindo123"

// Diogo - 454 ----- Ângelo - 532 -------- Tiago - 608

typedef struct ticket {
	int num;
	char letra;
	struct tm* _hora;	
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
					_tickets[*ultimoS]._hora=localtime(&segundos);
					printf("O seu ticket é A%d.\n",_tickets[*ultimoS].num);
					*ultimoS=*ultimoS+1;
					break;
				case 2:
					_tickets[*ultimoS].letra='B';
					*ultimoB=*ultimoB+1;
					_tickets[*ultimoS].num=*ultimoB;
					_tickets[*ultimoS].atendido=0;
					time(&segundos);
					_tickets[*ultimoS]._hora=localtime(&segundos);
					printf("O seu ticket é B%d.\n",_tickets[*ultimoS].num);
					*ultimoS=*ultimoS+1;
					break;
				case 3:
					break;
				default:
					printf("ERRO");
					fflush(stdin);
			}
		}while(erro1==1);
	}
	else{
		printf("Sala de espera cheia.");
		fflush(stdin);
	}
}

int escolheBalcao(int balcoes[], ticket _tickets[], int j, int *l){ // é preciso acabar esta funcao
	int i, a;
	if(_tickets[j].letra=='A'){
		a=4;
	}
	else{
		a=3;
	}
	for(i=0;i<a;i++){
		if(balcoes[i]==0){
			balcoes[i]=1;
			*l=i;
			return i+1;
			}
		}	
	return -1;
}
void remover(int i,ticket _tickets[],int *ultimoS){//remove clientes do vetor
	for(i;i<*ultimoS;i++){
		_tickets[i]=_tickets[i+1];
	}
	(*ultimoS)--;
}

void recebe(int *ultimoS, ticket _tickets[], int balcoes[]){ //falta acabar esta funcao
	int i, j, _presenca, flag, balcao;
	if(*ultimoS>0/*, && (_tickets[*ultimoS].num-_tickets[0].num)<*/){
		do{
			for(i=0; i<*ultimoS; i++){
				if(*ultimoS==1)
				_presenca=1;
				flag=0;
				if(_tickets[i].atendido<3){
					balcao=escolheBalcao(balcoes, _tickets, i, &j); 
					if(balcao==-1){
						break;
					}
					// necessátio testar a ver se o ticket é b e se o balcao é o 4, devendo chamar o proximo
					printf("\nO próximo ticket a ser atendido é o: %c%d\nBalcão: %d", _tickets[i].letra, _tickets[i].num, balcao);
					_presenca=presenca();
					if(_presenca==1){
						remover(i,_tickets,&*ultimoS);//falta mexer com tempos aqui e guardar info dos que foram atendidos
						break;
					}
					else{
						if(_presenca==0){
							(_tickets[i].atendido)++;// e aqui o tempo dos que estao à espera
							balcoes[j]=0;
						}
						else
							{
							if(_presenca==2)
							{
							balcoes[j]=0;
							break;
							}
						}
					}
				}
				else{
					if(_tickets[i].atendido==3)
					{
					printf("\nTicket %c%d fora da validade.\n",_tickets[i].letra, _tickets[i].num);
					flag=1;
					remover(i,_tickets,&*ultimoS);//falta info pros mapas dos que perderam a vez
					i--;
					}
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
			printf("\nO cliente está presente? [S/N]\nEscreva escreva T para retroceder.\n");
			fflush(stdin);
			scanf("%c", &presenca);
			if(toupper(presenca)=='S'){
				return 1;
			}
			else{
				if(toupper(presenca)=='N'){
					return 0;
				}
				else
				{
					if(toupper(presenca)=='T'){
					return 2;	
					}
				}
			}	
		}while(toupper(presenca)!='S'||toupper(presenca)!='N'||toupper(presenca)!='T');
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
	int menu, n, erro=1, erro1=1, erro2=1, ultimoA=0, ultimoB=0, ultimoS=0, ultimoAT=0, balcoes[4],l;
	for(l=0;l<4;l++) balcoes[l]=0;
	char username[strlen(USERNAME)], pass[strlen(PASS)];
	ticket _tickets[MAX];
	setlocale(LC_ALL,"Portuguese");
	printf("Sistema automático de senhas,\nFaça log in no sistema\nDigite 'sair' no username ou na password para sair \n");
	do{	
		printf("\nUsername: ");
		scanf("%[^\n]", username);
		fflush(stdin);
		if(strcmp(username, USERNAME)==0){
			printf("\nUsername reconhecido\n");
			do{
				printf("Password:\n\n"); 
   					 int p=0; 
   					 do{ 
      				  pass[p]=getch(); 
       				 if(pass[p]!='\r'){ 
        			    printf("*"); 
       				 	} 
    				    p++; 	
  					 	}while(pass[p-1]!='\r'); 
   						pass[p-1]='\0'; 
   						fflush(stdin);
				if(strcmp(pass, PASS)==0){
				printf("\nLogin bem sucedido\n");
					do {
						printf("\n___________________\n       Menu\n\n1. Gerar Ticket\n2. Receber Ticket\n3. Gerar mapas\n4. Sair\n___________________\n");
						scanf("%d",&menu);

						switch (menu){
						case 1: 
							 gera(&ultimoA,&ultimoB, &ultimoS,_tickets);		 
							 break;
						case 2:
							recebe(/*&ultimoA,&ultimoB,*/&ultimoS,_tickets, balcoes);
							break;
						case 3:
							printf("Funcao ainda nao implementada!");
							break;
						case 4:
							return 0;
							break;
						default:
							//textcolor(4);
							printf("\nEscolha inválida.\n");
							fflush(stdin);
						}
					}while(erro2==1);
				}
				else{
					/*if(strcmp(toupper(pass), "SAIR")==0){
						erro1=0;
						break;
					}
					else{*/
						printf("\nPassWord inválida.\n");
					//}
				}
			}while(erro1==1);
		}
		else{
			/*if(strcmp(toupper(username), "SAIR")==0){
				erro=0;
				break;
			}
			else{*/
				printf("\nUsername inválido.\n");
			//}
		}
	}while(erro==1);
	return 0;
}
