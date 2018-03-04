#ifndef CSFML_H
#define CSFML_H
#include <SFML/System.h>
#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "cenario.h"
#include "personagens.h"

typedef struct {
    sfClock * clock;
    sfClock * tempoTiro;
    sfClock * sobeNivel;
    sfClock * tempoMusica;
    sfRenderWindow * janela;
    sfFont * sffont;
    sfText * sftext;
    sfMusic * tema;
    sfMusic * tiro;
    sfMusic * explosao;
    sfMusic * perdeLife;
    sfTexture * tnave;
    sfSprite * snave;
    sfTexture * tinimigo;
    sfSprite * sinimigo;
    sfTexture * tbala;
    sfSprite * sbala;
    sfTexture * tespecial;
    sfSprite * sespecial;
    sfTexture * tfundo;
    sfSprite * sfundo;

}Visual;

sfRenderWindow * criar_janela();

Visual * criar_visual();

void juncao_visual(Visual * visual);

void liberar_memoria_visual(Visual * visual);

void tk_write(sfText * _text, sfRenderWindow * _janela, int _cell,  float x, float y, const char * format, ...);

void tocar_musica(Visual * visual);

void fechar_janela(Visual * visual);

#endif // CSFML_H
