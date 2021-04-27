#include <stdio.h>
#include <stdlib.h> //strtof();
#include <string.h> //strcpy()
#include <time.h> //time(), localtime();
#include <conio2.h>
#include <ctype.h>
#include <windows.h>
#include <time.h>
#include "display.h"
#include "TadComandos.h"
#include "tad.h"
#include "operations.h"
#include "manipulations.h"

void display(Arq *arquivo_aberto){
	int x = 15;
	Campos *c =  arquivo_aberto->cmps;
	while(c  != NULL){
		gotoxy(x, 9); printf(" %s ", c->fieldName);
		switch(c->type)
		{
            case 'N' : {
                gotoxy(x, 10);printf("%.2f", c->p_dados->valor.valorN);
                break;
            }
            
            case 'L' : {
                gotoxy(x, 10);printf("%c", c->p_dados->valor.valorL);
                break;
            }
            
            case 'D' : {
                gotoxy(x, 10);printf("%s", c->p_dados->valor.valorD);
                break;
            }
            case 'C' : {
                gotoxy(x, 10);printf("%s", c->p_dados->valor.valorC);
                break;
            }
            case 'M' : {
                gotoxy(x, 10);printf("%s", c->p_dados->valor.valorM);
                break;
            }
		}
		x = x + 20;
		c = c->prox;
	}
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
		
	int opc, id;
	char comando_field[50];
	char valor[50];
	valor[0] = '\0';
	
	//show();
	DesenhaBorda();
	gotoxy(2, 24); printf("Diretorio atual: [%c:]\n", unid->letter);
	gotoxy(2, 22); printf(". ");
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
			
			//EDIT
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
			//RECALL
			case 9 : {
				recall(&arquivo_aberto, id);
				break;
			}
			//CLEAR
			case 10 : {
				Delete(&arquivo_aberto, id);
				break;
			}
			//APPEND
			case 11 : { //*******************T*******************estar
				append(arquivo_aberto);
				break;
			}
			
			//DISPLAY
			case 12 : { //*******************T*******************estar
				display(arquivo_aberto);
				break;
			}
			
			//DELETE ALL
			case 13 : {
				DeleteAll(arquivo_aberto->stts);
				gotoxy(25, 21); printf("All deleted recordings\n");
				break;
			}
			
			//RECALL ALL
			case 14 : {
				RecallAll(arquivo_aberto->stts);
				gotoxy(25, 21); printf("All records retrieved\n");
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
				gotoxy(2, 2); printf("Incluir Fields ? (Y/N): ");
				opc = toupper(getche());
				
				if(opc == 'Y')
				{
					arquivo_aberto = abrirArquivo(unid, valor);
					insertFields(arquivo_aberto);
					
					gotoxy(2, 2); printf("Input data records now? (Y/N)");
					opc = toupper(getch());
					while(opc == 'Y')
					{
						//Chamada
						append(arquivo_aberto);
						DesenhaBorda();
						gotoxy(2, 2); printf("Continue including? (Y/N)");
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
				if(arquivo_aberto != NULL){
					gotoxy(25, 21); printf("Aberto: [%s]\n", arquivo_aberto->nomeDBF);
				}
				else{
					gotoxy(25, 21); printf("Not found\n");
				}
					
				break;
			}
			//GOTO
			case 21 : {
				id = atoi(valor) - 1;
				goto_(&arquivo_aberto, valor);
				break;
			}
			//SET DEFAULT TO
			case 22 : {
				arquivo_aberto = NULL;
				trocaUnidade(&unid, toupper(valor[0]));
				gotoxy(25, 21); printf("Diretorio atual: [%c:]\n", unid->letter);
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
			//SET DELETED
			case 25 : {
                set_delete(valor);
                break;
            }
			default :
				gotoxy(25, 21); printf("Comando Invalido\n");
		}
		Sleep(1000);
		DesenhaBorda();
		gotoxy(2, 24); printf("Diretorio atual: [%c:]\n", unid->letter);
		gotoxy(2, 22); printf(". ");
		fflush(stdin);
		gets(comando_field);
		opc = Compara_String(comando_field, valor);
	}
	
	return 0;
}
