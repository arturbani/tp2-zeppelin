#include "Bibliotecas/bibliotecas.h"
#include "glm.h"
#include "mecanicas.h"


#define MAX(x, y) (((x) > (y)) ? (x) : (y))


/**************************************************************/
//===============================================================================
// Funcoes Gerais
//===============================================================================

/*Aqui desenhamos um modelo */
void desenhaModelo(GLuint *mode, GLMmodel * pmodel){

    glColor3f(1, 1, 1);
    glmUnitize(pmodel);
    glmFacetNormals(pmodel);
    glmVertexNormals(pmodel, 90.0, GL_TRUE);

    if (pmodel)
	glmDraw(pmodel, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);

}

/* 
 * Essa funçao desenha uma display list.
*/
void desenhaLista(GLuint list){
    glPushMatrix();
    glCallList(list);
    glPopMatrix();

}

/* 
 * Essa funçao desenha uma display list a partir de um tamanho informado.
*/
void desenhaListaTamanho(GLuint list,float tam[3]){
    glPushMatrix();
    glScalef(tam[0],tam[1],tam[2]);
    glCallList(list);
    glPopMatrix();

}



void atualizaFPS(float *fps, int *momentoAnterior){
    int momentoAtual  = glutGet(GLUT_ELAPSED_TIME);
    int delta = momentoAtual - *momentoAnterior;

    *fps = 1000.0f / MAX(delta,1.0f);

    *momentoAnterior = momentoAtual;

    //Reescreve FPS
    char tituloDaJanela[200];
    sprintf(tituloDaJanela,
            "TP2  - %.2f fps",
            *fps);
    glutSetWindowTitle(tituloDaJanela);

}

/* 
 * Essa funcao cria uma display list para a tela de loading.
*/
GLuint createLoadingScreenList(GLuint ls_texture){
    GLuint loading_screen = glGenLists(1);
    
    glNewList(loading_screen,GL_COMPILE);
        // glBindTexture(GL_TEXTURE_2D,ls_texture);    

        glPushMatrix();
            glTranslated(-1,-1,-1);
            glScalef(2,2,2);
            glBegin(GL_TRIANGLE_FAN);
                glTexCoord2f(0, 0);  
                glVertex2f  (0, 0);
                
                glTexCoord2f(1, 0);  
                glVertex2f  (1, 0);
                
                glTexCoord2f(1, 1);  
                glVertex2f  (1, 1);
                
                glTexCoord2f(0, 1);  
                glVertex2f  (0, 1);
            glEnd();
        glPopMatrix();
    glEndList();

    return loading_screen;

}


/**************************************************************/
//===============================================================================
// Desenhos Especificos
//===============================================================================


void desenhaHelice3(StructHelice *heliceT,float y,float z,GLuint helicelist,float tam_Helice[3],int modoHelice){

    /*Aqui desenha a primeira helice*/
    glPushMatrix();
        glTranslated(0,y,z); //Posicao pra rotacao
        glRotatef(heliceT->angulo,0,0,1); //Rotacao no eixo Z
        glTranslated(0,5,0); //Raio da rotacao        
        desenhaListaTamanho(helicelist,tam_Helice);
    glPopMatrix();
    /*Aqui acaba de desenhar a helice*/

    /*Aqui desenha a segunda helice*/
    glPushMatrix();
        glTranslated(0,y,z+=2.5); //Posicao pra rotacao
        glRotatef(heliceT->angulo,0,0,modoHelice); //Rotacao no eixo Z, em funcao do modo da Helice.
        glTranslated(0,5,0); //Raio da rotacao        
        desenhaListaTamanho(helicelist,tam_Helice);
    glPopMatrix();
    /*Aqui acaba de desenhar a helice*/
    
    /*Aqui desenha a tercceira helice*/
    glPushMatrix();
        glTranslated(0,y,z+=2.5); //Posicao pra rotacao
        glRotatef(heliceT->angulo,0,0,1); //Rotacao no eixo Z
        glTranslated(0,5,0); //Raio da rotacao        
        desenhaListaTamanho(helicelist,tam_Helice);
        // helice->angulo+=1.3;
    glPopMatrix();
    /*Aqui acaba de desenhar a helice*/

        heliceT->angulo+=1.3;
}

