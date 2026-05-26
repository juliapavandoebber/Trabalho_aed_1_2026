
#ifndef MUSICA_H
#define MUSICA_H
#define ARQUIVO_MUSICA "musica.bin"

// Cabeçalho do arquivo binário de músicas
typedef struct {
    long cabeca; // Posição (RRN ou byte) da primeira música da lista
    long topo;   // Primeira posição livre no fim do arquivo
} CabecalhoMusica;

typedef struct {
    int codigo;
    char titulo[44];
    char artista[51];
    int ano;

    long prox;
} Musica;


Seu arquivo atual está com um conflito grave de merge (visível pelas marcações <<<<<<< HEAD e =======). Além disso, ele está misturando códigos de um sistema antigo de Livros/Biblioteca com o sistema atual de Músicas.Para o trabalho de AED da UNIOESTE , você deve remover completamente as menções a "Livro" e separar as funções de forma modular nos três arquivos .h que definimos. Cada arquivo .h deve conter apenas as funções que gerenciam diretamente a sua respectiva estrutura.  Abaixo está a divisão exata de onde cada função adaptada deve ficar:1. No arquivo musica.hEste arquivo conterá a struct da música e do seu cabeçalho, além de todas as funções responsáveis por gerenciar o Acervo Geral (inserção, leitura, listagem e busca de músicas no arquivo binário).  C#ifndef MUSICA_H
#define MUSICA_H

#include <stdio.h>

// Estruturas
typedef struct {
    long cabeca;
    long topo;
} CabecalhoMusica;

typedef struct {
    int codigo;
    char titulo[50];
    char artista[51];
    int ano;
    long prox;
} Musica;


// Abre o arquivo de músicas de acordo com o modo desejado
FILE* abrir_arquivo_musica(const char* modo);

// Verifica se já foi iniciado/criado o arquivo binário de músicas
void iniciar_musicas();

// Escreve o cabeçalho no arquivo de músicas
void escreve_cabecalho_musica(FILE* f_musicas, CabecalhoMusica* cab);

// Lê o cabeçalho do arquivo de músicas
CabecalhoMusica* le_cabecalho_musica();

// Escreve um nó de música em uma determinada posição do arquivo
void escreve_no_musica(FILE* f_musicas, Musica* x, long pos);

// Lê um nó de música em uma determinada posição do arquivo
Musica* le_no_musica(long pos);

// Interface via menu: Cadastra dados de uma música digitada pelo usuário
void cadastrarMusica();

// Adiciona uma música lida do arquivo de texto (Lote/Carregar arquivo)
void adicionarMusicaComRegistro(Musica* novo);

// Verifica se o código já pertence a uma música cadastrada
int verifica_cod_musica(int codigo);

// Dado um código, imprime os dados da respectiva música
void imprimirMusica(int codigo);

// Imprime todos os dados de todas as músicas do acervo geral
void listarmusicas();

// Busca e imprime dados da música pelo título
void buscarMusicaPorTitulo(const char *tituloBuscado);

// Conta e retorna a quantidade total de músicas no acervo
int contarTotalmusicas();


#endif //musica_h

