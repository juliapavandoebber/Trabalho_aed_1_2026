
#ifndef MUSICA_H
#define MUSICA_H
#define ARQUIVO_MUSICA "musica.bin"
#include <stdio.h>

// Cabeçalho do arquivo binário de músicas
typedef struct {
    long cabeca; // Posição (RRN ou byte) da primeira música da lista
    long topo;  // Primeira posição livre no fim do arquivo
} CabecalhoMusica;

typedef struct {
    int codigo;
    char titulo[100];
    char artista[51];
    int ano;
    long prox;
} Musica;

/**
 * @brief Abre o arquivo binário de músicas do acervo no modo especificado.
 * @pre 'modo' deve ser uma string válida de modo de abertura de arquivo em C (ex: "rb", "wb+", "rb+").
 * @pos Retorna um ponteiro FILE* associado ao arquivo físico aberto, ou NULL se houver falha na abertura.
 */
FILE* abrir_arquivo_musica(const char* modo);

// cria uma lista nova no arquivo de musicas
// pre-condicao: arquivo aberto para leitura/escrita
// pos-condicao: arquivo eh inicializado com uma lista vazia
void criar_lista_vazia_musica(FILE* f_musica);

/**
 * @brief Escreve ou atualiza o registro de cabeçalho no início do arquivo binário de músicas.
 * Propósito: Posicionar o ponteiro do arquivo no byte 0 (início) e persistir em disco as 
 * informações de controle atualizadas (cabeca e topo).
 * @pre O arquivo de músicas deve estar aberto em um modo que permita escrita ("rb+" ou "wb+"). 
 * O ponteiro 'cab' deve apontar para uma estrutura válida em memória.
 * @pos O registro do cabeçalho é gravado com sucesso no início do arquivo binário.
 */
void escreve_cabecalho_musica(FILE* f_musica, const CabecalhoMusica* cab);

/**
 * @brief Verifica se o arquivo binário de músicas já existe; caso contrário, inicializa-o.
 * @pre Nenhuma.
 * @pos Se o arquivo não existir, ele é criado e um cabeçalho inicial zerado (cabeca = -1, topo = tamanho do cabeçalho) é gravado no início.
 */
void iniciar_musicas();

/**
 * @brief Cadastra uma nova música no arquivo binário do acervo geral.
 * * Propósito: Recebe os dados de uma música, valida se o código é único e insere o registro
 * no final do arquivo binário (usando o topo do cabeçalho), atualizando os encadeamentos.
 * Pré-condições: O arquivo binário de músicas deve estar aberto em modo de leitura/escrita ("rb+").
 * O código fornecido não deve existir previamente no acervo.
 * Pós-condições: A música é gravada no arquivo e os ponteiros do cabeçalho são atualizados.
 */
int cadastrar_musica(FILE *f_musica, int codigo, const char *titulo, const char *artista, int ano);

/**
 * @brief Busca e imprime os dados de uma música específica no acervo.
 * * Propósito: Percorre a lista encadeada física no arquivo procurando pelo código fornecido.
 * Se encontrar, imprime código, título, artista e ano no terminal.
 * Pré-condições: O arquivo binário de músicas deve estar aberto em modo de leitura ("rb").
 * Pós-condições: Os dados da música são exibidos na tela ou uma mensagem de erro é gerada se não encontrada.
 */
void imprimir_dados_musica(FILE *f_musica, int codigo);

/**
 * @brief Lista todas as músicas presentes no acervo geral.
 * * Propósito: Percorre a lista encadeada de músicas a partir da "cabeca" guardada no cabeçalho,
 * imprimindo sequencialmente todas as músicas salvas.
 * Pré-condições: O arquivo binário de músicas deve estar aberto em modo de leitura ("rb").
 * Pós-condições: Exibe a lista de todas as músicas cadastradas no terminal.
 */
void listar_acervo(FILE *f_musica);

/**
 * @brief Busca interna para verificar a existência de uma música e retornar seus dados.
 * * Propósito: Localiza uma música pelo código e preenche uma estrutura em memória para uso das outras entidades.
 * Pré-condições: O arquivo binário de músicas deve estar aberto em modo de leitura ("rb").
 * Pós-condições: Retorna 1 se a música for encontrada e preenche o ponteiro 'saida'; retorna 0 caso contrário.
 */
int buscar_musica_por_codigo(FILE *f_musica, int codigo, Musica *saida);



#endif //musica_h