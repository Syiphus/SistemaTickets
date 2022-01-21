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
#define MAX 5 // tamanho da sala de espera
#define USERNAME "aprog" // username
#define PASS "aproglindo123" //palavra passe
#define CODIGOATENDE "aten" // código de funcionário para receber tickets
#define CODIGORECEBE "rece" // código de funcionário para atender clientes
#define HOR_ABERTURA 8 // horário de abertura
#define HOR_FECHO 24 // horário de fecho

 
typedef struct ticket { //info dos tickets
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

typedef struct mapas{ // info usada para gerar mapas
	char tik;
	float valor;
	char obs[50];
	char defeito[50];
	char equipamento[10];
	struct tm* tempo_esper;
	struct tm* tempo_atendiment;
	struct tm* horacriado;
	int tempo_espera;
	int tempo_atendimento;
}mapas;

struct tm *testehorario; // structs necessários para adquirir diversos tempos
struct tm *horas;
struct tm *hora;

void SetColor(int ForgC){ // funçao das cores da letra do terminal
	WORD wColor;
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	//We use csbi for the wAttributes word.
	if(GetConsoleScreenBufferInfo(hStdOut, &csbi)){
	    //Mask out all but the background attribute, and add in the forgournd     color
		wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
		SetConsoleTextAttribute(hStdOut, wColor);
	}
	return;
 }
 
void gerarMapas(mapas mapa[], int *atendido, int *perdidos, int produtividade[], int flag){ //gera mapas e guarda info no ficheiro
	int i, contA=0, contB=0, tempoEspTotA=0, tempoEspTotB=0, tempoAtTotA=0, tempoAtTotB=0, M=0, m=0;
	time_t segundos;
	time(&segundos);
	horas=localtime(&segundos);
	float lucro=0, ValorEmEquipamentos=0;
	if(flag==1){ 
		printf("\n______________________\nRelatório do dia de hoje %d/%d/%d\n", horas->tm_mday, horas->tm_mon+1, horas->tm_year+1900);
	}
	else{
		printf("\n______________________\nRelatório até ao momento\n");
	}
	printf("\nForam perdidos %d tickets.\n", *perdidos);
	if(*atendido>0){
		time(&segundos);
		horas=localtime(&segundos);
		printf("\nForam atendidos %d tickets: ", *atendido);
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
		printf("%d do tipo A e %d do tipo B.\n", contA, contB);
		if(contA>0){
			printf("\nTempos de espera\n\nO tempo médio de espera dos tickets do tipo A é de: %d segundos.",  tempoEspTotA/contA);
		}
		if(contB>0){
			printf("\nO tempo médio de espera dos tickets do tipo B é de: %d segundos.",  tempoEspTotB/contB);
		}
		printf("\nO tempo total médio de espera é de: %d segundos", (tempoEspTotA+tempoEspTotB)/(contA+contB));
		system("pause");
		if(contA>0){
			printf("\nTempos de atendimento\n\nO tempo médio de espera dos tickets do tipo A é de: %d segundos",  tempoAtTotA/contA);
		}
		else{
			SetColor(4);
			printf("\nNão foram atendidos tickets do tipo A.");
			SetColor(15);
		}
		if(contB>0){
			printf("\nTempos de espera\n\nO tempo médio de espera dos tickets do tipo B é de: %d segundos.",  tempoAtTotB/contB);
		}
		else{
			SetColor(4);
			printf("\nNão foram atendidos tickets do tipo B.");
			SetColor(15);
		}
		if(contA>0){
			printf("\nForam entregues os seguintes equipamentos para reparação:\n");
			for(i=0;i<*atendido; i++){
				if(mapa[i].tik=='A'){
					printf("- %s no valor de: %.2f\n", mapa[i].equipamento, mapa[i].valor);
					ValorEmEquipamentos=ValorEmEquipamentos+mapa[i].valor;
				}
			}
			printf("\nPrefazendo um total de %.2f em equipamentos para arranjar.\n", ValorEmEquipamentos);
		}
		if(contB>0){
			printf("\nForam entregues os seguintes equipamentos:\n");
			for(i=0;i<*atendido;i++){
				if(mapa[i].tik=='B'){
					printf("- %s tendo a pagar %.2f\n", mapa[i].equipamento, mapa[i].valor);
					lucro=lucro+mapa[i].valor;
				}
			}
			printf("\nPrefazendo um total de lucros de %.2f.\n", lucro);
		}
		M=produtividade[0];
		m=1;
		for(i=1;i<4;i++){
			if(produtividade[i]>M){
				M=produtividade[i];
				m=i;
			}
		}
		printf("\nO balcão mais produtivo foi o %d, tendo atendido %d clientes.\n", m+1, M);
	}
	else{
		if(flag==1){
			SetColor(4);
			printf("\nNo dia de hoje não foi atendido nenhum cliente.\n");
			SetColor(15);
		}
		else{
			SetColor(4);
			printf("\nNo dia de hoje ainda não foi atendido nenhum cliente.\n");
			SetColor(15);
		}	
	}
}
 
void gera(int *ultimoA, int *ultimoB, int *ultimoS, ticket _tickets[]){ //gera tickets do tipo a e b
	int erro1=0,menu;
	time_t segundos;
	if(*ultimoS<MAX){ // testa se a "sala de espera" já nao está cheia
		do{
			printf("\n___________________\nGerar Tickets\n\nTipo de Ticket\n1. Reparação.\n2. Entrega.\n3. Retroceder\n___________________\n");
			scanf("%d", &menu);
			switch (menu){
				case 1: // caso seja do tipo A
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
				case 2: // caso seja do tipo B
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
				case 3: // voltar para trás
					break;
				default: // erro
					SetColor(4);
					printf("\nEscolha inválida.\n");
					fflush(stdin);
					SetColor(15);
			}
		}while(erro1==1);
	}
	else{ // caso a sala de espera se encontre cheia
		SetColor(4);
		printf("Sala de espera cheia.\n");
		SetColor(15);
		fflush(stdin);
	}
}

int escolheBalcao(int balcoes[]){ // escolhe o balcão a ser ocupado, retorna -1 se estiverem todos cheios
	int i;
	for(i=0;i<4;i++){
		if(balcoes[i]==0){ // testa se o balcão está vazio
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

void receber(int *ultimoS, int balcoes[], ticket _tickets[],mapas mapa[], int *perdidos){ // ocupa balcões
	int balcaoEscolhido, _presenca, i, ultimoAtendido, contador=0, erro=1,segundo,segund;
	char codigo[strlen(CODIGORECEBE)];
	for(i=0;i<*ultimoS;i++){ // testa a ver se há clientes na sala de espera
		if(_tickets[i].recebido==1){
			contador++;
		}
	}
	if(contador>0){ // verdade se houver clientes na sala de espera
		do{
			balcaoEscolhido=escolheBalcao(balcoes); // vê que balcão está livre
			if(balcaoEscolhido!=-1){ // testa se os balcões estão cheios
				printf("\nDigite o código do funcionário: ");
				fflush(stdin);
				scanf("%[^\n]", codigo);
				fflush(stdin);
				if(strcmp(codigo, CODIGORECEBE)==0){ // testa o codigo de funcionário
					SetColor(10);
					printf("\nFuncionário reconhecido\n");
					SetColor(15);
					for(i=0;i<*ultimoS;i++){ //precorre o vetor que tem a ordem de chegada
						if(_tickets[i].atendido<3){ // testa se o ticket não perdeu a vez
							if(_tickets[i].recebido==1){ //testa se o ticket pode ser recebido
								if(!(_tickets[i].letra=='B' && balcaoEscolhido+1==4)){ //elemina a possibilidade de haver tickets do tipo B no 4º balcão
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
										else{ // volta para trás
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
				else{ // caso a password de funcionário esteja incorreta
					SetColor(4);
					printf("\nFuncionário não reconhecido\n");
					SetColor(15);
					break;
				}
			}
			else{ // caso os balcões estejam cheios
				SetColor(4);
				printf("Balcões  cheios, atenda clientes primeiro.\n");
				SetColor(15);
				erro=0;
				break;
			}	
		}while(erro==1);
	}
	else{ // caso não hajam tickets na sala
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
				return 1; // caso esteja presente
			}
			else{
				if(toupper(presenca)=='N'){
					return 0; // caso nao esteja presente
				}
				else
				{
					if(toupper(presenca)=='T'){
					return 2;	// opção para voltar para trás
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
	if(contador!=0){ // verdade se houverem clientes ao balcão
		do{
			printf("\nDigite o código de funcionário: ");
			fflush(stdin);
			scanf("%[^\n]", codigo);
			fflush(stdin);
			if(strcmp(codigo, CODIGOATENDE)==0){ // verdade de o código corresponder
				SetColor(10);
				printf("\nFuncionário reconhecido.\n");
				SetColor(15);
				printf("\nQue balcão pretende atender? (0 para sair.) ");
				fflush(stdin);
				scanf("%d", &balcaoAT);
				fflush(stdin);
				if(balcaoAT==0){ // instrução de saída
					break;
				}
				else{
					if(balcaoAT==1 || balcaoAT==2 || balcaoAT==3 || balcaoAT==4){
						if(balcoes[balcaoAT-1]==1){	
							for(i=0;i<*ultimoS;i++){ // encontra o "i" do ticket que está a ser atendido
								if(_tickets[i].balcao==balcaoAT-1 && _tickets[i].recebido==0){
									break;
								}
							}
							time(&segundos);
							_tickets[i].tempo_espera=segundos-_tickets[i].segs;
							_tickets[i].segs=segundos;
							mapa[*atendido].valor=-1;
							strcpy(mapa[*atendido].obs,"-----");
							strcpy(mapa[*atendido].defeito,"-----");
							strcpy(mapa[*atendido].equipamento,"-----");
							if(_tickets[i].letra=='A'){ //testa se o ticket é do tipo A
								do{
									printf("\nMENU\n\n1.Equipamento\n2.Valor do equipamento\n3.Principal defeito\n4.Observações\n5.Terminar atendimento\n");
									menu=-1;
									fflush(stdin);
									scanf("%d", &menu);
									fflush(stdin);
									switch(menu){
										case 1: //Equipamento
											printf("\nEquipamento: ");
											fflush(stdin);
											scanf("%10[^\n]", mapa[*atendido].equipamento);
											fflush(stdin);
											break;
										case 2: //valor
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
										case 3: // defeito
											printf("\n\nQual o defeito?"); 
											
											fflush(stdin);
											scanf("%50[^\n]", mapa[*atendido].defeito);
											fflush(stdin);
											break;
										case 4: // obs
											printf("\nObservações: ");
											fflush(stdin);
											scanf("%50[^\n]", mapa[*atendido].obs);
											fflush(stdin);
											printf("%s",mapa[*atendido].obs);
											break;
										case 5: //sair, guarda informações do atendimento no struct mapas
											if(mapa[*atendido].valor != -1 && strcmp(mapa[*atendido].obs, "-----")!=0 && strcmp(mapa[*atendido].defeito,"-----")!=0 && strcmp(mapa[*atendido].equipamento, "-----")!=0){ // testa se foram introduzidos caracteres ou valores nos pontos anteriores
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
											else{ //caso não tenha sito preenchida alguma coisa
												SetColor(4);
												printf("\nAtendimento incompleto\n");
												SetColor(15);
											}
											break;
										default: // erro
											SetColor(4);
											printf("\nEscolha inválida\n");
											SetColor(15);
									}
								}while(erro==1);
							}
							else{
								do{ // caso o ticket seja do tipo B
									printf("\nMENU\n\n1.Mercadoria a entregar\n2.Condições da mercadoria\n3.Valor a pagar\n4.Terminar atendimento\n");
									menu=-1;
									fflush(stdin);
									scanf("%d", &menu);
									fflush(stdin);
									switch(menu){
										case 1: // mercadoria
											printf("\nMercadoria a entregar: ");
											fflush(stdin);
											scanf("%10[^\n]", mapa[*atendido].equipamento);
											fflush(stdin);
											break;
										case 2: //condições
											printf("\nCondições da mercadoria: ");
												fflush(stdin);
												scanf("%50[^\n]", mapa[*atendido].defeito);
												fflush(stdin);
												break;
										case 3: //valor a pagar
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
										case 4: //sair
											if(mapa[*atendido].valor != -1 && strcmp(mapa[*atendido].defeito,"-----")!=0 && strcmp(mapa[*atendido].equipamento, "-----")!=0){ //mesmo teste que no cado dos tickets do tipo A
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
											else{ //Caso haja coisas por preencher
												SetColor(4);
												printf("\nAtendimento incompleto.\n");
												SetColor(15);
											}
											break;
										default: //erro
											SetColor(4);
											printf("Escolha inválida");
											SetColor(15);
									}
								}while(erro==1);	
							}
						}
						else{ //caso não haja ninguém no balcão selecionado
							SetColor(4);
							printf("\nBalcão vazio\n");
							SetColor(15);
							break;
						}
					}
					else{ //erro
						SetColor(4);
						printf("\nBalcão inválido.\n");
						SetColor(15);
					}
				}
			}
			else{ //em caso de erro no código de funcionário
				SetColor(4);
				printf("\nFuncionário não reconhecido\n");
				SetColor(15);
				break;
			}
		}while(erro1==1);
	}
	else{ //caso os balcões se encontrem todos vazios
		SetColor(4);
		printf("\nNenhum cliente para atender.\n");
		SetColor(15);
	}
}

int main () {
	int i, menu, n, ultimoA=0, ultimoB=0, ultimoS=0, balcoes[4],atendido=0, perdidos=0, produtividade[4], flag=0, espera=0;
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
							printf("\n\n1. Gerar Ticket\n2. Chamar Tickets\n3. Atender Tickets\n4. Tickets em espera\n5. Relatório até ao momento\n6. Sair\n");
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
								for(i=0;i<ultimoS;i++){
									if(_tickets[i].recebido==1){
										espera++;
									}	
								}
								if(espera>0){
									printf("%d tickets à espera:\n", espera);
									for(i=0;i<ultimoS;i++){
										segundos=_tickets[i].segs;
										hora=localtime(&segundos);
										printf("%c%d %d:%d:%d dia %d/%d/%d\n",_tickets[i].letra,_tickets[i].num,hora->tm_hour,hora->tm_min,hora->tm_sec, hora->tm_mday, hora->tm_mon+1, hora->tm_year+1900);
									}
								espera=0;
								}
								else{ // caso a sala de espera esteja vazia
									SetColor(4);
									printf("\nNenhum cliente à espera.\n");
									SetColor(15);
								}
								break;
							case 5:
								flag=0; // serve para a função saber onde é que está a ser chamada e ter comportamentos diferentes
								gerarMapas(mapa, &atendido, &perdidos, produtividade, flag);
								break;
							case 6: //fecha o programa
								espera=0;
								for(i=0;i<ultimoS;i++){ //conta as pessoas em espera ou a ser atendidas
									if(_tickets[i].recebido==1 || balcoes[i]==1){
										espera++;
									}	
								}
								if(espera==0){
									flag=1; // serve para a função saber onde é que está a ser chamada e ter comportamentos diferentes
									gerarMapas(mapa, &atendido, &perdidos, produtividade, flag);
									return 0;	
								}
								else{ //caso ainda hajam clientes para atender
									SetColor(4);
									printf("\nClientes por atender\n");
									SetColor(15);
									break;
								}							
							default: // erro
								SetColor(4);
								printf("\nEscolha inválida.\n");
								fflush(stdin);
								SetColor(15);
							}
						}while(1);
					} 
					else{ //caso a password nao seja reconhecida
							SetColor(4);
							printf("\n\nPassWord inválida.\n");
							SetColor(15);
					}
				}while(1);
			}
			else{ // caso o username nao seja reconhecido
					SetColor(4);
					printf("\nUsername inválido.\n");
					SetColor(15);
			}
		}while(1);
	}
	else{ //caso esteja fora do horario de trabalho
		SetColor(4);
		printf("Fora do Horário de Trabalho");
		SetColor(15);
	}
	return 0;
}
