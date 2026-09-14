CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g
INCLUDES = -I../curso -I../leer_Archivo
OBJS = quicksort.o curso.o leerArchivo.o
BIN = planeacion

.PHONY: all clean run

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN) $(OBJS)

quicksort.o: quicksort.c quicksort.h
	$(CC) $(CFLAGS) $(INCLUDES) -c quicksort.c

leerArchivo.o: ../leer_Archivo/leerArchivo.c ../leer_Archivo/leerArchivo.h
	$(CC) $(CFLAGS) $(INCLUDES) -c ../leer_Archivo/leerArchivo.c

curso.o: ../curso/curso.c ../curso/curso.h
	$(CC) $(CFLAGS) $(INCLUDES) -c ../curso/curso.c

run: all
	./$(BIN)

clean:
	rm -f $(OBJS) $(BIN)