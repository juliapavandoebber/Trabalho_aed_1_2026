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
 * Propósito: Encapsular a abertura do arquivo físico de faixas.
 * @pre 'modo' deve conter uma string válida de abertura de arquivos em C (ex: "rb", "rb+").
 * @pos Retorna o ponteiro FILE* associado ao arquivo de faixas aberto, ou NULL em caso de erro.
 */
FILE* abrir_arquivo_faixas(const char* modo);

/**
 * @brief Escreve ou atualiza o registro de cabeçalho no início do arquivo binário de faixas.
 * Propósito: Posicionar o ponteiro no byte 0 e salvar as variáveis de controle espacial (topo e lista_livres).
 * @pre O arquivo de faixas deve estar aberto em modo que permita escrita ("rb+" ou "wb+").
 * @pos O cabeçalho de faixas é devidamente persistido em disco.
 */
void escreve_cabecalho_faixa(FILE* f_faixa, const CabecalhoFaixa* cab);

/**
 * @brief Inicializa a estrutura de arquivos de faixas musicais e o gerenciador de espaço vago.
 * Propósito: Garantir que o arquivo exista e possua um cabeçalho de reaproveitamento válido gravado.
 * @pre Nenhuma.
 * @pos Se o arquivo não existir, cria-o e salva o cabeçalho com topo inicial e lista_livres = -1.
 */
void iniciar_faixas();

/**
 * @brief Insere uma música no início de uma playlist específica.
 * Propósito: Aloca um registro de faixa (reaproveitando nós de 'lista_livres' se houver) e o define como o novo 'id_faixa_ini'.
 * @pre Os arquivos de faixas e playlists devem estar abertos em modo "rb+". A música e a playlist devem existir.
 * @pos O nó contendo o código da música é embutido no início da playlist e as alterações são salvas.
 */
int adicionar_faixa_inicio(FILE *arq_faixas, FILE *arq_play, int codigo_playlist, int codigo_musica);

/**
 * @brief Insere uma música no final de uma playlist específica.
 * Propósito: Aloca um registro de faixa (com reaproveitamento de espaço livre se disponível) e o anexa usando o 'id_faixa_fim'.
 * @pre Os arquivos de faixas e playlists devem estar abertos em modo "rb+". A música e a playlist devem existir.
 * @pos A música é inserida no final da playlist e o ponteiro 'id_faixa_fim' é sincronizado em disco.
 */
int adicionar_faixa_fim(FILE *arq_faixas, FILE *arq_play, int codigo_playlist, int codigo_musica);

/**
 * @brief Remove uma música de uma playlist específica e move o nó físico para a lista de livres.
 * Propósito: Desconectar logicamente o nó de faixa da playlist e adicioná-lo na pilha de registros disponíveis ('lista_livres').
 * @pre Os arquivos de faixas e playlists devem estar abertos em modo "rb+". A playlist deve conter a música indicada.
 * @pos O nó é removido da playlist e seu endereço é anexado ao cabeçalho para futuro reaproveitamento em novas inserções.
 */
int remover_faixa(FILE *arq_faixas, FILE *arq_play, int codigo_playlist, int codigo_musica);

/**
 * @brief Imprime todas as posições físicas de registros atualmente livres no arquivo de faixas.
 * Propósito: Percorrer a lista ligada de nós apagados a partir de 'lista_livres' para monitoramento do reuso de espaço.
 * @pre O arquivo de faixas deve estar aberto em modo de leitura ("rb").
 * @pos Exibe os offsets em bytes de todos os registros que estão atualmente marcados como disponíveis.
 */
void imprimir_nos_livres(FILE *arq_faixas);

#endif // FAIXA_H