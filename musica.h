
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

//Abre o arquivo de livros de acordo com o modo desejado
//pré-condicao: uma string que representa um modo de abertura de arquivo válido (ex: "rb", "wb+", "ab+")
//pos-condicao: retorna o arquivo aberto no modo desejado
FILE* abrir_arquivo_livro(const char* modo);

/**
 *  Abre o arquivo binário de músicas do acervo no modo especificado.
 * pre-condicao: 'modo' deve ser uma string válida de modo de abertura de arquivo em C (ex: "rb", "wb+", "rb+").
 * pos-condicao Retorna um ponteiro FILE* associado ao arquivo físico aberto, ou NULL se houver falha na abertura.
 */
FILE* abrir_arquivo_musica(const char* modo);

/**
 *  Verifica se o arquivo binário de músicas já existe; caso contrário, inicializa-o.
 * pre-condicao: Nenhuma.
 * pos-condicao Se o arquivo não existir, ele é criado e um cabeçalho inicial zerado (cabeca = -1, topo = tamanho do cabeçalho) é gravado no início[cite: 109].
 */
void iniciar_musicas();

/**
 *  Escreve a estrutura de cabeçalho no início do arquivo binário de músicas.
 * pre-condicao: 'f_musicas' deve ser um ponteiro válido para o arquivo de músicas aberto em modo de escrita/atualização. 'cab' deve apontar para uma estrutura CabecalhoMusica válida.
 * pos-condicao O registro de cabeçalho é persistido na posição 0 (início) do arquivo binário[cite: 109].
 */
void escreve_cabecalho_musica(FILE* f_musicas, CabecalhoMusica* cab);

/**
 *  Lê a estrutura de cabeçalho presente no início do arquivo binário de músicas.
 * pre-condicao: O arquivo binário de músicas deve existir, estar inicializado e acessível para leitura.
 * pos-condicao Retorna um ponteiro alocado dinamicamente contendo os dados do cabeçalho lido do arquivo.
 */
CabecalhoMusica* le_cabecalho_musica();

/**
 *  Escreve um registro de música em uma posição física específica do arquivo binário.
 * pre-condicao: 'f_musicas' deve estar aberto em modo de escrita. 'x' deve ser um ponteiro válido com os dados da música. 'pos' deve ser um deslocamento em bytes ou RRN válido e seguro dentro do arquivo.
 * pos-condicao O registro da música é gravado na posição especificada, sobrescrevendo dados anteriores se houver.
 */
void escreve_no_musica(FILE* f_musicas, Musica* x, long pos);

/**
 *  Lê um registro de música de uma posição física específica do arquivo binário.
 * pre-condicao: 'pos' deve ser uma posição (offset em bytes ou RRN) válida de um registro existente dentro do arquivo.
 * pos-condicao Retorna um ponteiro alocado dinamicamente com os dados da música lida daquela posição.
 */
Musica* le_no_musica(long pos);

/**
 *  Interface via menu para coletar dados do terminal e realizar o cadastro de uma nova música no acervo.
 * pre-condicao: Nenhuma (interage com o usuário via prompt de comando)[cite: 35].
 * pos-condicao A música é inserida logicamente em ordem ou no final da lista encadeada do acervo, e o cabeçalho do arquivo é devidamente atualizado[cite: 23, 109].
 */
void cadastrarMusica();

/**
 *  Adiciona diretamente no arquivo binário uma estrutura de música pré-montada (usada no carregamento em lote).
 * pre-condicao: 'novo' deve ser um ponteiro válido para uma struct Musica preenchida com os dados vindos do arquivo de texto[cite: 32, 38].
 * pos-condicao A música é adicionada fisicamente no final do arquivo ('topo'), encadeada na lista geral, e as informações de controle de arquivo são atualizadas[cite: 109].
 */
void adicionarMusicaComRegistro(Musica* novo);

/**
 *  Varre o arquivo binário de músicas para verificar se um determinado código já está em uso.
 * pre-condicao: O arquivo binário de músicas deve estar acessível para leitura.
 * pos-condicao Retorna 1 se o código inserido já pertencer a alguma música do acervo, ou 0 caso o código esteja livre para uso[cite: 13].
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


#endif //musica_h

