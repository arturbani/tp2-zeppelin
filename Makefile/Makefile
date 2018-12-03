CC=gcc
OPCOES_COMPILADOR=-I. -lglut -lGLU -lGLEW -lGL -lm -lSOIL -lSDL2 -lSDL2_mixer
TODOS_ARQUIVOS_PONTOH =
TODOS_ARQUIVOS_OBJ = main.o desenha.o mecanicas.o glm.o glmimg.o glm_util.o

%.o: ../%.c $(TODOS_ARQUIVOS_PONTOH)
	$(CC) -o $@ -c $< $(OPCOES_COMPILADOR)

all: $(TODOS_ARQUIVOS_OBJ)
	gcc -o main $^ $(OPCOES_COMPILADOR)

run: all
	(cd .. && exec Makefile/main && cd Makefile)

clean:
	rm *.o main
