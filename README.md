# TP2 - Zeppelin

Trabalho feito para a disciplina Computação Gráfica, lecionada pelo professor Flávio Coutinho no CEFET-MG.

## Sobre o trabalho:
O trabalho consiste em um Zeppelin (no caso, uma nave! :) sobrevoando uma cidade. Seu objetivo é colocar em prática conceitos aprendidos em sala de aula e inaugurar a terceira dimensão em nossas práticas!

###Caso você seja o dono de algum(a) modelo/textura usado(a), por favor entrar em contato por meio do perfil de um dos criadores no GitHub ou por email (arturbani@gmail.com ou rgomesms227@gmail.com) para que possamos colocar os créditos!

###If you own any texture/model used in the game, please contact us here or by e-mail (arturbani@gmail.com or rgomesms227@gmail.com), so we can give you proper credits!

## Instalação e como "jogar":
Certifique-se que possui as bibliotecas **freeglut**, **glew** e **SOIL** instaladas! 

Bibliotecas extras utilizadas:
 - SDL2
 - SDL2-Mixer

### Caso estejam utilizando o Ubuntu, podem instalá-las por meio desses comandos:
    sudo apt-get install libsdl2-dev
    sudo apt-get install libsdl2-mixer-dev
    sudo apt-get install libsdl-mixer1.2-dev

Para compilar o programa, execute o Makefile disponível por meio do comando **make run**.
### Caso prefira, o comando para compilar manualmente usando o GCC é:
 - gcc main.c mecanicas.c desenha.c glm.c glmimg.c glm_util.c -lglut -lGLU -lSOIL -lGLEW -lGL -lm -lSDL2 -lSDL2_mixer

## Controles:
 - **WASD**: Movimentação
 - **Z**: Aumenta altitude
 - **C**: Diminui altitude
 - **Q/E**: Gira a nave
 - **1**: Câmera de cima
 - **2**: Câmera geral (Controlada pelo mouse)
 - **3**: Câmera em primeira pessoa (estilo DOOM)
 - **N**: Liga/Desliga neblina
 - **L**: Liga/Desliga iluminação
 
**Funcionalidade Extras:**
- **F**: Desaparece/Aparece com o cursor dentro da janela
- **P**: Fixa/Desafixa o cursor no centro da janela (fixo por padrão)
- **X**: Ativa o modo alternativo da hélice


