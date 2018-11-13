#include "bibliotecas.h"
#include "glm.h"
#include "mecanicas.h"
#include "SOIL/SOIL.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "desenha.h"



/**************************************************************/
//=============================================================================== 
// DECLARACAO DE VARIAVEIS GLOBAIS 
//===============================================================================

/***********/
//Configuraveis  
/***********/
/*Aqui estao algumas opcoes configuraveis para facil acesso*/
int musicaOn = 1;
int fogOn = 0;
int fullScreen = 1;
int MostraPosicaoConsole = 0;
float sensitivity = .1; //Sensibilidade do mouse
/* Determina qual eh o cursor sendo utilizado
 * basicamente, serve para habilitar ou desabilitar * o cursor(com a letra F)
*/
int cursorAtivo = 1;
int LockingCursorCenterScreen = 1; //Parada q fixa o cursor no centro da tela

/***********/
//Iluminacao  
/***********/
/*Iluminacao Global*/
static float m = 0.6;           // Intensidade da luz ambiente global
int iluminacaoOn = 1; // para controle da iluminação como o enunciado pede
int dia = 1;
int noite = 0;

/***********/
//Musica  
/***********/
Mix_Music * musica_ingame;

/***********/
//LoadingScreen 
/***********/
/*Aqui estao as variaveis usadas para a tela de loading*/
/*Tela de loading - Loading Screen*/
 int loadingScreen = 1; //Determina se a tela de load esta habilitada
 int loadingModels = 1; //NAO DESATIVAR - DETERMINA SE CARREGA OS MODELOS OU NAO
GLuint loading_screen; //DisplayList Loading Screen
GLuint ls_texture; //Textura Loading Screen

/***********/
//Tamanhos  
/***********/
/*Os tamanhos dos objetos carregados*/
float tam_Personagem[3] = {3,3,3};
float tam_Cidade[3] = {100,100,100};
float tam_Helice[3] = {.8,.8,.8};
float tam_Skybox[3] = {250,250,250};

/***********/
//Camera  
/***********/
/*Aqui estao as variaveis usadas para a movimentacao de camera com o mouse*/
//Obs:cpos eh um vetor de 4, para poder usar x,y,z como 1,2,3 respectivamente.
float cpos[4]; //Posicao do cenario (x,y,x respectivamente)
GLfloat lpos = 1.0; // lpos da fonte de luz
float xrot = 0, yrot = 0;
float cRaio = 40.0f; // distância da camera(raio) até o personagem.
float cRaioPrimeiraPessoa = -8;
/* Guarda o ultimo valor de X e de Y
 * e, por meio da variação destes, permite
 * a movimentação do mouse. (deltaX deltaY)
*/
float lastx=0, lasty=0;
//Define qual eh a camera sendo utilizada.
int camera = 2;
/*Para rotacionar a nave do personagem */
StructRotacao navePersonagem;
float incAnguloNavePersonagem = 2; //Incremento no angulo da nave do personagem com E e Q

/***********/
//Altura  
/***********/
/*Aqui estao as variaveis usadas para a movimentacao da altura, ao longo do eixo y*/
/*Propriedades da altura*/
struct Struct_Altura Altura; 
/* Esses valores abaixo, eu usarei nessa Struct Altura, o que
 * me permitirá, agrupar essas diversas variaveis, em uma  
 * coisa só, facilitando na hora de passar parametros.
 Variaveis de Controles da Altura: */
float altura = 600;
float limAlturaBaixo = 38;
float limAlturaCima = 100000;
float incAltura = 2;

/***********/
//Limites de Mundo  
/***********/
/*Aqui estao as variaveis que dizem respeito aos limites de mundo*/
/*Limites do mapa sem ser altura*/
float limMundoXMin =-4000;
float limMundoXMax = 2450;
float limMundoZMin =-4000;
float limMundoZMax = 3900;
StructLimites Limites;

/***********/
//Helice  
/***********/
/*Aqui estao variaveis para o controle da helice*/
//Variaveis de Controle da Helice:
float distanciaHelice = 9;
float incAnguloHelice = 1.3; //Incremento no angulo da helice
int modoHelice = 1; //A "helice" possui dois modos. Aperte X para ve-los
//Declaracao das helice
StructHelice helice;
StructHelice helice2;
StructHelice helice3;
StructHelice helice4;

/***********/
//Teclado  
/***********/
/*Para controlar o pressionamento de múltiplas
* teclas. */
#define numTeclas 9
int teclasPressionadas[numTeclas];

