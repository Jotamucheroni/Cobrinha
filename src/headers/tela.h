#include <stdio.h>

typedef struct Ponto
{
	unsigned char x,y; 
} ponto;

typedef enum alvo {TEXTO, FUNDO} alvo;

typedef enum padrao {_16CORES, _8BIT, RGB} padrao;

typedef struct rgb
{
	unsigned char r, g, b;
} rgb;

typedef enum nome_cor {PRETO = 30, VERMELHO, VERDE, AMARELO, AZUL, MAGENTA, CIANO, BRANCO} nome_cor;

typedef enum modificador {NORMAL, BRILHANTE} modificador;

typedef struct _16Cores
{
	nome_cor nome;
	modificador mod;
} _16Cores;

typedef union cor
{
	_16Cores _16CORES;
	unsigned char _8BIT;
	rgb RGB;
} cor;

typedef enum atributo {NEGRITO = 1, FRACO, ITALICO, SUBLINHADO, VIDEO_INVERTIDO = 7, INVISIVEL, RISCADO} atributo;

typedef enum estado {ATIVADO, DESATIVADO} estado;

typedef enum componente {COR_TEXTO, COR_FUNDO, FORMATACAO, TEXTO_E_FUNDO, TEXTO_E_FORMATACAO, FUNDO_E_FORMATACAO, TUDO} componente;

void clrscr();

int gotoxy(int x,int y);

int determina_cor(alvo opcao, padrao pd, cor atrb);

int formata_texto(atributo atrb, estado opcao);

int volta_padrao(componente opcao);

void testa_cores(); 

int insere_texto(ponto inicio, int largura, int altura, char texto[]);
