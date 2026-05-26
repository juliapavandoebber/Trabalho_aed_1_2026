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