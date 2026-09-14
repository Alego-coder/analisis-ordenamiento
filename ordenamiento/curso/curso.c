
#include "curso.h"

void imprimir_cursos(Curso *cursos, int n, const char *titulo, Curso *original) {
    printf("\n");
    printf("============================================================\n");
    printf("%s\n", titulo);
    printf("============================================================\n");

    for (int i = 0; i < n; i++) {
        printf("%d. %s\n", i + 1, cursos[i].nombre);
        printf("   Créditos: %d | Semestre: %d | Dificultad: %d\n",
               cursos[i].creditos, cursos[i].semestre, cursos[i].dificultad);

        if (cursos[i].num_prerequisitos > 0) {
            printf("   Prerequisitos: ");
            for (int j = 0; j < cursos[i].num_prerequisitos; j++) {
                int curso_index = cursos[i].prerequisitos[j];
                printf("%s", original[curso_index].nombre);
            }
            printf("\n");
        }
        printf("\n");
    }
}

void crear_curso(Curso *curso, const char *nombre, int creditos,
                 int semestre, int dificultad,
                 int *prerequisitos, int num_prerequisitos) {
    strncpy(curso->nombre, nombre, sizeof(curso->nombre) - 1);
    curso->nombre[sizeof(curso->nombre) - 1] = '\0';
    curso->creditos = creditos;
    curso->semestre = semestre;
    curso->dificultad = dificultad;
    curso->num_prerequisitos = num_prerequisitos;

    if (num_prerequisitos > 0) {
        curso->prerequisitos = (int *)malloc(num_prerequisitos * sizeof(int));
        for (int i = 0; i < num_prerequisitos; i++) {
            curso->prerequisitos[i] = prerequisitos[i];
        }
    } else {
        curso->prerequisitos = NULL;
    }
}

void liberar_curso(Curso *curso) {
    if (curso->prerequisitos != NULL) {
        free(curso->prerequisitos);
    }
}

Curso* copiar_arreglo_cursos(Curso *original, int n) {
    Curso *copia = (Curso *)malloc(n * sizeof(Curso));
    for (int i = 0; i < n; i++) {
        crear_curso(&copia[i], original[i].nombre,
                    original[i].creditos, original[i].semestre,
                    original[i].dificultad,
                    original[i].prerequisitos, original[i].num_prerequisitos);
    }
    return copia;
}

void liberar_arreglo_cursos(Curso *cursos, int n) {
    for (int i = 0; i < n; i++) {
        liberar_curso(&cursos[i]);
    }
    free(cursos);
}