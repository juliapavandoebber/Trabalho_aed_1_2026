
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
    char titulo[100];
    char artista[51];
    int ano;

    long prox;
} Musica;



/**
 *  Abre o arquivo binário de músicas do acervo no modo especificado.
 * Pré-condições: 'modo' deve ser uma string válida de modo de abertura de arquivo em C (ex: "rb", "wb+", "rb+").
 * Pós-condições: Retorna um ponteiro FILE* associado ao arquivo físico aberto, ou NULL se houver falha na abertura.
 */
FILE* abrir_arquivo_musica(const char* modo);

/**
 *  Verifica se o arquivo binário de músicas já existe; caso contrário, inicializa-o.
 * Pré-condições: Nenhuma.
 * Pós-condições: Se o arquivo não existir, ele é criado e um cabeçalho inicial zerado (cabeca = -1, topo = tamanho do cabeçalho) é gravado no início[cite: 109].
 */
void criar_lista_vazia_musica(FILE* f_musica);

/**
 *  Escreve ou atualiza o registro de cabeçalho no início do arquivo binário de músicas.
 * Propósito: Posicionar o ponteiro do arquivo no byte 0 (início) e persistir em disco as 
 * informações de controle atualizadas (cabeca e topo).
 * Pré-condições: O arquivo de músicas deve estar aberto em um modo que permita escrita ("rb+" ou "wb+"). 
 * O ponteiro 'cab' deve apontar para uma estrutura válida em memória.
 * Pós-condições: O registro do cabeçalho é gravado com sucesso no início do arquivo binário.
 */
void escreve_cabecalho_musica(FILE* f_musica, const CabecalhoMusica* cab);

/**
 *  Cadastra uma nova música no arquivo binário do acervo geral.
 * * Propósito: Recebe os dados de uma música, valida se o código é único e insere o registro
 * no final do arquivo binário (usando o topo do cabeçalho), atualizando os encadeamentos.
 * Pré-condições: O arquivo binário de músicas deve estar aberto em modo de leitura/escrita ("rb+").
 * O código fornecido não deve existir previamente no acervo.
 * Pós-condições: A música é gravada no arquivo e os ponteiros do cabeçalho são atualizados.
 */
int cadastrar_musica(FILE *arq, int codigo, const char *titulo, const char *artista, int ano);

/**
 *  Busca e imprime os dados de uma música específica no acervo.
 * * Propósito: Percorre a lista encadeada física no arquivo procurando pelo código fornecido.
 * Se encontrar, imprime código, título, artista e ano no terminal.
 * Pré-condições: O arquivo binário de músicas deve estar aberto em modo de leitura ("rb").
 * Pós-condições: Os dados da música são exibidos na tela ou uma mensagem de erro é gerada se não encontrada.
 */
void imprimir_dados_musica(FILE *arq, int codigo);

/**
 *  Lista todas as músicas presentes no acervo geral.
 * * Propósito: Percorre a lista encadeada de músicas a partir da "cabeca" guardada no cabeçalho,
 * imprimindo sequencialmente todas as músicas salvas.
 * Pré-condições: O arquivo binário de músicas deve estar aberto em modo de leitura ("rb").
 * Pós-condições: Exibe a lista de todas as músicas cadastradas no terminal.
 */
void listar_acervo(FILE *arq);

/**
 *  Busca interna para verificar a existência de uma música e retornar seus dados.
 * * Propósito: Localiza uma música pelo código e preenche uma estrutura em memória para uso das outras entidades.
 * Pré-condições: O arquivo binário de músicas deve estar aberto em modo de leitura ("rb").
 * Pós-condições: Retorna 1 se a música for encontrada e preenche o ponteiro 'saida'; retorna 0 caso contrário.
 */
int buscar_musica_por_codigo(FILE *arq, int codigo, Musica *saida);


/**
 *  Cria uma nova playlist no arquivo binário.
 * * Propósito: Instancia uma estrutura de playlist com os ponteiros de faixa inicializados como vazios (-1)
 * e a insere ordenadamente ou no fim da lista de playlists.
 * Pré-condições: O arquivo binário de playlists deve estar aberto em modo "rb+".
 * O código de playlist fornecido deve ser único.
 * Pós-condições: A nova playlist é persistida no arquivo e o cabeçalho é atualizado.
 */
int criar_playlist(FILE *arq_play, int codigo, const char *titulo);

/**
 *  Imprime o código e o título de todas as playlists.
 * * Propósito: Percorre de forma encadeada o arquivo de playlists exibindo seus dados básicos identificadores.
 * Pré-condições: O arquivo de playlists deve estar aberto em modo "rb".
 * Pós-condições: A lista resumida de todas as playlists criadas é impressa na tela.
 */
void imprimir_lista_playlists(FILE *arq_play);

