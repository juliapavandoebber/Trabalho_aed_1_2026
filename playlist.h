#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <stdio.h>

#define ARQUIVO_PLAYLIST "playlist.bin"
#define NULO -1

// Estrutura de cabeçalho do arquivo de playlists (no início do arquivo)
typedef struct {
    long cabeca; // Posição (byte) da primeira playlist do sistema
    long topo;   // Primeira posição livre (fim do arquivo) para novas playlists
} CabecalhoPlaylist;

// Estrutura do registro de Playlist
typedef struct {
    int codigo;                       // Identificador único da playlist
    char titulo[51];                  // Título da playlist (máximo 50 caracteres + '\0')
    long id_faixa_ini;                // Posição (byte) do primeiro nó de faixa desta playlist
    long id_faixa_fim;                // Posição (byte) do último nó de faixa desta playlist
    long prox;                        // Posição (byte) da próxima playlist no arquivo
} Playlist;

// Abre o arquivo binário de playlists no modo especificado
// pre-condicao: uma string que representa um modo de abertura de arquivo valido
// pos-condicao: retorna o arquivo aberto no modo desejado
FILE* abrir_arquivo_playlist(const char* modo);

// Cria uma lista vazia no arquivo de playlists
// pre-condicao: arquivo aberto para leitura/escrita
// pos-condicao: arquivo inicializado com cabecalho vazio
void criar_lista_vazia_playlist(FILE* f_play);

// Verifica se o arquivo de playlists existe e o inicializa caso necessario
// pre-condicao: nenhuma
// pos-condicao: arquivo binario criado e inicializado caso nao exista
void iniciar_playlists();

// Le o cabecalho do arquivo de playlists
// pre-condicao: arquivo aberto para leitura
// pos-condicao: retorna uma copia do cabecalho armazenado no arquivo
CabecalhoPlaylist ler_cabecalho_playlist(FILE *f_play);

// Escreve o cabecalho do arquivo de playlists
// pre-condicao: arquivo aberto para escrita
// pos-condicao: cabecalho atualizado no arquivo
void escrever_cabecalho_playlist(FILE *f_play, CabecalhoPlaylist cab);

// Le uma playlist de uma posicao especifica do arquivo
// pre-condicao: arquivo aberto para leitura e posicao valida
// pos-condicao: retorna a playlist armazenada na posicao informada
Playlist ler_playlist(FILE *f_play, long pos);

// Escreve uma playlist em uma posicao especifica do arquivo
// pre-condicao: arquivo aberto para escrita e posicao valida
// pos-condicao: playlist gravada na posicao informada
void escrever_playlist(FILE *f_play, long pos, Playlist p);

// Cria uma nova playlist no arquivo binário de playlists
// pre-condicao: arquivo aberto em modo leitura/escrita e codigo unico
// pos-condicao: playlist inserida na lista encadeada e cabecalho atualizado
int criar_playlist(FILE *f_play, int codigo, const char *titulo);

// Localiza uma playlist pelo codigo
// pre-condicao: arquivo aberto para leitura e ponteiros validos
// pos-condicao: retorna 1 se encontrada e preenche os parametros de saida, ou 0 caso contrario
int buscar_playlist_por_codigo(FILE *f_play, int codigo_playlist, Playlist *saida, long *pos_offset);

// Imprime todas as playlists cadastradas
// pre-condicao: arquivo aberto para leitura
// pos-condicao: exibe codigo e titulo de todas as playlists
void imprimir_lista_playlists(FILE *f_play);

// Imprime uma playlist especifica e suas musicas
// pre-condicao: arquivos abertos para leitura e playlist existente
// pos-condicao: exibe os dados da playlist e suas musicas
void imprimir_playlist_especifica(FILE *f_play, FILE *arq_faixas, FILE *arq_musicas, int codigo_playlist);

// Adiciona uma musica no inicio da playlist
// pre-condicao: arquivos abertos para leitura/escrita e entidades existentes
// pos-condicao: musica inserida no inicio da lista de faixas da playlist
void adicionar_na_playlist_inicio(FILE *f_play, FILE *f_faixas, FILE *f_musicas, int codigo_playlist, int codigo_musica);

// Adiciona uma musica no final da playlist
// pre-condicao: arquivos abertos para leitura/escrita e entidades existentes
// pos-condicao: musica inserida no final da lista de faixas da playlist
void adicionar_na_playlist_fim(FILE *f_play, FILE *f_faixas, FILE *f_musicas, int codigo_playlist, int codigo_musica);

// Remove uma musica da playlist
// pre-condicao: arquivos abertos para leitura/escrita e musica pertencente a playlist
// pos-condicao: musica removida da playlist e no enviado para lista de livres
void remover_da_playlist(FILE *f_playlist, FILE *f_faixa, int codigo_playlist, int codigo_musica);

#endif