#include <stdio.h>
#include <stdlib.h>
#include "ListaGrafos.h"
#include "grafo.h"
int main()
{
        struct ListaGrafos * l = newListaGrafos();
        leerArchivo("entrada.txt",l);
        resolverListaGrafos(l);

        return 0;
}