/**
 *  Imprime as músicas de uma playlist detalhadamente.
 * * Propósito: Localiza a playlist informada, acessa o arquivo de faixas a partir de 'cabeca_faixa'
 * e, para cada faixa, recupera o nome da música e artista no arquivo de músicas.
 * Pré-condições: O arquivo de playlists ("rb"), o de faixas ("rb") e o de músicas ("rb") devem estar abertos.
 * Pós-condições: Imprime o título da playlist seguido pelos títulos e artistas das músicas associadas, na ordem correta.
 */
int verifica_cod_musica(int codigo);

/**
 *  Busca uma música pelo código e imprime seus detalhes na tela.
 * pre-condicao: O código fornecido deve ser buscado no arquivo binário de músicas.
 * pos-condicao Se encontrada, imprime no console o código, título, artista e ano da música; caso contrário, exibe mensagem informando que a música não existe[cite: 24].
 */
void imprimirMusica(int codigo);

/**
 *  Percorre toda a lista encadeada do acervo de músicas no arquivo binário, imprimindo-as em formato de listagem.
 * pre-condicao: O arquivo binário de músicas deve estar inicializado e com registros.
 * pos-condicao Imprime na tela os dados estruturados de todas as músicas que pertencem à lista encadeada do acervo[cite: 25].
 */
void listarmusicas();

/**
 *  Busca por ocorrências de músicas no acervo que possuam o título exatamente igual ou semelhante ao informado.
 * pre-condicao: 'tituloBuscado' deve ser uma string de caracteres válida.
 * pos-condicao Imprime os dados de todas as músicas cujo título corresponda ao parâmetro de busca, ou informa que nenhuma foi encontrada.
 */
void buscarMusicaPorTitulo(const char *tituloBuscado);

//Conta quantos musica ja foram inseridos na lista
//pre-condicao: o arquivo de musica deve existir e esta acessivel
//pos-condicao: retorna a quantidade de musica cadastrados
int contarTotalmusica();

//mostra os dados do Musica
//pre-condicao: O ponteiro Musica deve apontar para uma estrutura no valida
//pos-condicao: imprime dados do Musica
void imprimirDetalhesMusica(Musica_no* Musica);

//Conta quantos titulos de musica ja foram inseridos na lista
//pre-condicao: o arquivo de musica deve existir e esta acessivel
//pos-condicao: retorna a quantidade de titulos cadastrados
int contarTitulosCadastrado();

//verifica se o codigo usado para o cadastro ja foi utilizado

//pre-condicao: numero utilizado para cadastro de livro
//pos-condicao: Retorna 1 se o código já está em uso por um livro, ou 0 caso contrário
int verifica_cod_livro (int codigo);

// Adiciona um livro lido de um arquivo de texto ao arquivo binário.
// pre-condicao: Um ponteiro válido para uma struct Livro_no (novo) contendo os dados do livro.
//               O arquivo binário de livros (ARQUIVO_LIVROS) deve estar acessível para leitura e escrita.
// pos-condicao: O novo livro é escrito no final do arquivo binário e o cabeçalho é atualizado.
void adicionarLivroComRegistro(Livro_no* novo);

//Verifica se ja há um livro com os mesmos dados mas com codigos diferentes
//pre-condicao: Arquivo livro deve existir e ser acessivel
//              Um ponteiro válido para uma struct Livro_no (novo) contendo os dados do livro.
//pos-condicao: Retorna 0 para caso nao haja, 1 caso haja e tenha acrescentado exemplares e -1
//              para caso não tenha modificado nada
int MesmoLivroCodigoDiferente (Livro_no* novo);

//pre-condicao: numero utilizado para cadastro de Musica
//pos-condicao: Retorna 1 se o código já está em uso por um Musica, ou 0 caso contrário
int verifica_cod_Musica (int codigo);

// Adiciona um Musica lido de um arquivo de texto ao arquivo binário.
// pre-condicao: Um ponteiro válido para uma struct Musica_no (novo) contendo os dados do Musica.
//               O arquivo binário de musica (ARQUIVO_musica) deve estar acessível para leitura e escrita.
// pos-condicao: O novo Musica é escrito no final do arquivo binário e o cabeçalho é atualizado.
void adicionarMusicaComRegistro(Musica_no* novo);

//Verifica se ja há um Musica com os mesmos dados mas com codigos diferentes
//pre-condicao: Arquivo Musica deve existir e ser acessivel
//              Um ponteiro válido para uma struct Musica_no (novo) contendo os dados do Musica.
//pos-condicao: Retorna 0 para caso nao haja, 1 caso haja e tenha acrescentado exemplares e -1
//              para caso não tenha modificado nada
int MesmoMusicaCodigoDiferente (Musica_no* novo);
=======
void imprimir_playlist_especifica(FILE *arq_play, FILE *arq_faixas, FILE *arq_musicas, int codigo_playlist);



#endif //musica_h