/*Essas variaveis serao usadas para controlar o FPS(exibido no titulo da janela)*/
int momentoAnterior;
float fps = 0;

/***********/
//Modelos  
/***********/
/* Variaveis para utilizar o OBJ no GLM */
GLMmodel* pmodel = NULL;	
GLMmodel* cidade = NULL;
GLMmodel* skybox = NULL;
GLMmodel* helicemodel = NULL;
GLMmodel* xwing = NULL;
char filename[256];		

/***********/
//Display Lists  
/***********/
GLuint pdlist;
GLuint cidadelist;
GLuint skyboxlist;
GLuint helicelist;
GLuint xwinglist;

/***********/
//Nave Animada
/***********/
StructXWING navexwing;



/**************************************************************/
//=============================================================================== 
// Inicializacao 
//===============================================================================


void inicializaHelice(){
    helice.distancia = distanciaHelice ;
    helice.angulo = 0;
    helice.incAngulo = incAnguloHelice;

    helice2.distancia = distanciaHelice ;
    helice2.angulo = 90;
    helice2.incAngulo = incAnguloHelice;

    helice3.distancia = distanciaHelice ;
    helice3.angulo = 180;
    helice3.incAngulo = incAnguloHelice;
    
    helice4.distancia = distanciaHelice ;
    helice4.angulo = 270;
    helice4.incAngulo = incAnguloHelice;

}

void inicializaNavePersonagem(){
    navePersonagem.angulo = 0;
    navePersonagem.incAngulo = incAnguloNavePersonagem;
}

void inicializaAltura(StructAltura *Altura){
    Altura->altura = altura;
    Altura->limAlturaBaixo = limAlturaBaixo;
    Altura->limAlturaCima = limAlturaCima;
    Altura->incAltura = incAltura;

}

void initLoadingScreen (void) {
  ls_texture = SOIL_load_OGL_texture("ls_dbd.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
  if(ls_texture == 0)
    printf("houve erro carregando a texture");

   loading_screen = createLoadingScreenList(ls_texture);

}

// Prepara o audio do jogo
void initAudio(){
    if(musicaOn){
        SDL_Init(SDL_INIT_AUDIO);
        Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    
        musica_ingame = Mix_LoadMUS("sons/the_prelude.mp3");
    }
    //Mix_PlayMusic(musica_ingame, -1);
}

void inicializacaoGeral(){
    initAudio();
    initLoadingScreen();
    inicializaNavePersonagem();
    inicializaHelice();
    inicializaAltura(&Altura);
    inicializaLimitesMapa(&Limites,limMundoXMin,limMundoXMax,limMundoZMin,limMundoZMax);

}


void enable (void) {
    glEnable (GL_DEPTH_TEST); //habilita profundidade
    glDisable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);
    glEnable(GL_COLOR_MATERIAL);
    glShadeModel (GL_SMOOTH); //shader smooth
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);

}



/**************************************************************/
//=============================================================================== 
// Display Lists e Carregar Modelos 
//===============================================================================

