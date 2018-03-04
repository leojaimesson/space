#ifndef CENARIO_H
#define CENARIO_H
#include "personagens.h"
#include "csfml.h"
#include <SFML/System.h>
#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include <stdlib.h>


typedef struct{

    int qtd_max_inimigo_absoluto;
    int qtd_max_inimigo;
    int aux_qtd_max_inimigo;
    int qtd_max_balas;
    int qtd_balas_atual;
    int qtd_atual;
    int largura;
    int altura;
    int Score;
    float vyFundo;
    float vy2Fundo;
    int mortes;
    int especiais;
    boolean sair;
    Balas * balas;
    Balas * especial;
    Inimigo * inimigos;
    Nave * nave;

}Cenario;


Cenario * criar_cenario(int largura, int altura, int max_balas, int max_inimigos);

void background_tela(Cenario * cenario,Visual * visual);

void movimento_nave(Cenario * cenario);

void limete_cenario(Cenario * cenario , Nave * nave, Visual * visual);

void colisao_inimigo_nave(Inimigo * inimigo, Nave * nave, float height,float width, Cenario * cenario);

void colisao_bala(Balas * bala, Inimigo * inimigo , Cenario * cenario);

void limete_bala(Balas *bala, Cenario * cenario);

void troca_vetor(Inimigo * a,Inimigo * b);

void trocar_bala(Balas * a, Balas * b);

void liberar_memoria_cenario(Cenario * cenario);

void printar_nave(Visual * visual, Cenario * cenario);

void criacao_todas_balas(Visual * visual,Cenario * cenario);

void printar_especial(Cenario * cenario, Visual * visual);

void limete_especial(Cenario * cenario);

void colisao_especial_x_inimigo(Cenario * cenario);

void printar_balas_tela(Cenario * cenario, Visual * visual);

void criacao_todos_inimigos(Visual * visual, Cenario * cenario);

void colisao_bala_x_inimigo(Cenario * cenario);

void limete_tiro_tela(Cenario * cenario);

void printando_inimigo_tela(Cenario * cenario, Visual * visual);

void atualizando_passos_inimigos(Cenario * cenario);

void colisao_nave_x_inimigo(Cenario * cenario,Visual * visual);

void Resetar_sair_jogo(Cenario * cenario,Visual * visual);

#endif // CENARIO_H
