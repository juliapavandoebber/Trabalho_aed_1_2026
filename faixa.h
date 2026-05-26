#ifndef FAIXA_H
#define FAIXA_H

// Estrutura de cabeçalho do arquivo de faixas 
typedef struct {
    long topo;          // Primeira posição livre no fim do arquivo 
    long lista_livres;  // Posição da cabeça da lista de nós deletados/livres 
} CabecalhoFaixa;

// Estrutura do nó de faixa musical (o elemento da lista interna da playlist) 
typedef struct {
    int codigo_musica;  // Apenas o código da música do acervo é armazenado aqui 
    long prox;          // Posição da próxima faixa pertencente a esta playlist 
} FaixaPlaylist;

// Abre o arquivo binário de faixas
FILE* abrir_arquivo_faixas(const char* modo);

// Inicializa o arquivo de faixas criando o cabeçalho com a lista de livres vazia (-1)
void iniciar_faixas();

// Escreve o cabeçalho no arquivo de faixas
void escreve_cabecalho_faixa(FILE* f_faixas, CabecalhoFaixa* cab);

// Lê o cabeçalho do arquivo de faixas
CabecalhoFaixa* le_cabecalho_faixa();

// Escreve uma faixa em uma determinada posição do arquivo
void escreve_no_faixa(FILE* f_faixas, FaixaPlaylist* f, long pos);

// Lê uma faixa de uma determinada posição do arquivo
FaixaPlaylist* le_no_faixa(long pos);

// Insere uma música no início de uma playlist específica
void adicionarMusicaInicioPlaylist(int codigo_playlist, int codigo_musica);

// Insere uma música no final de uma playlist específica
void adicionarMusicaFinalPlaylist(int codigo_playlist, int codigo_musica);

// Remove uma música de uma playlist específica e move o nó para a lista de livres
void removerMusicaPlaylist(int codigo_playlist, int codigo_musica);

// Imprime o título da playlist e todas as suas músicas (buscando dados no acervo)
void imprimirMusicasDaPlaylist(int codigo_playlist);

// Imprime todas as posições de registros livres gerados por remoções (Requisito do trabalho)
void imprimirNosLivres();

#endif