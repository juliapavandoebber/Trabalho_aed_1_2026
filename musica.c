#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "musica.h"

//Abre o arquivo de musicas de acordo com o modo desejado
//pre-condicao: 
//pos-condicao:
FILE* abrir_arquivo_musica(const char* modo){
    FILE* f = fopen(ARQUIVO_MUSICA, modo);

    if(f == NULL){
        perror("Erro ao abrir o arquivo de musicas");
        exit(1);
    }

    return f;
}

void iniciar_musica(){
    FILE* f_musica = fopen(ARQUIVO_MUSICA, "rb+");
    if(f_musica == NULL){
        printf("Arquivo musica nao encontrado. Criando um novo...\n");
        f_musica = fopen(ARQUIVO_MUSICA, "wb+");
        if(f_musica == NULL){
            perror("Erro fatal: Nao foi possivel abrir/criar arquivo musica");
            exit(1);
        }
        criar_lista_vazia_musica(f_musica);
    }
    fclose(f_musica);
}

