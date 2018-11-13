
typedef struct Struct_Altura{
    float altura;
    float limAlturaBaixo;
    float limAlturaCima;
    float incAltura;
}StructAltura;


typedef struct Struct_Helice{
    float distancia;
    float angulo;
    float incAngulo;
    int *eixo;
}StructHelice,StructRotacao;

typedef struct Struct_NaveAnimada{
    float posicao[3];
    float posicaoInicial[3];
    int rotacaoOn;
    
    float velocidade;
    float angulo;
    float incAngulo;
    float anguloMax;

    GLuint displayList;
}StructXWING;

typedef struct Struct_LimitesDoMundoSemSerAltura{
    float XMax;
    float XMin;
    float ZMax;
    float ZMin;
}StructLimites;


// Para nao incluir as funções multiplas vezes, o que resultaria em erro.
#ifndef MECANICAS_H
#define MECANICAS_H
void trocaCursor(int *cursorAtivo);
void sobeEDesce(int direcao,StructAltura * Altura);
void movimentaTodasDirecoes(int direcao, float xrot, float yrot, float cpos[4]);
void inicializaControles(int teclasPressionadas[], int numTeclas);
void verificaTeclas(int teclasPressionadas[],int xrot,int yrot, float cpos[4],StructAltura *Altura, StructRotacao *nave);
void ligaTecla(int teclasPressionadas[], int indice);
void desligaTecla(int teclasPressionadas[], int indice);
void rotacionaProprioEixo(int direcao,StructRotacao *Nave);
void inicializaLimitesMapa(StructLimites*Limites,float limMundoXMin,float limMundoXMax,float limMundoZMin,float limMundoZMax);

void inicializaNaveAnimada(StructXWING *nave, GLuint displayList);
void movimentaNaveAnimada(StructXWING *nave);
void respawnNaveAnimada(StructXWING *nave);
void desenhaNaveAnimada(StructXWING *nave);
void rotacionaNaveAnimada(StructXWING *nave);
void ligaRotacaoNaveAnimada(StructXWING *nave);
void desligaRotacaoNaveAnimada(StructXWING *nave);
void verificaAngulo(StructXWING *nave);


void passaFps(float fpsJogo);

#endif