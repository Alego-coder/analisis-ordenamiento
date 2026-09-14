
#include "leerArchivo.h"
#define TAM_MAX_LINEA 100
#define MAX_PREREQUISITOS 5

// Lee todos los cursos desde un archivo de texto tipo CSV.
//
// Formato esperado de cada línea (separado por comas):
//   nombre,creditos,semestre,dificultad[,prereq1,prereq2,...]
//
// Los primeros 4 campos son obligatorios (nombre, creditos, semestre,
// dificultad). Cualquier campo adicional se interpreta como el índice
// (0-based, según el orden de aparición en el archivo) de un curso del
// cual este curso depende. El número de prerequisitos se calcula
// automáticamente según cuántos campos adicionales tenga la línea.
//
// Devuelve un arreglo de Curso reservado dinámicamente y coloca en
// *n_cursos la cantidad de cursos leídos. Si el archivo no se puede
// abrir, devuelve NULL y *n_cursos = 0.
Curso* leer_cursos_archivo(const char *ruta_archivo, int *n_cursos) {
    int total = contar_lineas_archivo(ruta_archivo);
    if (total <= 0) {
        *n_cursos = 0;
        return NULL;
    }

    FILE *archivo = fopen(ruta_archivo, "r");
    if (archivo == NULL) {
        *n_cursos = 0;
        return NULL;
    }

    Curso *cursos = (Curso *)malloc(total * sizeof(Curso));
    char linea[TAM_MAX_LINEA];
    int indice = 0;

    while (fgets(linea, sizeof(linea), archivo) != NULL && indice < total) {
        quitar_salto_linea(linea);
        if (strlen(linea) == 0) {
            continue;
        }

        char nombre[100] = "";
        int creditos = 0, semestre = 0, dificultad = 0;
        int prerequisitos[MAX_PREREQUISITOS];
        int num_prerequisitos = 0;

        int campo = 0;
        char *token = strtok(linea, ",");

        while (token != NULL) {
            switch (campo) {
                case 0:
                    strncpy(nombre, token, sizeof(nombre) - 1);
                    break;
                case 1:
                    creditos = atoi(token);
                    break;
                case 2:
                    semestre = atoi(token);
                    break;
                case 3:
                    dificultad = atoi(token);
                    break;
                default:
                    if (strlen(token) > 0 && num_prerequisitos < MAX_PREREQUISITOS) {
                        prerequisitos[num_prerequisitos++] = atoi(token);
                    }
                    break;
            }
            campo++;
            token = strtok(NULL, ",");
        }

        crear_curso(&cursos[indice], nombre, creditos, semestre, dificultad,
                    num_prerequisitos > 0 ? prerequisitos : NULL,
                    num_prerequisitos);
        indice++;
    }

    fclose(archivo);
    *n_cursos = indice;
    return cursos;
}

// LECTURA DESDE ARCHIVO 


// Quita el salto de linea ('\n') y el retorno de carro ('\r', por si el
// archivo viene con terminaciones de linea estilo Windows) al final de una cadena.
void quitar_salto_linea(char *linea) {
    int len = (int)strlen(linea);
    while (len > 0 && (linea[len - 1] == '\n' || linea[len - 1] == '\r')) {
        linea[len - 1] = '\0';
        len--;
    }
}

// Cuenta cuántas líneas con contenido tiene el archivo (una linea = un curso).
int contar_lineas_archivo(const char *ruta_archivo) {
    FILE *archivo = fopen(ruta_archivo, "r");
    if (archivo == NULL) {
        return -1;
    }

    int contador = 0;
    char linea[TAM_MAX_LINEA];

    while (fgets(linea, sizeof(linea), archivo) != NULL) {
        quitar_salto_linea(linea);
        if (strlen(linea) > 0) {
            contador++;
        }
    }

    fclose(archivo);
    return contador;
}
