#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<ctype.h>
#include<string.h>
#include"Tad_Comandos.h"

int main(){
	
	char comando[50] = {"LOCATE FOR NOME = \"rafael\"" }, valor[50];
	//printf("# ");gets(comando);
	
	Compara_String(comando, valor);
	

	return 0;
}
