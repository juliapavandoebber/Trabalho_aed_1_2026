#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "carregar.h"
#include "musica.h"
#include "playlist.h"
#include "faixa.h"

void carregarArquivoTexto(const char *nome_arquivo) {
    FILE *f_txt = fopen(nome_arquivo, "r");
    if (f_txt == NULL) {
        printf("Erro: Nao foi possivel abrir o arquivo texto '%s'.\n", nome_arquivo);
        return;
    }

    FILE *f_musica = abrir_arquivo_musica("rb+");
    FILE *f_playlist = abrir_arquivo_playlist("rb+");
    FILE *f_faixa = abrir_arquivo_faixas("rb+");

    if (!f_musica || !f_playlist || !f_faixa) {
        printf("Erro: Um ou mais arquivos binarios nao estao inicializados.\n");
        if (f_txt) fclose(f_txt);
        if (f_musica) fclose(f_musica);
        if (f_playlist) fclose(f_playlist);
        if (f_faixa) fclose(f_faixa);
        return;
    }

    char linha[256];
    int linha_atual = 0;

    printf("Processando arquivo '%s'...\n", nome_arquivo);

    while (fgets(linha, sizeof(linha), f_txt) != NULL) {
        linha_atual++;
        
        linha[strcspn(linha, "\n")] = '\0';

        if (strlen(linha) == 0) continue;
        
        char *token = strtok(linha, ";");
        if (token == NULL) continue;

        if (strcmp(token, "M") == 0) {
            Musica m;
            m.codigo = atoi(strtok(NULL, ";"));
            
            strncpy(m.titulo, strtok(NULL, ";"), 100);
            strncpy(m.artista, strtok(NULL, ";"), 51);
            
            m.ano = atoi(strtok(NULL, ";"));
            m.prox = NULO;

            cadastrar_musica(f_musica, m);
            printf("[Linha %d] Musica '%s' carregada.\n", linha_atual, m.titulo);
        } 
        else if (strcmp(token, "P") == 0) {
            int cod = atoi(strtok(NULL, ";"));
            char *titulo = strtok(NULL, ";");
            
            criar_playlist(f_playlist, cod, titulo);
            printf("[Linha %d] Playlist '%s' carregada.\n", linha_atual, titulo);
        }
        else if (strcmp(token, "I") == 0) {
            char *posicao = strtok(NULL, ";");
            int cod_playlist = atoi(strtok(NULL, ";"));
            int cod_musica = atoi(strtok(NULL, ";"));
            
            if (strcmp(posicao, "I") == 0) {
                adicionar_na_playlist_inicio(f_playlist, f_faixa, f_musica, cod_playlist, cod_musica);
                printf("[Linha %d] Musica %d adicionada no INICIO da playlist %d.\n", linha_atual, cod_musica, cod_playlist);
            } else if (strcmp(posicao, "F") == 0) {
                adicionar_na_playlist_fim(f_playlist, f_faixa, f_musica, cod_playlist, cod_musica);
                printf("[Linha %d] Musica %d adicionada no FIM da playlist %d.\n", linha_atual, cod_musica, cod_playlist);
            }
        }
        else if (strcmp(token, "R") == 0) {
            int cod_playlist = atoi(strtok(NULL, ";"));
            int cod_musica = atoi(strtok(NULL, ";"));
            
            remover_da_playlist(f_playlist, f_faixa, cod_playlist, cod_musica);
            printf("[Linha %d] Comando de remocao: Musica %d da playlist %d.\n", linha_atual, cod_musica, cod_playlist);
        }
        else {
            printf("[Linha %d] Comando '%s' desconhecido ignorado.\n", linha_atual, token);
        }
    }

    fclose(f_txt);
    fclose(f_musica);
    fclose(f_playlist);
    fclose(f_faixa);
    
    printf("\nCarregamento de dados finalizado com sucesso!\n");
}