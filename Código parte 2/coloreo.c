#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "AlduinPaarthurnaxIrileth.h"
#include "AniquilamientoPositronicoIonizanteGravitatorio.h"
#include "arregloBits.h"
#include "types.h"

/* Chequea si el coloreo es propio */
static bool EsColoreoPropio(Grafo G, u32* coloreo) {
    bool coloreoPropio = true;
    u32 n = NumeroDeVertices(G);

    for (u32 i = 0; i < n && coloreoPropio; i++) {
        u32 grado = Grado(i, G);
        u32 color = coloreo[i];

        for (u32 j = 0; j < grado && coloreoPropio; j++) {
            coloreoPropio = (color != coloreo[IndiceONVecino(j, i, G)]);
        }
    }

    return coloreoPropio;
}

/* Colorea un grafo:
 *  Con BFS crea un árbol para cada componente conexa,
 *  y le asigna profundidad `mod` 2 + 1 a cada vértice
 * 
 * En realidad nunca crea un árbol de verdad, pero es para entender que hace
 * 
 * Devuelve un arreglo de tamaño n
 */
static u32* BFScoloreo(Grafo G) {
    u32 n = NumeroDeVertices(G);
    u32* coloreo = calloc(n, sizeof(u32)); // calloc inicializa la memoria a 0
    u32* cola = calloc(n, sizeof(u32));

    u32 i = 0; // Índice del elemento siendo procesado
    u32 j = 0; // Índice del primer lugar libre en la cola
    u32 c = 0; // Vertices que ya están en una componente conexa

    while (c < n) {
        if (coloreo[c] == 0) {
            /* c todavía no fue coloreado, por ende está en una componente conexa
               que todavía no fue prosesada */
            cola[j] = c;
            j++;
            coloreo[c] = 1;

            while (i < j) { // Colorear componente conexa empezando en c
                assert(j <= n);
                assert(i < n);
                u32 grado = Grado(cola[i], G);

                for (u32 k = 0; k < grado; k++) {
                    /* Recorrer los vecinos del vértice actual colorea y agrega
                        a la cola los que no habían sido coloreados
                     */
                    u32 v = IndiceONVecino(k, cola[i], G);
                    // vecino siendo procesado (v es el índice en el orden natural)
                    if (coloreo[v] == 0) {
                        cola[j] = v;
                        j++;
                        coloreo[v] = coloreo[cola[i]] == 1 ? 2 : 1;
                    }
                }

                i++;
            }
        } else {
            /* Ya fue coloreado, por ende está en una componente conexa que ya
               fue procesada */
            c++;
        }
    }
    assert(i == n && j == n);

    free(cola);
    cola = NULL;
    return coloreo;
}

u32* Bipartito(Grafo G) {
    u32* coloreo = BFScoloreo(G);

    if (!EsColoreoPropio(G, coloreo)) {
        free(coloreo);
        coloreo = NULL;
    }

    return coloreo;
}

/* Pone en Coloreo el coloreo que da greedy usando el orden de Orden
 * 
 * PRE: Orden != NULL && Coloreo != NULL && Orden es una permutación de 0..n-1
 */
