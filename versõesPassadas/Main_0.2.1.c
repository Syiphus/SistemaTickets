#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <conio.h>
#include <string.h> 
#include <dos.h>
#include <dir.h>
#include <windows.h>
#define MAX 5
#define USERNAME "aprog"
#define PASS "aproglindo123"
#define CODIGOATENDE "aten"
#define CODIGORECEBE "rece"
#define HOR_ABERTURA 8
#define HOR_FECHO 21

// Diogo - 454 ----- Ângelo - 532 -------- Tiago - 608
 
typedef struct ticket {
	int num;
	char letra;
	struct tm* _hora;
	int segs;
	int recebido;	
	int atendido;
	int balcao;
	int tempo_espera;
	int tempo_atendimento;
}ticket;

typedef struct mapas{
	char tik;
	float valor;
	char obs[50];
	char defeito[50];
	char equipamento[10];
	struct tm* tempo_esper;
	struct tm* tempo_atendiment;
	int tempo_espera;
	int tempo_atendimento;
	struct tm* horacriado;
}mapas;

struct tm *testehorario; 
struct tm *horas;

void SetColor(int ForgC)
 {
     WORD wColor;

      HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
      CONSOLE_SCREEN_BUFFER_INFO csbi;

                       //We use csbi for the wAttributes word.
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
                 //Mask out all but the background attribute, and add in the forgournd     color
          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
     return;
 }
 
void gerarMapas(mapas mapa[], int *atendido, int *perdidos, int produtividade[], int flag){
	int i, contA=0, contB=0, tempoEspTotA=0, tempoEspTotB=0, tempoAtTotA=0, tempoAtTotB=0, M=0;
	FILE *fp;
	time_t segundos;
	time(&segundos);
	horas=localtime(&segundos);
	float lucro=0, ValorEmEquipamentos=0;
	if(flag==1){
		printf("\n___________________\nRelatório do dia de hoje\n");
	}
	else{
		printf("\n___________________\nRelatório até ao momento");
	}
	printf("\nForam perdidos %d tickets.\n", *perdidos);
	if(*atendido>0){
		time(&segundos);
		horas=localtime(&segundos);
		if(horas->tm_hour>=HOR_FECHO){
			printf("\nForam atendidos %d tickets.\n", *atendido);
		}
		else{
			printf("\nAté às %d:%d:%d foram atendidos %d tickets: ", horas->tm_hour,horas->tm_min,horas->tm_sec,*atendido);//meter o tempo atual aqui
		}
		for(i=0;i<*atendido; i++){
			if(mapa[i].tik=='A'){
				contA++;
				tempoEspTotA=tempoEspTotA+mapa[i].tempo_espera;
				tempoAtTotA=tempoAtTotA+mapa[i].tempo_atendimento;
			}
			else{
				contB++;
				tempoEspTotB=tempoEspTotB+mapa[i].tempo_espera;
				tempoAtTotB=tempoAtTotB+mapa[i].tempo_atendimento;
			}
		}
		if(contB==0) contB=-1;
		if (contA==0) contA=-1;
		printf(" %d do tipo A e %d do tipo B\n", contA, contB);
		printf("\nTempos de espera\n\nO tempo médio de espera dos tickets do tipo A é de: %d\nO tempo médio de espera dos tickets do tipo B é de: %d\nO tempo total médio de espera é de: %d\n", tempoEspTotA/contA, tempoEspTotB/contB, (tempoEspTotA+tempoEspTotB)/contA+contB);
		system("pause");
		printf("\nTempos de atendimento\nO tempo médio de atendimento dos clientes do tipo A é de: %d\nO tempo médio de atendimento dos clientes do tipo B é de: %d\nO tempo total médio do atendimento é de: %d\n", tempoAtTotA/contA, tempoAtTotB/contB, (tempoAtTotA+tempoAtTotB)/contA+contB);
		printf("\nForam entregues os seguintes equipamentos para reparação:\n");
		for(i=0;i<*atendido; i++){
			if(mapa[i].tik=='A'){
				printf("- %s no valor de: %.2f\n", mapa[i].equipamento, mapa[i].valor);
				ValorEmEquipamentos=ValorEmEquipamentos+mapa[i].valor;
			}
		}
		printf("\nPrefazendo um total de %.2f em equipamentos para arranjar.\n", ValorEmEquipamentos);
		printf("\nForam entregues os seguintes equipamentos:\n");
		for(i=0;i<*atendido;i++){
			if(mapa[i].tik=='B'){
				printf("- %s tendo a pagar %.2f\n", mapa[i].valor);
				lucro=lucro+mapa[i].valor;
			}
		}
		printf("\nPrefazendo um total de lucros de %.2f.\n", lucro);
		produtividade[M]=produtividade[0];
		for(i=1;i<4;i++){
			if(produtividade[i]>produtividade[M]){
				produtividade[M]=produtividade[i];
			}
		}
		printf("\nO balcão mais produtivo foi o %d, tendo atendido %d clientes.\n", M+1, produtividade[M]);
	}
	else{
		SetColor(4);
		printf("\nNo dia de hoje ainda não foi atendido nenhum cliente.\n");
		SetColor(15);
	}
	printf("\nMapas totais:\n");
	//informacao total proveniente do ficheiro é apresentada aqui; testar se é a primeira vez devendo dizer que é o primeiro dia
}
 