void CriaDisplayLists(){
    char mode[30];
    pdlist = glmList(pmodel, GLM_TEXTURE | GLM_SMOOTH | GLM_MATERIAL);
    cidadelist = glmList(cidade, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
    skyboxlist = glmList(skybox,GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
    helicelist = glmList(helicemodel,GLM_TEXTURE|GLM_SMOOTH| GLM_COLOR);
    xwinglist = glmList(xwing,GLM_SMOOTH | GLM_COLOR   );
    printf("Finished creating DisplayLists\n");
    printf("Quit Loading Screen\n");
    loadingScreen = 0;
    loadingModels = 0;
    Mix_PlayMusic(musica_ingame, -1);

    inicializaNaveAnimada(&navexwing,xwinglist);
    if(fullScreen)
    glutFullScreen();
    
}

void CarregaModelos(){

    pmodel = glmReadOBJ("E-45-Aircraft/E-45_Aircraft_obj.obj");
    cidade = glmReadOBJ("cidade/cidade.obj");
    skybox = glmReadOBJ("ame_oasis/ame_oasis.obj");
    helicemodel = glmReadOBJ("BlackAndRedFloatingRobot/BlackAndRedFloatingRobot.obj");
    xwing = glmReadOBJ("Animated_Objects/X-WING.obj");
    printf("Finished loading models\n");
    CriaDisplayLists();

}


/**************************************************************/
//=============================================================================== 
// Camera e Projecao
//===============================================================================
float tamMundo = 150;

void gerenciaCamera()
{
    glLoadIdentity(); //Carrega matriz identidade
    if(camera == 1){
        gluLookAt(0 , 80 , 0 , 0 , 0 , 0 , 0 , 0 ,-1);
           xrot=0,yrot = 0;
    }

    if(camera==2){
        glTranslatef(0.0f, -2.0f, -cRaio); //translada a visao para tras do personagem
        glRotatef(xrot,1.0,0.0,0.0); //rotaciona a visao do personagem e do cenarifo
    }
    if(camera==3){
        glTranslatef(0.0f, -2.0f, -cRaioPrimeiraPessoa); //translada a visao para tras do personagem

    }
}

void configuraProjecao(){
    float aspectRatio = (float)glutGet(GLUT_WINDOW_WIDTH)/ (float)glutGet(GLUT_WINDOW_HEIGHT);
    glMatrixMode (GL_PROJECTION); //set the matrix to projection
        glLoadIdentity ();
        /*OBS: Levar em consideracao o depth com o tamanho do cubo para o skybox*/
        gluPerspective (60, aspectRatio, 0.1, tamMundo*1000); //Determina a perspectiva (angle of sight, width/height(aspect), depth)
    glMatrixMode (GL_MODELVIEW); //set the matrix back to model

}

void reshape (int w, int h) {
    glViewport (0, 0, (GLsizei)w, (GLsizei)h); //set the viewport
    configuraProjecao();
}



/**************************************************************/
//=============================================================================== 
// Mecanicas
//===============================================================================

// Essa função basicamente apenas altera a intensidade da luz global para dar a sensação de dia e noite.
void passarTempo(){
        // anoitecendo:
    if (dia == 1){
        m -= 0.01; // escurece
        // printf("1 hora se passou! Dia = %d Noite = %d Intensidade: %f\n", dia, noite, m);
        if (m <= 0.1){
            printf("entrei.\n");
            m = 0.1;
            dia = 0;
            noite = 1;
        }
    }
    
        // amanhecendo:
    else if (noite == 1){
        m += 0.01; // clareia
        // printf("1 hora se passou! Dia = %d Noite = %d Intensidade: %f\n", dia, noite, m);
        if (m >= 0.9){
            m = 0.9;
            dia = 1;
            noite = 0;
        }
    }

    glutTimerFunc(3000, passarTempo, 3000);


}

/*Essa funcao controla o fog*/
void controlaFog(){
    if(fogOn){
        float cor[3] = { .204f, .255f, .255f };
        // float cor[3] = { 1, 1, 1 };    
        glClearColor(cor[0], cor[1], cor[2], .3f);
        glFogi(GL_FOG_MODE, GL_EXP);
        glFogfv(GL_FOG_COLOR, cor);
        glFogf(GL_FOG_DENSITY, 0.001f); 
        glHint(GL_FOG_HINT, GL_DONT_CARE);   
        glFogf(GL_FOG_START, .1000f);
        glFogf(GL_FOG_END, 2000);
        glEnable(GL_FOG); 
    }
    else
        glDisable(GL_FOG);
}


/*Essa função determina o soltar de uma tecla*/
void soltaTecla(unsigned char key, int x, int y){
    switch (key)
    {
    //Movimentamento:
        case 'w':
        case 'W':
            desligaTecla(teclasPressionadas,1);
            break;
        case 'd':
        case 'D':
            desligaTecla(teclasPressionadas,2);
            break;
        case 's':
        case 'S':
            desligaTecla(teclasPressionadas,3);
            break;
        case 'a':
        case 'A':
            desligaTecla(teclasPressionadas,4);
            break;
    //Subir e Descer:
        case 'z':case 'Z':
        case 'y':case 'Y':
            desligaTecla(teclasPressionadas,5);
            break;
        case 'h':case 'H':
        case 'c':case 'C':
            desligaTecla(teclasPressionadas,6);
            break;            
    //Rotaciona Proprio Eixo
        case 'q':case 'Q':
            desligaTecla(teclasPressionadas,7);
            break;
        case 'e':case 'E':
            desligaTecla(teclasPressionadas,8);
            break;
    //Outros:

    }

}

/*Essa função determina o pressionar de uma tecla*/
void pressionaTecla(unsigned char key, int x, int y){
    switch (key)
    {
    //Cameras:
        case '1':
            camera = 1;
            break;
        case '2':
            camera = 2;
            break;
        case '3':
            camera = 3;
            break;
            
    // Iluminação
        case 'l':
        case 'L':
            if (iluminacaoOn){
                iluminacaoOn = 0;
                printf("Iluminacao desligada!\n");    
            }
            else{ 
                iluminacaoOn = 1;
                printf("Iluminacao ligada!\n");    
            }
            break;
        case 'm':
            if (m==0)
                m=0;
            else
                m-=0.1;
        break;
        case 'M':
            if (m==1)
                m=1;
            else
                m+=0.1;
        break;
    //Fog
        case 'n':case'N':
            if(fogOn==1)
                fogOn=0;
            else
                fogOn=1;
            break;

    //Movimentamento:
        case 'w':
        case 'W':
            ligaTecla(teclasPressionadas,1);
            // movimentaTodasDirecoes(1,xrot,yrot,cpos);
            break;
        case 'd':
        case 'D':
            ligaTecla(teclasPressionadas,2);
            // movimentaTodasDirecoes(3,xrot,yrot,cpos);
            break;
        case 's':
        case 'S':
            ligaTecla(teclasPressionadas,3);
            // movimentaTodasDirecoes(2,xrot,yrot,cpos);
            break;
        case 'a':
        case 'A':
            ligaTecla(teclasPressionadas,4);
            // movimentaTodasDirecoes(4,xrot,yrot,cpos);
            break;
    //Subir e Descer:
        case 'z':case 'Z':
        case 'y':case 'Y':
            ligaTecla(teclasPressionadas,5);
            break;
        case 'h':case 'H':
        case 'c':case 'C':
            ligaTecla(teclasPressionadas,6);
            break;
    //Rotaciona Proprio Eixo
        case 'q':case 'Q':
            ligaTecla(teclasPressionadas,7);
            break;
        case 'e':case 'E':
            ligaTecla(teclasPressionadas,8);
            break;

    //Muda modo da helice
        case 'x':case 'X':
            modoHelice*=-1;
            break;

    //TEMPORARIO
        case '.':
            ligaRotacaoNaveAnimada(&navexwing);
            break;  
        case ',':
            desligaRotacaoNaveAnimada(&navexwing);
            break;
        case ';':
            respawnNaveAnimada(&navexwing);
            break;

    //Outros:
        case 27: //Esc
            exit(0);
            break;
        case 'f':case 'F':
            trocaCursor(&cursorAtivo);
            break;
        case 'p':case'P':
            LockingCursorCenterScreen = !LockingCursorCenterScreen;
            break;

    }

}


/*Essa funcao eh responsavel pelo movimento do mouse*/
void mouseMovement(int x, int y) {

    if(camera != 1){
        int deltax=x-lastx; //Verifica a diferenca entre o x do cursor atual e o antigo
        int deltay=y-lasty; //Verifica a diferenca entre o y do cursor atual e o antigo
        lastx=x; //Armazena o valor do x pro antigo X
        lasty=y; //Armazena o valor do y pro antigo Y

        /*¿Nem ideia pq essa porra eh invertida?*/
        /*Resposta:
         * Eh pq vc ta rotacionando o x-axis e y-axis, e eh tipo
         * uma relação direta com o circulo. Ai funciona assim mesmo. 
         * xrot == x-axis (rotacionando eh cima em baixo)
         * yrot == y-axis (rotacionando eh direita esquerda)
         * Mais detalhes olha no google pq essa parada eh bugada (pro Artur).
        */ 
            xrot += (float) deltay*sensitivity; //Muda cima,baixo
        if(xrot>90 || xrot<-90)
            xrot-=deltay*sensitivity;

            yrot += (float) deltax*sensitivity;    //Muda direita esquerda

        /* Caso nao haja movimento algum, retorna:
         * Serve para impedir de centralizar o cursor, centralizando o movimento.
         * (OBS: o glutWarpPointer eh considerado movimento passivo também. Se não
         * retornar, e mover pro centro da tela, vai considerar o cursor esta num eterno 
         * movimento estático.(Profundo não?))
        */
        if(deltax == 0 && deltay ==0) return;

        //Desabilitar essa funcionalidade ao pressionar uma tecla.
        if(LockingCursorCenterScreen){
        /*Coloca o cursor de volta no centro da tela, ao fim do movimento,
        para evitar chegar no fim da janela, e nao poder mover mais a camera*/
            lastx=glutGet(GLUT_WINDOW_WIDTH)/2; //Pega a coordenada do centro do X da janela
            lasty=glutGet(GLUT_WINDOW_HEIGHT)/2;//Pega a coordenada do centro do Y da janela
            glutWarpPointer( lastx, lasty); //Movimenta o ponteiro no centro da tela

        }

    }

}

/**************************************************************/
//=============================================================================== 
// Desenho
//===============================================================================
// float tamMundo = 2000; *Declarado no Camera e Projecao*

/* desenhaSkybox(): 
 * Desenha todo o Mundo do jogo. Um gigantesco cubo texturizado que
 * cobre tudo.
*/
void desenhaSkybox(){
    glPushMatrix();
    glTranslated(+cpos[1],+Altura.altura,+cpos[3]); //Cancela o movimento do cenario para a skybox ficar centrada no personagem.'    
    glScalef(tamMundo,tamMundo,tamMundo); //Tamanho do mundo( Levar em consideração o depth no view do mundo(GL_PERSPECTIVE))
    glColor3f(1,1,1); //Cor Mundo
    // desenhaModelo(&mode,skybox);
    desenhaListaTamanho(skyboxlist,tam_Skybox);

    glPopMatrix();

}


void desenhaLoadingScreen(){
    glClearColor (0.0,0.0,0.0,1.0); //Limpa cores
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    configuraProjecao();
    glPushMatrix();
        glCallList(loading_screen);            
    glPopMatrix();

    glutSwapBuffers(); //Bota na tela
    if(loadingModels){
        CarregaModelos();
        loadingModels = 0;
    }
    return;
}

void desenhaHelice(){
    desenhaHelice3(&helice,2,3,helicelist,tam_Helice,modoHelice);
    desenhaHelice3(&helice2,2,3,helicelist,tam_Helice,modoHelice);
    desenhaHelice3(&helice3,2,3,helicelist,tam_Helice,modoHelice);
    desenhaHelice3(&helice4,2,3,helicelist,tam_Helice,modoHelice);
}

//Aqui desenha Personagem
void desenhaPersonagem(){
    glEnable(GL_LIGHTING);    
    glColor3f(1.0f, 1.0f, 1.0f);
    desenhaHelice();
    glPushMatrix();
        glRotatef(navePersonagem.angulo,0,0,1);
        desenhaListaTamanho(pdlist,tam_Personagem);
    glPopMatrix();
    glDisable(GL_LIGHTING);    



}

void desenhaCenario(){
    glColor3f(1.0f, 1.0f, 1.0f);
    desenhaSkybox();
    desenhaListaTamanho(cidadelist,tam_Cidade);
    desenhaNaveAnimada(&navexwing);

}


void display (void) {
    enable();

    //Chama a lista loading_screen, e depois manda carregar os modelos.
    if(loadingScreen==1)
        desenhaLoadingScreen();
    // Para caso a loading screen esteja desabilitada    
     if(loadingModels){
        CarregaModelos();
     }

    atualizaFPS(&fps,&momentoAnterior); 

    glClearColor (1.0,1.0,1.0,1.0); //Limpa cores
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Limpa os buffers de cor e de profundidade.

    verificaTeclas(teclasPressionadas,xrot,yrot,cpos,&Altura,&navePersonagem);

    gerenciaCamera();
    
    float globAmb[] = { m, m, m, 1.0 };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globAmb);        // Luz ambiente global
    glDisable(GL_LIGHTING);    
    

    desenhaPersonagem();
    if (iluminacaoOn)
        glEnable(GL_LIGHTING);    
    

    if(camera!=1)
     glRotatef(yrot,0.0,1.0,0.0);  //Rotaciona a camera de acordo com o mouse.

    
    glTranslated(-cpos[1],-Altura.altura,-cpos[3]); //Translada todo o cenario para a posição da camera.'
    if(MostraPosicaoConsole)
        printf("X:%0f  Y:%0f  Z:%0f\n",cpos[1],Altura.altura,cpos[3]);
    desenhaCenario();
    
    controlaFog();
    glutSwapBuffers(); //Bota na tela

}


int main (int argc, char **argv) {


 /* Programa começa aq */
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize (800, 600);
    glutInitWindowPosition (0,0);
    glutCreateWindow ("TP2");

    inicializacaoGeral();

    glutDisplayFunc (display);

        glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);  
        inicializaControles(teclasPressionadas,numTeclas);
        inicializaAltura(&Altura);
        // glutEnterGameMode();
        glutPassiveMotionFunc(mouseMovement); //Move o mouse
        // glutSetCursor(GLUT_CURSOR_NONE);
        glutKeyboardFunc (pressionaTecla);
        glutKeyboardUpFunc (soltaTecla);                    
        glutIdleFunc (display);

    glutReshapeFunc (reshape);

       
    glutTimerFunc(3000, passarTempo, 3000);
    glutMainLoop ();
    return 0;
}
