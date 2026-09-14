#ifndef QUICKSORT_H
#define QUICKSORT_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "quicksort.h"
#include "curso.h"
#include "leerArchivo.h"

// Declaración de funciones
void quicksort(Curso *arreglo, int n, int (*comparador)(const void *, const void *));
void quicksort_rec(Curso *arreglo, int inicio, int fin,int (*comparador)(const void *, const void *));

int particion(Curso *arreglo, int bajo, int alto, int (*comparador)(const void *, const void *));
void swap(Curso *a, Curso *b);

#endif // QUICKSORT_H