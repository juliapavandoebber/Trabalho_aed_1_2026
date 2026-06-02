#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "musica.h"
#include "playlist.h"
#include "faixa.h"
#include "carregar.h"

void carregarArquivoTexto(const char *nome_arquivo){
    FILE *arquivo = fopen(nome_arquivo, "r");

    if(arquivo == NULL){
        perror("Erro ao abrir arquivo");
        return;
    }

    FILE *f_musicas = abrir_arquivo_musica("rb+");
    FILE *f_playlists = abrir_arquivo_playlist("rb+");
    FILE *f_faixas = abrir_arquivo_faixas("rb+");

    char linha[512];

    while(fgets(linha,sizeof(linha),arquivo)){

        linha[strcspn(linha,"\r\n")] = '\0';

        char *token = strtok(linha,";");

        if(token == NULL)
            continue;

        /* M;codigo;titulo;artista;ano */
        if(strcmp(token,"M") == 0){

            int codigo = atoi(strtok(NULL,";"));
            char *titulo = strtok(NULL,";");
            char *artista = strtok(NULL,";");
            int ano = atoi(strtok(NULL,";"));

            Musica musica;

            if(!buscar_musica_por_codigo(f_musicas,codigo,&musica)){
                cadastrar_musica(
                    f_musicas,
                    codigo,
                    titulo,
                    artista,
                    ano
                );
            }
        }

        /* P;codigo;titulo */
        else if(strcmp(token,"P") == 0){

            int codigo = atoi(strtok(NULL,";"));
            char *titulo = strtok(NULL,";");

            criar_playlist(
                f_playlists,
                codigo,
                titulo
            );
        }

        /* I;I;playlist;musica
           I;F;playlist;musica */
        else if(strcmp(token,"I") == 0){

            char *tipo = strtok(NULL,";");
            int cod_playlist = atoi(strtok(NULL,";"));
            int cod_musica = atoi(strtok(NULL,";"));

            if(strcmp(tipo,"I") == 0){

                adicionar_na_playlist_inicio(
                    f_playlists,
                    f_faixas,
                    f_musicas,
                    cod_playlist,
                    cod_musica
                );
            }
            else if(strcmp(tipo,"F") == 0){

                adicionar_na_playlist_fim(
                    f_playlists,
                    f_faixas,
                    f_musicas,
                    cod_playlist,
                    cod_musica
                );
            }
        }

        /* R;playlist;musica */
        else if(strcmp(token,"R") == 0){

            int cod_playlist = atoi(strtok(NULL,";"));
            int cod_musica = atoi(strtok(NULL,";"));

            remover_da_playlist(
                f_playlists,
                f_faixas,
                cod_playlist,
                cod_musica
            );
        }
    }

    fclose(f_musicas);
    fclose(f_playlists);
    fclose(f_faixas);
    fclose(arquivo);
}