#ifndef MUSICA_H
#define MUSICA_H

#define ARQUIVO_MUSICA "musica.bin"
#include <stdio.h>

// Cabeçalho do arquivo binário de músicas
typedef struct {
    long cabeca; // Posição da primeira música do acervo
    long topo;   // Primeira posição livre no final do arquivo
} CabecalhoMusica;

typedef struct {
    int codigo;
    char titulo[100];
    char artista[51];
    int ano;                    
    long prox;                  
} Musica;

// Abre o arquivo de musicas de acordo com o modo desejado
// pre-condicao: uma string que representa um modo de abertura de arquivo valido (ex: "rb", "wb+", "rb+")
// pos-condicao: retorna o arquivo aberto no modo desejado
FILE* abrir_arquivo_musica(const char* modo);

// cria uma lista nova no arquivo de musicas
// pre-condicao: arquivo aberto para leitura/escrita
// pos-condicao: arquivo eh inicializado com uma lista vazia
void criar_lista_vazia_musica(FILE* f_musica);

// verifica se ja foi iniciado/criado o arquivo binario de musicas
// pre-condicao: nenhuma
// pos-condicao: criacao do arquivo .bin caso ele ainda nao exista
void iniciar_musicas();

// Cadastra uma nova música no arquivo binário do acervo geral
// pre-condicao: arquivo aberto em modo de leitura/escrita ("rb+") e o codigo fornecido nao deve existir previamente no acervo
// pos-condicao: a musica eh gravada no final do arquivo (topo) e inserida na lista encadeada, atualizando o cabecalho em disco
void cadastrar_musica(FILE *f_musica, int codigo, const char *titulo, const char *artista, int ano);

// Busca e imprime os dados de uma música específica no acervo seguindo a lista encadeada
// pre-condicao: arquivo aberto para leitura
// pos-condicao: os dados da musica sao exibidos no terminal ou exibe uma mensagem de erro caso nao seja encontrada
void imprimir_dados_musica(FILE *f_musica, int codigo);

// Lista todas as músicas presentes no acervo geral percorrendo a lista a partir da cabeca
// pre-condicao: arquivo aberto para leitura
// pos-condicao: exibe a listagem de todas as musicas ativas do acervo no terminal
void listar_acervo(FILE *f_musica);

// Localiza uma música pelo código e copia seus dados para uma estrutura em memória
// pre-condicao: arquivo aberto para leitura e ponteiro 'saida' valido
// pos-condicao: retorna 1 se a musica for encontrada e preenche o ponteiro 'saida', ou retorna 0 caso contrario
int buscar_musica_por_codigo(FILE *f_musica, int codigo, Musica *saida);

#endif // MUSICA_H