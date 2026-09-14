#include "quicksort.h"

// Comparar por dificultad
int comparar_dificultad(const void *a, const void *b) {
    Curso *c1 = (Curso *)a;
    Curso *c2 = (Curso *)b;
    return c1->dificultad - c2->dificultad;
}

// Comparar por semestre
int comparar_semestre(const void *a, const void *b) {
    Curso *c1 = (Curso *)a;
    Curso *c2 = (Curso *)b;
    return c1->semestre - c2->semestre;
}

// Comparar por creditos
int comparar_creditos(const void *a, const void *b) {
    Curso *c1 = (Curso *)a;
    Curso *c2 = (Curso *)b;
    return c1->creditos - c2->creditos;
}

// Comparar por nombre
int comparar_nombre(const void *a, const void *b) {
    Curso *c1 = (Curso *)a;
    Curso *c2 = (Curso *)b;
    return strcmp(c1->nombre, c2->nombre);
}

// QUICKSORT

void quicksort(Curso *arreglo, int n,
               int (*comparador)(const void *, const void *)) {
    if (n > 0) {
        quicksort_rec(arreglo, 0, n - 1, comparador);
    }
}

void quicksort_rec(Curso *arreglo, int inicio, int fin,
                   int (*comparador)(const void *, const void *)) {
    if (inicio < fin) {
        int indice_pivote = particion(arreglo, inicio, fin, comparador);

        quicksort_rec(arreglo, inicio, indice_pivote - 1, comparador);
        quicksort_rec(arreglo, indice_pivote + 1, fin, comparador);
    }
}


int particion(Curso *arreglo, int inicio, int fin, 
    int (*comparador)(const void *, const void *)) {
        // Elegir el ultimo elemento como pivote
    Curso pivote = arreglo[fin];
        // Indice del elemento más pequeño
    int i = inicio - 1;

    for (int j = inicio; j < fin; j++) {
        if (comparador(&arreglo[j], &pivote) <= 0) {
            i++;
            // Intercambiar
            swap(&arreglo[i], &arreglo[j]);
        }
    }

    // Intercambiar pivote a su posición final
    swap(&arreglo[i + 1], &arreglo[fin]);

    return i + 1;
}

void swap(Curso *a, Curso *b){
    Curso temp = *a;
    *a = *b;
    *b = temp;
}


//MAIN 

int main(int argc, char *argv[]) {
    const char *ruta_archivo = (argc > 1) ? argv[1] : "cursos.txt";

    int n = 0;
    Curso *cursos = leer_cursos_archivo(ruta_archivo, &n);

    if (cursos == NULL || n == 0) {
        printf("No se pudieron leer cursos desde '%s'.\n", ruta_archivo);
        printf("Verifica que el archivo exista y este en el mismo directorio, ");
        printf("o pasa la ruta como argumento: %s <ruta_al_archivo>\n",
               (argc > 0) ? argv[0] : "programa");
        return 1;
    }

    printf("Se leyeron %d cursos desde '%s'\n", n, ruta_archivo);

    // Mostrar datos originales tal como se leyeron del archivo
    imprimir_cursos(cursos, n, "Lista Original (leida desde archivo)", cursos);

    // Prueba Quicksort por dificultad
    Curso *copia_qs = copiar_arreglo_cursos(cursos, n);
    quicksort(copia_qs, n, comparar_dificultad);
    imprimir_cursos(copia_qs, n, "Ordenado con Quicksort (por Dificultad)", cursos);
    liberar_arreglo_cursos(copia_qs, n);

    // Prueba Quicksort por semestre
    Curso *copia_ms = copiar_arreglo_cursos(cursos, n);
    quicksort(copia_ms, n, comparar_semestre);
    imprimir_cursos(copia_ms, n, "Ordenado con Quicksort (por Semestre)", cursos);
    liberar_arreglo_cursos(copia_ms, n);

    // Prueba Quicksort por créditos
    Curso *copia_qs_cred = copiar_arreglo_cursos(cursos, n);
    quicksort(copia_qs_cred, n, comparar_creditos);
    imprimir_cursos(copia_qs_cred, n, "Ordenado con Quicksort (por Créditos)", cursos);
    liberar_arreglo_cursos(copia_qs_cred, n);

    // Prueba Quicksort por nombre
    Curso *copia_qs_nombre = copiar_arreglo_cursos(cursos, n);
    quicksort(copia_qs_nombre, n, comparar_nombre);
    imprimir_cursos(copia_qs_nombre, n, "Ordenado con Quicksort (por Nombre)", cursos);
    liberar_arreglo_cursos(copia_qs_nombre, n);

    // Liberar memoria original
    liberar_arreglo_cursos(cursos, n);

    return 0;
}