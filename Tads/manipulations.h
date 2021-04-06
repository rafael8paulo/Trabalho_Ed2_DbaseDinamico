/*struct posicoes
{
	unsigned int y;
};
typedef struct posicoes Posicoes;
*/
int setdel_onoff = 0;
struct field
{
	char nome[50];
	char tipo; 
	int largura;
	int dec;
};
typedef struct field Entradas;
void set_delete(char valor[])
{
    if(!stricmp("on", valor))
    {
        setdel_onoff = 0;
        printf("set deleted 0\n");
    }
    else if(!stricmp("off", valor))
    {
        setdel_onoff = 1;
        printf("set deleted 1\n");
    }
    else printf("Comando Invalido\n");
}
int trocaUnidade (Dir **unid, char letra)
{
	/*
	*return 1 - successfully
	*return 0 - unsuccessfully
	*/
	
	Dir *aux = *unid;
	while(aux->top != NULL && aux->letter != letra)
		aux = aux->top;
	
	if(aux->letter == letra)
	{
		*unid = aux;
		return 1;
	}
		
	aux = *unid;
	while(aux->bottom != NULL && aux->letter != letra)
		aux = aux->bottom;
		
	if(aux->letter == letra)
	{
		*unid = aux;
		return 1;
	}
	return 0;
}

Arq *novoArquivo (Dir *unid, char nomeArq[])
{
	return createNewDBF(unid, nomeArq);
}

void listaArquivo (Dir *unid)
{
	Arq *aux = unid->arqs;
	while(aux != NULL)
	{
		printf("%s\n", aux->nomeDBF);
		aux = aux->prox;
	}
}

Arq *abrirArquivo (Dir *unid, const char *nomeArq)
{
	Arq *aux = unid->arqs;
	while(aux != NULL && stricmp(aux->nomeDBF, nomeArq))
		aux = aux->prox;
		
	return aux;
}

void insertFields(Arq *arq)
{
	Entradas in;
	int i = 1;
	show();
	printf("  %d  ", i);
	fflush(stdin);
	gets(in.nome);
	
	while(stricmp(in.nome, "\0"))
	{
		gotoxy(17, i + 2); in.tipo = getche();
		fflush(stdin);
		gotoxy(25, i + 2); scanf("%d", &in.largura);
		fflush(stdin);
		gotoxy(33, i + 2); scanf("%d", &in.dec);
		i++;
		
		createNewField(arq, in.nome, toupper(in.tipo), in.largura, in.dec);
		
		printf("  %d  ", i);
		fflush(stdin);
		gets(in.nome);
	}
	system("cls");
}

void listarFields(Arq *arq, Dir *uni)
{
	if(arq != NULL)
	{
		Campos *f = arq->cmps;
		int i = 1;
		system("cls");
		printf("Structure for database: %c:%s\n", uni->letter, arq->nomeDBF);
		printf("Field	Field Name		Type	Width	Dec\n");
		while(f != NULL)
		{
			gotoxy(3, i + 2); printf("  %d  ", i);
			gotoxy(9, i + 2); printf("%s", f->fieldName);
			gotoxy(33, i + 2); printf("%c", f->type);
			gotoxy(41, i + 2); printf("%d", f->width);
			gotoxy(49, i + 2); printf("%d", f->dec);
			f = f->prox;
			i++;
		}
		printf("\n");
	}
}

void append (Arq *arq)
{
	if(arq != NULL)
	{
		Campos *aux = arq->cmps;
		char info[50];
		
		if(aux != NULL) //Exibicao das Fields
		{
			system("cls");
			while(aux != NULL)
			{
				printf("%s\n", aux->fieldName);
				aux = aux->prox;
			}
			aux = arq->cmps;
			createNewStatus(arq);
		}
		
		int i = 1;
		while(aux != NULL)
		{
			gotoxy(17, i++);
			fflush(stdin);
			gets(info);
			createNewCell(aux, info);
			aux = aux->prox;
		}
	}
}

int getRegSize(Status *stts)
{
	int i = 0;
	Status *aux = stts;
	while(aux != NULL)
	{
		if(aux->status)
			i++;
		aux = aux->prox;
	}
	return i;
}

void list (Arq *arq) { //Ok
	
	system("cls");
	
	int i = 0, x = 25, y = 2;
	Status *posStts = arq->stts;
	Campos *auxCmps = arq->cmps;
	pDados *auxP;
	
	printf("Record#			");
	while (auxCmps != NULL)
	{
		printf("%s			", auxCmps->fieldName); 
		auxCmps = auxCmps->prox;
	}
	
	auxCmps = arq->cmps;
	while(auxCmps != NULL){
		auxP = auxCmps->p_dados;
		posStts = arq->stts;
		while(auxP != NULL)	{
			if(setdel_onoff || posStts->status){
				switch(auxCmps->type)
				{
					case 'N' : {
						gotoxy(x, y++); printf("%.2f			", auxP->valor.valorN);
						break;
					}
					
					case 'L' : {
						gotoxy(x, y++); printf("%c			", auxP->valor.valorL);
						break;
					}
					
					case 'D' : {
						gotoxy(x, y++); printf("%s			", auxP->valor.valorD);
						break;
					}
					case 'C' : {
						gotoxy(x, y++); printf("%s			", auxP->valor.valorC);
						break;
					}
					case 'M' : {
						gotoxy(x, y++); printf("%s		", auxP->valor.valorM);
						break;
					}
				}
			}
			auxP = auxP->prox;
			posStts = posStts->prox;
		}
		y = 2;
		x = x + 25;
		auxCmps = auxCmps->prox;
	}

	auxP =  arq->cmps->p_dados;
	posStts = arq->stts;
	y = 2;
	while(posStts != NULL){
		if(setdel_onoff || posStts->status)
		{
			gotoxy(5, y++); printf(" %d ", i+1);
		}
		i++;
		posStts = posStts->prox;
	}
}

