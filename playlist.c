#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "playlist.h"
#include "faixa.h"
#include "musica.h"

FILE* abrir_arquivo_playlist(const char* modo) {
    return fopen(ARQUIVO_PLAYLIST, modo);
}

void criar_lista_vazia_playlist(FILE* f_play) {
    CabecalhoPlaylist cab;
    cab.cabeca = NULO;
    cab.topo = sizeof(CabecalhoPlaylist);
    escrever_cabecalho_playlist(f_play, cab);
}

void iniciar_playlists() {
    FILE* f = abrir_arquivo_playlist("rb");
    if (f == NULL) {
        f = abrir_arquivo_playlist("wb+");
        if (f != NULL) {
            criar_lista_vazia_playlist(f);
            fclose(f);
        } else {
            printf("Erro ao criar o arquivo de playlists!\n");
        }
    } else {
        fclose(f);
    }
}

CabecalhoPlaylist ler_cabecalho_playlist(FILE *f_play) {
    CabecalhoPlaylist cab;
    fseek(f_play, 0, SEEK_SET);
    fread(&cab, sizeof(CabecalhoPlaylist), 1, f_play);
    return cab;
}

void escrever_cabecalho_playlist(FILE *f_play, CabecalhoPlaylist cab) {
    fseek(f_play, 0, SEEK_SET);
    fwrite(&cab, sizeof(CabecalhoPlaylist), 1, f_play);
}

Playlist ler_playlist(FILE *f_play, long pos) {
    Playlist p;
    fseek(f_play, pos, SEEK_SET);
    fread(&p, sizeof(Playlist), 1, f_play);
    return p;
}

void escrever_playlist(FILE *f_play, long pos, Playlist p) {
    fseek(f_play, pos, SEEK_SET);
    fwrite(&p, sizeof(Playlist), 1, f_play);
}

int buscar_playlist_por_codigo(FILE *f_play, int codigo_playlist, Playlist *saida, long *pos_offset) {
    CabecalhoPlaylist cab = ler_cabecalho_playlist(f_play);
    long atual = cab.cabeca;
    
    while (atual != NULO) {
        *saida = ler_playlist(f_play, atual);
        if (saida->codigo == codigo_playlist) {
            if (pos_offset != NULL) *pos_offset = atual;
            return 1;
        }
        atual = saida->prox;
    }
    return 0;
}

int criar_playlist(FILE *f_play, int codigo, const char *titulo) {
    Playlist existente;
    if (buscar_playlist_por_codigo(f_play, codigo, &existente, NULL)) {
        printf("Erro: Ja existe uma playlist com o codigo %d.\n", codigo);
        return 0;
    }

    CabecalhoPlaylist cab = ler_cabecalho_playlist(f_play);
    Playlist nova;
    nova.codigo = codigo;
    strncpy(nova.titulo, titulo, 50);
    nova.titulo[50] = '\0';
    nova.id_faixa_ini = NULO;
    nova.id_faixa_fim = NULO;
    nova.prox = NULO;

    long pos_nova = cab.topo;
    cab.topo += sizeof(Playlist);

    if (cab.cabeca == NULO) {
        cab.cabeca = pos_nova;
    } else {
        long atual = cab.cabeca;
        Playlist temp;
        while (atual != NULO) {
            temp = ler_playlist(f_play, atual);
            if (temp.prox == NULO) break;
            atual = temp.prox;
        }
        temp.prox = pos_nova;
        escrever_playlist(f_play, atual, temp);
    }

    escrever_playlist(f_play, pos_nova, nova);
    escrever_cabecalho_playlist(f_play, cab);
    printf("Playlist '%s' criada com sucesso!\n", nova.titulo);
    
    return 1;
}

void imprimir_lista_playlists(FILE *f_play) {
    CabecalhoPlaylist cab = ler_cabecalho_playlist(f_play);
    long atual = cab.cabeca;
    
    printf("\n--- Lista de Playlists ---\n");
    if (atual == NULO) {
        printf("Nenhuma playlist cadastrada.\n");
    } else {
        while (atual != NULO) {
            Playlist p = ler_playlist(f_play, atual);
            printf("Cod: %d | Titulo: %s\n", p.codigo, p.titulo);
            atual = p.prox;
        }
    }
    printf("--------------------------\n");
}

