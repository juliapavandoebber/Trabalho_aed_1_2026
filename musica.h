
#ifndef MUSICA_H
#define MUSICA_H
#define ARQUIVO_MUSICA "musica.bin"

// Cabeçalho do arquivo binário de músicas
typedef struct {
    long cabeca; // Posição (RRN ou byte) da primeira música da lista
    long topo;   // Primeira posição livre no fim do arquivo
} CabecalhoMusica;

typedef struct {
    int codigo;
    char titulo[44];
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

/**
 * @brief Verifica se o arquivo binário de músicas já existe; caso contrário, inicializa-o.
 * @pre Nenhuma.
 * @pos Se o arquivo não existir, ele é criado e um cabeçalho inicial zerado (cabeca = -1, topo = tamanho do cabeçalho) é gravado no início[cite: 109].
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
int cadastrar_musica(FILE *arq, int codigo, const char *titulo, const char *artista, int ano);

/**
 * @brief Busca e imprime os dados de uma música específica no acervo.
 * * Propósito: Percorre a lista encadeada física no arquivo procurando pelo código fornecido.
 * Se encontrar, imprime código, título, artista e ano no terminal.
 * Pré-condições: O arquivo binário de músicas deve estar aberto em modo de leitura ("rb").
 * Pós-condições: Os dados da música são exibidos na tela ou uma mensagem de erro é gerada se não encontrada.
 */
void imprimir_dados_musica(FILE *arq, int codigo);

/**
 * @brief Lista todas as músicas presentes no acervo geral.
 * * Propósito: Percorre a lista encadeada de músicas a partir da "cabeca" guardada no cabeçalho,
 * imprimindo sequencialmente todas as músicas salvas.
 * Pré-condições: O arquivo binário de músicas deve estar aberto em modo de leitura ("rb").
 * Pós-condições: Exibe a lista de todas as músicas cadastradas no terminal.
 */
void listar_acervo(FILE *arq);

/**
 * @brief Busca interna para verificar a existência de uma música e retornar seus dados.
 * * Propósito: Localiza uma música pelo código e preenche uma estrutura em memória para uso das outras entidades.
 * Pré-condições: O arquivo binário de músicas deve estar aberto em modo de leitura ("rb").
 * Pós-condições: Retorna 1 se a música for encontrada e preenche o ponteiro 'saida'; retorna 0 caso contrário.
 */
int buscar_musica_por_codigo(FILE *arq, int codigo, Musica *saida);

/**
 * @brief Cria uma nova playlist no arquivo binário.
 * * Propósito: Instancia uma estrutura de playlist com os ponteiros de faixa inicializados como vazios (-1)
 * e a insere ordenadamente ou no fim da lista de playlists.
 * Pré-condições: O arquivo binário de playlists deve estar aberto em modo "rb+".
 * O código de playlist fornecido deve ser único.
 * Pós-condições: A nova playlist é persistida no arquivo e o cabeçalho é atualizado.
 */
int criar_playlist(FILE *arq_play, int codigo, const char *titulo);

/**
 * @brief Imprime o código e o título de todas as playlists.
 * * Propósito: Percorre de forma encadeada o arquivo de playlists exibindo seus dados básicos identificadores.
 * Pré-condições: O arquivo de playlists deve estar aberto em modo "rb".
 * Pós-condições: A lista resumida de todas as playlists criadas é impressa na tela.
 */
void imprimir_lista_playlists(FILE *arq_play);

/**
 * @brief Imprime as músicas de uma playlist detalhadamente.
 * * Propósito: Localiza a playlist informada, acessa o arquivo de faixas a partir de 'cabeca_faixa'
 * e, para cada faixa, recupera o nome da música e artista no arquivo de músicas.
 * Pré-condições: O arquivo de playlists ("rb"), o de faixas ("rb") e o de músicas ("rb") devem estar abertos.
 * Pós-condições: Imprime o título da playlist seguido pelos títulos e artistas das músicas associadas, na ordem correta.
 */
void imprimir_playlist_especifica(FILE *arq_play, FILE *arq_faixas, FILE *arq_musicas, int codigo_playlist);


#endif //musica_h

