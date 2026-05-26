#ifndef FAIXA_H
#define FAIXA_H

#include <stdio.h>

#define ARQUIVO_FAIXA "faixa.bin"

// Estrutura de cabeçalho do arquivo de faixas (no início do arquivo)
typedef struct {
    long topo;          // Primeira posição livre no fim do arquivo (EOF físico)
    long lista_livres;  // Posição (byte) da cabeça da lista de nós deletados/livres
} CabecalhoFaixa;

// Estrutura do registro de nó de faixa musical
typedef struct {
    int codigo_musica;  // Código da música correspondente no acervo geral
    long prox;          // Posição (byte) da próxima faixa pertencente a esta playlist
} FaixaPlaylist;

/**
 * @brief Abre o arquivo binário responsável por armazenar os nós de faixas das playlists.
 * Propósito: Encapsular a abertura do arquivo físico de faixas de música.
 * @pre 'modo' deve conter uma string válida de abertura de arquivos em C (ex: "rb", "rb+").
 * @pos Retorna o ponteiro FILE* associado ao arquivo de faixas aberto, ou NULL em caso de erro.
 */
FILE* abrir_arquivo_faixas(const char* modo);

/**
 * @brief Inicializa a estrutura de arquivos de faixas musicais e o gerenciador de espaço vago.
 * Propósito: Garantir a criação e a gravação do cabeçalho de controle se o arquivo for novo.
 * @pre Nenhuma.
 * @pos Se o arquivo não existir, cria-o e grava o cabeçalho configurando 'topo' inicial e definindo 'lista_livres' como vazia (-1).
 */
void iniciar_faixas();

/**
 * @brief Insere uma música no início de uma playlist específica.
 * Propósito: Cria um nó de faixa. Reaproveita um offset da lista de livres se disponível; caso contrário, 
 * aloca no final (topo) do arquivo. Ajusta os ponteiros 'id_faixa_ini' e 'id_faixa_fim' da playlist envolvida.
 * @pre Os arquivos de faixas e playlists devem estar abertos em modo de leitura/escrita ("rb+"). 
 * A música e a playlist informadas devem existir previamente.
 * @pos Um nó de faixa contendo o código da música é adicionado no início da lista da playlist indicada.
 */
int adicionar_faixa_inicio(FILE *arq_faixas, FILE *arq_play, int codigo_playlist, int codigo_musica);

/**
 * @brief Insere uma música no final de uma playlist específica.
 * Propósito: Aloca um nó de faixa (reaproveitando nós de 'lista_livres' se disponíveis) e o anexa 
 * atualizando o ponteiro apontado por 'id_faixa_fim' da playlist desejada.
 * @pre Os arquivos de faixas e playlists devem estar abertos em modo "rb+". A música e a playlist informadas devem existir.
 * @pos O nó de faixa é inserido no final da playlist e o ponteiro 'id_faixa_fim' é atualizado adequadamente em disco.
 */
int adicionar_faixa_fim(FILE *arq_faixas, FILE *arq_play, int codigo_playlist, int codigo_musica);

/**
 * @brief Remove uma música de uma playlist específica e move o nó físico para a lista de livres.
 * Propósito: Localiza o código da música na lista encadeada daquela playlist, remove a associação alterando os 
 * ponteiros dos nós vizinhos (ou da playlist) e insere a posição desse registro físico vago no início de 'lista_livres'.
 * @pre Os arquivos de faixas e playlists devem estar abertos em modo "rb+". A playlist deve conter a música informada.
 * @pos O nó é desvinculado logicamente da playlist e o offset físico do registro é indexado na lista de reaproveitamento do cabeçalho.
 */
int remover_faixa(FILE *arq_faixas, FILE *arq_play, int codigo_playlist, int codigo_musica);

/**
 * @brief Imprime todas as posições físicas de registros atualmente livres no arquivo de faixas.
 * Propósito: Percorrer de forma encadeada a lista de nós reaproveitáveis a partir de 'lista_livres' para fins de depuração.
 * @pre O arquivo de faixas deve estar aberto em modo de leitura ("rb").
 * @pos Exibe em tela todos os offsets em bytes que estão prontos para reuso no sistema.
 */
void imprimir_nos_livres(FILE *arq_faixas);

#endif // FAIXA_H