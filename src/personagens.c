#include "personagens.h"
#include <stdlib.h>


//--------------------------------------------------------------------------------------------------------------------------------------------
//----função para criar e atribuir valores a nave----//

Nave * criar_nave(int vida){
    Nave * nave = malloc(sizeof(Nave));
    nave->poder = 2;
    nave->x = 360;
    nave->y = 540;
    nave->vida = vida;
    nave->exist = TRUE;
    return nave;
}

//--------------------------------------------------------------------------------------------------------------------------------------------
//----função para criar e atribuir valores ao inimigo----//

Inimigo criar_inimigo(Inimigo * inimigo, int x,float height,float width){
    inimigo->vida = 2;
    inimigo->poder = 1;
    inimigo->x= x;
    inimigo->y=0;
    inimigo->height = height;
    inimigo->width = width;
    inimigo->exist = FALSE;

    return *inimigo;
}

//--------------------------------------------------------------------------------------------------------------------------------------------
//----função para criar e atribuir valor a bala----//

Balas criar_balas(Balas * balas, float x, float y,float height,float width){
    balas->poder = 1;
    balas->x= x;
    balas->y=y;
    balas->height = height;
    balas->width = width;
    balas->exist = FALSE;

    return *balas;
}


//--------------------------------------------------------------------------------------------------------------------------------------------
//----função para criar e atribuir valor ao especial----//
Balas criar_especial(Balas * especial, float x, float y,float height,float width){
    especial->poder = 1;
    especial->x= x;
    especial->y=y;
    especial->height = height;
    especial->width = width;
    especial->exist = TRUE;
    especial->esp=TRUE;
    return *especial;
}

//--------------------------------------------------------------------------------------------------------------------------------------------
//----função atualizar os passos da bala----//
void balas_update(Balas * bala){
    bala->y-=7;
};


//--------------------------------------------------------------------------------------------------------------------------------------------
//----função para atualizar os ṕassos do inimigo----//
void inimigo_update(Inimigo *inimigo,Nave * nave){
    if(nave->x - inimigo->x >0)
        inimigo->x+=2.4;
    if(nave->x - inimigo->x <0)
        inimigo->x-=2.4;
    if(nave->y - inimigo->y >0)
        inimigo->y += 2.4;
    if(nave->y - inimigo->y <0)
        inimigo->y -= 2.4;
}

//--------------------------------------------------------------------------------------------------------------------------------------------
//----função para o inimigo desviar da bala----//
void trapaca_inimigo(Inimigo * inimigo, Balas * bala){
    if(((bala->x<= inimigo->x+inimigo->width && bala->x >= inimigo->x) || (bala->x+bala->width >= inimigo->x && bala->x+bala->width <= inimigo->x+inimigo->width))&& bala->y> inimigo->y){
     // if(inimigo->y+inimigo->height >= bala->y && inimigo->y <= bala->y && ((inimigo->x <= bala->x && inimigo->x+inimigo->width >= bala->x) || (inimigo->x >= bala->x && inimigo->x+inimigo->width <= bala->x)) )
        //if()

        if(((inimigo->width+inimigo->x)-(bala->x)) > inimigo->width/2)
            inimigo->x+=3.9;
        else
            inimigo->x-=3.9;

     }
}
