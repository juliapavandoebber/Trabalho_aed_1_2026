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

/**
 *  Abre o arquivo binário responsável por armazenar os nós de faixas das playlists.
 * pre-condicao: 'modo' contendo string válida de abertura de arquivos em C.
 * pos-condicao: Retorna o ponteiro FILE* associado ao arquivo de faixas aberto.
 */
FILE* abrir_arquivo_faixas(const char* modo);

/**
 *  Inicializa a estrutura de arquivos de faixas musicais e o gerenciador de espaço vago.
 * pre-condicao: Nenhuma.
 * pos-condicao: Se o arquivo não existir, cria-o e grava o cabeçalho configurando o 'topo' inicial e definindo a lista de nós livres como vazia (-1)[cite: 110].
 */
void iniciar_faixas();

/**
 * @brief Insere uma música no início de uma playlist específica.
 * * Propósito: Cria um nó de faixa. Verifica se existe espaço na lista de nós livres para reaproveitá-lo;
 * caso contrário, aloca no final (topo) do arquivo. Ajusta os ponteiros de cabeçalho da playlist.
 * Pré-condições: Os arquivos de faixas e playlists devem estar abertos em modo "rb+".
 * A música e a playlist informadas devem existir previamente nos seus respectivos arquivos.
 * Pós-condições: Um nó de faixa contendo o código da música é adicionado no início da lista da playlist indicada.
 */
int adicionar_faixa_inicio(FILE *arq_faixas, FILE *arq_play, int codigo_playlist, int codigo_musica);

/**
 * @brief Insere uma música no final de uma playlist específica.
 * * Propósito: Aloca um nó de faixa (reaproveitando nós livres se disponíveis) e o anexa 
 * utilizando o ponteiro 'fim_faixa' da estrutura da playlist desejada.
 * Pré-condições: Os arquivos de faixas e playlists devem estar abertos em modo "rb+".
 * A música e a playlist informadas devem existir.
 * Pós-condições: O nó de faixa é inserido no final da playlist e o ponteiro 'fim_faixa' é devidamente atualizado.
 */
int adicionar_faixa_fim(FILE *arq_faixas, FILE *arq_play, int codigo_playlist, int codigo_musica);

/**
 * @brief Remove uma música de uma playlist específica e move o nó para a lista de livres.
 * * Propósito: Localiza a música dentro da lista encadeada daquela playlist, remove a associação ajustando os 
 * ponteiros dos nós vizinhos (ou da playlist) e insere a posição desse registro físico agora vago 
 * na cabeça da lista de nós livres do cabeçalho de faixas.
 * Pré-condições: Os arquivos de faixas e playlists devem estar abertos em modo "rb+".
 * A playlist deve conter a música informada para remoção.
 * Pós-condições: O nó é desvinculado da playlist, e o offset físico do registro é indexado na lista de reaproveitamento.
 */
int remover_faixa(FILE *arq_faixas, FILE *arq_play, int codigo_playlist, int codigo_musica);

/**
 * @brief Imprime todas as posições físicas de registros atualmente livres no arquivo de faixas.
 * * Propósito: Percorre a lista encadeada de nós livres iniciada em 'livre_casa' no cabeçalho de faixas,
 * mostrando os offsets que foram liberados por remoções passadas.
 * Pré-condições: O arquivo de faixas deve estar aberto em modo "rb".
 * Pós-condições: Exibe na tela todas as posições físicas prontas para reaproveitamento no sistema.
 */
void imprimir_nos_livres(FILE *arq_faixas);

#endif