#include "Bibliotecas/bibliotecas.h"
#include "mecanicas.h"

#include "glm.h"
#include "desenha.h"





/**************************************************************/
//===============================================================================
//Movimentação 
//===============================================================================

float velocidade = 2;
float oldVelocidade = 2;
int numTeclasPressionadas = 0;
StructLimites Limites;
/* Essa função sera responsavel por mover o cenario em qualquer direção. Tendo base
* a tecla pressionada, e os angulos de rotacoes vigentes. (xrot e yrot)
* DIRECAO: * Em relação ao personagem.                  
*            1          1:Frente
*            /\         2:Direita
*          4<  >2       3:Traseira
*            \/         4:Esquerda
*            3
*
*/
void movimentaTodasDirecoes(int direcao, float xrot, float yrot, float cpos[4]){
    
    
    float xrotrad,yrotrad;
    yrotrad = (yrot / 180 * 3.141592654f); //Converte para radiandos
    xrotrad = (xrot / 180 * 3.141592654f); //Converte para radiandos
    
    /* Se o numTeclasPressionadas for igual a 1, significa que ja existe uma tecla 
     * pressionada, entao iremos diminuir a velocidade por 2, para evitar de ficar
     * extremamente rapido quando andamos na diagonal.
    */ 
    if(numTeclasPressionadas>=1){
        velocidade = velocidade/2;
        // printf("Multikeys\n");
    }
    switch (direcao){
        case 1: //Frente
        if(cpos[1] <= Limites.XMax && cpos[1]>= Limites.XMin)
        if(cpos[1] <= Limites.ZMax && cpos[1]>= Limites.ZMin)        
        {
            cpos[1] += (sin(yrotrad)) * velocidade;
            cpos[3] -= (cos(yrotrad)) * velocidade;
            cpos[2] -= (sin(xrotrad)) * velocidade;
        }
            break;

        case 2: //Direita
            cpos[1] += (cos(yrotrad)) * velocidade;
            cpos[3] += (sin(yrotrad)) * velocidade;
            break;
        case 3: //Baixo
            cpos[1] -= (sin(yrotrad)) * velocidade;
            cpos[3] += (cos(yrotrad)) * velocidade;
            cpos[2] += (sin(xrotrad)) * velocidade;
            break;

        case 4: //Esquerda
            cpos[1] -= (cos(yrotrad)) * velocidade;
            cpos[3] -= (sin(yrotrad)) * velocidade;
            break;
    }
    velocidade = oldVelocidade;
}


/*Essa funcao regula a altura do cenário.*/
void sobeEDesce(int direcao,StructAltura * Altura){
    if(numTeclasPressionadas>=1){
        Altura->incAltura/=2;
    }

    if(direcao == 1)//Entao sobe
        if( (Altura->altura) < (Altura->limAlturaCima) )
            Altura->altura += Altura->incAltura;
    if( direcao == -1 ) //Entao desce
        if( Altura->altura > Altura->limAlturaBaixo)//Caso nao ultrapasse a altura limite
            (Altura->altura) += direcao * (float) (Altura->incAltura);

    if(numTeclasPressionadas>=1){
        Altura->incAltura*=2;
    }

}

/*Essa funcao rotaciona a nave em torno do proprio eixo*/
void rotacionaProprioEixo(int direcao,StructRotacao *nave){
    if(direcao==-1) //Esquerda
        nave->angulo-=nave->incAngulo;
    else if(direcao==1) //Direita
        nave->angulo+=nave->incAngulo;

}


void inicializaLimitesMapa(StructLimites*Limite,float limMundoXMin,float limMundoXMax,float limMundoZMin,float limMundoZMax){
    Limite->XMin = limMundoXMin;
    Limite->XMax = limMundoXMax;
    Limite->ZMin = limMundoZMin;
    Limite->ZMax = limMundoZMax; 
    Limites = *Limite;
}



/**************************************************************/
//===============================================================================
//Controles 
//===============================================================================

