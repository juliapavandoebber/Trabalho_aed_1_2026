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
 *  Atualiza o cabeçalho de controle do arquivo de faixas (topo e ponteiro de livres).
 * pre-condicao: 'f_faixas' aberto em modo de escrita e 'cab' contendo os dados de controle atualizados.
 * pos-condicao: Grava o cabeçalho no início do arquivo binário de faixas[cite: 110].
 */
void escreve_cabecalho_faixa(FILE* f_faixas, CabecalhoFaixa* cab);

/**
 *  Lê o estado do cabeçalho do arquivo de faixas para verificar o topo e nós reaproveitáveis.
 * pre-condicao: O arquivo de faixas deve estar devidamente inicializado no disco.
 * pos-condicao: Retorna um ponteiro alocado com a estrutura CabecalhoFaixa contendo as informações lidas.
 */
CabecalhoFaixa* le_cabecalho_faixa();

/**
 *  Grava uma faixa musical em uma posição específica do arquivo de faixas.
 * pre-condicao: 'f_faixas' aberto, 'f' apontando para uma estrutura FaixaPlaylist válida e 'pos' sendo uma posição adequada.
 * pos-condicao: O nó de faixa contendo o código da música e o ponteiro para o próximo elemento é gravado na posição especificada[cite: 21].
 */
void escreve_no_faixa(FILE* f_faixas, FaixaPlaylist* f, long pos);

/**
 *  Extrai do arquivo de faixas um nó localizado em determinada posição.
 * pre-condicao: 'pos' deve apontar para uma faixa armazenada de forma íntegra no arquivo.
 * pos-condicao: Retorna um ponteiro alocado com o objeto FaixaPlaylist lido da posição enviada.
 */
FaixaPlaylist* le_no_faixa(long pos);

/**
 *  Insere uma música do acervo no início da lista encadeada de uma playlist.
 * pre-condicao: Tanto o código da playlist quanto o código da música devem existir previamente nos seus respectivos arquivos[cite: 28].
 * pos-condicao: Aloca um nó de faixa (priorizando o reaproveitamento da lista de livres), aponta-o para o antigo início da playlist, atualiza a cabeça da playlist no arquivo de playlists e reconecta os ponteiros necessários[cite: 18, 28, 110].
 */
void adicionarMusicaInicioPlaylist(int codigo_playlist, int codigo_musica);

/**
 *  Insere uma música do acervo no final da lista encadeada de uma playlist.
 * pre-condicao: O código da playlist e o código da música informados devem ser válidos e existentes no sistema[cite: 27].
 * pos-condicao: Aloca um nó de faixa (reaproveitando espaço livre se disponível), anexa-o após o nó apontado por 'id_faixa_fim' da playlist, e atualiza o novo fim da playlist no arquivo correspondente[cite: 19, 27, 110].
 */
void adicionarMusicaFinalPlaylist(int codigo_playlist, int codigo_musica);

/**
 *  Remove uma música específica de dentro de uma playlist indicada.
 * pre-condicao: A playlist informada deve existir e conter a música que se deseja remover[cite: 29].
 * pos-condicao: Remove o nó da lista encadeada daquela playlist (ajustando os ponteiros anterior e próximo). O espaço físico do nó excluído é inserido no início da lista de nós livres gerenciada pelo cabeçalho do arquivo de faixas para posterior reaproveitamento[cite: 29, 110].
 */
void removerMusicaPlaylist(int codigo_playlist, int codigo_musica);

/**
 *  Imprime as músicas de uma playlist na ordem correta, buscando seus dados no acervo geral.
 * pre-condicao: O código da playlist deve existir no sistema[cite: 30].
 * pos-condicao: Imprime o título da playlist e, em seguida, percorre sua lista de faixas lendo os respectivos dados textuais (título e artista) diretamente do arquivo de músicas para exibi-los na tela[cite: 30].
 */
void imprimirMusicasDaPlaylist(int codigo_playlist);

/**
 *  Lista na tela todas as posições físicas de registros que foram excluídos e aguardam reaproveitamento.
 * pre-condicao: O arquivo de faixas deve estar inicializado.
 * pos-condicao: Percorre e exibe em formato de lista todas as posições em bytes (ou RRN) que fazem parte da lista encadeada de nós livres (`lista_livres`)[cite: 34, 110].
 */
void imprimirNosLivres();

#endif