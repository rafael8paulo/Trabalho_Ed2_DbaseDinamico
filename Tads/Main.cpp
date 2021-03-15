#include <stdio.h>
#include <stdlib.h> //strtof();
#include <string.h> //strcpy()
#include <time.h> //time(), localtime();
#include <ctype.h>
#include "tad_comandos.h"
#include "tad.h"
#include "operations.h"
#include "manipulations.h"
#include "conio.h"

int main(){
	system("title dBase III - Estruturas de Dados II");
	
	Dir *unid;
	Arq *arquivo_aberto;
	initDir(&unid); //Initializing
	
	buildUnit(&unid); //Build Unit C:
	buildUnit(&unid); //Build Unit D:
	buildUnit(&unid); //Build Unit E:
		
	char opc;
	char comando_field[50];
	char valor[50];
	valor[0] = '\0';
	
	printf("Diretorio atual: [%c:]\n", unid->letter);
	printf(". ");
	fflush(stdin);
	gets(comando_field);
	opc = Compara_String(comando_field, valor);
	
	while(opc != 3)
	{
		switch (opc)
		{

			//SET DEFAULT TO
			case 1 : {
				
				
				//system("cls"); //Goto
				trocaUnidade(&unid, toupper(valor[0]));
				//printf("Letra atual: %c\n", unid->letter); //Goto
				printf("Diretorio atual: [%c:]\n", unid->letter);
				break;
			}

			//CRIATE
			case 2 : {
					
				//Criar DBF
				novoArquivo(unid, valor);
				printf("Incluir dados ? <Y/N>: ");
				opc = toupper(getche());
				
				if(opc == 'Y')
				{
					arquivo_aberto = abrirArquivo(unid, valor);
					insertFields(arquivo_aberto);
				}
				break;
			}
			//USE
			case 5 : {
				
				arquivo_aberto = NULL;
				trocaUnidade(&unid, toupper(valor[0]));
				printf("Diretorio atual: [%c:]\n", unid->letter);
				break;
			}
			//LIST
			case 8 : {
				
				listaArquivo(unid);
				break;
			}
			//CLEAR
			case 9 : {
				
				system("cls");
				break;
			}
			
			default :
				printf("Comando Invalido\n");
		}
		
		printf(". ");
		fflush(stdin);
		gets(comando_field);
		opc = Compara_String(comando_field, valor);
	}
	
	return 0;
}
