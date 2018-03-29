#ifndef TELA_H
#define TELA_H

#include <stdio.h>

typedef struct Ponto
{
	unsigned char x, y; 
} ponto;

typedef enum alvo {TEXTO, FUNDO} alvo;

typedef enum padrao {SISTEMA, _16CORES, _8BIT, RGB} padrao;

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

typedef struct cor
{
	union
	{
		_16Cores _16CORES;
		unsigned char _8BIT;
		rgb RGB;
	};
	padrao pd;
} cor;

typedef enum atributo {NEGRITO = 1, FRACO, ITALICO, SUBLINHADO, VIDEO_INVERTIDO = 7, INVISIVEL, RISCADO} atributo;

typedef enum estado {DESATIVADO = 0, ATIVADO} estado;

typedef struct perfil
{
	cor cor_texto, cor_fundo;
	estado negrito : 1, fraco : 1, italico : 1, sublinhado : 1, video_invertido : 1, invisivel : 1, riscado : 1;
} perfil;

typedef enum componente {COR_TEXTO, COR_FUNDO, FORMATACAO, TEXTO_E_FUNDO, TEXTO_E_FORMATACAO, FUNDO_E_FORMATACAO, TUDO} componente;

void clrscr();

int gotoxy(int x,int y);

int determina_cor(alvo opcao, cor atrb);

int formata_texto(atributo atrb, estado opcao);

int volta_padrao(componente opcao);

int configura_perfil(perfil pf);

void inicializa_perfil(perfil* pf);

void testa_cores(); 

int insere_texto(ponto inicio, int largura, int altura, char texto[]);

#endif