u32 Greedy(Grafo G, u32* Orden, u32* Coloreo) {
    u32 n = NumeroDeVertices(G);

    // Inicializar coloreo en 2^32 - 1
    for (u32 i = 0; i < n; i++) {
        Coloreo[i] = MAX_U32;
    }

    u32 color = 0;

    // Arreglo de bits, cada bit i representa si el color i-ésimo está usado
    // por los vecinos del vertice actual
//    u8* coloresUsadosPorVecinos = calloc((Delta(G) + 1) / 8 + 1, sizeof(u8));

    for (u32 i = 0; i < n; i++) {
        u32 v = Orden[i];
        u32 d = Grado(v, G);

        u32 indicesUsables = min(color + 1, d);
        u8* coloresUsadosPorVecinos = calloc((indicesUsables + 1) / 8 + 1, sizeof(u8));

        // Recorrer los vecinos del vértice actual, poniendo en 1 los bits de colores ya usados
        for (u32 j = 0; j < d; j++) {
            u32 w = IndiceONVecino(j, v, G);
            u32 color_w = Coloreo[w];

            if (color_w != MAX_U32 && color_w <= d) {
                // color_w != MAX_U32 ⇒ w ya está coloreado
                
                // color_w > d + 1 ⇒ si o si va a haber un color libre menor que color_w
                // Por eso en ese caso no se pone en 1 el bit color_w
                
                ponerEn1(coloresUsadosPorVecinos, color_w);
            }
        }

        // Buscar el primer color libre
        u32 color_v = primer0(coloresUsadosPorVecinos);

        assert(color_v <= color + 1);

        Coloreo[v] = color_v;
        color = max(color, color_v + 1);

        free(coloresUsadosPorVecinos);
        // u32 indicesUsados = min(color, d);
        /* for (u32 j = 0; j < indicesUsados; j++) {
            coloresUsadosPorVecinos[j] = 0;
        } */
//        memset(coloresUsadosPorVecinos, 0, indicesUsados / 8 + 1);

        // Verificar que haya todo 0s en coloresUsadosPorVecinos
/*         for (u32 j = 0; j < ((Delta(G) + 1) / 8 + 1); j++) {
            if (coloresUsadosPorVecinos[j] != 0) {
                printf("Error: coloresUsadosPorVecinos[%u] = 0x%x\n", j, coloresUsadosPorVecinos[j]);
                printf("       indicesUsados = %u\n", indicesUsados);
                assert(false);
            }
        } */
    }

    //free(coloresUsadosPorVecinos);

    return color;
}

/* Pone en Orden los índices que ordenan a key de mayor a menor
 *
 * En caso de error de alocado de memoria retorna 1, en cualquier otro caso retorna 0
 *
 * PRE: key != NULL && Orden != NULL && ⟨∀i ∈ {0,…,n-1} : key[i] < n⟩
 */
char OrdenFromKey(u32 n, u32* key, u32* Orden) {
    assert(key != NULL && Orden != NULL);

    u32* count = calloc(n, sizeof(u32)); // calloc inicializa la memoria a 0
    if (count == NULL) {
        return 1;
    }

    // Contar cuántas veces aparece cada elemento
    for (u32 i = 0; i < n; i++) {
        count[key[i]]++;
    }

    // Contar cuantos elementos menores o iguales a cada elemento hay
    for (u32 i = 1; i < n; i++) {
        count[i] += count[i - 1];
    }

    for (u32 i = 0; i < n; i++) {
        // Poner i en uno de los lugares posibles
        Orden[n - count[key[i]]] = i;
        // Restar uno al contador de elementos menores o iguales a key[i], para
        // que cuando haya otro igual a key[i] se ponga en el siguiente lugar
        count[key[i]]--;
    }

    free(count);
    count = NULL;

    return 0;
}

/* Devuelve un número aletario entre 0 y n-1 usando rand() */
static u32 randMenorQue(u32 n) {
    // Idea de https://stackoverflow.com/questions/1202687/how-do-i-get-a-specific-range-of-numbers-from-rand
    return (u32)(rand() / (RAND_MAX / n + 1));
}

/* Pone en key n números pseudo-aleatorios entre 0 y n-1 usando a R como semilla
 * 
 * PRE: key != NULL
 */
void AleatorizarKeys(u32 n, u32 R, u32* key) {
    assert(key != NULL);

    // Setear semilla
    srand(R);

    // Generar números pseudo-aleatorios
    for (u32 i = 0; i < n; i++) {
        key[i] = randMenorQue(n);
    }
}

static void swap(u32* a, u32* b) {
    u32 tmp = *a;
    *a = *b;
    *b = tmp;
}

/* Devuelve el valor del elemento maximo de array
 * Mira los números de 0 a n-1
 * En caso de que n sea 0 devuelve 0 (neutro de max para u32)
 */
