#ifndef musica_H
#define musica_H
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
    long proximo;
} Musica;


//Abre o arquivo de musica de acordo com o modo desejado
//pré-condicao: uma string que representa um modo de abertura de arquivo válido (ex: "rb", "wb+", "ab+")
//pos-condicao: retorna o arquivo aberto no modo desejado
FILE* abrir_arquivo_musica(const char* modo);

//verifica se ja foi iniciado/criado o arquivo binario de musica
//pre-condicao: nenhuma
//pos-condicao: criacao do arquivo .bin caso ele ainda nao exista
void iniciar_musica();

//cria uma lista nova no arquivo de musica
//pre-condicao: arquivo aberto para leitura/escrita
//pos-condicao: arquivo eh inicializado com uma lista vazia
void criar_lista_vazia_playlist(FILE* f_musica);

//escreve no arquivo de Musica o cabecalho contendo as informacoes da lista
//pre-condicao: arquivo deve estar aberto e ser um arquivo de lista
//pos-condicao: cabecalho escrito no arquivo
void escreve_cabecalho_musica(FILE* f_musica, musica_cabecalho* cab);

//le o cabecalho do arquivo de musica contendo as informacoes da lista
//pre-condicao: O arquivo de usuários deve existir e estar acessível
//pos-condicao: retorna um ponteiro para o cabecalho lido
musica_cabecalho* le_cabecalho_musica();

//busca se ha musica cadastrado com o codigo inserido pelo usuario
//pre-condicao: O ponteiro musica deve apontar para uma estrutura no valida
//pos-condicao: imprime dados do musica
void imprimirDetalhesmusica(musica_no* musica);

//verifica se o codigo ja pertence a um musica
//pre-condicao: o arquivo de musica deve esta aberto e acessivel
//pos-condicao: informa se o codigo esta disponivel,
//              caso nao, imprime informacoes do Musica que contem o codigo,
//              da a escolha ao usuario se ele deseja adicionar exemplares do Musica,
//              caso sim, atualiza os dados de exemplares no arquivo e caso contrario eh cancelado o cadastro
int cadastro_codigo_Musica_existente(int codigo_procurado, FILE* f_Musica, Musica_cabecalho* cab);

//escreve um no em uma determinada posicao do arquivo de Musica
//pre-condicao: arquivo deve estar aberto e ser um arquivo de lista
//              pos deve ser uma posicao valida no arquivo
//pos-condicao: no escrito no arquivo
void escreve_no_Musica(FILE* f_Musica, Musica_no* x, int pos);

//Cadastra dados do Musica e imprime os dados do Musica cadastrado
//pre-condicao: nenhuma
//pos-condicao: insere um Musica novo na lista e atualiza o cabecalho da lista
void cadastrarMusica();

//le um no em uma determinada posicao do arquivo do Musica
//pre-condicao: pos deve ser uma posicao valida da lista
//pos-condicao: ponteiro para no lido é retornado
Musica_no* le_no_Musica(int pos);

//busca se ha Musica cadastrado com o codigo inserido pelo usuario
//pre-condicao: o arquivo de musica deve existir e esta acessivel
//pos-condicao: imprime dados do Musica caso ele exista ou informa que o Musica com o codigo nao existe
void imprimirMusica(int codigo);

//Lista todos os musica cadastrados e suas informacoes
//pre-condicao: o arquivo de musica deve existir e esta acessivel
//pos-condicao: imprime dados de todos os musica ou informa que nao ha nenhuma Musica cadastrado
void listarmusica();

//busca se ha Musica cadastrado com o titulo inserido pelo usuario
//pre-condicao: o arquivo de musica deve existir e esta acessivel
//pos-condicao: imprime dados do Musica caso ele exista ou informa que o Musica com o titulo nao existe
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