void imprimir_playlist_especifica(FILE *f_play, FILE *arq_faixas, FILE *arq_musicas, int codigo_playlist) {
    Playlist p;
    if (!buscar_playlist_por_codigo(f_play, codigo_playlist, &p, NULL)) {
        printf("Playlist nao encontrada.\n");
        return;
    }
    
    printf("\n--- Playlist: %s (Cod: %d) ---\n", p.titulo, p.codigo);
    long atual = p.id_faixa_ini;
    
    if (atual == NULO) {
        printf("Esta playlist esta vazia.\n");
    } else {
        while (atual != NULO) {
            FaixaPlaylist f = ler_faixa(arq_faixas, atual);
            Musica m;
            
            if (buscar_musica_por_codigo(arq_musicas, f.codigo_musica, &m)) {
                printf("[%d] %s - %s (%d)\n", m.codigo, m.titulo, m.artista, m.ano);
            } else {
                printf("[Aviso] Musica com codigo %d nao encontrada no acervo.\n", f.codigo_musica);
            }
            atual = f.prox;
        }
    }
    printf("--------------------------------\n");
}

void adicionar_na_playlist_inicio(FILE *f_play, FILE *f_faixas, FILE *f_musicas, int codigo_playlist, int codigo_musica) {
    Playlist p; long pos_p;
    if (!buscar_playlist_por_codigo(f_play, codigo_playlist, &p, &pos_p)) {
        printf("Playlist nao encontrada.\n"); return;
    }
    
    Musica m;
    if (!buscar_musica_por_codigo(f_musicas, codigo_musica, &m)) {
        printf("Musica nao encontrada no acervo geral.\n"); return;
    }
    
    long pos_nova_faixa = alocar_faixa(f_faixas, codigo_musica);
    FaixaPlaylist nova_faixa = ler_faixa(f_faixas, pos_nova_faixa);
    
    nova_faixa.prox = p.id_faixa_ini;
    escrever_faixa(f_faixas, pos_nova_faixa, nova_faixa);
    
    // Atualiza a playlist
    p.id_faixa_ini = pos_nova_faixa;
    if (p.id_faixa_fim == NULO) {
        p.id_faixa_fim = pos_nova_faixa;
    }
    
    escrever_playlist(f_play, pos_p, p);
    printf("Musica '%s' adicionada no INICIO da playlist '%s'.\n", m.titulo, p.titulo);
}

void adicionar_na_playlist_fim(FILE *f_play, FILE *f_faixas, FILE *f_musicas, int codigo_playlist, int codigo_musica) {
    Playlist p; long pos_p;
    if (!buscar_playlist_por_codigo(f_play, codigo_playlist, &p, &pos_p)) {
        printf("Playlist nao encontrada.\n"); return;
    }
    
    Musica m;
    if (!buscar_musica_por_codigo(f_musicas, codigo_musica, &m)) {
        printf("Musica nao encontrada no acervo geral.\n"); return;
    }
    
    long pos_nova_faixa = alocar_faixa(f_faixas, codigo_musica);
    
    if (p.id_faixa_ini == NULO) {
        p.id_faixa_ini = pos_nova_faixa;
        p.id_faixa_fim = pos_nova_faixa;
    } else {
        FaixaPlaylist ultima = ler_faixa(f_faixas, p.id_faixa_fim);
        ultima.prox = pos_nova_faixa;
        escrever_faixa(f_faixas, p.id_faixa_fim, ultima);
        p.id_faixa_fim = pos_nova_faixa;
    }
    
    escrever_playlist(f_play, pos_p, p);
    printf("Musica '%s' adicionada no FIM da playlist '%s'.\n", m.titulo, p.titulo);
}

void remover_da_playlist(FILE *f_play, FILE *f_faixa, int codigo_playlist, int codigo_musica) {
    Playlist p; long pos_p;
    if (!buscar_playlist_por_codigo(f_play, codigo_playlist, &p, &pos_p)) {
        printf("Playlist nao encontrada.\n"); return;
    }

    long atual = p.id_faixa_ini;
    long ant = NULO;
    FaixaPlaylist f;

    while (atual != NULO) {
        f = ler_faixa(f_faixa, atual);
        
        if (f.codigo_musica == codigo_musica) {
            if (ant == NULO) { 
                p.id_faixa_ini = f.prox;
            } else { 
                FaixaPlaylist faixa_ant = ler_faixa(f_faixa, ant);
                faixa_ant.prox = f.prox;
                escrever_faixa(f_faixa, ant, faixa_ant);
            }
            
            if (atual == p.id_faixa_fim) { 
                p.id_faixa_fim = ant;
            }
            
            escrever_playlist(f_play, pos_p, p);
            liberar_faixa(f_faixa, atual);
            printf("Musica %d removida da playlist com sucesso.\n", codigo_musica);
            return;
        }
        ant = atual;
        atual = f.prox;
    }
    printf("Musica com codigo %d nao esta nesta playlist.\n", codigo_musica);
}