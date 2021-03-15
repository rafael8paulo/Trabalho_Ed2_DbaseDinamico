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