#include "cenario.h"
#include "personagens.h"
#include <SFML/System.h>
#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include <stdlib.h>

//--------------------------------------------------------------------------------------------------------------------------------------------
//----funçao para criar o cenario----//

Cenario * criar_cenario(int largura, int altura, int max_balas, int max_inimigos){
    Cenario * cenario = malloc(sizeof(Cenario));
    cenario->largura=largura;
    cenario->altura=altura;
    cenario->qtd_atual=0;
    cenario->qtd_balas_atual=0;
    cenario->aux_qtd_max_inimigo = max_inimigos;
    cenario->qtd_max_inimigo_absoluto = 100;
    cenario->qtd_max_inimigo=cenario->aux_qtd_max_inimigo;
    cenario->qtd_max_balas = max_balas;
    cenario->Score = 0;
    cenario->vyFundo = -690;
    cenario->vy2Fundo = 0;
    cenario->mortes = 0;
    cenario->especiais = 0;
    cenario->balas = malloc(sizeof(Balas)*max_balas);
    cenario->especial = malloc(sizeof(Balas));
    cenario->inimigos = malloc(sizeof(Inimigo)*max_inimigos);
    cenario->nave = criar_nave(10);
    cenario->sair = FALSE;
    return cenario;

}

//--------------------------------------------------------------------------------------------------------------------------------------------
//----função para movimentar o background----//

void background_tela(Cenario * cenario,Visual * visual){

    sfRenderWindow_drawSprite(visual->janela,visual->sfundo,NULL);
    if(cenario->vyFundo >= 0)
        cenario->vyFundo = -690;
    if(cenario->vy2Fundo >= 689)
        cenario->vy2Fundo = -1;
    sfSprite_setPosition(visual->sfundo,(sfVector2f){0,cenario->vyFundo});
    sfRenderWindow_drawSprite(visual->janela,visual->sfundo,NULL);
    sfSprite_setPosition(visual->sfundo,(sfVector2f){0,cenario->vy2Fundo});
    cenario->vyFundo += 1;
    cenario->vy2Fundo +=1;
}



//--------------------------------------------------------------------------------------------------------------------------------------------
//----função para

void movimento_nave(Cenario * cenario){

    if(cenario->nave->vida > 0){
        if(sfKeyboard_isKeyPressed(sfKeyA))
            cenario->nave->x-=4;
        if(sfKeyboard_isKeyPressed(sfKeyD))
            cenario->nave->x+=4;
        if(sfKeyboard_isKeyPressed(sfKeyW))
            cenario->nave->y-=4;
        if(sfKeyboard_isKeyPressed(sfKeyS))
            cenario->nave->y+=4;
    }
}


//--------------------------------------------------------------------------------------------------------------------------------------------
//----função para não permitir a nave sair da tela----//

void limete_cenario(Cenario *cenario, Nave *nave,Visual * visual){
    sfFloatRect rectNave = sfSprite_getLocalBounds(visual->snave);
    if(nave->y < 0)
        nave->y = 0;
    if(nave->y + rectNave.height > cenario->altura)
        nave->y = cenario->altura - rectNave.height;
    if(nave->x  < 0)
        nave->x = 0;
    if(nave->x > cenario->largura - rectNave.width)
        nave->x = cenario->largura - rectNave.width;
}


//--------------------------------------------------------------------------------------------------------------------------------------------
//----função para checar se a nave inimiga se chocou com a nossa nave----//

void colisao_inimigo_nave(Inimigo * inimigo, Nave * nave,float height,float width, Cenario * cenario){
    if(((inimigo->y <= nave->y && nave->y <= inimigo->y+inimigo->height) && (inimigo->x <= nave->x && nave->x <= inimigo->x + inimigo->width)) || ((nave->y <= inimigo->y && inimigo->y <= nave->y+height) && (nave->x <= inimigo->x && inimigo->x <= nave->x + width))){
        nave->vida-=1;
        cenario->qtd_atual -=1;
        inimigo->exist = TRUE;
    }
}

//--------------------------------------------------------------------------------------------------------------------------------------------
//----função para checar se a bala se chocou com o inimigo----//

