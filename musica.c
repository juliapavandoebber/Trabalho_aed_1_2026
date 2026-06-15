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
void iniciar_musica(){
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
    cab.cabeca = NULO;
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

// Localiza uma música pelo código e copia seus dados para uma estrutura em memória
// pre-condicao: arquivo aberto para leitura e ponteiro 'saida' valido
// pos-condicao: retorna 1 se a musica for encontrada e preenche o ponteiro 'saida', ou retorna 0 caso contrario
int buscar_musica_por_codigo(FILE *f_musica, int codigo, Musica *saida){
    CabecalhoMusica cab = ler_cabecalho_musica(f_musica);
    long atual = cab.cabeca;

    while(atual != NULO){
        Musica m = ler_musica(f_musica, atual);

        if(m.codigo == codigo){
            *saida = m;
            return 1;
        }

        atual = m.prox;
    }

    return 0;
}

// Cadastra uma nova música no arquivo binário do acervo geral
// pre-condicao: arquivo aberto em modo de leitura/escrita ("rb+") e a musica fornecida deve possuir codigo unico
// pos-condicao: a musica eh gravada no final do arquivo (topo) e inserida na lista encadeada, atualizando o cabecalho em disco
void cadastrar_musica(FILE *f_musica, Musica m){
    Musica aux;

    if(buscar_musica_por_codigo(f_musica, m.codigo, &aux)){
        printf("Codigo ja cadastrado.\n");
        return;
    }

    CabecalhoMusica cab = ler_cabecalho_musica(f_musica);
    long pos = cab.topo;
    m.prox = cab.cabeca;
    escrever_musica(f_musica, pos, m);
    cab.cabeca = pos;
    cab.topo++;

    escrever_cabecalho_musica(f_musica, cab);
}

// Busca e imprime os dados de uma música específica no acervo seguindo a lista encadeada
// pre-condicao: arquivo aberto para leitura
// pos-condicao: os dados da musica sao exibidos no terminal ou exibe uma mensagem de erro caso nao seja encontrada
void imprimir_dados_musica(FILE *f_musica, int codigo){
    Musica m;

    if(buscar_musica_por_codigo(f_musica, codigo, &m)){
        printf("Codigo: %d\n", m.codigo);
        printf("Titulo: %s\n", m.titulo);
        printf("Artista: %s\n", m.artista);
        printf("Ano: %d\n", m.ano);
    }
    else{
        printf("Musica nao encontrada.\n");
    }
}

// Lista todas as músicas presentes no acervo geral percorrendo a lista a partir da cabeca
// pre-condicao: arquivo aberto para leitura
// pos-condicao: exibe a listagem de todas as musicas ativas do acervo no terminal
void listar_acervo(FILE *f_musica){
    CabecalhoMusica cab = ler_cabecalho_musica(f_musica);
    long atual = cab.cabeca;

    while(atual != NULO){
        Musica m = ler_musica(f_musica, atual);
        printf("Codigo: %d\n", m.codigo);
        printf("Titulo: %s\n", m.titulo);
        printf("Artista: %s\n", m.artista);
        printf("Ano: %d\n\n", m.ano);

        atual = m.prox;
    }
}
