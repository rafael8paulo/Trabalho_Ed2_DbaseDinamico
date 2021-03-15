//TAD Manipulacoes

void initDir(Dir **uni)
{
	*uni = NULL;
}

void getDate(char date[])
{
	struct tm *p;
    time_t seconds;
    time(&seconds);
    p = localtime(&seconds);
    sprintf(date, "%d/%d/%d\0", p->tm_mday, p->tm_mon + 1, p->tm_year + 1900);
}

void getHour(char hour[])
{
	struct tm *p;
    time_t seconds;
    time(&seconds);
    p = localtime(&seconds);
    sprintf(hour, "%d:%d:%d\0", p->tm_hour, p->tm_min, p->tm_sec);
}


void buildUnit(Dir **uni)
{
	Dir *aux = *uni;
	Dir *newUnit = (Dir*) malloc(sizeof(Dir));
	newUnit->bottom = newUnit->top = NULL;
	newUnit->arqs = NULL;
	
	//Primeira Caixa
	if(*uni == NULL)
	{
		newUnit->letter = 'C';
		*uni = newUnit;
	}
	else{ //Demais caixas
	
		while (aux->bottom != NULL)
			aux = aux->bottom;
		
		newUnit->letter = aux->letter + 1; //Considerando que esteja na ultima letra
		newUnit->top = aux;
		aux->bottom = newUnit;
	}
}

//Apos criado, o arquivo.DBF é aberto, para insercoes de dados
Arq *createNewDBF (Dir *uni, char name[]) //nao necessario passagem por referencia
{
	char date[9];
	char hour[9];
	
	getDate(date);
	getHour(hour);
	
	
	//Arq *aux = (*uni)->arqs;
	Arq *aux; //= (*uni)->arqs;
	Arq *newDBF = (Arq*) malloc (sizeof(Arq));
	
	strcpy(newDBF->nomeDBF, name);
	strcpy(newDBF->data, date);
	strcpy(newDBF->hora, hour);
	
	newDBF->stts = NULL;
	newDBF->cmps = NULL;
	newDBF->prox = NULL;
	
	//Primeiro Arquivo
	if(uni->arqs == NULL)
	{
		newDBF->ant = NULL;
		uni->arqs = newDBF;
	}
	else{ //Demais Arquivos
	
		aux = uni->arqs;
		
		while(aux->prox != NULL)
			aux = aux->prox;
			
		newDBF->ant = aux;
		aux->prox = newDBF;
	}
	return newDBF;
}


//Recebe o ponteiro onde o arquivo DBF esta aberto
void createNewField (Arq *open_file, char name[], char type, int width, int dec)
{
	Campos *aux;
	Campos *newField = (Campos*) malloc (sizeof(Campos));
	
	newField->pAtual = NULL;
	strcpy(newField->fieldName, name);
	newField->type = type;
	newField->width = width;
	newField->dec = dec;
	newField->p_dados = NULL;
	newField->prox = NULL;
	
	if (open_file->cmps == NULL)
	{
		open_file->cmps = newField;
	}
	else
	{
		aux = open_file->cmps;
		while(aux->prox != NULL)
			aux = aux->prox;
		
		aux->prox = newField;
	}
}


void createNewStatus (Arq *open_file)
{
	Status *aux;
	Status *newStts = (Status*) malloc (sizeof(Status));
	
	newStts->status = 1;
	newStts->prox = NULL;
	
	if(open_file->stts == NULL)
	{
		open_file->stts = newStts;
	}
	else{
		
		aux = open_file->stts;
		while (aux->prox != NULL)
			aux = aux->prox;
		
		aux->prox = newStts;
	}
}

void createNewCell (Campos *open_field, char info[])
{
	pDados *aux;
	pDados *reg = (pDados*) malloc (sizeof(pDados));
	reg->prox = NULL;
	
	
	switch (open_field->type)
	{
		case 'N' :
		case 'n' : {
			reg->valor.valorN = strtof(info, NULL);
			break;
		}
		case 'D' :
		case 'd' : {
			strcpy(reg->valor.valorD, info);
			break;
		}
		case 'L' :
		case 'l' : {
			reg->valor.valorL = info[0];
			break;
		}
		case 'C' :
		case 'c' : {
			strcpy(reg->valor.valorC, info);
			break;
		}
		case 'M' :
		case 'm' : {
			strcpy(reg->valor.valorM, info);
			break;
		}
	}
	
	if (open_field->p_dados == NULL)
	{
		open_field->p_dados = reg;
		open_field->pAtual  = reg;
	}
	else {
		
		aux = open_field->p_dados;
		while (aux->prox != NULL)
			aux = aux->prox;
			
		aux->prox = reg;
	}
}