#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "carregar.h"
#include "faixa.h"
#include "musica.h"
#include "playlist.h"

int main(){
    int menu, leitura_de_numeros;
    FILE *f_musica = NULL;
    FILE *f_playlist = NULL;
    FILE *f_faixa = NULL;
    
    iniciar_musica();
    iniciar_playlists();
    iniciar_faixas();

    do{
        printf ("\n\n=============================================\n");
        printf ("Escolha uma das opcoes: \n");
        printf ("\t1 - Cadastrar musica\n");
        printf ("\t2 - Imprimir dados da musica\n");
        printf ("\t3 - Listar Acervo\n");
        printf ("\t4 - Criar playlist\n");
        printf ("\t5 - Adicionar musica do acervo no começo de uma playlist\n");
        printf ("\t6 - Adicionar musica do acervo no final de uma playlist\n");
        printf ("\t7 - Remover musica da playlist\n");
        printf ("\t8 - Imprimir as musicas de uma playlist especifica\n");
        printf ("\t9 - Imprimir lista de playlist\n");
        printf ("\t10 - Carregar arquivos\n");
        printf ("\t11 - Imprimir nos livres\n");
        printf ("\t0 - Sair\n");
        printf ("=============================================\n\n");

        leitura_de_numeros = scanf("%d", &menu);

        if(leitura_de_numeros == 0){
            while(getchar() != '\n');
            menu = -1;
        }
        else{
            while(getchar() != '\n');
        }

        switch (menu){
            case 0:
                printf ("Finalizando programa...\n");
                break;
                
            case 1: {
                Musica m;
                printf("Digite o codigo da musica: ");
                scanf("%d%*c", &m.codigo);
                
                printf("Digite o titulo da musica: ");
                fgets(m.titulo, sizeof(m.titulo), stdin);
                m.titulo[strcspn(m.titulo, "\n")] = '\0';
                
                printf("Digite o artista: ");
                fgets(m.artista, sizeof(m.artista), stdin);
                m.artista[strcspn(m.artista, "\n")] = '\0';
                
                printf("Digite o ano de lancamento: ");
                scanf("%d%*c", &m.ano);
                
                f_musica = abrir_arquivo_musica("rb+");
                if (f_musica != NULL) {
                    cadastrar_musica(f_musica, m);
                    fclose(f_musica);
                } else {
                    printf("Erro ao abrir arquivo de musicas.\n");
                }
                break;
            }
            
            case 2: {
                int id_musica;
                printf("Digite o codigo da musica para buscar: ");
                scanf("%d%*c", &id_musica);
                
                f_musica = abrir_arquivo_musica("rb");
                if (f_musica != NULL) {
                    imprimir_dados_musica(f_musica, id_musica);
                    fclose(f_musica);
                } else {
                    printf("Erro ao abrir arquivo de musicas.\n");
                }
                break;
            }
            
            case 3: {
                f_musica = abrir_arquivo_musica("rb");
                if (f_musica != NULL) {
                    listar_acervo(f_musica);
                    fclose(f_musica);
                } else {
                    printf("Erro ao abrir arquivo de musicas.\n");
                }
                break;
            }
            
            case 4: {
                int codigo;
                char titulo[51];
                
                printf("Digite o codigo da playlist: ");
                scanf("%d%*c", &codigo);
                
                printf("Digite o titulo da playlist: ");
                fgets(titulo, sizeof(titulo), stdin);
                titulo[strcspn(titulo, "\n")] = '\0';
                
                f_playlist = abrir_arquivo_playlist("rb+");
                if (f_playlist != NULL) {
                    criar_playlist(f_playlist, codigo, titulo);
                    fclose(f_playlist);
                } else {
                    printf("Erro ao abrir arquivo de playlists.\n");
                }
                break;
            }
            
            case 5: {
                int cod_playlist, cod_musica;

                printf("Codigo da playlist: ");
                scanf("%d", &cod_playlist);

                printf("Codigo da musica: ");
                scanf("%d", &cod_musica);

                adicionar_na_playlist_inicio(
                    f_playlist,
                    f_faixa,
                    f_musica,
                    cod_playlist,
                    cod_musica
                );

                break;
            }
            
            case 6: {
                int cod_playlist, cod_musica;

                printf("Codigo da playlist: ");
                scanf("%d", &cod_playlist);

                printf("Codigo da musica: ");
                scanf("%d", &cod_musica);

                adicionar_na_playlist_fim(
                    f_playlist,
                    f_faixa,
                    f_musica,
                    cod_playlist,
                    cod_musica
                );

                break;
            }

            case 7: {
                int id_musica, id_playlist;
                printf("Digite o codigo da playlist: ");
                scanf("%d%*c", &id_playlist);
                printf("Digite o codigo da musica a ser removida: ");
                scanf("%d%*c", &id_musica);
                
                f_playlist = abrir_arquivo_playlist("rb+");
                f_faixa = abrir_arquivo_faixas("rb+"); // CORREÇÃO: Usando a sua função padronizada
                
                if (f_playlist && f_faixa) {
                    remover_da_playlist(f_playlist, f_faixa, id_playlist, id_musica);
                } else {
                    printf("Erro ao abrir os arquivos necessarios.\n");
                }
                
                if(f_playlist) fclose(f_playlist);
                if(f_faixa) fclose(f_faixa);
                break;
            }
            
            case 8: {
                int id_playlist;
                printf("Digite o codigo da playlist: ");
                scanf("%d%*c", &id_playlist);
                
                f_playlist = abrir_arquivo_playlist("rb");
                f_faixa = abrir_arquivo_faixas("rb");
                f_musica = abrir_arquivo_musica("rb");
                
                if (f_playlist && f_faixa && f_musica) {
                    imprimir_playlist_especifica(f_playlist, f_faixa, f_musica, id_playlist);
                } else {
                    printf("Erro ao abrir os arquivos necessarios.\n");
                }
                
                if(f_playlist) fclose(f_playlist);
                if(f_faixa) fclose(f_faixa);
                if(f_musica) fclose(f_musica);
                break;
            }
            
            case 9: {
                f_playlist = abrir_arquivo_playlist("rb");
                if (f_playlist != NULL) {
                    imprimir_lista_playlists(f_playlist);
                    fclose(f_playlist);
                } else {
                    printf("Erro ao abrir arquivo de playlists.\n");
                }
                break;
            }
            
            case 10: {
                char nome_arquivo[100];
                printf("Digite o nome do arquivo texto a ser carregado: ");
                fgets(nome_arquivo, sizeof(nome_arquivo), stdin);
                nome_arquivo[strcspn(nome_arquivo, "\n")] = '\0';
                
                carregarArquivoTexto(nome_arquivo);
                break;
            }
            
            case 11: {
                f_faixa = abrir_arquivo_faixas("rb");
                if (f_faixa != NULL) {
                    imprimir_nos_livres(f_faixa);
                    fclose(f_faixa);
                } else {
                    printf("Erro ao abrir arquivo de faixas.\n");
                }
                break;
            }
            
            default:
                printf ("Opcao invalida!\n");
                break;
        }
    } while(menu != 0);

    return 0;
}