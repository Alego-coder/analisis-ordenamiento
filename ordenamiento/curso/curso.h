#ifndef CURSO_H
#define CURSO_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
    char nombre[100];
    int creditos;
    int semestre;
    int dificultad;
    int *prerequisitos;
    int num_prerequisitos;
} Curso;

void crear_curso(Curso *curso, const char *nombre, int creditos,
                 int semestre, int dificultad,
                 int *prerequisitos, int num_prerequisitos);
void liberar_curso(Curso *curso);
void imprimir_cursos(Curso *cursos, int n, const char *titulo, Curso *original);
void liberar_arreglo_cursos(Curso *cursos, int n);
Curso* copiar_arreglo_cursos(Curso *original, int n);
#endif // CURSO_H