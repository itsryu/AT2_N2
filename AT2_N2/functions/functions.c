#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <windows.h>
#include <conio.h>

#include "../headers/types.h"
#include "../headers/functions.h"

No* criarNo(const char* artista, const char* musica) {
	No* no = (No*) malloc(sizeof(No));
	strcpy(no->artista, artista);
	strcpy(no->musica, musica);
	no->prox = no->anterior	 = no;

	return no;
}

Playlist* criarPlaylist() {
	Playlist* playlist = (Playlist*) malloc(sizeof(Playlist));
	playlist->topo = NULL;
	playlist->atual = NULL;

	return playlist;
}

void adicionarArtista(Playlist* playlist, const char* artist, const char* song) {
	No* novoNo = criarNo(artist, song);

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

    	atual = playlist->topo;

    	for (int i = 0; i < numMus; i++) {
        	aux[i] = atual;
        	atual = atual->prox;
    	}

    	for (int i = 0; i < numMus - 1; i++) {
        	for (int j = i + 1; j < numMus; j++) {
            	if (strcmp(aux[i]->musica, aux[j]->musica) > 0) {
					No* temp = aux[i];
                	aux[i] = aux[j];
                	aux[j] = temp;
            	}
        	}
    	}

    	for (int i = 0; i < numMus; i++) {
			if (aux[i] == musicaAtual) {
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

void lerArquivo(FILE* arquivo, Playlist* playlist) {
	char artista[100] = { "" }, musica[100] = { "" };

	while(fscanf(arquivo, "%[^;];%[^\n]\n", artista, musica) != EOF) {
		adicionarArtista(playlist, artista, musica);
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

void exibirMenu(FILE* arquivo, Playlist* playlist) {
	int opcao = 0;

	printf("---------- Sistema de playlist ----------\n\n");
	printf("1. Exibir a playlist\n");
	printf("2. Exibir a playlist ordenada\n");
	printf("3. Inserir nova música\n");
	printf("4. Remover uma música\n");
	printf("5. Buscar por determinada música\n");
	printf("8. Sair\n\n");
	printf("Escolha uma opção: ");

	while(scanf("%d", &opcao) != 1 && opcao < 0 || opcao > 8) {
		printf("Opção inválida. Tente novamente: ");
		while(getchar() != '\n');
	}

	switch(opcao) {
		case 1: {
			limparTela();

			No* atual = musicaAtual(playlist);

			exibirPlaylist(playlist, atual);

			int key = 0;

			while(true) {
				key = getch();

				if(key == 224) {
					switch(getch()) {
						case DIREITA: {
							atual = avancarMusica(playlist);
							limparTela();
							exibirPlaylist(playlist, atual);
							break;
						}
						case ESQUERDA: {
							atual = voltarMusica(playlist);
							limparTela();
							exibirPlaylist(playlist, atual);
							break;
						}
					}		
				} else if(key == ENTER) {
					break;
				}
			}

			voltarAoMenu(arquivo, playlist);

			break;
		}
		case 2: {
			limparTela();

			No* atual = musicaAtual(playlist);

			exibirPlaylistOrdenada(playlist, atual);

			int key = 0;

			while(true) {
				key = getch();

				if(key == 224) {
					switch(getch()) {
						case DIREITA: {
							atual = avancarMusica(playlist);
							limparTela();
							exibirPlaylistOrdenada(playlist, atual);
							break;
						}
						case ESQUERDA: {
							atual = voltarMusica(playlist);
							limparTela();
							exibirPlaylistOrdenada(playlist, atual);
							break;
						}
					}		
				} else if(key == ENTER) {
					break;
				}
			}

			voltarAoMenu(arquivo, playlist);

			break;
		}
		case 8:
		{
			limparTela();
			return;
		}
	}
}

//-------------------------------------------------------------------------------------------------------------------//

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