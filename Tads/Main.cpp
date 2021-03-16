#include <stdio.h>
#include <stdlib.h> //strtof();
#include <string.h> //strcpy()
#include <time.h> //time(), localtime();
#include <ctype.h>
#include <conio.h>
#include "meuconio.h"
#include "display.h"
#include "tad_comandos.h"
#include "tad.h"
#include "operations.h"
#include "manipulations.h"



int main(){
	system("title dBase III - Estruturas de Dados II");
	
	Dir *unid;
	Arq *arquivo_aberto;
	initDir(&unid); //Initializing
	
	buildUnit(&unid); //Build Unit C:
	
	arquivo_aberto = createNewDBF(unid, "CLIENTES.dbf");
	
	arquivo_aberto->cmps = createNewField(arquivo_aberto, "CODIGO", 'N', 8, 0);
	arquivo_aberto->cmps = createNewField(arquivo_aberto, "NOME", 'C', 20, 0);
	
	append(&arquivo_aberto);
	
	exibir(arquivo_aberto);
	
	return 0;
}

/*int main(){
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

			//CREATE
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
			//DIR
			case 3 : {
				listaArquivo(unid);
				break;
			}
			//USE
			case 5 : {
				
				arquivo_aberto = NULL;
				trocaUnidade(&unid, toupper(valor[0]));
				printf("Diretorio atual: [%c:]\n", unid->letter);
				break;
			}
			//LIS STRUCTURE
			case 6: {
				listarFields(arquivo_aberto, unid);
				break;
			}
			//APPEND
			case 7: {
				append(&arquivo_aberto);
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
}*/
