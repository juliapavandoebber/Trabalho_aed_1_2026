#ifndef FAIXA_H
#define FAIXA_H

#include <stdio.h>

#define ARQUIVO_FAIXA "faixa.bin"

// Estrutura de cabeçalho do arquivo de faixas (no início do arquivo)
typedef struct {
    long topo;          // Primeira posição livre no fim do arquivo (EOF físico)
    long lista_livres;  // Posição (byte) da cabeça da lista de nós deletados/livres
} CabecalhoFaixa;

// Estrutura do registro de nó de faixa musical
typedef struct {
    int codigo_musica;  // Código da música correspondente no acervo geral
    long prox;          // Posição (byte) da próxima faixa pertencente a esta playlist
} FaixaPlaylist;

// Abre o arquivo binário responsável por armazenar os nós de faixas das playlists
// pre-condicao: uma string que representa um modo de abertura de arquivo valido (ex: "rb", "wb+", "rb+")
// pos-condicao: retorna o arquivo aberto no modo desejado
FILE* abrir_arquivo_faixas(const char* modo);

// cria uma lista nova no arquivo de faixas
// pre-condicao: arquivo aberto para leitura/escrita
// pos-condicao: arquivo eh inicializado com um cabecalho contendo lista_livres = -1 e topo = tamanho do cabecalho
void criar_lista_vazia_faixa(FILE* f_faixas);

// verifica se ja foi iniciado/criado o arquivo binario de faixas
// pre-condicao: nenhuma
// pos-condicao: criacao do arquivo .bin caso ele ainda nao exista, chamando a inicializacao do cabecalho limpo
void iniciar_faixas();

// Gerencia o espaço físico em disco retirando um nó da lista de livres ou expandindo o topo do arquivo
// pre-condicao: arquivo aberto em modo de leitura/escrita ("rb+")
// pos-condicao: grava uma nova struct com o codigo da musica, atualiza o cabecalho de faixas e retorna o offset do local alocado
long alocar_faixa(FILE *f_faixas, int codigo_musica);

// Adiciona uma música do acervo geral no início da lista de faixas de uma playlist específica
// pre-condicao: os arquivos de faixas, playlists e musicas devem estar abertos em modo de leitura/escrita ("rb+") e as entidades devem existir
// pos-condicao: aloca um no de faixa (reaproveitando ou criando no fim) e o conecta no inicio da playlist, atualizando os arquivos em disco
void adicionar_faixa_inicio(FILE *f_faixas, FILE *f_play, FILE *f_musicas, int codigo_playlist, int codigo_musica);

// Adiciona uma música do acervo geral no final da lista de faixas de uma playlist específica
// pre-condicao: os arquivos de faixas, playlists e musicas devem estar abertos em modo de leitura/escrita ("rb+") e as entidades devem existir
// pos-condicao: aloca um no de faixa (reaproveitando ou criando no fim) e o conecta no fim da playlist, atualizando os arquivos em disco
void adicionar_faixa_fim(FILE *f_faixas, FILE *f_play, FILE *f_musicas, int codigo_playlist, int codigo_musica);

// Remove uma música de uma playlist específica e move o nó físico para a lista de livres
// pre-condicao: os arquivos de faixas e playlists devem estar abertos em modo de leitura/escrita ("rb+") e a playlist deve conter a musica indicada
// pos-condicao: o no eh desconectado da playlist e seu endereco fisico (offset) eh inserido na pilha de nos livres para futuro reuso
int remover_faixa(FILE *f_faixas, FILE *f_play, int codigo_playlist, int codigo_musica);

// Imprime todas as posições físicas de registros atualmente livres no arquivo de faixas
// pre-condicao: arquivo aberto em modo de leitura ("rb")
// pos-condicao: percorre a lista encadeada a partir de lista_livres e exibe no terminal os offsets em bytes de todos os espacos disponiveis
void imprimir_nos_livres(FILE *f_faixas);

#endif // FAIXA_H