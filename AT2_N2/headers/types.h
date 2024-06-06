#pragma once

#define CAMINHO_ARQUIVO "./musicas.txt"

typedef struct Node {
	char artista[100];
	char musica[100];
	struct Node* prox;
	struct Node* anterior;
} Node;

typedef struct Playlist {
	struct Node* topo;
	struct Node* atual;
} Playlist;