void gera(int *ultimoA, int *ultimoB, int *ultimoS, ticket _tickets[]){ //gera tickets do tipo a e b
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
					_tickets[*ultimoS].recebido=1;
					time(&segundos);
					_tickets[*ultimoS].segs=segundos;
					_tickets[*ultimoS]._hora=localtime(&segundos);
					printf("O seu ticket é A%d.\n",_tickets[*ultimoS].num);
					*ultimoS=*ultimoS+1;
					break;
				case 2:
					_tickets[*ultimoS].letra='B';
					*ultimoB=*ultimoB+1;
					_tickets[*ultimoS].num=*ultimoB;
					_tickets[*ultimoS].atendido=0;
					_tickets[*ultimoS].recebido=1;
					time(&segundos);
					_tickets[*ultimoS].segs=segundos;
					_tickets[*ultimoS]._hora=localtime(&segundos);
					printf("O seu ticket é B%d.\n",_tickets[*ultimoS].num);
					*ultimoS=*ultimoS+1;
					break;
				case 3:
					break;
				default:
					SetColor(4);
					printf("\nEscolha inválida.\n");
					fflush(stdin);
					SetColor(15);
			}
		}while(erro1==1);
	}
	else{
		SetColor(4);
		printf("Sala de espera cheia.\n");
		SetColor(15);
		fflush(stdin);
	}
}

