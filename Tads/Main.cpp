#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<ctype.h>
#include<string.h>
#include"Tad_Comandos.h"

int main(){
	
	char comando[50];
	printf("# ");gets(comando);
	
	Compara_String(comando);
	

	return 0;
}
