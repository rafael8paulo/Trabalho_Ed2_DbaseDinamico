#include <stdio.h>
#include <stdlib.h> //strtof();
#include <string.h> //strcpy()
#include <time.h> //time(), localtime();
#include <ctype.h>
#include "tad_comandos.h"
#include "tad.h"
#include "operations.h"
#include "manipulations.h"
#include "meuconio.h"

int main(){
	system("title dBase III - Estruturas de Dados II");
	
	Dir *unid;
	Arq *arquivo_aberto;
	initDir(&unid); //Initializing
	
	buildUnit(&unid); //Build Unit C:
	buildUnit(&unid); //Build Unit D:
	buildUnit(&unid); //Build Unit E:
		
	int opc;
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
				
				
				novoArquivo(unid, valor);
				//printf("Arquivo: |%s|\n", unid->arqs->nomeDBF); 
				printf("Incluir dados ? <Y/N>: ");
				//opc = toupper(getch());
				scanf("%d", &opc);
				printf("\n");
				
				if(opc == 'Y')
					printf("Tela\n");
				
				break;
			}
			//USE
			case 5 : {
				

				arquivo_aberto = abrirArquivo(unid, valor);
				
				
				if(arquivo_aberto != NULL)
					printf("Aberto: [%s]\n", arquivo_aberto->nomeDBF);
				else
					printf("Not found\n");
					
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
		
		/*printf("comando_field [%s]\n", comando_field);
		printf("valor [%s]\n", valor);*/
		
		printf(". ");
		fflush(stdin);
		gets(comando_field);
		opc = Compara_String(comando_field, valor);
	}
	
	return 0;
}