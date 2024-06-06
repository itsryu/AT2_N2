#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#include "../headers/types.h"
#include "../headers/functions.h"

Node* criarNo(const char* artista, const char* musica) {
	Node* no = (Node*) malloc(sizeof(Node));
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
	Node* novoNo = criarNo(artist, song);

	if(!playlist->topo) {
		playlist->topo = novoNo;
		playlist->atual = novoNo;
	} else {
		Node* aux = playlist->topo->anterior;
		aux->prox = novoNo;

		novoNo->anterior = aux;
		novoNo->prox = playlist->topo;
		playlist->topo->anterior = novoNo;
	}
}

void exibirPlaylist(Playlist* playlist) {
	if(!playlist->topo) {
		printf("Playlist vazia!\n");
		return;
	} else {
		Node* current = playlist->topo;

		do {
			printf("%s - %s\n", current->artista, current->musica);
			current = current->prox;
		} while(current != playlist->topo);

		printf("\n");
	}
}

void lerArquivo(FILE* arquivo, Playlist* playlist) {
	char artista[100] = { "" }, musica[100] = { "" };

	while(fscanf(arquivo, "%[^;];%[^\n]\n", artista, musica) != EOF) {
		adicionarArtista(playlist, artista, musica);
	}
}

void exibirMenu(FILE* arquivo, Playlist* playlist) {
	int opcao = 0;

	printf("---------- Sistema de playlist ----------\n\n");
	printf("1. Exibir a playlist\n");
	printf("2. Exibir a playlist ordenada\n");
	printf("3. Inserir nova música\n");
	printf("4. Remover uma música\n");
	printf("5. Buscar por determinada música\n");
	printf("6. Avançar para próxima música\n");
	printf("7. Retornar a música anterior\n");
	printf("8. Sair\n\n");
	printf("Escolha uma opção: ");

	while(scanf("%d", &opcao) != 1 && opcao < 0 || opcao > 8) {
		printf("Opção inválida. Tente novamente: ");
		while(getchar() != '\n');
	}

	switch(opcao) {
		case 1:
		{
			limparTela();
			exibirPlaylist(playlist);
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

void voltarAoMenu(FILE* file, Playlist* playlist) {
	pausarTela();
	limparTela();
	exibirMenu(file, playlist);
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
		system("title Gerenciamento de Hotel");
	#endif

	char* local = setlocale(LC_ALL, "");

	if(local == NULL || strcmp(local, "Portuguese_Brazil.1252") != 0) {
		#ifdef _WIN32
			setlocale(LC_ALL, "Portuguese");
		#endif
	}
}