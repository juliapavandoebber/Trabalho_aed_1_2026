#include <stdio.h>
#include <stdlib.h>
#include "faixa.h"

FILE* abrir_arquivo_faixas(const char* modo) {
    return fopen(ARQUIVO_FAIXA, modo);
}

void criar_lista_vazia_faixa(FILE* f_faixas) {
    CabecalhoFaixa cab;
    cab.topo = sizeof(CabecalhoFaixa); 
    cab.lista_livres = NULO;
    
    escrever_cabecalho_faixa(f_faixas, cab);
}

void iniciar_faixas() {
    FILE* f = abrir_arquivo_faixas("rb");
    if (f == NULL) {
        f = abrir_arquivo_faixas("wb+");
        if (f != NULL) {
            criar_lista_vazia_faixa(f);
            fclose(f);
        } else {
            printf("Erro ao criar o arquivo de faixas!\n");
        }
    } else {
        fclose(f);
    }
}

CabecalhoFaixa ler_cabecalho_faixa(FILE *f_faixas) {
    CabecalhoFaixa cab;
    fseek(f_faixas, 0, SEEK_SET);
    fread(&cab, sizeof(CabecalhoFaixa), 1, f_faixas);
    return cab;
}

void escrever_cabecalho_faixa(FILE *f_faixas, CabecalhoFaixa cab) {
    fseek(f_faixas, 0, SEEK_SET);
    fwrite(&cab, sizeof(CabecalhoFaixa), 1, f_faixas);
}

FaixaPlaylist ler_faixa(FILE *f_faixas, long pos) {
    FaixaPlaylist faixa;
    fseek(f_faixas, pos, SEEK_SET);
    fread(&faixa, sizeof(FaixaPlaylist), 1, f_faixas);
    return faixa;
}

void escrever_faixa(FILE *f_faixas, long pos, FaixaPlaylist faixa) {
    fseek(f_faixas, pos, SEEK_SET);
    fwrite(&faixa, sizeof(FaixaPlaylist), 1, f_faixas);
}

long alocar_faixa(FILE *f_faixas, int codigo_musica) {
    CabecalhoFaixa cab = ler_cabecalho_faixa(f_faixas);
    long pos_alocada;
    FaixaPlaylist nova_faixa;
    
    nova_faixa.codigo_musica = codigo_musica;
    nova_faixa.prox = NULO;

    if (cab.lista_livres != NULO) {
        pos_alocada = cab.lista_livres;
        
        FaixaPlaylist no_livre = ler_faixa(f_faixas, pos_alocada);
        
        cab.lista_livres = no_livre.prox;
    } else {
        pos_alocada = cab.topo;
        cab.topo += sizeof(FaixaPlaylist);
    }

    escrever_faixa(f_faixas, pos_alocada, nova_faixa);
    escrever_cabecalho_faixa(f_faixas, cab);
    
    return pos_alocada;
}

void liberar_faixa(FILE *f_faixas, long pos) {
    if (pos == NULO) return;

    CabecalhoFaixa cab = ler_cabecalho_faixa(f_faixas);
    FaixaPlaylist no_liberado = ler_faixa(f_faixas, pos);
    no_liberado.prox = cab.lista_livres;
    no_liberado.codigo_musica = NULO; 
    escrever_faixa(f_faixas, pos, no_liberado);
    cab.lista_livres = pos;
    escrever_cabecalho_faixa(f_faixas, cab);
}

void imprimir_nos_livres(FILE *f_faixas) {
    CabecalhoFaixa cab = ler_cabecalho_faixa(f_faixas);
    long atual = cab.lista_livres;
    
    printf("\n--- Lista de Nos Livres (Faixas) ---\n");
    if (atual == NULO) {
        printf("Nenhum espaco livre no arquivo no momento.\n");
        return;
    }
    
    while (atual != NULO) {
        printf("[Byte: %ld] -> ", atual);
        FaixaPlaylist no_livre = ler_faixa(f_faixas, atual);
        atual = no_livre.prox;
    }
    printf("NULO\n");
    printf("------------------------------------\n");
}