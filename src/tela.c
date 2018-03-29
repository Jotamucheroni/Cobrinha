#include "headers/tela.h"

static int verifica_cor(cor atrb);

static int verifica_perfil(perfil pf);

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

int verifica_cor(cor atrb)
{
	if(atrb.pd < SISTEMA || atrb.pd > RGB || (atrb.pd == _16CORES &&  (atrb._16CORES.nome < PRETO || atrb._16CORES.nome > BRANCO || atrb._16CORES.mod < NORMAL || atrb._16CORES.mod > BRILHANTE) ) )
		return -1;
		
	return 0;
}

int verifica_perfil(perfil pf)
{
	if(verifica_cor(pf.cor_texto) == -1 || verifica_cor(pf.cor_fundo) == -1)
		return -1;
		
	return 0;
}

int determina_cor(alvo opcao, cor atrb)
{
	unsigned char param;
	
	if(opcao < TEXTO || opcao > FUNDO || verifica_cor(atrb) == -1)
		return -1;
		
	if(atrb.pd == SISTEMA)
		switch(opcao)
		{
			case TEXTO:
				volta_padrao(COR_TEXTO);
			break;
			
			case FUNDO:
				volta_padrao(COR_FUNDO);
		}
	else
	{
		if(atrb.pd == _16CORES)
		{
			param = atrb._16CORES.nome;
			if(atrb._16CORES.mod == BRILHANTE)
				param += 60;
		}
		else
			param = 38;
		if(opcao == FUNDO)
			param += 10;
		switch(atrb.pd)
		{
			case _16CORES:
				printf("\e[%dm", param);
			break;
			
			case _8BIT:
				printf("\e[%d;5;%dm", param, atrb._8BIT);
			break;
			
			case RGB:
				printf("\e[%d;2;%d;%d;%dm", param, atrb.RGB.r, atrb.RGB.g, atrb.RGB.b);
			break;
			
			default:
			break;
		}
	}
	
	return 0;
}

