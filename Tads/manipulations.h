/*struct posicoes
{
	unsigned int y;
};
typedef struct posicoes Posicoes;
*/
struct field
{
	char nome[50];
	char tipo; 
	int largura;
	int dec;
};
typedef struct field Entradas;

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
void operations(){
	
}
