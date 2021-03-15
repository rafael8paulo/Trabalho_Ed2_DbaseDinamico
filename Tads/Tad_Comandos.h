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

bool SeparaComando(char digitado[], char comando[], char res[])
{
	char aux[50];
	int pos = 0;
	
	while(toupper(digitado[pos]) == toupper(comando[pos]) && digitado[pos] != '\0' && comando[pos] != '\0'){
		aux[pos] = comando[pos];
		pos++;
	}
	aux[pos] = '\0';
	
	if(stricmp(aux, comando)==0){
		int i=0;
		while(digitado[pos] != '\0'){
			res[i] = digitado[pos];
			i++;
			pos++;
		}
		res[i] = '\0';
		if(res[0] != '\0')
			return 1;
	}	
	return 0;	
}

//field_param(comando, res);
void field_param(char field[], char digitado[])
{
	int i = 0;
	while(digitado[i] != '=' && digitado[i] != '\0')
	{
		field[i] = digitado[i];
		digitado[i] = ' ';
		i++;
	}
	field[i] = '\0';
}

void trim (char comando[])
{
	int i = 0;
	int x = 0;
	int y = strlen(comando) - 1;
	char aux[50];
	
	while(comando[x] == ' ')
		x++;
		
	while(comando[y] == ' ')
		y--;
		
	while(x <= y)
		aux[i++] = comando[x++];
		
	aux[i] = '\0';
	
	strcpy(comando, aux);
}
//Recebe a string e a trata para a fun��o 
int Compara_String(char comando[], char field[])
{
	/* ISSUES
	*verificar se atributo passado a uma funcao que faz uso da mesma, nao esta vazio
	*
	*/
	
	char create[] = "CREATE";
	char setdef[] = "SET DEFAULT TO";
	char use[] = "USE";
	char locate[] = "LOCATE FOR";
	char list_nome[] = "LIST FOR";
	char gt[] = "GOTO";
	char setdel[] = "SET DELETED";
	
	char res[50], aux[50];
	trim(comando);
	
	if(SeparaComando(comando, setdef, res)) //Ok
	{
		replace(res, ' ');
		replace(res, ':');
		strcpy(comando, res);
		return 1;
	}
	
	if(SeparaComando(comando, create, res)) //Ok
	{
		replace(res, ' ');
		strcpy(comando, res);
		return 2;
	}
	
	if(!stricmp(comando, "DIR")) //Ok
		return 3;
		
	if(!stricmp(comando, "QUIT")) //Ok
		return 4;
		
	if(SeparaComando(comando, use, res)) //Ok
	{
		replace(res, ' ');
		strcpy(comando, res);
		return 5;
	}
	
	if(!stricmp(comando, "LIST STRUCTURE")) //Ok
		return 6;
	
	if(!stricmp(comando, "APPEND")) //Ok
		return 7;
	
	if(!stricmp(comando, "LIST")) //Ok
		return 8;
	
	if(!stricmp(comando, "CLEAR")) //Ok
		return 9;
	
	if(SeparaComando(comando, locate, res)) //Ok
	{
		field_param(comando, res);
		replace(res, '=');
		replace(res, '\"');
		strcpy(field, res);
		trim(res);
		trim(comando);
		return 10;
	}
	
	if(SeparaComando(comando, gt, res)) //Ok
	{
		replace(res, ' ');
		trim(res);
		strcpy(field, res);
		return 11;
	}
	
	if(!stricmp(comando, "DISPLAY"))//Ok
		return 12;
	
	if(!stricmp(comando, "EDIT")) //Ok
		return 13;
	
	if(!stricmp(comando, "DELETE")) //Ok
		return 14;
	
	if(!stricmp(comando, "RECALL")) //Ok
		return 15;
	
	if(SeparaComando(comando, setdel, res)) //Ok
	{
		trim(res);
		strcpy(field, res);
		return 16;
	}
		
	
	if(!stricmp(comando, "PACK")) //Ok
		return 17;
	
	if(!stricmp(comando, "ZAP")) //Ok
		return 18;
		
		
	if(SeparaComando(comando, list_nome, res)) //Ok
	{
		trim(res);
		field_param(comando, res);
		replace(res, '=');
		replace(res, '\"');
		trim(res);
		strcpy(field, res);
		return 19;
	}
		
	if(!stricmp(comando, "DELETE ALL")) //Ok
		return 20;
	
	if(!stricmp(comando, "RECALL ALL")) //Ok
		return 21;
		
	if(!stricmp(comando, "MODIFY STRUCTURE")) //Ok
		return 22;
	
	if(!stricmp(comando, "SORT")) //Ok
		return 23;


	return 0; //Nenhuma das opcoes
}
