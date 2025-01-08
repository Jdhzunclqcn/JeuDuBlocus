### VARIABLES ###

CC = gcc
CFLAGS = -Wall -ansi -pedantic
LIBS = -lgraph
EXE = blocus
OFILES = gui.o jeu.o main.o partie.o

### BUT PAR DEFAUT ###

all : ${EXE}

### REGLES ESSENTIELLES ###

jeu.o : jeu.c jeu.h types.h
	$(CC) $(CFLAGS) -c jeu.c

gui.o : gui.c gui.h jeu.h types.h
	$(CC) $(CFLAGS) -c gui.c

partie.o : partie.c partie.h jeu.h types.h
	$(CC) $(CFLAGS) -c partie.c

main.o : main.c gui.h jeu.h types.h
	$(CC) $(CFLAGS) -c main.c

${EXE} : ${OFILES}
	$(CC) $(CFLAGS) -o ${EXE} ${OFILES} ${LIBS}

### REGLES OPTIONNELLES ###

run : ${EXE}
	./${EXE}

clean :
	-rm -f ${OFILES} ${EXE}

### BUTS FACTICES ###

.PHONY : all run clean

### FIN ###