static u32 maximum(u32 n, const u32* array) {
    u32 m = 0;
    for (u32 i = 0; i < n; i++) {
        m = max(m, array[i]);
    }
    return m;
}

/* Asumiendo que Coloreo es un coloreo, permuta los colores
 * 
 * PRE: Coloreo != NULL && Coloreo es un coloreo
 */
u32* PermutarColores(u32 n, u32* Coloreo, u32 R) {
    assert(Coloreo != NULL);

    // Averiguar cantidad de colores
    u32 r = maximum(n, Coloreo) + 1;

    // Crear un arreglo para permutar los colores
    u32* permC = calloc(sizeof(u32), r);
    if (permC == NULL) {
        return NULL;
    }

    for (u32 i = 0; i < r; i++) {
        permC[i] = i;
    }

    srand(R);

    // Permutar los colores
    for (u32 i = 0; i < r; i++) {
        u32 j = randMenorQue(i + 1);
        swap(&permC[i], &permC[j]);
    }

    // Crear el arreglo de colores permutados
    u32* nuevoC = calloc(sizeof(u32), n);
    if (nuevoC == NULL) {
        return NULL;
    }

    // Llenar el arreglo de colores permutados
    for (u32 i = 0; i < n; i++) {
        nuevoC[i] = permC[Coloreo[i]];
    }

    free(permC);
    permC = NULL;

    return nuevoC;
}

struct elemIndice {
    u32 indice;
    u32 valor;
};

// Funcion de comparación de qsort para indicesOrdenadosMayorMenor
static int cmp(const struct elemIndice* a, const struct elemIndice* b) {
    return a->valor < b->valor;
}

/* Devuelve los indices de el argumento array de mayor a menor tal que:
 * array[res[0]] >= array[res[1]] >= ... >= array[res[n-1]]
 *
 * Utiliza qsort
 * 
 * PRE: array != NULL
 */
static u32* indicesOrdenadosMayorMenor(u32 n, const u32* array) {
    assert(array != NULL);

    struct elemIndice* elems = calloc(n, sizeof(struct elemIndice));

    for (u32 i = 0; i < n; i++) {
        elems[i].indice = i;
        elems[i].valor = array[i];
    }

    qsort(elems, n, sizeof(struct elemIndice), (int (*)(const void*, const void*))cmp);

    u32* indices = calloc(n, sizeof(u32));
    for (u32 i = 0; i < n; i++) {
        indices[i] = elems[i].indice;
    }
    free(elems);

    return indices;
}

u32* RecoloreoCardinalidadDecrecienteBC(u32 n, u32* Coloreo) {
    assert(Coloreo != NULL);

    // Averiguar cantidad de colores
    u32 r = maximum(n, Coloreo) + 1;

    // Arreglo para llevar la cuenta de cuantas veces aparece cada color
    u32* count = calloc(r, sizeof(u32)); // calloc inicializa la memoria a 0
    for (u32 i = 0; i < n; i++) {
        count[Coloreo[i]]++;
    }

    // Arreglo que contiene los colores ordenados de mayor a menor en función de cuantas
    // veces aparece cada uno
    u32* coloresOrd = calloc(r, sizeof(u32));
    coloresOrd = indicesOrdenadosMayorMenor(r, count);

    // Arreglo que contiene la posición de los colores en coloresOrd
    // Cada indice representa un color, ejemplo:
    // posiciones[0] -> 2  => El color 0 se encuentra en coloresOrd[2]
    u32* posiciones = calloc(r, sizeof(u32));
    for (u32 i = 0; i < r; i++) {
        posiciones[coloresOrd[i]] = i;
    }

    u32* nuevoColoreo = calloc(n, sizeof(u32));
    for (u32 i = 0; i < n; i++) {
        nuevoColoreo[i] = posiciones[Coloreo[i]];
    }

    free(count);
    free(coloresOrd);

    return nuevoColoreo;
}
