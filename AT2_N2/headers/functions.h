#pragma once

#include <stdio.h>

#include "../headers/types.h"

void configurarAmbiente();
void pausarTela();
void limparTela();
Playlist* criarPlaylist();
No* criarNo(const char* artista, const char* musica);
void exibirMenu(FILE* arquivo, Playlist* playlist);
void voltarAoMenu(FILE* arquivo, Playlist* playlist);
void lerArquivo(FILE* arquivo, Playlist* playlist);
int salvarArquivo(FILE* arquivo, Playlist* playlist);
void exibirPlaylist(Playlist* playlist, No* musicaAtual);
void exibirPlaylistOrdenada(Playlist* playlist, No* musicaAtual);
void adicionarArtista(Playlist* playlist, const char* artista, const char* musica);
No* encontrarMusica(Playlist* playlist, const char* musica);
int removerArtista(Playlist* playlist, No* musica);
No* voltarMusica(Playlist* playlist);
No* avancarMusica(Playlist* playlist);
No* musicaAtual(Playlist* playlist);
