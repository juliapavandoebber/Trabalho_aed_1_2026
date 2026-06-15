#ifndef CARREGAR_H
#define CARREGAR_H

// Carrega um conjunto de operacoes a partir de um arquivo texto.
// pre-condicao: nome_arquivo deve referenciar um arquivo texto valido, seguindo a sintaxe especificada no trabalho. Os arquivos binarios de musicas, playlists e faixas devem existir e estar devidamente inicializados.
// pos-condicao: todas as operacoes presentes no arquivo sao processadas, atualizando os arquivos binarios de musicas, playlists e faixas conforme os comandos encontrados.
void carregarArquivoTexto(const char *nome_arquivo);

#endif // CARREGAR_H