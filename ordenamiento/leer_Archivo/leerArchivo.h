#ifndef LEER_ARCHIVO_H
#define LEER_ARCHIVO_H
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "../quicksort/quicksort.h"
#include "curso.h"
#define TAM_MAX_LINEA 100
#define MAX_PREREQUISITOS 5

// Funciones para leer cursos desde un archivo
Curso* leer_cursos_archivo(const char *ruta_archivo, int *n_cursos);
void quitar_salto_linea(char *linea);
int contar_lineas_archivo(const char *ruta_archivo);

#endif // LEER_ARCHIVO_H