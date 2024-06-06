#pragma once

#define CAMINHO_ARQUIVO "./musicas.txt"
#define true 1
#define false 0
#define ESQUERDA 75
#define DIREITA 77
#define ENTER 13

typedef struct No {
	char artista[100];
	char musica[100];
	struct No* prox;
	struct No* anterior;
} No;

typedef struct Playlist {
	struct No* topo;
	struct No* atual;
} Playlist;