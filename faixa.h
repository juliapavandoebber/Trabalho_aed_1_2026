#ifndef FAIXA_H
#define FAIXA_H

#include <stdio.h>

#define ARQUIVO_FAIXA "faixa.bin"
#define NULO -1

typedef struct {
    long topo;          // Primeira posição livre no fim do arquivo
    long lista_livres;  // Posição da cabeça da lista de nós deletados/livres
} CabecalhoFaixa;

typedef struct {
    int codigo_musica;  // Código da música correspondente no acervo geral
    long prox;          // Posição da próxima faixa pertencente a esta playlist
} FaixaPlaylist;

// Abre o arquivo binário responsável por armazenar os nós de faixas das playlists
// pre-condicao: uma string que representa um modo de abertura de arquivo valido (ex: "rb", "wb+", "rb+")
// pos-condicao: retorna o arquivo aberto no modo desejado
FILE* abrir_arquivo_faixas(const char* modo);

// cria uma lista nova no arquivo de faixas
// pre-condicao: arquivo aberto para leitura/escrita
// pos-condicao: arquivo eh inicializado com um cabecalho contendo lista_livres = -1 e topo = 0
void criar_lista_vazia_faixa(FILE* f_faixas);

// verifica se ja foi iniciado/criado o arquivo binario de faixas
// pre-condicao: nenhuma
// pos-condicao: criacao do arquivo .bin caso ele ainda nao exista, chamando a inicializacao do cabecalho limpo
void iniciar_faixas();

// Lê o cabeçalho do arquivo de faixas
// pre-condicao: arquivo aberto para leitura
// pos-condicao: retorna uma copia do cabecalho armazenado no inicio do arquivo
CabecalhoFaixa ler_cabecalho_faixa(FILE *f_faixas);

// Escreve o cabeçalho do arquivo de faixas
// pre-condicao: arquivo aberto para escrita
// pos-condicao: o cabecalho armazenado no arquivo eh atualizado
void escrever_cabecalho_faixa(FILE *f_faixas, CabecalhoFaixa cab);

// Lê uma faixa em uma posição específica do arquivo
// pre-condicao: arquivo aberto para leitura e posicao valida
// pos-condicao: retorna a faixa armazenada na posicao informada
FaixaPlaylist ler_faixa(FILE *f_faixas, long pos);

// Escreve uma faixa em uma posição específica do arquivo
// pre-condicao: arquivo aberto para escrita e posicao valida
// pos-condicao: a faixa eh gravada na posicao informada
void escrever_faixa(FILE *f_faixas, long pos, FaixaPlaylist faixa);

// Gerencia o espaço físico em disco retirando um nó da lista de livres ou expandindo o topo do arquivo
// pre-condicao: arquivo aberto em modo de leitura/escrita ("rb+")
// pos-condicao: grava uma nova struct com o codigo da musica, atualiza o cabecalho de faixas e retorna a posicao alocada
long alocar_faixa(FILE *f_faixas, int codigo_musica);

// Libera uma faixa e a adiciona na lista de nós livres
// pre-condicao: arquivo aberto em modo de leitura/escrita ("rb+") e posicao valida
// pos-condicao: a faixa eh inserida na lista encadeada de nos livres e o cabecalho eh atualizado
void liberar_faixa(FILE *f_faixas, long pos);

// Imprime todas as posições físicas de registros atualmente livres no arquivo de faixas
// pre-condicao: arquivo aberto em modo de leitura ("rb")
// pos-condicao: percorre a lista encadeada a partir de lista_livres e exibe no terminal os offsets de todos os espacos disponiveis
void imprimir_nos_livres(FILE *f_faixas);

#endif // FAIXA_H