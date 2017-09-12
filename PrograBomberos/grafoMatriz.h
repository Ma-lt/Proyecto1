#include <stdbool.h>
#include "Arbol.h"
typedef struct Vertice {
    int valor;
    bool visitado;
}Vertice;

struct Vertice * newVertice(int val){
    struct Vertice * v = malloc(sizeof(struct Vertice));

    if (v)
        v->valor = val;
    v->visitado = false;
    return v;
};

typedef struct grafoMatriz {
    int maximo;
    int matriz[21][21];
    int vertices[21];
    // bool visitados[100];
    int cantidadVertices;
    int destino;
    ArbolCaminos * arbol;

}grafoMatriz;

struct grafoMatriz * newgrafoMatriz(int destino){
    struct grafoMatriz * g = malloc(sizeof(struct grafoMatriz));

    if (g) {
        g->destino = destino;
        g->maximo = 21;
        g->cantidadVertices = 21;
        // inicializa arreglos
        int i;
        for (i = 0; i < 21; i++) {
            g->vertices[i] = i + 1;
            // g->visitados[i] = 0;

            // para incializar matriz
            int j;
            for (j = 0; j < 21; j++) {
                g->matriz[i][j] = 0;
            }
        }
        return g;
    }
} // newgrafoMatriz

void crearArbolgrafoMatriz(grafoMatriz * g, int destino){
    g->arbol = newArbolCaminos(destino, g->cantidadVertices - 1);
}

int buscarHijoValidoEngrafoMatriz(grafoMatriz * g, NodoEsquina * n){
    int i;
    int columna = n->dato - 1;

    for (i = 0; i < g->cantidadVertices; i++) {
        // recorriendo la columna
        if (g->matriz[i][columna] != 0) {
            // ya encontro un hijo
            // pregunta si esta en lista de hijos
            int j;
            if (n->numHijos == 0 && !esAncestro(n, i + 1))
                return i + 1;
            for (j = 0; j < n->numHijos; j++) {
                // n->hijos[j]->dato: hijo de la lista
                // i+1: hijo que lleva al nodo n
                NodoEsquina * hijoEnLista = buscarHijoEnNodoEsquina(n, i + 1);
                // no esta en lista de hijos
                if (hijoEnLista == NULL && !esAncestro(n, i + 1)) {
                    return i + 1;
                }
            }

        }
    }
    return 0;
} // buscarHijoValidoEngrafoMatriz


int  resolverArbolgrafoMatriz(grafoMatriz * g, int destino, NodoEsquina * actual, int rutas){
    // primero crea el arbol
    if (g->arbol == NULL) {
        crearArbolgrafoMatriz(g, destino);
        actual = g->arbol->raiz;
    }
    if (actual->padre == NULL && buscarHijoValidoEngrafoMatriz(g, actual) == 0) {
        return rutas;
    } else {
        // luego resuelve el arbol
        if (actual->dato == 1) {
            imprimirRutaDesdeNodo(actual);
            actual = actual->padre;
            return resolverArbolgrafoMatriz(g, destino, actual, rutas + 1);
        } else {
            if (buscarHijoValidoEngrafoMatriz(g, actual) == 0) {
                actual = actual->padre;
                return resolverArbolgrafoMatriz(g, destino, actual, rutas);
            } else {
                int hijo = buscarHijoValidoEngrafoMatriz(g, actual);
                insertarHijoNodoEsquina(actual, hijo);
                NodoEsquina * nodoHijo = buscarHijoEnNodoEsquina(actual, hijo);
                return resolverArbolgrafoMatriz(g, destino, nodoHijo, rutas);
            }
        }
    }
} // resolverArbolgrafoMatriz
/*
 * // agregar vertice
 *  void agregarVerticegrafoMatriz(struct grafoMatriz * g,int v)
 *  {
 *
 *      int i;
 *      for (i = 0; i < g->cantidadVertices; i++)
 *      {
 *
 *          if (g->vertices[i] == v){
 *              return 0;
 *          }
 *
 *      }
 *       // si hay campo y v no est'a en el grafo
 *     if (g->cantidadVertices < g->maximo)// && indexOfVerticegrafoMatriz(g,v) == -1)
 *     {
 *          g->vertices[v-1] = v;
 *          g->cantidadVertices++;
 *     }
 *  }
 * // index de un vertice
 * int indexOfVerticegrafoMatriz(struct grafoMatriz*g,int v)
 *  {
 *      int i;
 *      for (i = 0; i < g->cantidadVertices; i++) {
 *          if (g->vertices[i] == v)
 *              return i;
 *      }
 *
 *      return -1;
 *  }*/
// agregar arista
void agregarAristagrafoMatriz(struct grafoMatriz * g, int origen, int destino, int peso){
    // int orig = indexOfVerticegrafoMatriz(g,origen);
    // int dest = indexOfVerticegrafoMatriz(g,destino);

    if (origen != 0 && destino != 0) {
        g->matriz[destino - 1][origen - 1] = peso;
    }
}

void agregarAristaDoblegrafoMatriz(struct grafoMatriz * g, int origen, int destino, int peso){
    agregarAristagrafoMatriz(g, origen, destino, peso);
    agregarAristagrafoMatriz(g, destino, origen, peso);
}

// imprimir
void imprimirgrafoMatriz(struct grafoMatriz * g){
    printf(" \t");
    int i;
    for (i = 0; i < g->cantidadVertices; i++) {
        printf("%d", g->vertices[i]);
        printf(" \t");
    }
    printf("\n");
    for (i = 0; i < g->cantidadVertices; i++) {
        printf("%d", g->vertices[i]);
        printf(" \t");
        int j;
        for (j = 0; j < g->cantidadVertices; j++) {

            printf("%d", g->matriz[i][j]);
            printf(" \t");
        }
        printf("\n");
    }
}
