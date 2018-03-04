#ifndef PERSONAGENS_H
#define PERSONAGENS_H

typedef enum{FALSE,TRUE}boolean;

typedef struct{
    int poder;
    float x;
    float y;
    int vida;
    boolean exist;
}Nave;

typedef struct{
    int poder;
    float x,y;
    int vida;
    float height;
    float width;
    boolean exist;
}Inimigo;

typedef struct{
    int poder;
    float x,y;
    float height;
    float width;
    boolean esp;
    boolean exist;
}Balas;


Nave * criar_nave(int vida);

Inimigo criar_inimigo(Inimigo * inimigo,int x,float height,float width);

Balas criar_balas(Balas * balas, float x,float y,float height,float width);

Balas criar_especial(Balas * especial ,float x, float y,float height,float width);

void balas_update(Balas * bala);

void inimigo_update(Inimigo * inimigo,Nave * nave);

void trapaca_inimigo(Inimigo * inimigo, Balas * bala);

#endif // PERSONAGENS_H
