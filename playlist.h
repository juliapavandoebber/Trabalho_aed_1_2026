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

/**
 * @brief Abre o arquivo binário de controle de playlists no modo especificado.
 * @pre 'modo' deve ser uma string válida de modo de abertura de arquivo (ex: "rb", "wb+", "rb+").
 * @pos Retorna o ponteiro FILE* correspondente ao arquivo aberto, ou NULL em caso de erro.
 */
FILE* abrir_arquivo_playlist(const char* modo);

/**
 * @brief Garante a existência do arquivo binário de playlists na inicialização do sistema.
 * @pre Nenhuma.
 * @pos Cria o arquivo físico de playlists caso inexistente, gravando o cabeçalho de controle inicial (cabeca = -1, topo = tamanho do cabeçalho)[cite: 109].
 */
void iniciar_playlists();

#endif