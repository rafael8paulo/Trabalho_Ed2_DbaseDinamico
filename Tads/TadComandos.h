void replace(char string[], char delimitador)
{
	int i = 0;
	int x = 0;
	char aux[strlen(string) + 1];
	
	//Possivel redundancia
	while(i< strlen(string) && string[i] != '\0')
	{
		if(string[i] != delimitador){
			aux[x] = string[i];
			x++;
		}
		i++;
	}
	aux[x] = '\0';
	strcpy(string, aux);
}

void trim (char res[])
{
	int i = 0;
	int x = 0;
	int y = strlen(res) - 1;
	char aux[50];
	
	while(res[x] != '\0' && res[x] == ' ')
		x++;
		
	while(y >= 0 && res[y] == ' ')
		y--;
		
	while(x <= y)
		aux[i++] = res[x++];
		
	aux[i] = '\0';
	
	strcpy(res, aux);
}

int SeparaComando(char digitado[], const char comando[], char res[])
{
	char aux[50];
	int pos = 0;
	
	while(toupper(digitado[pos]) == toupper(comando[pos]) && digitado[pos] != '\0' && comando[pos] != '\0')
	{
		aux[pos] = comando[pos];
		pos++;
	}
	aux[pos] = '\0';
	
	if(stricmp(aux, comando) == 0){
		int i=0;
		while(digitado[pos] != '\0'){
			res[i] = digitado[pos];
			i++;
			pos++;
		}
		res[i] = '\0';
		trim(res);
		if(res[0] != '\0')
			return 1;
	}	
	return 0;	
}

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
	trim(field);
}

//Recebe a string e a trata para a função 
int Compara_String(char comando_field[], char valor[])
{
	/* ISSUES
	*verificar se atributo passado a uma funcao que faz uso da mesma, nao esta vazio
	*testar
	*/
	
	char res[50];
	const char gt[] = "GOTO";
	const char use[] = "USE";
	const char create[] = "CREATE";
	const char locate[] = "LOCATE FOR";
	const char list_nome[] = "LIST FOR";
	const char setdef[] = "SET DEFAULT TO";
	
	trim(comando_field);
	
	if(!stricmp(comando_field, "ZAP")) //Ok
		return 1;
	
	if(!stricmp(comando_field, "DIR")) //Ok
		return 2;
		
	if(!stricmp(comando_field, "QUIT")) //Ok
		return 3;
		
	if(!stricmp(comando_field, "EDIT")) //Ok
		return 4;
	
	if(!stricmp(comando_field, "PACK")) //Ok
		return 5;
	
	if(!stricmp(comando_field, "SORT")) //Ok
		return 6;
			
	if(!stricmp(comando_field, "LIST")) //Ok
		return 7;
		
	if(!stricmp(comando_field, "CLEAR")) //Ok
		return 8;
		
	if(!stricmp(comando_field, "RECALL")) //Ok
		return 9;
	
	if(!stricmp(comando_field, "DELETE")) //Ok
		return 10;
		
	if(!stricmp(comando_field, "APPEND")) //Ok
		return 11;
		
	if(!stricmp(comando_field, "DISPLAY")) //Ok
		return 12;
		
	if(!stricmp(comando_field, "DELETE ALL")) //Ok
		return 13;
		
	if(!stricmp(comando_field, "RECALL ALL")) //Ok
		return 14;
	
	if(!stricmp(comando_field, "SET DELETED ON")) //Ok
		return 15;
	
	if(!stricmp(comando_field, "LIST STRUCTURE")) //Ok
		return 16;
		
	if(!stricmp(comando_field, "SET DELETED OFF")) //Ok
		return 17;
	
	if(!stricmp(comando_field, "MODIFY STRUCTURE")) //Ok
		return 18;
	
	if(SeparaComando(comando_field, create, res)) //Ok
	{
		strcpy(valor, res);
		return 19;
	}
	
	if(SeparaComando(comando_field, use, res)) //Ok
	{
		strcpy(valor, res);
		return 20;
	}
	
	if(SeparaComando(comando_field, gt, res)) //Ok
	{
		strcpy(valor, res);
		return 21;
	}
	
	if(SeparaComando(comando_field, setdef, res)) //Ok
	{
		replace(res, ' ');
		replace(res, ':');
		strcpy(valor, res);
		return 22;
	}
	
	if(SeparaComando(comando_field, list_nome, res)) //Ok
	{
		field_param(comando_field, res);
		replace(res, '=');
		replace(res, '\"');
		trim(res);
		strcpy(valor, res);
		return 23;
	}
	
	if(SeparaComando(comando_field, locate, res)) //Ok
	{
		field_param(comando_field, res);
		replace(res, '=');
		replace(res, '\"');
		trim(res);
		strcpy(valor, res);
		return 24;
	}
	return 0; //Nenhuma das opcoes
}
