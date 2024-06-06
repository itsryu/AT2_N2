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
No* criarNo(const char* artist, const char* song);
void exibirPlaylist(Playlist* playlist, No* musicaAtual);
void exibirPlaylistOrdenada(Playlist* playlist, No* musicaAtual);
void adicionarArtista(Playlist* playlist, const char* artist, const char* song);
No* voltarMusica(Playlist* playlist);
No* avancarMusica(Playlist* playlist);
No* musicaAtual(Playlist* playlist);