void copy_value(char str[], Campos *field)
{
	switch(field->type)
	{
		case 'N' : {
			sprintf(str, "%f", field->pAtual->valor.valorN);
			break;
		}
		case 'L' : {
			str[0] = field->pAtual->valor.valorL;
			str[1] = '\0';
			break;
		}
		
		case 'D' : {
			strcpy(str, field->pAtual->valor.valorD);
			break;
		}
		case 'C' : {
			strcpy(str, field->pAtual->valor.valorC);
			break;
		}
		case 'M' : {
			strcpy(str, field->pAtual->valor.valorM);
			break;
		}
	}
}

void listFor (Arq *arq, char field[], char valor[])
{
	if(arq != NULL && arq->stts != NULL && (/*SET DELETED off/on*/ 0 || getRegSize(arq->stts)))
	{
		//POSICIONA PONTEIROS
		int i = 1;
		int flag = 0;
		char str[50];
		Status *posStts = arq->stts;
		Campos *auxCmps = arq->cmps;
		Campos *fieldEncontrada;
		//POSICIONA PONTEIROS
		
		
		//Já verificando se Field exisite
		while (!flag && auxCmps != NULL)
		{
			if(!stricmp(auxCmps->fieldName, field))
				flag = 1;
			else
				auxCmps = auxCmps->prox;
		}
		//Já verificando se Field exisite
				
		if(flag)
		{
			fieldEncontrada = auxCmps; //Atribuindo a field encontrada
			auxCmps = arq->cmps;
			
			//posicionando pAtual no primeiro registro
			while(auxCmps != NULL)
			{
				auxCmps->pAtual = auxCmps->p_dados;
				auxCmps = auxCmps->prox;
			}
			auxCmps = arq->cmps;
			//posicionando pAtual no primeiro registro
			
			//Exibe linha de Fields
			printf("Record#		");
			while (auxCmps != NULL)
			{
				printf("%s		", auxCmps->fieldName);
				auxCmps = auxCmps->prox;
			}
			printf("\n");
			auxCmps = arq->cmps;
			//Exibe linha de Fields
			
			while(posStts != NULL)
			{
				flag = 1;
				copy_value(str, fieldEncontrada);
				
				while(auxCmps != NULL)
				{
					if((/*SET DELETED off/on*/ 0 || posStts->status) && indexOf(str, valor) != -1)
					{
						if(flag)
						{
							printf("%d		", i++);
							flag = 0;
						}
						
						switch(auxCmps->type)
						{
							case 'N' : {
								printf("%.2f		", auxCmps->pAtual->valor.valorN);
								break;
							}
							
							case 'L' : {
								printf("%c		", auxCmps->pAtual->valor.valorL);
								break;
							}
							
							case 'D' : {
								printf("%s		", auxCmps->pAtual->valor.valorD);
								break;
							}
							case 'C' : {
								printf("%s		", auxCmps->pAtual->valor.valorC);
								break;
							}
							case 'M' : {
								printf("%s		", auxCmps->pAtual->valor.valorM);
								break;
							}
						}
					}
					auxCmps->pAtual = auxCmps->pAtual->prox;
					auxCmps = auxCmps->prox;
				}
				if(!flag)
					printf("\n"); //Tratar
				posStts = posStts->prox;
				auxCmps = arq->cmps;
			}
			
			//Retornar pAtual posStts para primeira posicao valida (nao marcada para exclusao).
			/*struct pointers {
				//unidade aberta
				//arquivo aberto
				//registro atual
			};*/
			
			posStts = arq->stts;
			while(auxCmps != NULL)
			{
				auxCmps->pAtual = auxCmps->p_dados;
				while(posStts != NULL  && posStts->status == 0)
				{
					auxCmps->pAtual = auxCmps->pAtual->prox;
					posStts = posStts->prox;
				}
				auxCmps = auxCmps->prox;
				if(auxCmps != NULL)
					posStts = arq->stts;
			}
			auxCmps = arq->cmps;
		}
	}
}

void DeleteAll(Status *s) 
{
	if(s != NULL) {
		DeleteAll(s->prox);
		s->status = 0;
	}
}

void RecallAll(Status *s)
{
	if(s != NULL) {
		RecallAll(s->prox);
		s->status = 1;
	}
}
void Delete(Arq **arquivo_aberto, int id){
	int i=0;
	Status *s =  (*arquivo_aberto)->stts;
	
	while(s != NULL && i < id){
		i++;
		s = s->prox;
	}
	
	if(s != NULL){
		s->status = 0;
		printf("\n %d record deleted", i+1);
	}else{
		printf("\n does not exist");
	}
		
}
void recall(Arq **arquivo_aberto, int id){
	int i=0;
	Status *s =  (*arquivo_aberto)->stts;
	
	while(s != NULL && i < id){
		i++;
		s = s->prox;
	}
	
	if(s != NULL){
		s->status = 1;
		printf("\n %d record recalled", i+1);
	}else{
		printf("\n does not exist");
	}
}
