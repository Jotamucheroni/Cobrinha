#include "headers/tela.h"

void clrscr()
{
	printf("\e[f\e[2J\e[3J");
}

int gotoxy(int x,int y)
{
	if(x < 1 || y < 1)
		return -1;
    printf("\e[%d;%df", y, x);
    
    return 0;
}

int determina_cor(alvo opcao, padrao pd, cor atrb)
{
	unsigned char param;
	if(opcao < TEXTO || opcao > FUNDO || pd < _16CORES || pd > RGB)
		return -1;
	if(pd == _16CORES)
	{
		if(atrb._16CORES.nome < PRETO || atrb._16CORES.nome > BRANCO || atrb._16CORES.mod < NORMAL || atrb._16CORES.mod > BRILHANTE)
			return -1;
		param = atrb._16CORES.nome;
		if(atrb._16CORES.mod == BRILHANTE)
			param += 60;
	}
	else
		param = 38;
	if(opcao == FUNDO)
		param += 10;
	switch(pd)
	{
		case _16CORES:
			printf("\e[%dm", param);
		break;
		
		case _8BIT:
			printf("\e[%d;5;%dm", param, atrb._8BIT);
		break;
		
		case RGB:
			printf("\e[%d;2;%d;%d;%dm", param, atrb.RGB.r, atrb.RGB.g, atrb.RGB.b);
	}
	
	return 0;
}

int formata_texto(atributo atrb, estado opcao)
{
	int param;
	
	if(atrb < NEGRITO || atrb > RISCADO || opcao < ATIVADO || opcao > DESATIVADO)
		return -1;
	param = atrb;
	if(opcao == DESATIVADO)
		param += 20;
	printf("\e[%dm", param);
	
	return 0;
}

int volta_padrao(componente opcao)
{
	if(opcao < COR_TEXTO || opcao > TUDO)
		return -1;
	if(opcao == TUDO)
		printf("\e[0m");
	else
	{
		if(opcao == COR_TEXTO || opcao == TEXTO_E_FUNDO || opcao == TEXTO_E_FORMATACAO)
			printf("\e[39m");
		if(opcao == COR_FUNDO || opcao == TEXTO_E_FUNDO || opcao == FUNDO_E_FORMATACAO)
			printf("\e[49m");
		if(opcao == FORMATACAO || opcao == TEXTO_E_FORMATACAO ||  opcao == FUNDO_E_FORMATACAO)
			printf("\e[21;22;23;24;27;28;29m");
	}
	
	return 0;	
}

void testa_cores()
{
    cor cor_teste;
	int i;
	
	volta_padrao(TUDO);
	clrscr();
	
	//16 Cores----------------------------------------------------------
	printf("Padrão 16 Cores:\n");
	cor_teste._16CORES.mod = NORMAL;
	for(i = PRETO; i <= BRANCO; i++)
	{
		cor_teste._16CORES.nome = i;
		determina_cor(TEXTO, _16CORES, cor_teste);
		printf("aa");
	}
	cor_teste._16CORES.mod = BRILHANTE;
	for(i = PRETO; i <= BRANCO; i++)
	{
		cor_teste._16CORES.nome = i;
		determina_cor(TEXTO, _16CORES, cor_teste);
		printf("aa");
	}
	volta_padrao(TEXTO);
	printf("\n");
	cor_teste._16CORES.mod = NORMAL;
	for(i = PRETO; i <= BRANCO; i++)
	{
		cor_teste._16CORES.nome = i;
		determina_cor(FUNDO, _16CORES, cor_teste);
		printf("  ");
	}
	cor_teste._16CORES.mod = BRILHANTE;
	for(i = PRETO; i <= BRANCO; i++)
	{
		cor_teste._16CORES.nome = i;
		determina_cor(FUNDO, _16CORES, cor_teste);
		printf("  ");
	}
	volta_padrao(FUNDO);
	
	//8bit--------------------------------------------------------------
	printf("\n\nPadrão 8bit:\n");
	for(i = 0; i <= 255; i++)
	{
		cor_teste._8BIT = i;
		determina_cor(TEXTO, _8BIT, cor_teste);
		printf("aa");
	}
	volta_padrao(COR_TEXTO);
	printf("\n");
	for(i = 0; i <= 255; i++)
	{
		cor_teste._8BIT = i;
		determina_cor(FUNDO, _8BIT, cor_teste);
		printf("  ");
	}
	volta_padrao(COR_FUNDO);
	
	//RGB---------------------------------------------------------------
	printf("\n\nPadrão RGB:\n");
	cor_teste.RGB.g = cor_teste.RGB.b = 0;
	for(i = 0; i <= 255; i++)
	{
		cor_teste.RGB.r = i;
		determina_cor(TEXTO, RGB, cor_teste);
		printf("aa");
	}
	printf("\n");
	cor_teste.RGB.r = cor_teste.RGB.b = 0;
	for(i = 0; i <= 255; i++)
	{
		cor_teste.RGB.g = i;
		determina_cor(TEXTO, RGB, cor_teste);
		printf("aa");
	}
	printf("\n");
	cor_teste.RGB.r = cor_teste.RGB.g = 0;
	for(i = 0; i <= 255; i++)
	{
		cor_teste.RGB.b = i;
		determina_cor(TEXTO, RGB, cor_teste);
		printf("aa");
	}
	printf("\n");
	for(i = 0; i <= 255; i++)
	{
		cor_teste.RGB.r = cor_teste.RGB.g = cor_teste.RGB.b = i;
		determina_cor(TEXTO, RGB, cor_teste);
		printf("aa");
	}
	volta_padrao(COR_TEXTO);
	cor_teste.RGB.g = cor_teste.RGB.b = 0;
	for(i = 0; i <= 255; i++)
	{
		cor_teste.RGB.r = i;
		determina_cor(FUNDO, RGB, cor_teste);
		printf("  ");
	}
	printf("\n");
	cor_teste.RGB.r = cor_teste.RGB.b = 0;
	for(i = 0; i <= 255; i++)
	{
		cor_teste.RGB.g = i;
		determina_cor(FUNDO, RGB, cor_teste);
		printf("  ");
	}
	printf("\n");
	cor_teste.RGB.r = cor_teste.RGB.g = 0;
	for(i = 0; i <= 255; i++)
	{
		cor_teste.RGB.b = i;
		determina_cor(FUNDO, RGB, cor_teste);
		printf("  ");
	}
	printf("\n");
	for(i = 0; i <= 255; i++)
	{
		cor_teste.RGB.r = cor_teste.RGB.g = cor_teste.RGB.b = i;
		determina_cor(FUNDO, RGB, cor_teste);
		printf("  ");
	}
	volta_padrao(COR_FUNDO);
}

int insere_texto(ponto inicio, int largura, int altura, char texto[])
{
	int i;
	ponto final, atual;
	
	if(largura < 1 || altura < 1 || texto[0] == '\0')
		return -1;
	
	atual = inicio;
	gotoxy(atual.x, atual.y);
	final.x = inicio.x + largura - 1;
	final.y = inicio.y + altura - 1;
	
	for(i = 0; texto[i] != '\0'; i++)
	{
		putchar(texto[i]);
		if(atual.x == final.x)
		{
			if(atual.y == final.y)
			{
				if(texto[i+1] == '\0')
					return 0;
				return 1;
			}
			atual.x = inicio.x;
			atual.y++;
			gotoxy(atual.x, atual.y);	
		}
		else
			atual.x++;
	}
	
	return 0;
}
