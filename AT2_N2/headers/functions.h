#pragma once

#include <stdio.h>

#include "../headers/types.h"

void configurarAmbiente();
void pausarTela();
void limparTela();
void exibirMenu(FILE* file, Playlist* playlist);
void voltarAoMenu(FILE* file, Playlist* playlist);
void lerArquivo(FILE* arquivo, Playlist* playlist);
Playlist* criarPlaylist();
Node* criarNo(const char* artist, const char* song);
void exibirPlaylist(Playlist* playlist);
void adicionarArtista(Playlist* playlist, const char* artist, const char* song);
