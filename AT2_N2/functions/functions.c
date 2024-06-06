#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <windows.h>

#include "../headers/types.h"
#include "../headers/functions.h"

No* criarNo(const char* artista, const char* musica) {
	No* no = (No*) malloc(sizeof(No));

	if(no == NULL) {
		return NULL;
	} else {
		strcpy(no->artista, artista);
		strcpy(no->musica, musica);
		no->prox = no->anterior = no;

		return no;
	}
}

Playlist* criarPlaylist() {
	Playlist* playlist = (Playlist*) malloc(sizeof(Playlist));

	if(playlist == NULL) {
		return NULL;
	} else {
		playlist->topo = NULL;
		playlist->atual = NULL;

		return playlist;
	}
}

void adicionarArtista(Playlist* playlist, const char* artista, const char* musica) {
	No* novoNo = criarNo(artista, musica);

	if(!playlist->topo) {
		playlist->topo = novoNo;
		playlist->atual = novoNo;
	} else {
		No* aux = playlist->topo->anterior;
		aux->prox = novoNo;

		novoNo->anterior = aux;
		novoNo->prox = playlist->topo;
		playlist->topo->anterior = novoNo;
	}
}

No* encontrarArtista(Playlist* playlist, const char* musica) {
	if(!playlist->topo) {
		return NULL;
	} else {
		No* atual = playlist->topo;

		do {
			if(strcmp(atual->musica, musica) == 0) return atual;
			atual = atual->prox;
		} while(atual != playlist->topo);

		return NULL;
	}
}

int removerArtista(Playlist* playlist, const char* musica) {
	if(!playlist->topo) {
		return 0;
	} else {
		No* atual = playlist->topo;

		do {
			if(strcmp(atual->musica, musica) == 0) {
				if(atual == playlist->topo) {
					if(playlist->topo->prox == playlist->topo) {
						free(playlist->topo);
						playlist->topo = NULL;
						playlist->atual = NULL;
					} else {
						No* aux = playlist->topo->anterior;
						playlist->topo = playlist->topo->prox;
						playlist->topo->anterior = aux;
						aux->prox = playlist->topo;

						free(atual);
					}
				} else {
					atual->anterior->prox = atual->prox;
					atual->prox->anterior = atual->anterior;
					free(atual);
				}
				return 1;
			}
			atual = atual->prox;
		} while(atual != playlist->topo);
	}

	return 0;
}

void exibirPlaylist(Playlist* playlist, No* musicaAtual) {
	if(!playlist->topo) {
		printf("Playlist vazia!\n");
		return;
	} else {
		No* current = playlist->topo;
		
		do {
			if(current == musicaAtual) {
				printf("-> ");
			} else {
				printf("   ");
			}

			printf("%s - %s\n", current->musica, current->artista);
			current = current->prox;
		} while(current != playlist->topo);

		printf("\n");
	}
}

void exibirPlaylistOrdenada(Playlist* playlist, No* musicaAtual) {
    if (!playlist->topo) {
		printf("Playlist vazia!\n");
		return;
	} else {
		No* atual = playlist->topo;
		int numMus = 0;

    	do {
        	numMus++;
        	atual = atual->prox;
    	} while (atual != playlist->topo);

		No** aux = (No**) malloc(numMus * sizeof(No*));

		if(aux == NULL) {
			return;
		} else {
			atual = playlist->topo;

			for(int i = 0; i < numMus; i++) {
				aux[i] = atual;
				atual = atual->prox;
			}

			for(int i = 0; i < numMus - 1; i++) {
				for(int j = i + 1; j < numMus; j++) {
					if(strcmp(aux[i]->musica, aux[j]->musica) > 0) {
						No* temp = aux[i];
						aux[i] = aux[j];
						aux[j] = temp;
					}
				}
			}

			for(int i = 0; i < numMus; i++) {
				if(aux[i] == musicaAtual) {
					printf("-> ");
				} else {
					printf("   ");
				}

				printf("%s - %s\n", aux[i]->musica, aux[i]->artista);
			}

			printf("\n");

			free(aux);
		}
	}
}

void lerArquivo(FILE* arquivo, Playlist* playlist) {
	char artista[100] = { "" }, musica[100] = { "" };

	while(fscanf(arquivo, "%[^;];%[^\n]\n", artista, musica) != EOF) {
		adicionarArtista(playlist, artista, musica);
	}
}

int salvarArquivo(FILE* arquivo, Playlist* playlist) {
    arquivo = fopen(CAMINHO_ARQUIVO, "w");

    if (arquivo == NULL) {
        return 1;
	} else {
		No* atual = playlist->topo;

		if(atual) {
			do {
				fprintf(arquivo, "%s;%s\n", atual->artista, atual->musica);
				atual = atual->prox;
			} while(atual != playlist->topo);
		}

		fclose(arquivo);
		return 0;
	}
}

No* avancarMusica(Playlist* playlist) {
    if (playlist->atual) {
        playlist->atual = playlist->atual->prox;
    }

    return playlist->atual;
}

No* voltarMusica(Playlist* playlist) {
    if (playlist->atual) {
        playlist->atual = playlist->atual->anterior;
    }

    return playlist->atual;
}

No* musicaAtual(Playlist* playlist) {
	return playlist->atual;
}

//-------------------------------------------------------------------------------------------------------------------//

// Exibe o menu;
void voltarAoMenu(FILE* arquivo, Playlist* playlist) {
	pausarTela();
	limparTela();
	exibirMenu(arquivo, playlist);
}

// Limpa a tela do console;
void limparTela() {
	#ifdef _WIN32
		system("cls");
	#endif
}

// Pausa a tela do console;
void pausarTela() {
	#ifdef _WIN32
		system("pause");
	#endif
}

// Configura o ambiente de execu��o;
void configurarAmbiente() {
	#ifdef _WIN32
		system("color 0A");
		system("title Sistema de Playlist");
	#endif

	char* local = setlocale(LC_ALL, "");

	if(local == NULL || strcmp(local, "Portuguese_Brazil.1252") != 0) {
		#ifdef _WIN32
			setlocale(LC_ALL, "Portuguese");
		#endif
	}

	SetConsoleOutputCP(1252);
}