#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <stdio.h>

#define ARQUIVO_PLAYLIST "playlist.bin"
#define MAX_TITULO_PLAYLIST 51 // Máximo de 50 caracteres + '\0' 

// Estrutura de cabeçalho do arquivo de playlists (no início do arquivo) [cite: 109]
typedef struct {
    long cabeca; // Posição (byte) da primeira playlist do sistema [cite: 109]
    long topo;   // Primeira posição livre (fim do arquivo) para novas playlists [cite: 109]
} CabecalhoPlaylist;

// Estrutura do registro de Playlist [cite: 15]
typedef struct {
    int codigo;         // Identificador único da playlist [cite: 16]
    char titulo[MAX_TITULO_PLAYLIST]; // Título da playlist 
    long id_faixa_ini;  // Posição (cabeça) da lista encadeada de faixas neste arquivo [cite: 18]
    long id_faixa_fim;  // Posição (fim) da lista encadeada de faixas neste arquivo [cite: 19]
    long prox;          // Endereço (posição) da próxima playlist no arquivo [cite: 19]
} Playlist;

/**
 *  Abre o arquivo binário de controle de playlists no modo especificado.
 * Propósito: Encapsular a abertura do arquivo físico de playlists.
 * Pré-condições: 'modo' deve ser uma string válida de modo de abertura de arquivo (ex: "rb", "rb+").
 * Pós-condições: Retorna o ponteiro FILE* correspondente ao arquivo aberto, ou NULL em caso de erro.
 */
FILE* abrir_arquivo_playlist(const char* modo);

/**
 *  Garante a existência do arquivo binário de playlists na inicialização do sistema.
 * Propósito: Verificar a presença do arquivo e criar a estrutura inicial se necessário.
 * Pré-condições: Nenhuma.
 * Pós-condições: Cria o arquivo físico de playlists caso inexistente, gravando o cabeçalho de controle inicial (cabeca = -1, topo = tamanho do cabeçalho)[cite: 109].
 */
void iniciar_playlists();

/**
 *  Cria uma nova playlist no arquivo binário.
 * Propósito: Instancia uma estrutura de playlist com os ponteiros de faixa inicializados como vazios (-1) 
 * e a insere no final ou ordenadamente na lista de playlists.
 * Pré-condições: O arquivo binário de playlists deve estar aberto em modo "rb+". O código de playlist fornecido deve ser único.
 * Pós-condições: A nova playlist é persistida no arquivo e o cabeçalho é atualizado.
 */
int criar_playlist(FILE *arq_play, int codigo, const char *titulo);

/**
 *  Imprime o código e o título de todas as playlists cadastradas[cite: 31].
 * Propósito: Percorre de forma encadeada o arquivo de playlists exibindo seus dados básicos identificadores[cite: 31].
 * Pré-condições: O arquivo de playlists deve estar aberto em modo "rb".
 * Pós-condições: A lista resumida (código e título) de todas as playlists criadas é impressa na tela[cite: 31].
 */
void imprimir_lista_playlists(FILE *arq_play);

/**
 *  Imprime as músicas de uma playlist detalhadamente[cite: 30].
 * Propósito: Localiza a playlist informada, acessa o arquivo de faixas a partir de 'id_faixa_ini' 
 * e, para cada faixa, recupera o nome da música e artista no arquivo de músicas[cite: 30].
 * Pré-condições: Os arquivos de playlists ("rb"), faixas ("rb") e músicas ("rb") devem estar abertos.
 * Pós-condições: Imprime o título da playlist seguido pelos títulos e artistas das músicas associadas, na ordem correta[cite: 30].
 */
void imprimir_playlist_especifica(FILE *arq_play, FILE *arq_faixas, FILE *arq_musicas, int codigo_playlist);

/**
 *  Busca interna para localizar uma playlist pelo seu código e retornar sua posição em disco.
 * Propósito: Encontrar uma playlist para leitura ou futura modificação de seus ponteiros de faixas.
 * Pré-condições: O arquivo binário de playlists deve estar aberto.
 * Pós-condições: Retorna 1 se a playlist for encontrada, preenchendo a estrutura 'saida' e guardando em 'pos_offset' 
 * a posição física do registro no arquivo. Retorna 0 caso contrário.
 */
int buscar_playlist_por_codigo(FILE *arq_play, int codigo_playlist, Playlist *saida, long *pos_offset);

/**
 *  Atualiza os dados de uma playlist existente em uma posição específica do arquivo.
 * Propósito: Sobrescrever os dados de uma playlist (geralmente para atualizar id_faixa_ini ou id_faixa_fim).
 * Pré-condições: O arquivo binário de playlists deve estar aberto em modo "rb+". 'pos_offset' deve ser um deslocamento válido em bytes.
 * Pós-condições: O registro da playlist na posição indicada é atualizado com as novas informações em disco.
 */
void atualizar_playlist(FILE *arq_play, long pos_offset, const Playlist *playlist_atualizada);

#endif // PLAYLIST_H