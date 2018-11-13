
void desenhaModelo(GLuint *mode, GLMmodel * pmodel);
void desenhaLista(GLuint list);
void desenhaListaTamanho(GLuint list,float tam[3]);
void atualizaFPS(float *fps, int *momentoAnterior);
GLuint createLoadingScreenList(GLuint ls_texture);
void desenhaHelice3(StructHelice *heliceT,float y,float z,int helicelist,float tam_Helice[3],int modoHelice);