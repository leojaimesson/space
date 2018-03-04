#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>
#include <string.h>
#include "cenario.h"
#include "csfml.h"
#include <SFML/System.h>
#include <SFML/Graphics.h>
#include <SFML/Audio.h>



int main(void){

    srand(time(NULL));

    Cenario * cenario = criar_cenario(800,600,10,2);

    Visual * visual = criar_visual(cenario->largura,cenario->altura);
    juncao_visual(visual);



//----------------------------------------------------------------------------------------------------------------------------------
    sfMusic_play(visual->tema);
    while(sfRenderWindow_isOpen(visual->janela)){
           fechar_janela(visual);
//----------------------------------------------------------------------------------------------------------------------------------
         //limpando tela
        sfRenderWindow_clear(visual->janela,sfBlack);

        tocar_musica(visual);

//----------------------------------------------------------------------------------------------------------------------------------
        //Movimentação 

        movimento_nave(cenario);

//----------------------------------------------------------------------------------------------------------------------------------
         //Limetes tela

        limete_cenario(cenario,cenario->nave,visual);




        background_tela(cenario,visual);

//----------------------------------------------------------------------------------------------------------------------------------
        //fazendo a nave aparecer na tela
        printar_nave(visual,cenario);


        tk_write(visual->sftext, visual->janela, 15, 20,20 , "Vida %d", cenario->nave->vida);
        tk_write(visual->sftext, visual->janela, 15, 20,40 , "Score %d", cenario->Score);
        tk_write(visual->sftext, visual->janela, 15, 20,60 , "Especiais %d", cenario->especiais);
        tk_write(visual->sftext, visual->janela, 15, 130,20,"Mais vale um fracasso honroso do que um sucesso indigno.");
        tk_write(visual->sftext,visual->janela,8,690,580,"By: Leo Jaimesson");
        tk_write(visual->sftext,visual->janela,8,690,590,"    Rodrigo Almeida");
            if(cenario->nave->vida <= 0){
                tk_write(visual->sftext,visual->janela,30,300,300, "GAMER OVER");
                tk_write(visual->sftext,visual->janela,10,320,350,"Aperte 'Q' se quer sair");
                tk_write(visual->sftext,visual->janela,10,370,360,"ou");
                tk_write(visual->sftext,visual->janela,10,320,370,"'R'' para Reinicia");
        }

//----------------------------------------------------------------------------------------------------------------------------------

        //Criação da bala e movimentação
        criacao_todas_balas(visual,cenario);

        printar_especial(cenario,visual);

        colisao_especial_x_inimigo(cenario);

//----------------------------------------------------------------------------------------------------------------------------------

        printar_balas_tela(cenario,visual);
//----------------------------------------------------------------------------------------------------------------------------------

        criacao_todos_inimigos(visual,cenario);

//----------------------------------------------------------------------------------------------------------------------------------

        //colisao bala inimigo

        colisao_bala_x_inimigo(cenario);
//----------------------------------------------------------------------------------------------------------------------------------

        limete_tiro_tela(cenario);

//----------------------------------------------------------------------------------------------------------------------------------

        printando_inimigo_tela(cenario,visual);

//----------------------------------------------------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------------------------------------------------


        colisao_nave_x_inimigo(cenario,visual);

        sfRenderWindow_display(visual->janela);

        Resetar_sair_jogo(cenario,visual);

        if(cenario->sair)
            break;

    }

    liberar_memoria_cenario(cenario);
    liberar_memoria_visual(visual);
    return 0;
}
