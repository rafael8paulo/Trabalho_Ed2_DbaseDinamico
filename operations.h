//TAD Manipulacoes
int indexOf(char str[], char subs[])
{
	int flag = 0;
	char auxStr[50];
	char auxSubs[50];
	
	strcpy(auxStr, str); 
	strcpy(auxSubs, subs); 
	
	int x;
	int y = 0;
	int i = 0;
	int pos = -1;
	
	if (str[0] == '\0' || subs[0] == '\0' || strlen(subs) > strlen(str))
		return -1;
		
	
	while (str[i] != '\0' && !flag)
	{
		if(str[i] == subs[0])
		{
			flag = 1;
			x = i; 
			y = 0; 
			
			while (auxStr[x] != '\0' && auxSubs[y] != '\0' && flag)
			{
				flag = auxStr[x] != auxSubs[y] ? 0 : 1;
			
				x++; 
				y++; 
			}
		}
		pos++;
		i++;
	}
	
	if(auxSubs[y] == '\0' && flag == 1)
		return pos;
	return -1;
}

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

//Apos criado, o arquivo.DBF � aberto, para insercoes de dados
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
	newField->type = toupper(type);
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
//LOCATE FOR 
Campos *Busca_Campos(Campos *Inicio, char valor[]){
	
	while(Inicio != NULL && stricmp(Inicio->fieldName, valor)!=0)
		Inicio = Inicio->prox;
		
	return Inicio;
}
void Busca_ValorC(pDados *Inicio, char valor[], Status *s){
	
	int i=0;
	
	while(Inicio != NULL){
		if(stricmp(Inicio->valor.valorC, valor)==0 && s->status == 1){
			printf("\nRecord = %d", i+1);
		}
		Inicio =  Inicio->prox;
		s = s->prox;
		i++;
	}
	if(i == 0)
		printf("\nElemento nao encontrado!");
}
void Busca_ValorN(pDados *Inicio, char v[], Status *s){
	int i=0, valor = atof(v);
	
	while(Inicio != NULL){
		if(Inicio->valor.valorN == valor && s->status == 1){
			gotoxy(25, 21); printf("\nRecord = %d", i+1);
		}
		Inicio =  Inicio->prox;
		s = s->prox;
		i++;
	}
	if(i == 0)
		gotoxy(25, 21); printf("\nElemento nao encontrado!");
}
void Busca_ValorD(pDados *Inicio, char valor[], Status *s){
	int i=0;
	
	while(Inicio != NULL){
		if(stricmp(Inicio->valor.valorD, valor)==0 && s->status){
			gotoxy(25, 21);  printf("\nRecord = %d", i+1);
		}
		Inicio =  Inicio->prox;
		s = s->prox;
		i++;
	}
	if(i == 0)
		gotoxy(25, 21);  printf("\nElemento nao encontrado!");
}
void Busca_ValorL(pDados *Inicio, char valor[], Status *s){
	int i=0;
	
	while(Inicio != NULL){
		if(Inicio->valor.valorL == valor[0] && s->status){
			gotoxy(25, 21);  printf("\nRecord = %d", i+1);
		}
		Inicio =  Inicio->prox;
		s = s->prox;
		i++;
	}
	if(i == 0)
		gotoxy(25, 21); printf("\nElemento nao encontrado!");
}
void Busca_ValorM(pDados *Inicio, char valor[], Status *s){
	int i=0;
	
	while(Inicio != NULL){
		if(stricmp(Inicio->valor.valorM, valor)==0 && s->status){
			gotoxy(25, 21);  printf("\nRecord = %d", i+1);
		}
		Inicio =  Inicio->prox;
		s = s->prox;
		i++;
	}
	if(i == 0)
		gotoxy(25, 21); printf("\nElemento nao encontrado!");
}
void locate(Arq *arquivo_aberto, char comando_field[], char valor[]){
	
	Campos *c = arquivo_aberto->cmps;
	Campos *aux = Busca_Campos(c, comando_field);
	int pos;
	if(aux != NULL){
		
		switch(c->type){
			case 'N':
				Busca_ValorN(aux->p_dados, valor, arquivo_aberto->stts);
				break;
			case 'D':
				Busca_ValorD(aux->p_dados, valor, arquivo_aberto->stts);
				break;
			case 'L':
				Busca_ValorL(aux->p_dados, valor, arquivo_aberto->stts);
				break;
			case 'C':
				Busca_ValorC(aux->p_dados, valor, arquivo_aberto->stts);
				break;
			case 'M':
				Busca_ValorM(aux->p_dados, valor, arquivo_aberto->stts);
				break;
		}
	}	
}
//PACK
void remove_status(Status **status,  int pos){
	int i=0;
	if(pos == 0){
		*status = (*status)->prox;
	}else{
		Status *aux = *status, *ant;
		
		while(i < pos){
			ant = aux;
			aux = aux->prox;
			i++;
		}
		ant->prox =  aux->prox;
	}
}
void remove_pDados(Campos **Campos, int pos){
	int i=0;
	if(pos == 0){
		(*Campos)->p_dados = (*Campos)->p_dados->prox;
	}else{
		pDados *aux = (*Campos)->p_dados, *ant;
		
		while(i < pos){
			ant = aux;
			aux = aux->prox;
			i++;
		}
		ant->prox =  aux->prox;
	}
}
void pack(Arq **arquivo_aberto){

	pDados *p = (*arquivo_aberto)->cmps->p_dados, *antP;
	Campos *c = (*arquivo_aberto)->cmps;
	Status *s = (*arquivo_aberto)->stts;
	
	int pos = 0, vet[100], TL = 0, i=0;
	
	while(s != NULL){
		if(s->status == 0){
			vet[TL] = i;
			TL++;
		}	
		i++;
		s = s->prox;
	}
	//Remover da coluna status
	s = (*arquivo_aberto)->stts;
	for(i = 0; i<TL;i++){
			pos = vet[i];
			remove_status(&s, pos);
	}
	//Remover pDados
	while(c != NULL){
		for(i = 0; i<TL;i++){
			pos = vet[i];
			remove_pDados(&c, pos);
		}
		c = c->prox;
	}
	gotoxy(25, 21); printf("\n* Elementos Excluidos *");
}
//GOTO 
int goto_(Arq **arquivo_aberto, char vl[]){
	int i;
	Campos *c = (*arquivo_aberto)->cmps;
	pDados *p = (*arquivo_aberto)->cmps->p_dados, *aux;

	int pos = atoi(vl) - 1;
	
	while(c != NULL){
		
		aux = c->p_dados;
		i=0;
		
		while(i < pos){
			i++;
			aux = aux->prox;
		}
		
		if(aux != NULL){
			c->pAtual = aux;
		}else{
			gotoxy(25, 21); printf("\nRegistro nao existe!\n");
		}
		
		c = c->prox;
	}
}
//Edit
void edit(Arq **arquivo_aberto){
	
	char aux[50];
	Campos *c = (*arquivo_aberto)->cmps;
	
	system("cls");
	while(c != NULL){
		
		printf("\n %s\t", c->fieldName);
		fflush(stdin);
		gets(aux);
		
		switch (c->type)
		{
			case 'N' :{
				c->pAtual->valor.valorN = atof(aux);
				break;
			}
			case 'D' :{
				strcpy(c->pAtual->valor.valorD, aux);
				break;
			}
			case 'L' :{
				c->pAtual->valor.valorL = aux[0];
				break;
			}
			case 'C' :{
				strcpy(c->pAtual->valor.valorC, aux);
				break;
			}
			case 'M' :{
				strcpy(c->pAtual->valor.valorM, aux);
				break;
			}
		}
		c = c->prox;
	}
	
}	
void list2(Arq *arquivo_aberto){
	
	Status *posStts = arquivo_aberto->stts;
	Campos *auxCmps = arquivo_aberto->cmps;
	pDados *p = arquivo_aberto->cmps->p_dados;
	
	while(posStts != NULL) //ou posStts != NULL
	{ 
	    while(auxCmps != NULL)
	    {
			while(p != NULL)
			{
				switch(auxCmps->type)
		        {
		            case 'N' : {
		                printf("%.2f			", auxCmps->p_dados->valor.valorN);
		                break;
		            }
		            
		            case 'L' : {
		                printf("%c			", auxCmps->p_dados->valor.valorL);
		                break;
		            }
		            
		            case 'D' : {
		                printf("%s			", auxCmps->p_dados->valor.valorD);
		                break;
		            }
		            case 'C' : {
		                printf("%s			", auxCmps->p_dados->valor.valorC);
		                break;
		            }
		            case 'M' : {
		                printf("%s		", auxCmps->p_dados->valor.valorM);
		                break;
		            }
		    	}
				p = p->prox;	
			}
			auxCmps = auxCmps->prox;
	    }
	    posStts = posStts->prox;
	}	
}	
