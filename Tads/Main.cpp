#include <stdio.h>
#include <stdlib.h> //strtof();
#include <string.h> //strcpy()
#include <time.h> //time(), localtime();
#include <conio2.h>
#include <ctype.h>
#include "display.h"
#include "TadComandos.h"
#include "tad.h"
#include "operations.h"
#include "manipulations.h"

/*struct pointers {
	
	//unidade aberta
	//arquivo aberto
	//registro atual
};*/

void conta(Arq *arquivo_aberto){
	int i=0;
	pDados *p = arquivo_aberto->cmps->p_dados;
	Campos *c = arquivo_aberto->cmps;
	Status *s = arquivo_aberto->stts;
	
	while(s != NULL){
		i++;
		s = s->prox;
	}
	printf("\ns = %d", i);
	i=0;
	while(c != NULL){
		while(p != NULL){
			i++;
			p = p->prox;
		}	
		c = c->prox;
	}
	printf("\np = %d", i);
}
int main()
{
	system("title dBase III - Estruturas de Dados II - Fipp - By: @rodrigueseti @rafael8paulo - github.com/rodrigueseti/dBase3");
	
	Dir *unid;
	Arq *arquivo_aberto = NULL;
	Entradas en;
	initDir(&unid); //Initializing
	
	buildUnit(&unid); //Build Unit C:
	buildUnit(&unid); //Build Unit D:
	buildUnit(&unid); //Build Unit E:
		
	int opc;
	char comando_field[50];
	char valor[50];
	valor[0] = '\0';
	
	//show();
	
	printf("Diretorio atual: [%c:]\n", unid->letter);
	printf(". ");
	fflush(stdin);
	gets(comando_field);
	opc = Compara_String(comando_field, valor);
	
	while(opc != 3)
	{
		switch (opc)
		{
			//DIR
			case 2 : {
				listaArquivo(unid);
				break;
			}
			
			//DIR
			case 4 : {
				edit(&arquivo_aberto);
				break;
			}
			
			//PACK
			case 5 : {
				pack(&arquivo_aberto);
				break;
			}
			
			//LIST
			case 7 : {
				list(arquivo_aberto);
				break;
			}
		
			//CLEAR
			case 8 : {
				system("cls");
				break;
			}
			//APPEND
			case 11 : { //*******************T*******************estar
				append(arquivo_aberto);
				break;
			}
			
			//DELETE ALL
			case 13 : {
				DeleteAll(arquivo_aberto->stts);
				printf("All deleted recordings\n");
				break;
			}
			
			//RECALL ALL
			case 14 : {
				RecallAll(arquivo_aberto->stts);
				printf("All records retrieved\n");
				break;
			}
			
			//LIST STRUCTURE
			case 16 : {
				listarFields(arquivo_aberto, unid);
				break;
			}
			
			//CREATE
			case 19 : {
				
				novoArquivo(unid, valor);
				printf("Incluir Fields ? (Y/N): ");
				opc = toupper(getche());
				
				if(opc == 'Y')
				{
					arquivo_aberto = abrirArquivo(unid, valor);
					insertFields(arquivo_aberto);
					
					printf("Input data records now? (Y/N)");
					opc = toupper(getch());
					while(opc == 'Y')
					{
						//Chamada
						append(arquivo_aberto);
						printf("Continue including? (Y/N)");
						opc = toupper(getch());
					}
				}
				printf("\n");
				break;
			}
			
			//USE
			case 20 : {
				arquivo_aberto = abrirArquivo(unid, valor);
				
				//GOTO
				if(arquivo_aberto != NULL)
					printf("Aberto: [%s]\n", arquivo_aberto->nomeDBF);
				else
					printf("Not found\n");
					
				break;
			}
			//GOTO
			case 21 : {
				//printf("\n goto = %s", valor);
				goto_(&arquivo_aberto, valor);
				break;
			}
			//SET DEFAULT TO
			case 22 : {
				arquivo_aberto = NULL;
				trocaUnidade(&unid, toupper(valor[0]));
				printf("Diretorio atual: [%c:]\n", unid->letter);
				break;
			}
			
			//LIST FOR
			case 23 : {
				listFor(arquivo_aberto, comando_field, valor);
				break;
			}
			//LOCATE FOR
			case 24 : {
				locate(arquivo_aberto, comando_field, valor);
				break;
			}
			default :
				printf("Comando Invalido\n");
		}
		printf("\n %s\n", arquivo_aberto->cmps->pAtual);
		printf(". ");
		fflush(stdin);
		gets(comando_field);
		opc = Compara_String(comando_field, valor);
	}
	
	return 0;
}
