#include <stdio.h>
#include <conio.h>

#include "../headers/types.h"
#include "../headers/functions.h"

void exibirMenu(FILE* arquivo, Playlist* playlist) {
	int opcao = 0;

	printf("---------- Sistema de playlist ----------\n\n");
	printf("1. Exibir a playlist\n");
	printf("2. Exibir a playlist ordenada\n");
	printf("3. Inserir nova música\n");
	printf("4. Remover uma música\n");
	printf("5. Buscar por determinada música\n");
	printf("6. Sair\n\n");
	printf("Escolha uma opção: ");

	while(scanf("%d", &opcao) != 1 || opcao < 1 || opcao > 6) {
		printf("Opção inválida. Tente novamente: ");
		while(getchar() != '\n');
	}

	switch(opcao) {
		case 1:
		{
			limparTela();

			No* atual = musicaAtual(playlist);

			exibirPlaylist(playlist, atual);

			int key = 0;

			while(true) {
				key = getch();

				if(key == 224) {
					switch(getch()) {
						case DIREITA:
						{
							atual = avancarMusica(playlist);
							limparTela();
							exibirPlaylist(playlist, atual);
							break;
						}
						case ESQUERDA:
						{
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
		case 2:
		{
			limparTela();

			No* atual = musicaAtual(playlist);

			exibirPlaylistOrdenada(playlist, atual);

			int key = 0;

			while(true) {
				key = getch();

				if(key == 224) {
					switch(getch()) {
						case DIREITA:
						{
							atual = avancarMusica(playlist);
							limparTela();
							exibirPlaylistOrdenada(playlist, atual);
							break;
						}
						case ESQUERDA:
						{
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
		case 3:
		{
			limparTela();

			char artista[100] = { "" }, musica[100] = { "" };

			printf("Digite o nome do artista: ");
			while(scanf(" %[^\n]", artista) != 1) {
				printf("Erro ao ler o nome do artista, tente novamente: ");
				while(getchar() != '\n');
			}

			printf("Nome da música: ");
			while(scanf(" %[^\n]", musica) != 1) {
				printf("Erro ao ler o nome da música, tente novamente: ");
				while(getchar() != '\n');
			}

			adicionarArtista(playlist, artista, musica);

			if(salvarArquivo(arquivo, playlist) == 0) {
				printf("Música adicionada com sucesso.\n");
			} else {
				printf("Erro ao adicionar a música.\n");
			}

			voltarAoMenu(arquivo, playlist);

			break;
		}
		case 4: {
			limparTela();

			char musica[100] = { "" };

			printf("Digite o nome da música a ser removida: ");
			while(scanf(" %[^\n]", musica) != 1) {
				printf("Erro ao ler o nome do artista, tente novamente: ");
				while(getchar() != '\n');
			}

			No* musicaEncontrada = encontrarMusica(playlist, musica);

			if(musicaEncontrada) {
				if(removerArtista(playlist, musicaEncontrada) == 0) {;
					salvarArquivo(arquivo, playlist);
					printf("Música removida com sucesso.\n");
				} else {
					printf("Erro ao remover a música. Playlist vazia\n");
				}
			} else {
				printf("Música não encontrada.\n");
			}

			voltarAoMenu(arquivo, playlist);

			break;
		}
		case 5: {
			limparTela();

			char musica[100] = { "" };

			printf("Digite o nome da música a ser buscada: ");
			while(scanf(" %[^\n]", musica) != 1) {
				printf("Erro ao ler o nome do artista, tente novamente: ");
				while(getchar() != '\n');
			}

			No* musicaEncontrada = encontrarMusica(playlist, musica);

			if(musicaEncontrada) {
				printf("Música encontrada: %s - %s\n", musicaEncontrada->artista, musicaEncontrada->musica);
			} else {
				printf("Música não encontrada.\n");
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