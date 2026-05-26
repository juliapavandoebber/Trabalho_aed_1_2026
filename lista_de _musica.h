#ifndef MUSICA_H
#define MUSICA_H
#define ARQUIVO_LIVROS "musicas_teste.bin"
// Cabeçalho do arquivo binário de músicas
typedef struct {
    long cabeca; // Posição (RRN ou byte) da primeira música da lista
    long topo;   // Primeira posição livre no fim do arquivo
} CabecalhoMusica;

// Registro da música
typedef struct {
    int codigo;
    char titulo[44];
    char artista[51];
    long proximo; // "Ponteiro" (posição no arquivo) para a próxima música
} Musica;


//Abre o arquivo de livros de acordo com o modo desejado
//pré-condicao: uma string que representa um modo de abertura de arquivo válido (ex: "rb", "wb+", "ab+")
//pos-condicao: retorna o arquivo aberto no modo desejado
FILE* abrir_arquivo_livro(const char* modo);

//verifica se ja foi iniciado/criado o arquivo binario de livros
//pre-condicao: nenhuma
//pos-condicao: criacao do arquivo .bin caso ele ainda nao exista
void iniciar_livros();

//cria uma lista nova no arquivo de livros
//pre-condicao: arquivo aberto para leitura/escrita
//pos-condicao: arquivo eh inicializado com uma lista vazia
void criar_lista_vazia_playlist(FILE* f_musicas);

//escreve no arquivo de livro o cabecalho contendo as informacoes da lista
//pre-condicao: arquivo deve estar aberto e ser um arquivo de lista
//pos-condicao: cabecalho escrito no arquivo
void escreve_cabecalho_livro(FILE* f_musicas, Livro_cabecalho* cab);

//le o cabecalho do arquivo de livro contendo as informacoes da lista
//pre-condicao: O arquivo de usuários deve existir e estar acessível
//pos-condicao: retorna um ponteiro para o cabecalho lido
Livro_cabecalho* le_cabecalho_livro();

//busca se ha livro cadastrado com o codigo inserido pelo usuario
//pre-condicao: O ponteiro livro deve apontar para uma estrutura no valida
//pos-condicao: imprime dados do livro
void imprimirDetalhesLivro(Livro_no* livro);

//verifica se o codigo ja pertence a um livro
//pre-condicao: o arquivo de livros deve esta aberto e acessivel
//pos-condicao: informa se o codigo esta disponivel,
//              caso nao, imprime informacoes do livro que contem o codigo,
//              da a escolha ao usuario se ele deseja adicionar exemplares do livro,
//              caso sim, atualiza os dados de exemplares no arquivo e caso contrario eh cancelado o cadastro
int cadastro_codigo_livro_existente(int codigo_procurado, FILE* f_livro, Livro_cabecalho* cab);

//escreve um no em uma determinada posicao do arquivo de livro
//pre-condicao: arquivo deve estar aberto e ser um arquivo de lista
//              pos deve ser uma posicao valida no arquivo
//pos-condicao: no escrito no arquivo
void escreve_no_livro(FILE* f_livro, Livro_no* x, int pos);

//Cadastra dados do livro e imprime os dados do livro cadastrado
//pre-condicao: nenhuma
//pos-condicao: insere um livro novo na lista e atualiza o cabecalho da lista
void cadastrarLivro();

//le um no em uma determinada posicao do arquivo do livro
//pre-condicao: pos deve ser uma posicao valida da lista
//pos-condicao: ponteiro para no lido é retornado
Livro_no* le_no_livro(int pos);

//busca se ha livro cadastrado com o codigo inserido pelo usuario
//pre-condicao: o arquivo de livros deve existir e esta acessivel
//pos-condicao: imprime dados do livro caso ele exista ou informa que o livro com o codigo nao existe
void imprimirLivro(int codigo);

//Lista todos os livros cadastrados e suas informacoes
//pre-condicao: o arquivo de livros deve existir e esta acessivel
//pos-condicao: imprime dados de todos os livros ou informa que nao ha nenhuma livro cadastrado
void listarLivros();

//busca se ha livro cadastrado com o titulo inserido pelo usuario
//pre-condicao: o arquivo de livros deve existir e esta acessivel
//pos-condicao: imprime dados do livro caso ele exista ou informa que o livro com o titulo nao existe
void buscarLivroPorTitulo(const char *tituloBuscado);

//Conta quantos livros ja foram inseridos na lista
//pre-condicao: o arquivo de livros deve existir e esta acessivel
//pos-condicao: retorna a quantidade de livros cadastrados
int contarTotalLivros();

//mostra os dados do livro
//pre-condicao: O ponteiro livro deve apontar para uma estrutura no valida
//pos-condicao: imprime dados do livro
void imprimirDetalhesLivro(Livro_no* livro);

//Conta quantos titulos de livros ja foram inseridos na lista
//pre-condicao: o arquivo de livros deve existir e esta acessivel
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



#endif //musica_h