/* Na nossa seção de controles, um dos principais objetivos é de ter controle 
 * sobre as teclas pressionadas, permitindo multiplas ações ao mesmo tempo.
 * Utilizaremos então, um array associando todas os comandos a um valor pré-determinado,
 * dessa forma, saberemos quais teclas estao ou nao sendo apertadas.
 * Utilizaremos 1 para o indicar que a tecla esta ligada, e 0 para a tecla desligada.
 * Para isso, faremos os seguintes processos:
 * 1 - Estabelecer todo o array de teclas pressionadas como 0(estado inicial desligado).
 * 2 - Nossa função de keyboard, na main, chamará funções para ligar e desligar as teclas.
 * 3 - Para finalizar, iremos verificar todas as teclas pressionadas e realizar a ação
 * correspondente. 
*/ 

/*Essa função ira estabelecer todo o array de teclas pressionadas como 0 
 *(estado inicial desligado)
*/
void inicializaControles(int teclasPressionadas[], int numTeclas){
    int i;
    for(i=0;i<=numTeclas;i++){
        teclasPressionadas[i] = 0;
    }
}

/*Essa funcao verifica quais teclas estao pressionadas e realiza a acao correspondente    
*/
void verificaTeclas(int teclasPressionadas[],int xrot,int yrot, float cpos[4], 
                    StructAltura* Altura,StructRotacao* nave ){
    numTeclasPressionadas = 0;    
    // Movimentacao:
    // 1 - Frente
    if(teclasPressionadas[1] == 1){
        movimentaTodasDirecoes(1,xrot,yrot,cpos);
        numTeclasPressionadas++;
    // printf("%i\n",numTeclasPressionadas);

    }
    // 2 - Direita
    if(teclasPressionadas[2] == 1){
        movimentaTodasDirecoes(2,xrot,yrot,cpos);
        numTeclasPressionadas++;
    }
    // 3 - Tras
    if(teclasPressionadas[3] == 1){
        movimentaTodasDirecoes(3,xrot,yrot,cpos);
        numTeclasPressionadas++;
    }
    // 4 - Esquerda
    if(teclasPressionadas[4] == 1){
        movimentaTodasDirecoes(4,xrot,yrot,cpos);
        numTeclasPressionadas++;
    }
    // 5 - Cima
    if(teclasPressionadas[5] == 1){
        sobeEDesce(1,Altura);
        numTeclasPressionadas++;
    }
    //6 - Baixo
    if(teclasPressionadas[6] == 1){
        sobeEDesce(-1,Altura);
        numTeclasPressionadas++;
    }
    //7 - Rotaciona Esquerda
    if(teclasPressionadas[7] == 1){
        rotacionaProprioEixo(1,nave);
    }

    //8 - Rotaciona Direita
    if(teclasPressionadas[8] == 1){
        rotacionaProprioEixo(-1,nave);
    }

}

/*Essa funcao liga a tecla( muda pra valor 1) no indice correspondente */
void ligaTecla(int teclasPressionadas[], int indice){
    teclasPressionadas[indice] = 1;
}

/*Essa funcao desliga a tecla( muda pra valor 0) no indice correspondente */
void desligaTecla(int teclasPressionadas[], int indice){
    teclasPressionadas[indice] = 0;
}


/**************************************************************/
//===============================================================================
//Outros
//===============================================================================

void trocaCursor(int *cursorAtivo){
    /*Caso esteja ativo, desabilita o cursor*/
    if(*cursorAtivo){
        glutSetCursor(GLUT_CURSOR_NONE);
        *cursorAtivo = 0;
    }

    /*Caso esteja inativo, habilita o cursor*/

    else{
        glutSetCursor(GLUT_CURSOR_RIGHT_ARROW);
        *cursorAtivo = 1;
    }

}



/**************************************************************/
//===============================================================================
//XWING
//===============================================================================

int printOn = 0;
// int rotacaoOn = 0;
float tamanhoNave[3] = {25,25,25};
float posicaoInicial[3] = {0,1300,0};
float incAngulo = 1.2;
float velocidadeNave = 6;
int verificaLimitesOn = 1;
int tempoMinVerificarLimites = 9000; //Em ms (milisegundos)

