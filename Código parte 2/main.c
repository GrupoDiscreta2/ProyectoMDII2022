#include "AlduinPaarthurnaxIrileth.h"
#include "AniquilamientoPositronicoIonizanteGravitatorio.h"

#include <assert.h>

#include <stdlib.h>
#include <stdio.h>

u32* BFScoloreo(Grafo G);

int main() {
    Grafo G = NULL;
    u32* coloreo = NULL;

    G = ConstruccionDelGrafo();
    assert(G != NULL);
    u32 n = NumeroDeVertices(G);


    coloreo = Bipartito(G);

    if (coloreo == NULL) {
        printf("No es bipartito\n");
    } else {
        free(coloreo);
        printf("Es bipartito\n");
    }

/*     for (u32 i = 0; i < n; i++) {
        printf("%u: %u\n", Nombre(i, G), coloreo[i]);
    } */

    DestruccionDelGrafo(G);

    return(0);
}