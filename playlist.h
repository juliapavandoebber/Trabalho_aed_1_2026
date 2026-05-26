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
 *  Abre o arquivo binário de controle de playlists no modo especificado.
 * pre-condicao 'modo' deve ser uma string válida de modo de abertura de arquivo (ex: "rb", "wb+", "rb+").
 * pos-condicao Retorna o ponteiro FILE* correspondente ao arquivo aberto, ou NULL em caso de erro.
 */
FILE* abrir_arquivo_playlist(const char* modo);

/**
 *  Garante a existência do arquivo binário de playlists na inicialização do sistema.
 * pre-condicao Nenhuma.
 * pos-condicao Cria o arquivo físico de playlists caso inexistente, gravando o cabeçalho de controle inicial (cabeca = -1, topo = tamanho do cabeçalho)[cite: 109].
 */
void iniciar_playlists();

/**
 *  Escreve fisicamente o cabeçalho de controle no início do arquivo de playlists.
 * pre-condicao 'f_playlists' aberto para escrita e 'cab' apontando para dados válidos de CabecalhoPlaylist.
 * pos-condicao O cabeçalho contendo a indicação da cabeça da lista e o topo do arquivo é atualizado na posição 0[cite: 109].
 */
void escreve_cabecalho_playlist(FILE* f_playlists, CabecalhoPlaylist* cab);

/**
 *  Realiza a leitura do cabeçalho do arquivo binário de playlists.
 * pre-condicao O arquivo de playlists deve existir e estar acessível para leitura.
 * pos-condicao Retorna um ponteiro alocado com a estrutura do cabeçalho extraída do arquivo.
 */
CabecalhoPlaylist* le_cabecalho_playlist();

/**
 *  Grava os dados de uma playlist em uma posição definida do arquivo.
 * pre-condicao 'f_playlists' aberto, 'p' contendo dados válidos de uma Playlist e 'pos' mapeando um local seguro do arquivo.
 * pos-condicao O registro da playlist é escrito na posição física 'pos'.
 */
void escreve_no_playlist(FILE* f_playlists, Playlist* p, long pos);

/**
 *  Lê um registro de playlist localizado em uma determinada posição do arquivo binário.
 * pre-condicao 'pos' deve representar o endereço ou RRN de uma playlist válida existente no arquivo.
 * pos-condicao Retorna um ponteiro alocado com a estrutura preenchida da Playlist lida.
 */
Playlist* le_no_playlist(long pos);

/**
 *  Cria uma nova playlist vazia no sistema, adicionando-a à lista encadeada de playlists.
 * pre-condicao O 'codigo' deve ser único e o 'titulo' não deve exceder o limite de caracteres definido[cite: 16, 17].
 * pos-condicao A playlist é inserida na lista encadeada dentro do arquivo binário, com seus apontadores de faixa inicial e final definidos como vazios (-1), atualizando o cabeçalho do arquivo[cite: 18, 19, 109].
 */
void criarPlaylist(int codigo, const char* titulo);

/**
 *  Exibe na tela a relação de todas as playlists cadastradas no sistema.
 * pre-condicao O arquivo binário de playlists deve estar acessível.
 * pos-condicao Varre a lista encadeada de playlists imprimindo sequencialmente apenas o código e o título de cada uma[cite: 31].
 */
void listarPlaylists();

/**
 *  Procura uma playlist específica pelo seu código de identificação.
 * pre-condicao O arquivo binário de playlists deve conter dados inicializados.
 * pos-condicao Retorna a posição em bytes (ou RRN) da playlist encontrada dentro do arquivo binário, ou -1 caso ela não exista[cite: 16].
 */
long buscarPlaylistPorCodigo(int codigo);
#endif