void inicializaNaveAnimada(StructXWING *nave, GLuint displayList){
    //Posicao
    
    nave->posicao[0] = posicaoInicial[0];
    nave->posicao[1] = posicaoInicial[1];
    nave->posicao[2] = posicaoInicial[2];
//PosicaoInicial e PosicaoLimite
    nave->posicaoInicial[0] = posicaoInicial[0];
    nave->posicaoInicial[1] = posicaoInicial[1];
    nave->posicaoInicial[2] = posicaoInicial[2];
    
    nave->angulo =0;
    nave->incAngulo = incAngulo;
    nave->anguloMax = 180;
    nave->rotacaoOn=0;
    
    nave->velocidade = velocidadeNave;
    nave->displayList = displayList;
}

void movimentaNaveAnimada(StructXWING *nave){
    // if(nave->posicao[2] <= nave->posicaoMaxima[2])
    if(nave->rotacaoOn==0)
        nave->posicao[0]+=nave->velocidade;
}

void rotacionaNaveAnimada(StructXWING *nave){ //Isso permite mover pra frente enquanto roda, fazendo o movimento ficar mais fluido.
    // if(nave->angulo<180)
    float angulo = nave->angulo;
    float angulorad = (angulo/ 180 * 3.141592654f);  //Posicao em radiandos.

    nave->posicao[0] += sin(angulorad); //Posicao igual ao seno da parada.

    nave->angulo+=nave->incAngulo;

    verificaAngulo(nave);


}  


void verificaAngulo(StructXWING *nave){
    //Rotacao -> 0
    if(!nave->rotacaoOn) //Rotacao desligada. Deseja verificar e estabelecer o angulo maximo.
    { 
        if(nave->angulo<180)
            nave->anguloMax = 180;

        if(nave->angulo>=180) //Caso a nave ja esteja rotacionada
            nave->anguloMax = 360;

    }

    //Rotacao -> 1
    if(nave->rotacaoOn)
    {
        if(nave->angulo >= nave->anguloMax ){  //Se o angulo da nave for maior que o angulo maximo
            nave->rotacaoOn = 0; //Desligar rotacao, pois acabou o movimento.
            nave->velocidade *=-1; //Inverter velocidade, pois o objeto girou (senao ele andaria de costas).
            
            if(nave->angulo>=360) //Caso ele tenha dado uma volta completa. Voltar para o angulo 0.(Diminuir 360 graus)
                nave->angulo -= 360;
        }
    }

}


void ligaRotacaoNaveAnimada(StructXWING *nave){
    verificaAngulo(nave);
    nave->rotacaoOn = 1;
    if(printOn)
        printf("RotacaoOn\n");
}

void desligaRotacaoNaveAnimada(StructXWING *nave){
    verificaAngulo(nave);
    nave->rotacaoOn = 0;
        if(printOn)
            printf("RotacaoOff\n");
}


void respawnNaveAnimada(StructXWING *nave){
    int i;
    for(i=0;i<3;i++)
        nave->posicao[i] = nave->posicaoInicial[i];
    nave->rotacaoOn = 0;
    nave->velocidade = 1;
    nave->angulo = 0;

}

void chamaVerificaLimites(){
    verificaLimitesOn = 1;
}

/*Verifica se a nave alcancou o limite do mapa, para realizar rotacao*/
void verificaLimites(StructXWING *nave){

    if( (nave->posicao[0] >= Limites.ZMax || nave->posicao[0] <= Limites.ZMin)){
        ligaRotacaoNaveAnimada(nave);
        verificaLimitesOn = 0;
    }

    
    glutTimerFunc(tempoMinVerificarLimites,chamaVerificaLimites,tempoMinVerificarLimites);

}

void desenhaNaveAnimada(StructXWING *nave){

    if(verificaLimitesOn == 1)
        verificaLimites(nave); 

    if(nave->rotacaoOn) //Se rotacao ligada, rotacionar.
        rotacionaNaveAnimada(nave);
    else //Caso contrario, movimentar-se normalmente.
        movimentaNaveAnimada(nave);


    glPushMatrix();
        glTranslated(nave->posicao[0],nave->posicao[1],nave->posicao[2]);
        glRotated(nave->angulo,0,1,0);
        // glTranslated(-nave->posicao[0],-nave->posicao[1],-nave->posicao[2]); //Rotacionar em torno de uma coisa.
        glScaled(tamanhoNave[0],tamanhoNave[1],tamanhoNave[2]);
        desenhaLista(nave->displayList);
    glPopMatrix();


}
