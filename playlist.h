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

/**
 * @brief Abre o arquivo binário de controle de playlists no modo especificado.
 * Propósito: Encapsular a abertura do arquivo físico de playlists.
 * @pre 'modo' deve ser uma string válida de modo de abertura de arquivo (ex: "rb", "rb+").
 * @pos Retorna o ponteiro FILE* correspondente ao arquivo aberto, ou NULL em caso de erro.
 */
FILE* abrir_arquivo_playlist(const char* modo);

/**
 * @brief Inicializa o arquivo de playlists com uma estrutura de controle vazia.
 * Propósito: Gravar o cabeçalho inicial configurando a lista como vazia e definindo o topo físico.
 * @pre O arquivo de playlists deve estar aberto para leitura/escrita e posicionado no início (byte 0).
 * @pos O arquivo é inicializado com um cabeçalho contendo cabeca = -1 e topo = sizeof(CabecalhoPlaylist).
 */
void criar_lista_vazia_playlist(FILE* f_play);

/**
 * @brief Escreve ou atualiza o registro de cabeçalho no início do arquivo binário de playlists.
 * Propósito: Mover o ponteiro do arquivo para o byte 0 e salvar as informações de controle (cabeca e topo).
 * @pre O arquivo de playlists deve estar aberto em um modo que permita escrita ("rb+" ou "wb+").
 * @pos O cabeçalho é gravado com sucesso no início do arquivo de playlists.
 */
void escreve_cabecalho_playlist(FILE* f_play, const CabecalhoPlaylist* cab);

/**
 * @brief Garante a existência do arquivo binário de playlists na inicialização do sistema.
 * Propósito: Criar o arquivo de playlists caso não exista, chamando a inicialização do cabeçalho limpo.
 * @pre Nenhuma.
 * @pos O arquivo físico existirá em disco e conterá um cabeçalho inicial estruturado.
 */
void iniciar_playlists();

/**
 * @brief Cria uma nova playlist no arquivo binário.
 * Propósito: Instancia uma estrutura de playlist e a insere no final da lista encadeada global de playlists.
 * @pre O arquivo binário de playlists deve estar aberto em modo "rb+". O código fornecido deve ser único.
 * @pos A nova playlist é gravada no arquivo e os ponteiros de controle no cabeçalho são atualizados em disco.
 */
int criar_playlist(FILE *f_play, int codigo, const char *titulo);

/**
 * @brief Imprime o código e o título de todas as playlists cadastradas.
 * Propósito: Percorrer de forma encadeada o arquivo de playlists imprimindo sequencialmente os dados na tela.
 * @pre O arquivo de playlists deve estar aberto em modo de leitura ("rb").
 * @pos A lista com o identificador e título de todas as playlists é gerada no terminal.
 */
void imprimir_lista_playlists(FILE *f_play);

/**
 * @brief Imprime detalhadamente as músicas pertencentes a uma playlist.
 * Propósito: Localizar a playlist, caminhar pela sua lista encadeada de faixas e buscar no acervo os títulos/artistas.
 * @pre Os arquivos de playlists ("rb"), faixas ("rb") e músicas ("rb") devem estar abertos.
 * @pos Imprime o título da playlist seguido de todas as suas músicas na ordem correta de inserção.
 */
void imprimir_playlist_especifica(FILE *f_play, FILE *arq_faixas, FILE *arq_musicas, int codigo_playlist);

/**
 * @brief Busca interna para localizar uma playlist pelo código e capturar sua posição física.
 * Propósito: Obter os dados da playlist e seu offset em bytes para possibilitar atualizações de ponteiros de faixas.
 * @pre O arquivo binário de playlists deve estar aberto.
 * @pos Retorna 1 se encontrada (preenchendo 'saida' e 'pos_offset'), ou retorna 0 caso contrário.
 */
int buscar_playlist_por_codigo(FILE *f_play, int codigo_playlist, Playlist *saida, long *pos_offset);

/**
 * @brief Atualiza os dados de uma playlist existente em uma posição específica do arquivo.
 * Propósito: Sobrescrever um registro de playlist em disco após alterações lógicas de ponteiros de faixas.
 * @pre O arquivo binário de playlists deve estar aberto em modo "rb+". 'pos_offset' deve ser um deslocamento válido.
 * @pos O registro da playlist é atualizado no arquivo físico com as novas informações.
 */
void atualizar_playlist(FILE *f_play, long pos_offset, const Playlist *playlist_atualizada);

#endif // PLAYLIST_H