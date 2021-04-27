void DesenhaBorda(){
	int i;
	system("cls");
	textcolor(15);
	clrscr();
	gotoxy(1,1); printf("%c",201);
    gotoxy(1,25); printf("%c",200);
    gotoxy(80,1); printf("%c",187);
    gotoxy(80,25); printf("%c",188);
    
    for(i=2; i<80; i++)
    {
        gotoxy(i,1); printf("%c",205);
        gotoxy(i,25); printf("%c",205);
    }

    for(i=2; i<25; i++)
    {
        gotoxy(1,i); printf("%c",186);
        gotoxy(80,i); printf("%c",186);
    }
}

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
        gotoxy(25, 21); printf("set deleted 0\n");
    }
    else if(!stricmp("off", valor))
    {
        setdel_onoff = 1;
        gotoxy(25, 21); printf("set deleted 1\n");
    }
    //else gotoxy(25, 21); printf("Comando Invalido\n");
}
int trocaUnidade (Dir **unid, char letra)
{
	
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
	DesenhaBorda();
	show();
	printf("  %d  ", i);
	fflush(stdin);
	gets(in.nome);
	
	while(stricmp(in.nome, "\0"))
	{
		gotoxy(17, i + 3); in.tipo = getche();
		fflush(stdin);
		gotoxy(25, i + 3); scanf("%d", &in.largura);
		fflush(stdin);
		gotoxy(33, i + 3); scanf("%d", &in.dec);
		i++;
		
		createNewField(arq, in.nome, toupper(in.tipo), in.largura, in.dec);
		
		printf("  %d  ", i);
		fflush(stdin);
		gets(in.nome);
	}
	system("cls");
	DesenhaBorda();
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
	int u = 2;
	if(arq != NULL)
	{
		Campos *aux = arq->cmps;
		char info[50];
		
		if(aux != NULL) //Exibicao das Fields
		{
			DesenhaBorda();
			while(aux != NULL)
			{
				gotoxy(u, 2); printf("%s\n", aux->fieldName);
				aux = aux->prox;
				u = u + 15;
			}
			aux = arq->cmps;
			createNewStatus(arq);
		}

		u = 2;
		while(aux != NULL)
		{
			fflush(stdin);
			gotoxy(u, 3); gets(info);
			u = u + 15;
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
	DesenhaBorda();
	
	int i = 0, x = 15, y = 3, u = 3;
	Status *posStts = arq->stts;
	Campos *auxCmps = arq->cmps;
	pDados *auxP;
	
	gotoxy(u, 2); printf("Record#			");
	u = u + 15;
	while (auxCmps != NULL)
	{
		gotoxy(u, 2);printf("%s			", auxCmps->fieldName); 
		auxCmps = auxCmps->prox;
		u = u + 15;
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
		y = 3;
		x = x + 15;
		auxCmps = auxCmps->prox;
	}

	auxP =  arq->cmps->p_dados;
	posStts = arq->stts;
	y = 3;
	while(posStts != NULL){
		if(setdel_onoff || posStts->status)
		{
			gotoxy(5, y++); printf(" %d ", i+1);
		}
		i++;
		posStts = posStts->prox;
	}
	gotoxy(25, 21); printf("press any key to continue");
	getch();
	
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
		
		
		//J� verificando se Field exisite
		while (!flag && auxCmps != NULL)
		{
			if(!stricmp(auxCmps->fieldName, field))
				flag = 1;
			else
				auxCmps = auxCmps->prox;
		}
		//J� verificando se Field exisite
				
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
		gotoxy(25, 21); printf("%d record deleted", i+1);
	}else{
		gotoxy(25, 21); printf("does not exist");
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
		gotoxy(25, 21); printf("%d record recalled", i+1);
	}else{
		gotoxy(25, 21); printf("does not exist");
	}
}