int formata_texto(atributo atrb, estado opcao)
{
	int param;
	
	if(atrb < NEGRITO || atrb > RISCADO || opcao < DESATIVADO || opcao > ATIVADO)
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

int configura_perfil(perfil pf)
{
	if(verifica_perfil(pf) == -1)
		return -1;
	
	determina_cor(TEXTO, pf.cor_texto);
	determina_cor(FUNDO, pf.cor_fundo);
	
	/* Utilizando as sequências de escape ANSI, não é possível desabilitar
	 * apenas o negrito ou apenas o fraco, volta-se sempre para a intensidade
	 * normal de cor. Por isso, caso apenas um deva ser desativado, desativa-se
	 * ambos e em seguida ativasse o outro. 
	 */
	if(pf.negrito ^ pf.fraco)
	{
		formata_texto(FRACO, DESATIVADO);
		formata_texto(pf.negrito ? NEGRITO : FRACO, ATIVADO);
	}
	else
	{
		formata_texto(NEGRITO, pf.negrito);
		formata_texto(FRACO, pf.fraco);
	}
	formata_texto(ITALICO, pf.italico);
	formata_texto(SUBLINHADO, pf.sublinhado);
	formata_texto(VIDEO_INVERTIDO, pf.video_invertido);
	formata_texto(INVISIVEL, pf.invisivel);
	formata_texto(RISCADO, pf.riscado);
	
	return 0;
}

void inicializa_perfil(perfil* pf)
{
	pf->cor_texto.pd = pf->cor_fundo.pd = SISTEMA;
	pf->negrito = pf->fraco = pf->italico = pf->sublinhado = pf->video_invertido = pf->invisivel = pf->riscado = DESATIVADO;
}

void testa_cores()
{
    cor cor_teste;
	int i;
	
	volta_padrao(TUDO);
	clrscr();
	
	//16 Cores----------------------------------------------------------
	printf("Padrão 16 Cores:\n");
	cor_teste.pd = _16CORES;
	cor_teste._16CORES.mod = NORMAL;
	for(i = PRETO; i <= BRANCO; i++)
	{
		cor_teste._16CORES.nome = i;
		determina_cor(TEXTO, cor_teste);
		printf("aa");
	}
	cor_teste._16CORES.mod = BRILHANTE;
	for(i = PRETO; i <= BRANCO; i++)
	{
		cor_teste._16CORES.nome = i;
		determina_cor(TEXTO, cor_teste);
		printf("aa");
	}
	volta_padrao(TEXTO);
	printf("\n");
	cor_teste._16CORES.mod = NORMAL;
	for(i = PRETO; i <= BRANCO; i++)
	{
		cor_teste._16CORES.nome = i;
		determina_cor(FUNDO, cor_teste);
		printf("  ");
	}
	cor_teste._16CORES.mod = BRILHANTE;
	for(i = PRETO; i <= BRANCO; i++)
	{
		cor_teste._16CORES.nome = i;
		determina_cor(FUNDO, cor_teste);
		printf("  ");
	}
	volta_padrao(FUNDO);
	
	//8bit--------------------------------------------------------------
	printf("\n\nPadrão 8bit:\n");
	cor_teste.pd = _8BIT;
	for(i = 0; i <= 255; i++)
	{
		cor_teste._8BIT = i;
		determina_cor(TEXTO, cor_teste);
		printf("aa");
	}
	volta_padrao(COR_TEXTO);
	printf("\n");
	for(i = 0; i <= 255; i++)
	{
		cor_teste._8BIT = i;
		determina_cor(FUNDO, cor_teste);
		printf("  ");
	}
	volta_padrao(COR_FUNDO);
	
	//RGB---------------------------------------------------------------
	printf("\n\nPadrão RGB:\n");
	cor_teste.pd = RGB;
	cor_teste.RGB.g = cor_teste.RGB.b = 0;
	for(i = 0; i <= 255; i++)
	{
		cor_teste.RGB.r = i;
		determina_cor(TEXTO, cor_teste);
		printf("aa");
	}
	printf("\n");
	cor_teste.RGB.r = cor_teste.RGB.b = 0;
	for(i = 0; i <= 255; i++)
	{
		cor_teste.RGB.g = i;
		determina_cor(TEXTO, cor_teste);
		printf("aa");
	}
	printf("\n");
	cor_teste.RGB.r = cor_teste.RGB.g = 0;
	for(i = 0; i <= 255; i++)
	{
		cor_teste.RGB.b = i;
		determina_cor(TEXTO, cor_teste);
		printf("aa");
	}
	printf("\n");
	for(i = 0; i <= 255; i++)
	{
		cor_teste.RGB.r = cor_teste.RGB.g = cor_teste.RGB.b = i;
		determina_cor(TEXTO, cor_teste);
		printf("aa");
	}
	volta_padrao(COR_TEXTO);
	cor_teste.RGB.g = cor_teste.RGB.b = 0;
	for(i = 0; i <= 255; i++)
	{
		cor_teste.RGB.r = i;
		determina_cor(FUNDO, cor_teste);
		printf("  ");
	}
	printf("\n");
	cor_teste.RGB.r = cor_teste.RGB.b = 0;
	for(i = 0; i <= 255; i++)
	{
		cor_teste.RGB.g = i;
		determina_cor(FUNDO, cor_teste);
		printf("  ");
	}
	printf("\n");
	cor_teste.RGB.r = cor_teste.RGB.g = 0;
	for(i = 0; i <= 255; i++)
	{
		cor_teste.RGB.b = i;
		determina_cor(FUNDO, cor_teste);
		printf("  ");
	}
	printf("\n");
	for(i = 0; i <= 255; i++)
	{
		cor_teste.RGB.r = cor_teste.RGB.g = cor_teste.RGB.b = i;
		determina_cor(FUNDO, cor_teste);
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
