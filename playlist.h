#ifndef PLAYLIST_H
#define PLAYLIST_H

// Estrutura de cabeçalho do arquivo de playlists (no início do arquivo) 
typedef struct {
    long cabeca; // RRN ou byte da primeira playlist do sistema 
    long topo;   // Primeira posição livre (fim do arquivo) para novas playlists 
} CabecalhoPlaylist;

// Estrutura do registro de Playlist [cite: 15]
typedef struct {
    int codigo;         // Identificador único da playlist 
    char titulo[51];    // Título da playlist (máximo 50 caracteres + '\0') 
    long id_faixa_ini;  // Posição (cabeça) da lista encadeada de faixas neste arquivo 
    long id_faixa_fim;  // Posição (fim) da lista encadeada de faixas neste arquivo 
    long prox;          // Endereço (posição) da próxima playlist no arquivo 
} Playlist;

// Abre o arquivo de playlists
FILE* abrir_arquivo_playlist(const char* modo);

// Inicializa o arquivo de playlists criando um cabeçalho vazio se não existir
void iniciar_playlists();

// Escreve o cabeçalho no arquivo de playlists
void escreve_cabecalho_playlist(FILE* f_playlists, CabecalhoPlaylist* cab);

// Lê o cabeçalho do arquivo de playlists
CabecalhoPlaylist* le_cabecalho_playlist();

// Escreve uma playlist em uma posição específica do arquivo binário
void escreve_no_playlist(FILE* f_playlists, Playlist* p, long pos);

// Lê uma playlist de uma posição específica do arquivo binário
Playlist* le_no_playlist(long pos);

// Cria uma nova playlist no sistema (opção do menu e lote)
void criarPlaylist(int codigo, const char* titulo);

// Imprime a lista com o código e título de todas as playlists cadastradas
void listarPlaylists();

// Busca uma playlist pelo seu código e retorna a sua struct/posição
long buscarPlaylistPorCodigo(int codigo);

#endif