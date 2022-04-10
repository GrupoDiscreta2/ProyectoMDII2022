#include "AlduinPaarthurnaxIrileth.h"
#include "AniquilamientoPositronicoIonizanteGravitatorio.h"
#include "types.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* Chequea si el coloreo es propio */
bool EsColoreoPropio(Grafo G, u32* coloreo) {
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
u32* BFScoloreo(Grafo G) {
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
    u32 n = NumeroDeVertices(G);
    u32* coloreo = BFScoloreo(G);

    if (!EsColoreoPropio(G, coloreo)) {
        free(coloreo);
        coloreo = NULL;
    }

    return coloreo;
}
