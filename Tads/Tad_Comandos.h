void replace(char string[], char delimitador){
	int i=0, x=0;
	char aux[strlen(string)+1];
	
	while(i< strlen(string) && string[i] != '\0'){
		if(string[i] != delimitador){
			aux[x] = string[i];
			x++;
		}
		i++;
	}
	aux[x] = '\0';
	strcpy(string, aux);
}
bool SeparaComando(char digitado[], char comando[],char res[]){
	
	char aux[50];
	int pos=0;
	
	while(toupper(digitado[pos]) == toupper(comando[pos]) && digitado[pos] != '\0' && comando[pos] != '\0'){
		aux[pos] = comando[pos];
		pos++;
	}
	aux[pos] = '\0';
	
	if(stricmp(aux, comando)==0){
		int i=0;
		while(pos < strlen(digitado) && digitado[pos] != '\0'){
			res[i] = digitado[pos];
			i++;
			pos++;
		}
		return 1;
	}	
	return 0;	
}

//Recebe a string e a trata para a fun��o 
void Compara_String(char comando[]){

	char set[] = "SET DELETED";
	char gt[] = "GOTO";
	char locate[] = "LOCATE FOR NOME";
	char setdef[] = "SET DEFAULT TO";
	char res[30], aux[30];
	
	if(SeparaComando(comando, set, res)==1){
		replace(res, ' ');
		printf("\nSet: %s", res);
	}
	else if(SeparaComando(comando, gt, res)==1){
		printf("\nGOTO");
	}
	else if(SeparaComando(comando, locate, res)==1){	
		replace(res, '=');
		replace(res, '\"');
		replace(res, ' ');
		puts(res);
	}
	else if(SeparaComando(comando, setdef, res)==1){
		replace(res, ' ');
		printf("\nCriar Arquivo: %s", res);
	}
	else if(stricmp(comando,"LIST STRUCTURE")==0){
		printf("\nLISTAR");	
	}
	else if(stricmp(comando,"CREATE")==0){
		printf("\nCriar Tabela");
	}
	else if(stricmp(comando,"DIR")==0){
		printf("\nDIR");
	}
	else if(stricmp(comando,"USE")==0){
		printf("\nUSE"); 
	}
	else if(stricmp(comando,"APPEND")==0){
		printf("\nAPPEND");
	}
	else if(stricmp(comando,"LIS")==0){
		printf("\nLIST");
	}
	else if(stricmp(comando,"DISPLAY")==0){
		printf("\nDISPLAY");
	}
	else if(stricmp(comando,"EDIT")==0){
		printf("\nEDIT");
	}
	else if(stricmp(comando,"DELETE")==0){
		printf("\nDELETE");
	}
	else if(stricmp(comando,"RECALL")==0){
		printf("\nRECALL");
	}
	else{
		printf("\n comando invalido");
	}	
}
