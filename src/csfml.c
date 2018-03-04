#include "cenario.h"
#include "personagens.h"
#include "csfml.h"
#include <SFML/System.h>
#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>

//--------------------------------------------------------------------------------------------------------------------------------------------
//----função para criar a janela----//

sfRenderWindow * criar_janela(int largura,int altura){
    sfRenderWindow * janela;
    sfVideoMode mode = {largura,altura,32};
    janela = sfRenderWindow_create(mode,"nave",sfResize | sfClose,NULL);

    sfRenderWindow_setFramerateLimit(janela,60);

    return janela;
}

//--------------------------------------------------------------------------------------------------------------------------------------------
//----função para criar o visual----//

Visual * criar_visual(int largura, int altura){
    Visual * visual = malloc(sizeof(Visual));
    visual->clock = sfClock_create();
    visual->tempoTiro = sfClock_create();
    visual->sobeNivel = sfClock_create();
    visual->tempoMusica = sfClock_create();
    visual->janela = criar_janela(largura,altura);
    visual->sffont = sfFont_createFromFile("../font/OpenSans-Light.ttf");
    visual->sftext = sfText_create();

    visual->tema = sfMusic_createFromFile("../musica/musica.ogg");
    visual->tiro = sfMusic_createFromFile("../musica/tiro1.ogg");
    visual->explosao = sfMusic_createFromFile("../musica/explosao.ogg");
    visual->perdeLife = sfMusic_createFromFile("../musica/perdevida.ogg");


    visual->tfundo = sfTexture_createFromFile("../imagens/universo.png",NULL);
    visual->sfundo = sfSprite_create();


    visual->tnave = sfTexture_createFromFile("../imagens/nave.png",NULL);
    visual->snave = sfSprite_create();
    visual->tinimigo = sfTexture_createFromFile("../imagens/inimigo.png",NULL);
    visual->sinimigo = sfSprite_create();
    visual->tbala = sfTexture_createFromFile("../imagens/ball.png",NULL);
    visual->sbala = sfSprite_create();

    visual->tespecial = sfTexture_createFromFile("../imagens/especial.png",NULL);
    visual->sespecial = sfSprite_create();

    return visual;
}

//--------------------------------------------------------------------------------------------------------------------------------------------
//----função para juntar o sprite e a texture----//

void juncao_visual(Visual * visual){

    sfText_setFont(visual->sftext, visual->sffont);

    sfSprite_setTexture(visual->snave,visual->tnave,0);

    sfSprite_setTexture(visual->sinimigo,visual->tinimigo,0);


    sfSprite_setTexture(visual->sbala,visual->tbala,0);


    sfSprite_setTexture(visual->sespecial,visual->tespecial,0);

    sfSprite_setScale(visual->sbala,(sfVector2f){0.20,0.20});

    sfSprite_setTexture(visual->sfundo,visual->tfundo,0);
    sfSprite_setScale(visual->sfundo,(sfVector2f){1.5,2.3});



    sfMusic_setVolume(visual->tema,69);
    sfMusic_setVolume(visual->perdeLife,40);
    sfMusic_setVolume(visual->explosao,64);
     sfMusic_setVolume(visual->tiro,59);

    //sfSprite_move(visual->sfundo,(sfVector2f){0,22});
}

//--------------------------------------------------------------------------------------------------------------------------------------------
//----função para liberar a memoria do visual----//

void liberar_memoria_visual(Visual * visual){
    sfClock_destroy(visual->clock);
    sfClock_destroy(visual->tempoTiro);
    sfClock_destroy(visual->sobeNivel);
    sfClock_destroy(visual->tempoMusica);

    sfTexture_destroy(visual->tnave);
    sfSprite_destroy(visual->snave);

    sfTexture_destroy(visual->tespecial);
    sfSprite_destroy(visual->sespecial);

    sfFont_destroy(visual->sffont);
    sfText_destroy(visual->sftext);

    sfTexture_destroy(visual->tinimigo);
    sfSprite_destroy(visual->sinimigo);

    sfTexture_destroy(visual->tbala);
    sfSprite_destroy(visual->sbala);

    sfMusic_destroy(visual->tema);
    sfMusic_destroy(visual->tiro);
    sfMusic_destroy(visual->explosao);
    sfMusic_destroy(visual->perdeLife);

    sfRenderWindow_destroy(visual->janela);

    free(visual);
}


//--------------------------------------------------------------------------------------------------------------------------------------------
//----função para mostrar texto na tela----//
void tk_write(sfText * _text, sfRenderWindow * _janela, int _cell,  float x, float y, const char * format,...)
{
    char str[1000];
    va_list args;
    va_start( args, format );
    vsprintf(str, format, args);
    va_end( args );

    sfText_setColor(_text, sfWhite);
    sfText_setString(_text, str);
    sfText_setCharacterSize(_text, _cell);
    sfVector2f pos = {x , y};
    sfText_setPosition(_text, pos);
    sfRenderWindow_drawText(_janela, _text, NULL);
}


void tocar_musica(Visual * visual){
    if(sfClock_getElapsedTime(visual->tempoMusica).microseconds > sfMilliseconds(205000).microseconds){
        sfMusic_stop(visual->tema);
        sfMusic_play(visual->tema);
        sfClock_restart(visual->tempoMusica);
    }
}

//--------------------------------------------------------------------------------------------------------------------------------------------
//----função para fechar janela----//

void fechar_janela(Visual *visual){
    sfEvent evento;
    while(sfRenderWindow_pollEvent(visual->janela,&evento)){
        if(evento.type == sfEvtClosed)
            sfRenderWindow_close(visual->janela);
    }
}