int escolheBalcao(int balcoes[]){ // retorna que balcão está livre, -1 se estiverem todos ocupados
	int i;
	for(i=0;i<4;i++){
		if(balcoes[i]==0){
			return i;
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

void receber(int *ultimoS, int balcoes[], ticket _tickets[],mapas mapa[], int *perdidos){ // ocupa balcoes
	int balcaoEscolhido, _presenca, i, ultimoAtendido, contador=0, erro=1,segundo,segund;
	char codigo[strlen(CODIGORECEBE)];
	for(i=0;i<*ultimoS;i++){
		if(_tickets[i].recebido==1){
			contador++;
		}
	}
	if(*ultimoS>0 && contador>0){
		do{
			balcaoEscolhido=escolheBalcao(balcoes);
			if(balcaoEscolhido!=-1){
				printf("\nDigite o código do funcionário: ");
				fflush(stdin);
				scanf("%[^\n]", codigo);
				fflush(stdin);
				if(strcmp(codigo, CODIGORECEBE)==0){
					SetColor(10);
					printf("\nFuncionário reconhecido\n");
					SetColor(15);
					for(i=0;i<*ultimoS;i++){
						if(_tickets[i].atendido<3){
							if(_tickets[i].recebido==1){
								if(!(_tickets[i].letra=='B' && balcaoEscolhido+1==4)){
									printf("\nO próximo ticket a ser atendido é o: %c%d\nBalcão: %d", _tickets[i].letra, _tickets[i].num, balcaoEscolhido+1);
									_presenca=presenca();
									if(_presenca==0){ //não está presente
										_tickets[i].atendido++;
									}
									else{
										if(_presenca==1){ //está presente
											balcoes[balcaoEscolhido]=1;
											_tickets[i].balcao=balcaoEscolhido;
											_tickets[i].recebido=0;
											SetColor(10);
											printf("\nCliente recebido.\n");
											SetColor(15);
											erro=0;
											break;
										}
										else{
											erro=0;
											break;
										}
									}
								}
							}
						}
						else{ //perdeu a vez
							(*perdidos)++;
							printf("\nTicket %c%d fora da validade.\n",_tickets[i].letra, _tickets[i].num);
							remover(i, _tickets, &*ultimoS);
						}
					}
					break;	
				}
				else{
					SetColor(4);
					printf("\nFuncionário não reconhecido\n");
					SetColor(15);
					break;
				}
			}
			else{
				SetColor(4);
				printf("Balcões  cheios, atenda clientes primeiro.\n");
				SetColor(15);
				erro=0;
				break;
			}	
		}while(erro==1);
	}
	else{
		SetColor(4);
		printf("\nNenhum ticket para receber.\n");
		SetColor(15);
	}
}

int presenca(){ // Testa a presença de um ticket e retorna 1 para presente e 0 para ausente
	int i;
	char presenca;
		do{
			printf("\nO cliente está presente? [S/N]\nEscreva escreva T para retroceder.\n");
			fflush(stdin);
			scanf("%c", &presenca);
			fflush(stdin);
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

void atender(int balcoes[], ticket _tickets[], int *ultimoS, int *atendido, mapas mapa[], int produtividade[]){ //atende clientes, preenchendo o struct dos mapas, e liberando balcões
	char codigo[strlen(CODIGOATENDE)];
	int balcaoAT, menu, i, erro=1, erro1=1, contador=0;
	time_t segundos;
	for(i=0;i<4;i++){
		if(balcoes[i]==1){
			contador++;
		}
	}
	if(contador!=0){
		do{
			printf("\nDigite o código de funcionário: ");
			fflush(stdin);
			scanf("%[^\n]", codigo);
			fflush(stdin);
			if(strcmp(codigo, CODIGOATENDE)==0){
				SetColor(10);
				printf("\nFuncionário reconhecido.\n");
				SetColor(15);
				printf("\nQue balcão pretende atender? (0 para sair.) ");
				fflush(stdin);
				scanf("%d", &balcaoAT);
				fflush(stdin);
				if(balcaoAT==0){
					break;
				}
				else{
					if(balcaoAT==1 || balcaoAT==2 || balcaoAT==3 || balcaoAT==4){
						if(balcoes[balcaoAT-1]==1){	
							for(i=0;i<*ultimoS;i++){
								if(_tickets[i].balcao==balcaoAT-1 && _tickets[i].recebido==0){
									break;
								}
							}
							time(&segundos);
							_tickets[i].tempo_espera=segundos-_tickets[i].segs;
							_tickets[i].segs=segundos;
							mapa[i].valor=-1;
							strcpy(mapa[*atendido].obs,"-----");
							strcpy(mapa[*atendido].defeito,"-----");
							strcpy(mapa[*atendido].equipamento,"-----");
							if(_tickets[i].letra=='A'){
								do{
									printf("esta a atender o ticket %c%d",_tickets[i].letra,_tickets[i].num);
									printf("\nMENU\n\n1.Equipamento\n2.Valor do equipamento\n3.Principal defeito\n4.Observações\n5.Terminar atendimento\n");
									menu=-1;
									fflush(stdin);
									scanf("%d", &menu);
									fflush(stdin);
									switch(menu){
										case 1:
											printf("\nEquipamento: ");
											
											fflush(stdin);
											scanf("%10[^\n]", mapa[*atendido].equipamento);
											fflush(stdin);
											break;
										case 2:
											do{
												printf("\nQual o valor do equipamento? ");
												fflush(stdin);
												mapa[*atendido].valor=-1;
												scanf("%f", &mapa[*atendido].valor);
												fflush(stdin);
												if(&mapa[*atendido].valor<0){
													SetColor(4);
													printf("\nValor inválido\n");
													SetColor(15);
												}
											}while(mapa[*atendido].valor<0);
											break;
										case 3:
											printf("\n\nQual o defeito?"); 
											
											fflush(stdin);
											scanf("%50[^\n]", mapa[*atendido].defeito);
											fflush(stdin);
											break;
										case 4:
											printf("\nObservações: ");
										
											fflush(stdin);
											scanf("%50[^\n]", mapa[*atendido].obs);
											fflush(stdin);
											printf("%s",mapa[*atendido].obs);
											break;
										case 5: //validar se os outros campos foram preenchidos usar -1 como default nos valores e strcmp com default de ----- nos espacos
											if(mapa[*atendido].valor != -1 && strcmp(mapa[*atendido].obs, "-----")!=0 && strcmp(mapa[*atendido].defeito,"-----")!=0 && strcmp(mapa[*atendido].equipamento, "-----")!=0){
												mapa[*atendido].horacriado=_tickets[i]._hora;
												time(&segundos);
												mapa[*atendido].tik='A';
												mapa[*atendido].tempo_espera=_tickets[i].tempo_espera;
												mapa[*atendido].tempo_atendimento=segundos-_tickets[i].segs;
												produtividade[balcaoAT-1]=produtividade[balcaoAT-1]+1;
												balcoes[balcaoAT-1]=0;
												remover(i,_tickets,&*ultimoS);
												erro=0;
												erro1=0;
												(*atendido)++;	
											}
											else{
												SetColor(4);
												printf("\nCoisas por Preencher\n");
												SetColor(15);
											}
											break;
										default:
											SetColor(4);
											printf("\nEscolha inválida\n");
											SetColor(15);
									}
								}while(erro==1);
							}
							else{
								do{
									printf("esta a atender o ticket %c%d",_tickets[i].letra,_tickets[i].num);
									printf("\nMENU\n\n1.Mercadoria a entregar\n2.Condições da mercadoria\n3.Valor a pagar\n4.Terminar atendimento\n");
									menu=-1;
									fflush(stdin);
									scanf("%d", &menu);
									fflush(stdin);
									switch(menu){
										case 1:
											printf("\nMercadoria a entregar: ");
											fflush(stdin);
											scanf("%10[^\n]", mapa[*atendido].equipamento);
											fflush(stdin);
											break;
										case 2:
											printf("\nCondições da mercadoria: ");
												fflush(stdin);
												scanf("%50[^\n]", mapa[*atendido].defeito);
												fflush(stdin);
												break;
										case 3:
											do{
												printf("\nValor a pagar: ");
												fflush(stdin);
												mapa[*atendido].valor=-1;
												scanf("%f", &mapa[*atendido].valor);
												printf("%f",mapa[*atendido].valor);
												fflush(stdin);
												if(mapa[*atendido].valor<0){
													SetColor(4);
													printf("\nValor inválido\n");
													SetColor(15);
												}
											}while(mapa[*atendido].valor<0);
											break;
										case 4://testar se foram todos atendidos
											if(mapa[*atendido].valor != -1 /*&& strcmp(mapa[i].obs, "-----")!=0*/ && strcmp(mapa[*atendido].defeito,"-----")!=0 && strcmp(mapa[*atendido].equipamento, "-----")!=0){
												mapa[*atendido].tik='B';
												mapa[*atendido].horacriado=_tickets[i]._hora;
												mapa[*atendido].tempo_espera=_tickets[i].tempo_espera;
												mapa[*atendido].tempo_atendimento=segundos-_tickets[i].segs;
												balcoes[balcaoAT-1]=0;
												remover(i,_tickets,&*ultimoS);
												erro=0;
												erro1=0;
												(*atendido)++;
											}
											else{
												SetColor(4);
												printf("\nCoisas por preencher.\n");
												SetColor(15);
											}
											break;
										default:
											SetColor(4);
											printf("Escolha inválida");
											SetColor(15);
									}
								}while(erro==1);	
							}
						}
						else{
							SetColor(4);
							printf("\nBalcão vazio\n");
							SetColor(15);
							break;
						}
					}
					else{
						SetColor(4);
						printf("\nBalcão inválido.\n");
						SetColor(15);
					}
				}
			}
			else{
				SetColor(4);
				printf("\nFuncionário não reconhecido\n");
				SetColor(15);
				break;
			}
		}while(erro1==1);
	}
	else{
		SetColor(4);
		printf("\nNenhum cliente para atender.\n");
		SetColor(15);
	}
}

int main () {
	int i, menu, n, ultimoA=0, ultimoB=0, ultimoS=0, balcoes[4],atendido=0, perdidos=0, produtividade[4], flag=0;
	for(i=0;i<4;i++) balcoes[i]=0;
	for(i=0;i<4;i++) produtividade[i]=0;
	char username[strlen(USERNAME)], pass[strlen(PASS)];
	time_t segundos;
	time(&segundos);
	testehorario=localtime(&segundos);
	mapas mapa[100];
	ticket _tickets[MAX];
	setlocale(LC_ALL,"Portuguese");
	if(testehorario->tm_hour >=HOR_ABERTURA && testehorario->tm_hour <HOR_FECHO){
		printf("Sistema automático de senhas,\nFaça login no sistema\nDigite 'sair' no username ou na password para sair \n");
		do{	
			printf("\nUsername: ");
			fflush(stdin);
			scanf("%[^\n]", username);
			fflush(stdin);
			if(strcmp(username, USERNAME)==0){
				SetColor(10);
				printf("\nUsername reconhecido\n");
				SetColor(15);
				do{
					printf("\nPassword:  "); 
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
						SetColor(10);
						printf("\n\nLogin bem sucedido\n\n");
						SetColor(15);
						do{
							SetColor(1);
							printf("___________________\n       Menu");
							SetColor(15);
							printf("\n\n1. Gerar Ticket\n2. Chamar Tickets\n3. Atender Tickets\n4. Gerar mapas\n5. Sair\n");
							SetColor(1);
							printf("___________________\n");
							SetColor(15);
							menu=-1;
							fflush(stdin);
							scanf("%d",&menu);
							fflush(stdin);
							switch (menu){
							case 1: 
								time(&segundos);
								testehorario=localtime(&segundos);	 
								if(testehorario->tm_hour >=HOR_ABERTURA && testehorario->tm_hour <HOR_FECHO){
									gera(&ultimoA,&ultimoB, &ultimoS, _tickets);
								}
								else{
									SetColor(4);
									printf("\nFora do Horário de Trabalho. Não se geram mais tickets.\n");
									SetColor(15);
								}
								break;	
							case 2:
								receber(&ultimoS, balcoes, _tickets, mapa, &perdidos);
								break;
							case 3:
								atender(balcoes, _tickets, &ultimoS, &atendido, mapa, produtividade);
								break;
							case 4:
								flag=0;
								gerarMapas(mapa, &atendido, &perdidos, produtividade, flag);
								break;
							case 5:
								flag=1;
								gerarMapas(mapa, &atendido, &perdidos, produtividade, flag);
								return 0;
							case 6:
								printf("Tickets à espera:\n");
								for(i=0;i<ultimoS;i++)
								{
									printf("%c%d Hora criado: %d:%d:%d\n",_tickets[i].letra,_tickets[i].num,_tickets[i]._hora->tm_hour,_tickets[i]._hora->tm_min,_tickets[i]._hora->tm_sec);
								}
							default:
								SetColor(4);
								printf("\nEscolha inválida.\n");
								fflush(stdin);
								SetColor(15);
							}
						}while(1);
					}
					else{
							SetColor(4);
							printf("\n\nPassWord inválida.\n");
							SetColor(15);
					}
				}while(1);
			}
			else{
					SetColor(4);
					printf("\nUsername inválido.\n");
					SetColor(15);
			}
		}while(1);
	}
	else{
		SetColor(4);
		printf("Fora do Horário de Trabalho");
		SetColor(15);
	}
	return 0;
}