void colisao_bala(Balas * bala, Inimigo * inimigo , Cenario * cenario){
    if(inimigo->y+inimigo->height >= bala->y && inimigo->y <= bala->y && ((inimigo->x <= bala->x && inimigo->x+inimigo->width >= bala->x) || (inimigo->x >= bala->x && inimigo->x+inimigo->width <= bala->x)) ){
        inimigo->vida-=bala->poder;
        bala->exist = TRUE;
        cenario->qtd_balas_atual -=1;

        if(inimigo->vida<=0){
            inimigo->exist = TRUE;
            cenario->qtd_atual -= 1;
            cenario->Score += 25;
            cenario->mortes+=1;

            if(cenario->mortes > 4){
                cenario->especiais+=1;
                cenario->mortes = 0;
            }

        }

    }
}


//--------------------------------------------------------------------------------------------------------------------------------------------
//----função para fazer a bala se destruir ao chegar no final da tela----//

void limete_bala(Balas *bala,Cenario * cenario){
    if(bala->y < 0){
        bala->exist = TRUE;
        cenario->qtd_balas_atual -= 1;
    }
}



//--------------------------------------------------------------------------------------------------------------------------------------------
//----função para desenhar a nave do jogador na tela----//

void printar_nave(Visual * visual, Cenario * cenario){
    sfSprite_setPosition(visual->snave,(sfVector2f){cenario->nave->x,cenario->nave->y});
    sfRenderWindow_drawSprite(visual->janela,visual->snave,NULL);
}


//--------------------------------------------------------------------------------------------------------------------------------------------
//----função que faz com que o vetor de balas seja preenchido----//

void criacao_todas_balas(Visual * visual,Cenario * cenario){
    sfFloatRect rectBala = sfSprite_getLocalBounds(visual->sbala);
    if(cenario->nave->vida > 0 && sfKeyboard_isKeyPressed(sfKeySpace) && sfClock_getElapsedTime(visual->tempoTiro).microseconds > sfMilliseconds(200).microseconds){
        if(cenario->qtd_balas_atual < cenario->qtd_max_balas){
            cenario->balas[cenario->qtd_balas_atual] = criar_balas(&cenario->balas[cenario->qtd_balas_atual],(rectBala.width/2)+cenario->nave->x-4,cenario->nave->y - rectBala.height*0.20, rectBala.height*0.20,rectBala.width*0.20);
            cenario->qtd_balas_atual+=1;
            sfMusic_play(visual->tiro);
        }
        sfClock_restart(visual->tempoTiro);
    }
    //-----criação do especial------//
    if(sfKeyboard_isKeyPressed(sfKeyK) && cenario->especial->exist == FALSE && cenario->especiais > 0){
        sfFloatRect rectBala = sfSprite_getLocalBounds(visual->sespecial);
        sfMusic_play(visual->explosao);
        criar_especial(cenario->especial,cenario->nave->x - 80,cenario->nave->y - 170, rectBala.height,rectBala.width);
    }

}

//--------------------------------------------------------------------------------------------------------------------------------------------
//----função para printar o especial na tela----//

void printar_especial(Cenario * cenario, Visual * visual){
    if(cenario->especial->esp == TRUE && cenario->especiais >=1){
        sfSprite_setPosition(visual->sespecial,(sfVector2f){cenario->especial->x,cenario->especial->y});
        sfRenderWindow_drawSprite(visual->janela,visual->sespecial,NULL);
        limete_especial(cenario);
        cenario->especial->y-=5;
    }
}



//--------------------------------------------------------------------------------------------------------------------------------------------
//----função para destruir o especial quando chegar ao final da tela----//

void limete_especial(Cenario * cenario){
    if(cenario->especial->y+cenario->especial->height <= 0){
        cenario->especial->esp = FALSE;
        cenario->especial->exist = FALSE;
        cenario->especiais -=1;
    }
}

//--------------------------------------------------------------------------------------------------------------------------------------------
//----função para ver se ocorreu a colisao entre o especial e algum inimigo----//

