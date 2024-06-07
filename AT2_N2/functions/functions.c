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

No* encontrarMusica(Playlist* playlist, const char* musica) {
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

int removerArtista(Playlist* playlist, No* musica) {
	if(!playlist->topo) {
		return 1;
	} else {
		if(musica == playlist->topo) {
			if(playlist->topo->prox == playlist->topo) {
				free(playlist->topo);

				playlist->topo = NULL;
				playlist->atual = NULL;
			} else {
				No* aux = playlist->topo->anterior;

				playlist->topo = playlist->topo->prox;
				playlist->topo->anterior = aux;
				aux->prox = playlist->topo;

				free(musica);
			}
		} else {
			musica->anterior->prox = musica->prox;
			musica->prox->anterior = musica->anterior;

			free(musica);
		}

		return 0;
	}
}

static void formatarLinha(char *dest, const char *src, int tamanho) {
    int lenSrc = strlen(src);

    if (lenSrc > tamanho) {
        strncpy(dest, src, tamanho - 3);
        dest[tamanho - 3] = '\0';
        strcat(dest, "...");
    } else {
        strcpy(dest, src); 
    }
}

void exibirPlaylist(Playlist* playlist, No* musicaAtual) {
	if(!playlist->topo) {
		printf("Playlist vazia!\n");
		return;
	} else {
		No* current = playlist->topo;

		printf("---------- Músicas adicionadas ----------\n\n");
		
		do {
			if(current == musicaAtual) {
				printf("-> ");
			} else {
				printf("   ");
			}

			printf("%s - %s\n", current->musica, current->artista);
			current = current->prox;
		} while(current != playlist->topo);

		int largura = 32;
    	char musica[120] = {0}, artista[120] = {0}; 
    		
		formatarLinha(musica, musicaAtual->musica, largura);
    	formatarLinha(artista, musicaAtual->artista, largura);

		printf("\n+------------------------------------+\n");
		printf("|                                    |\n");
		printf("|    %-32s|\n", musica);
		printf("|    %-32s|\n", artista);
		printf("|                                    |\n");
		printf("|           |<    ||    >|           |\n");
		printf("+------------------------------------+\n\n");

		printf("\n\nUtilize as setas do teclado (<- / ->) para mudar de música.\n");
		printf("Pressione ENTER para voltar.");

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

			printf("---------- Músicas adicionadas ----------\n\n");

			for(int i = 0; i < numMus; i++) {
				if(aux[i] == musicaAtual) {
					printf("-> ");
				} else {
					printf("   ");
				}

				printf("%s - %s\n", aux[i]->musica, aux[i]->artista);
			}

			int largura = 32;
    		char musica[120] = {0}, artista[120] = {0}; 
    		
			formatarLinha(musica, musicaAtual->musica, largura);
    		formatarLinha(artista, musicaAtual->artista, largura);

			printf("\n+------------------------------------+\n");
			printf("|                                    |\n");
			printf("|    %-32s|\n", musica);
			printf("|    %-32s|\n", artista);
			printf("|                                    |\n");
			printf("|           |<    ||    >|           |\n");
			printf("+------------------------------------+\n\n");

			printf("\n\nUtilize as setas do teclado (<- / ->) para mudar de música.\n");
			printf("Pressione ENTER para voltar.");

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

// Configura o ambiente de execução;
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