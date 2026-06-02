#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "musica.h"

//Abre o arquivo de musicas de acordo com o modo desejado
//pre-condicao: uma string que representa um modo de abertura de arquivo valido (ex: "rb", "wb+", "ab+")
//pos-condicao: retorna o arquivo aberto no modo desejado
FILE* abrir_arquivo_musica(const char* modo){
    FILE* f = fopen(ARQUIVO_MUSICA, modo);

    if(f == NULL){
        perror("Erro ao abrir o arquivo de musicas");
        exit(1);
    }

    return f;
}

//verifica se ja foi iniciado/criado o arquivo binario de musicas
//pre-condicao: nenhuma
//pos-condicao: criacao do arquivo .bin caso ele ainda nao exista
void iniciar_musicas(){
    FILE* f_musica = fopen(ARQUIVO_MUSICA, "rb+");
    if(f_musica == NULL){
        printf("Arquivo musica nao encontrado. Criando um novo...\n");
        f_musica = fopen(ARQUIVO_MUSICA, "wb+");
        if(f_musica == NULL){
            perror("Erro fatal: Nao foi possivel abrir/criar arquivo musica");
            exit(1);
        }
        criar_lista_vazia_musica(f_musica);
    }
    fclose(f_musica);
}

// cria uma lista nova no arquivo de musicas
// pre-condicao: arquivo aberto para leitura/escrita
// pos-condicao: arquivo eh inicializado com uma lista vazia
void criar_lista_vazia_musica(FILE* f_musica){
    CabecalhoMusica cab;
    cab.cabeca = -1;
    cab.topo = 0;

    fseek(f_musica, 0, SEEK_SET);
    fwrite(&cab, sizeof(CabecalhoMusica), 1, f_musica);
}

//Lê o cabeçalho do arquivo de músicas 
//pre-condicao: arquivo aberto para leitura
//pos-condicao: retorna uma copia do cabecalho armazenado no inicio do arquivo
CabecalhoMusica ler_cabecalho_musica(FILE *f_musica){
    CabecalhoMusica cab;

    fseek(f_musica, 0, SEEK_SET);
    fread(&cab, sizeof(CabecalhoMusica), 1, f_musica);

    return cab;
}

//Escreve o cabeçalho do arquivo de músicas 
//pre-condicao: arquivo aberto para escrita
//pos-condicao: o cabecalho armazenado no arquivo eh atualizado
void escrever_cabecalho_musica(FILE *f_musica, CabecalhoMusica cab){
    fseek(f_musica, 0, SEEK_SET);
    fwrite(&cab, sizeof(CabecalhoMusica), 1, f_musica);
}

//Lê uma música em uma posição específica do arquivo
//pre-condicao: arquivo aberto para escrita e posicao valida
//pos-condicao: a musica eh gravada na posicao informada
Musica ler_musica(FILE *f_musica, long pos){
    Musica m;

    fseek(
        f_musica,
        sizeof(CabecalhoMusica) + pos * sizeof(Musica),
        SEEK_SET
    );

    fread(&m, sizeof(Musica), 1, f_musica);

    return m;
}

//Escreve uma música em uma posição específica do arquivo
//pre-condicao: arquivo aberto para escrita e posicao valida
//pos-condicao: a musica eh gravada na posicao informada
void escrever_musica(FILE *f_musica, long pos, Musica m){
    fseek(
        f_musica, 
        sizeof(CabecalhoMusica) + pos * sizeof(Musica),
        SEEK_SET
    );

    fwrite(&m, sizeof(Musica), 1, f_musica);
}

void cadastrar_musica(FILE *f_musica, Musica m){

}