void colisao_especial_x_inimigo(Cenario * cenario){
    int i;
    for(i =0; i < cenario->qtd_atual;i++){
        if( (( (cenario->inimigos[i].y >= cenario->especial->y && cenario->inimigos[i].y + cenario->inimigos[i].height <= cenario->especial->y + cenario->especial->height) || (cenario->inimigos[i].y + cenario->inimigos[i].height >= cenario->especial->y && cenario->inimigos[i].y + cenario->inimigos[i].height <= cenario->especial->y + cenario->especial->height) || (cenario->inimigos[i].y >= cenario->especial->y && cenario->inimigos[i].y <= cenario->especial->y + cenario->especial->height )) && ( (cenario->inimigos[i].x <= cenario->especial->x && cenario->inimigos[i].x + cenario->inimigos[i].width >= cenario->especial->x) || (cenario->inimigos[i].x <= cenario->especial->x + cenario->especial->width && cenario->inimigos[i].x >= cenario->especial->x + cenario->especial->x + cenario->especial->width))) || (cenario->especial->y <= cenario->inimigos[i].y && cenario->especial->y + cenario->especial->height >= cenario->inimigos[i].y + cenario->inimigos[i].height && cenario->especial->x <= cenario->inimigos[i].x && cenario->especial->x + cenario->especial->width >= cenario->inimigos[i].x + cenario->inimigos[i].width)){
            cenario->inimigos[i].exist = TRUE;
            cenario->Score+=25;
        }
        if(cenario->inimigos[i].exist == TRUE){
             cenario->qtd_atual-=1;
             troca_vetor(&cenario->inimigos[i],&cenario->inimigos[cenario->qtd_atual]);

        }
    }
}

//--------------------------------------------------------------------------------------------------------------------------------------------
//----função para printar todas as balas na tela----//

void printar_balas_tela(Cenario * cenario, Visual * visual){
    int i;
    for(i = 0; i < cenario->qtd_balas_atual;i++){
        sfSprite_setPosition(visual->sbala,(sfVector2f){cenario->balas[i].x,cenario->balas[i].y});
        sfRenderWindow_drawSprite(visual->janela,visual->sbala,NULL);
        balas_update(&cenario->balas[i]);
    }
}

//--------------------------------------------------------------------------------------------------------------------------------------------
//----função para a criação de todos os inimigos----//

void criacao_todos_inimigos(Visual * visual, Cenario * cenario){
    if(sfClock_getElapsedTime(visual->sobeNivel).microseconds > sfMilliseconds(15000).microseconds && cenario->qtd_max_inimigo < cenario->qtd_max_inimigo_absoluto){
        cenario->qtd_max_inimigo++;
        cenario->inimigos=(Inimigo *) realloc(cenario->inimigos,sizeof(Inimigo)*cenario->qtd_max_inimigo);
        sfClock_restart(visual->sobeNivel);
    }

    if(sfClock_getElapsedTime(visual->clock).microseconds > sfMilliseconds(300).microseconds){
        if(cenario->qtd_atual < cenario->qtd_max_inimigo){
            sfFloatRect rectInimigo = sfSprite_getLocalBounds(visual->sinimigo);
            cenario->inimigos[cenario->qtd_atual] = criar_inimigo(&cenario->inimigos[cenario->qtd_atual],rand()%cenario->largura,rectInimigo.height,rectInimigo.width);
            cenario->qtd_atual+=1;
        }
        sfClock_restart(visual->clock);
    }
}

//--------------------------------------------------------------------------------------------------------------------------------------------
//----função para testar se aluguma bala acertou algum inimigo----//

void colisao_bala_x_inimigo(Cenario * cenario){
    int i,j;
    for(i = 0;i < cenario->qtd_atual;i++){
        for(j = 0; j< cenario->qtd_balas_atual;j++){
            colisao_bala(&cenario->balas[j],&cenario->inimigos[i],cenario);
            if(cenario->balas[j].exist == TRUE)
                trocar_bala(&cenario->balas[j],&cenario->balas[cenario->qtd_balas_atual]);
        }
        if(cenario->inimigos[i].exist == TRUE){
             troca_vetor(&cenario->inimigos[i],&cenario->inimigos[cenario->qtd_atual]);
        }
    }
}

