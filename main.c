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
    
    iniciar_musica();
    iniciar_playlist();
    iniciar_faixa();

    do{
        printf ("\n\n=============================================\n");
        printf ("Escolha uma das opcoes: \n");
        printf ("\t1 - Cadastrar música\n");
        printf ("\t2 - Imprimir dados da música\n");
        printf ("\t3 - Listar Acervo\n");
        printf ("\t4 - Criar playlist\n");
        printf ("\t5 - Adicionar música do acervo no final de uma playlist\n");
        printf ("\t6 - Remover música da playlist\n");
        printf ("\t7 - Imprimir as músicas de uma playlist específica\n");
        printf ("\t8 - Imprimir lista de playlist\n");
        printf ("\t9 - Carregar arquivos\n");
        printf ("\t10 - Imprimir nós livres\n");
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
            case 1:
                cadastrarLivro();
                break;
            case 2: {
                int buscar;
                printf ("Digite o codigo do livro para buscar as informaçoes");
                scanf ("%d%*c", &buscar);
                imprimirLivro(buscar);
                break;
            }
            case 3:{
                char titulo_buscar [51];
                printf ("Digite o titulo do livro para buscar as informaçoes");
                fgets(titulo_buscar, sizeof(titulo_buscar), stdin);
                titulo_buscar[strcspn(titulo_buscar, "\n")] = '\0';
                buscarLivroPorTitulo(titulo_buscar);
                break;
            }
            case 4:
                listarLivros();
                break;
            case 5: {
                int qnt = contarTotalLivros();
                int titulos = contarTitulosCadastrado();
                printf("Total de livros cadastrados: %d\n", qnt);
                printf("Total de titulos cadastrados: %d\n", titulos);
                break;
            }
            case 6: {
                Cadastrar_user();
                break;
            }
            case 7: {
                cadastrarEmprestimo();
                break;
            }
            case 8: {
                cadastrarDevolucao();
                break;
            }
            case 9: {
                listarEmprestimo();
                break;
            }
            case 10:{
                char nome_arquivo[100];
                printf("Digite o nome do arquivo a ser carregado: ");
                fgets(nome_arquivo, sizeof(nome_arquivo), stdin);
                nome_arquivo[strcspn(nome_arquivo, "\n")] = '\0';
                carregarArquivoTexto(nome_arquivo);
                atualizarExemplaresAposCarregamento();
                break;
            }
            default:
                printf ("Opcao invalida!\n");
                break;
        }
    } while(menu != 0);

    return 0;
}