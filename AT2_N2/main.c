#include <stdio.h>

#include "./headers/types.h"
#include "./headers/functions.h"

int main(void) {
	configurarAmbiente();

	FILE* arquivo = fopen(CAMINHO_ARQUIVO, "r");

	if(arquivo == NULL) {
		printf("Não foi possivel abrir o arquivo. Encerrando o programa...\n");
		return 1;
	} else {
		Playlist* playlist = criarPlaylist();
		lerArquivo(arquivo, playlist);

		// Exibindo o menu;
		exibirMenu(arquivo, playlist);
	}

	// Fechando o arquivo e encerrando o programa;
	fclose(arquivo);
	printf("Programa encerrado com sucesso!\n");
	return 0;
}