//--------------------------------------------------------------------------------------------------------------------------------------------
//----função para fazer a bala ser destruida apos encostar no final da tela----//

void limete_tiro_tela(Cenario * cenario){
    int i;
    for(i = 0; i<cenario->qtd_balas_atual;i++){
       limete_bala(&cenario->balas[i], cenario);

       if(cenario->balas[i].exist == TRUE)
           trocar_bala(&cenario->balas[i] , &cenario->balas[cenario->qtd_balas_atual]);
    }
}

//--------------------------------------------------------------------------------------------------------------------------------------------
//----função para printar todos os inimigos na tela----//

void printando_inimigo_tela(Cenario * cenario, Visual * visual){
    int i;
    for(i = 0; i < cenario->qtd_atual;i++){

        sfSprite_setPosition(visual->sinimigo,(sfVector2f){cenario->inimigos[i].x,cenario->inimigos[i].y});
        sfRenderWindow_drawSprite(visual->janela,visual->sinimigo,NULL);

    }
    atualizando_passos_inimigos(cenario);

}


//--------------------------------------------------------------------------------------------------------------------------------------------
//----Função que faz multiplas atualizações das naves inimigas----//

void atualizando_passos_inimigos(Cenario * cenario){

    int i,j;
    for(i = 0;i<cenario->qtd_atual;i++){
        inimigo_update(&cenario->inimigos[i],cenario->nave);
    }
    if(cenario->qtd_balas_atual>0){
           for(i = 0; i<cenario->qtd_balas_atual;i++){
               for(j = 0; j<cenario->qtd_atual; j++){
                   trapaca_inimigo(&cenario->inimigos[j],&cenario->balas[i]);
               }
           }
     }
}



//--------------------------------------------------------------------------------------------------------------------------------------------
//----função que faz multiplas verificações se alguma nave inimiga se chocou com a nave do jogado----//
void colisao_nave_x_inimigo(Cenario * cenario,Visual * visual){
    int i;
    sfFloatRect rectNave = sfSprite_getLocalBounds(visual->snave);

    for(i = 0;i<cenario->qtd_atual;i++){
        colisao_inimigo_nave(&cenario->inimigos[i], cenario->nave,rectNave.height,rectNave.width, cenario);
       if(cenario->inimigos[i].exist == TRUE){
           sfMusic_play(visual->perdeLife)
;            troca_vetor(&cenario->inimigos[i],&cenario->inimigos[cenario->qtd_atual]);
       }
    }
}


//--------------------------------------------------------------------------------------------------------------------------------------------
//----função para resetar jogo----//

void Resetar_sair_jogo(Cenario * cenario,Visual * visual){
    if(cenario->nave->vida <= 0){
        cenario->nave->vida = 0;
        cenario->qtd_max_inimigo = 0;

        sfMusic_stop(visual->tema);

        if(sfKeyboard_isKeyPressed(sfKeyQ))
           cenario->sair = TRUE;
        if(sfKeyboard_isKeyPressed(sfKeyR)){
            sfMusic_play(visual->tema);
            cenario->nave->vida = 10;
            cenario->nave->x = 360;
            cenario->nave->y = 540;
            cenario->qtd_max_inimigo = cenario->aux_qtd_max_inimigo;
            cenario->qtd_atual = 0;
            cenario->qtd_balas_atual = 0;
            cenario->Score = 0;
            cenario->especiais = 0;
        }

    }
}



//--------------------------------------------------------------------------------------------------------------------------------------------
//----funções auxiliares----//


//----função para trocar as posições dos inimigos no vetor----//
void troca_vetor(Inimigo *a, Inimigo *b){
    Inimigo aux;
    aux = *a;
    *a = *b;
    *b = aux;
}

//----função para trocar as posições das balas no vetor----//
void trocar_bala(Balas *a, Balas *b){
    Balas aux = * a;
    *a = *b;
    *b = aux;
}

//----função para liberar memoria----//
void liberar_memoria_cenario(Cenario * cenario){
    free(cenario->nave);
    free(cenario->inimigos);
    free(cenario->balas);
    free(cenario->especial);
    free(cenario);
}
