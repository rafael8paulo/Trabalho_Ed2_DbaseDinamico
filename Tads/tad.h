union dados
{
    float valorN;
    char valorD[10];
    char valorL;
    char valorC[50];
    char valorM[50];
};

struct ponteiroDados
{
    union dados valor;
    struct ponteiroDados *prox;
};
typedef struct ponteiroDados pDados;

struct campos{
	
    struct ponteiroDados *pAtual;
	
    char fieldName[20]; 
	char type; //Definir
    int width; //TL
	int dec;
    
	struct ponteiroDados *p_dados;
    
    struct campos *prox;
};
typedef struct campos Campos;

struct status {
    int status;
    struct status *prox;
};
typedef struct status Status;

struct arquivo {
	
    struct arquivo *ant;
    char nomeDBF[40];
    char data[9]; //Pegar data atual do sistema
	char hora[9];  //Pegar hora atual do sistema 
	
	struct status *stts;
	struct campos *cmps;
	
    struct arquivo *prox;
}; 
typedef struct arquivo Arq;

struct unidade{
	
	struct unidade *top;
    char letter; //Definir
    struct arquivo *arqs;
    struct unidade *bottom;
};
typedef struct unidade Dir;
