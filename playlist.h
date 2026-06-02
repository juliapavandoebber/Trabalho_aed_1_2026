#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <stdio.h>

#define ARQUIVO_PLAYLIST "playlist.bin"

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

// Abre o arquivo binário de controle de playlists no modo especificado
// pre-condicao: uma string que representa um modo de abertura de arquivo valido (ex: "rb", "wb+", "rb+")
// pos-condicao: retorna o arquivo aberto no modo desejado
FILE* abrir_arquivo_playlist(const char* modo);

// cria uma lista nova no arquivo de playlists
// pre-condicao: arquivo aberto para leitura/escrita
// pos-condicao: arquivo eh inicializado com uma lista vazia e cabecalho estruturado (cabeca = -1, topo = tamanho do cabecalho)
void criar_lista_vazia_playlist(FILE* f_play);

// verifica se ja foi iniciado/criado o arquivo binario de playlists
// pre-condicao: nenhuma
// pos-condicao: criacao do arquivo .bin caso ele ainda nao exista, chamando a inicializacao do cabecalho limpo
void iniciar_playlists();

// Cria uma nova playlist no arquivo binário de playlists
// pre-condicao: arquivo aberto em modo de leitura/escrita ("rb+") e o codigo fornecido deve ser unico
// pos-condicao: a nova playlist eh gravada no final do arquivo (topo) e inserida na lista encadeada global, atualizando o cabecalho em disco
int criar_playlist(FILE *f_play, int codigo, const char *titulo);

// Imprime o código e o título de todas as playlists cadastradas seguindo o encadeamento
// pre-condicao: arquivo aberto para leitura
// pos-condicao: exibe a listagem com o identificador e o titulo de todas as playlists no terminal
void imprimir_lista_playlists(FILE *f_play);

// Imprime detalhadamente o título e as músicas pertencentes a uma playlist específica
// pre-condicao: os arquivos de playlists, faixas e musicas devem estar abertos em modo de leitura
// pos-condicao: exibe os dados da playlist seguidos de todas as suas musicas na ordem correta de insercao
void imprimir_playlist_especifica(FILE *f_play, FILE *arq_faixas, FILE *arq_musicas, int codigo_playlist);

// Localiza uma playlist pelo código e captura seus dados e sua posição física no arquivo
// pre-condicao: arquivo aberto para leitura e ponteiro 'saida' valido
// pos-condicao: retorna 1 se encontrada preenchendo a estrutura 'saida' e o offset em 'pos_offset', ou retorna 0 caso contrario
int buscar_playlist_por_codigo(FILE *f_play, int codigo_playlist, Playlist *saida, long *pos_offset);

// Adiciona uma música do acervo geral no início da lista de faixas de uma playlist específica
// pre-condicao: os arquivos de playlists, faixas e musicas devem estar abertos em modo de leitura/escrita ("rb+") e as entidades devem existir
// pos-condicao: uma nova faixa eh alocada e conectada na cabeca da sublista da playlist informada, atualizando os ponteiros em disco
void adicionar_na_playlist_inicio(FILE *f_play, FILE *f_faixas, FILE *f_musicas, int codigo_playlist, int codigo_musica);

// Adiciona uma música do acervo geral no final da lista de faixas de uma playlist específica
// pre-condicao: os arquivos de playlists, faixas e musicas devem estar abertos em modo de leitura/escrita ("rb+") e as entidades devem existir
// pos-condicao: uma nova faixa eh alocada e conectada no fim da sublista da playlist informada, atualizando o ponteiro 'id_faixa_fim' em disco
void adicionar_na_playlist_fim(FILE *f_play, FILE *f_faixas, FILE *f_musicas, int codigo_playlist, int codigo_musica);

// Remove uma determinada música da lista de faixas de uma playlist específica
// pre-condicao: os arquivos de playlists e faixas devem estar abertos em modo de leitura/escrita ("rb+") e a playlist deve conter a musica indicada
// pos-condicao: o no da faixa eh desconectado da playlist e seu endereco eh enviado para a lista de nos livres do arquivo de faixas
void remover_da_playlist(FILE *f_playlist, FILE *f_faixa, int codigo_playlist, int codigo_musica);

#endif // PLAYLIST_H